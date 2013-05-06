from django.contrib.admin.util import quote
import operator
from django.core.urlresolvers import NoReverseMatch, reverse
from django.utils.safestring import mark_safe
from django.template.defaultfilters import escape, capfirst
from django.utils.encoding import force_unicode
from django.template.loader import render_to_string
from django.utils.datastructures import SortedDict
from reqtool.lib import gvgen
from django.core.files.temp import NamedTemporaryFile

class DotGraph(object):
    
    def __init__(self):
        pass
    
    def graph(self):
        """Should return a GvGen object with the graph."""
        raise NotImplementedError()
    
    def get_png_graph(self):
        """Returns a PNG file with the Dot graph visualization."""
        import os
        dot_tmpf = NamedTemporaryFile()
        dot_tmpf.close()
        self.graph().dot(fd=file(dot_tmpf.name, 'w'))
        
        png_tmpf = NamedTemporaryFile()
        png_tmpf.close()
        os.system('dot -Tpng %s > %s' % (dot_tmpf.name, png_tmpf.name))
        return file(png_tmpf.name)

class ProductModulesGraph(DotGraph):
    def __init__(self, products_queryset):
        super(ProductModulesGraph, self).__init__()
        self._graph = gvgen.GvGen(None, "compound=true;rankdir=TB;layout=fdp;")
        self._graph.styleDefaultAppend("shape","box")
        self._queryset = products_queryset
        
    def _generate_graph(self):
        for p in self._queryset:
            product_node = self._graph.newItem(p.name.encode('ascii', 'ignore'))
            for m in p.modules.all():
                module_node = self._graph.newItem(m.name.encode('ascii', 'ignore'), product_node)
                self._graph.styleAppend('modulestyle', 'style', 'filled')
                self._graph.styleAppend('modulestyle', 'color', 'lightgray')
                self._graph.styleApply('modulestyle', module_node)
        return self._graph
    
    def graph(self):
        return self._generate_graph()

class ProductMapGraph(DotGraph):
    
    def __init__(self, products_queryset):
        super(ProductMapGraph, self).__init__()
        self._graph = gvgen.GvGen(None, "compound=true;rankdir=LR;layout=dot;")
        self._graph.styleDefaultAppend("shape","record")
        self._queryset = products_queryset
        self._nodes = {}
    
    def _go_deep_on_feature(self, feature):
        """Links the child features recursively."""
        fname_parent = feature.name.encode('ascii', 'ignore')
        for f in feature.feature_set.all():
            fname = f.name.encode('ascii', 'ignore')
            if not self._nodes.has_key(fname):
                self._nodes[fname] = self._graph.newItem('Feature|' + fname)
            self._graph.newLink(self._nodes[fname_parent], self._nodes[fname])    
            self._go_deep_on_feature(f)
        return
    
    def _generate_graph(self):
        for p in self._queryset:
            pname = p.name.encode('ascii', 'ignore')
            if not self._nodes.has_key(pname):
                self._nodes[pname] = self._graph.newItem('Product|'+pname+'')
             
            for m in p.modules.all():
                mname = m.name.encode('ascii', 'ignore')
                if not self._nodes.has_key(mname):
                    self._nodes[mname] = self._graph.newItem('Module|' + mname)
                link = self._graph.newLink(self._nodes[pname], self._nodes[mname])
                
                for f in m.feature_set.all():
                    fname = f.name.encode('ascii', 'ignore')
                    if not self._nodes.has_key(fname):
                        self._nodes[fname] = self._graph.newItem('Feature|' + fname)
                    self._graph.newLink(self._nodes[mname], self._nodes[fname])
                    self._go_deep_on_feature(f)
                    
        return self._graph
    
    def graph(self):
        return self._generate_graph()
    
    def _features_graph(self):
        pass


class FeatureModelGraph(DotGraph):
    
    def __init__(self, products_queryset):
        super(FeatureModelGraph, self).__init__()
        
        self._graph = gvgen.GvGen(None, "compound=true;rankdir=LR;layout=dot;")
        self._graph.styleDefaultAppend("shape","record")
        
        self._graph.styleAppend('exclusionstyle', 'style', 'filled')
        self._graph.styleAppend('exclusionstyle', 'color', 'red')
        
        self._graph.styleAppend('implicationstyle', 'style', 'filled')
        self._graph.styleAppend('implicationstyle', 'color', 'green')
        self._queryset = products_queryset
    
    def _add_legend(self):
        legend = self._graph.newItem('Legend')
        
        c = self._graph.newItem('a', legend)
        d = self._graph.newItem('b', legend)
        ll = self._graph.newLink(c, d)
        self._graph.propertyAppend(ll, 'label', 'excludes')
        self._graph.styleApply('exclusionstyle', ll)
        
        e = self._graph.newItem('a', legend)
        f = self._graph.newItem('b', legend)
        lll = self._graph.newLink(e, f)
        self._graph.propertyAppend(lll, 'label', 'parent of')
        
        a = self._graph.newItem('a', legend)
        b = self._graph.newItem('b', legend)
        l = self._graph.newLink(a, b)
        self._graph.propertyAppend(l, 'label', 'requires')
        self._graph.styleApply('implicationstyle', l)
    
    def _generate_graph(self):
        self._add_legend()
        nodes = {}
        nodes_count = {}
        
        for f in self._queryset:
            fname = f.name.encode('ascii', 'ignore')
            
            #put only features with some relationship
            if not nodes.has_key(fname):
                if f.parent or (f.excludes.all() \
                                or f.requires.all()):
                    fnode = self._graph.newItem(fname)
                    nodes[fname] = fnode
                    nodes_count[fname] = 1
                else:
                    continue
            
            if f.parent:
                pname = f.parent.name.encode('ascii', 'ignore')
                if not nodes.has_key(pname):
                    nodes[pname] = self._graph.newItem(pname)
                self._graph.newLink(nodes[pname], nodes[fname])
            
            for fex in f.excludes.all():
                fexname = fex.name.encode('ascii', 'ignore')
                link = None
                if nodes.has_key(fexname):
                    link = self._graph.newLink(nodes[fname], nodes[fexname])
                    nodes_count[fexname] += 1
                else:
                    nodes[fexname] = self._graph.newItem(fexname)
                    nodes_count[fexname] = 1
                    link = self._graph.newLink(nodes[fname], nodes[fexname])
                self._graph.styleApply('exclusionstyle', link)
                
            for fre in f.requires.all():
                frename = fre.name.encode('ascii', 'ignore')
                link = None
                if nodes.has_key(frename):
                    link = self._graph.newLink(nodes[fname], nodes[frename])
                    nodes_count[frename] += 1
                else:
                    nodes[frename] = self._graph.newItem(frename)
                    nodes_count[frename] = 1
                    link = self._graph.newLink(nodes[fname], nodes[frename])
                self._graph.styleApply('implicationstyle', link)
                    
        return self._graph
    
    def graph(self):
        return self._generate_graph()

def render_to_latex(template, context, context_instance=None):
    import os, codecs
    body = render_to_string(template, context, context_instance)
    #TODO: there is still a lot of HTML codes to replace here
    body = body.replace('&quote;', '"')
    body = body.replace('&apos;', '\'')
    body = body.replace('&amp;', '\&')
    body = body.replace('<br>', '\\')
    tempf = NamedTemporaryFile()
    tempf.close()
    tempf = codecs.open(tempf.name,'w', 'utf-8')
    tempf.write(body)
    tempf.close()
    for i in range(3):
        os.system('pdflatex -interaction nonstopmode -output-directory %s %s' % 
                  (os.path.split(tempf.name)[0], tempf.name))
    return open(tempf.name + '.pdf').read()

def _my_format_callback(obj, user, admin_site, levels_to_root):
    has_admin = obj.__class__ in admin_site._registry
    opts = obj._meta
    try:
        admin_url = reverse('%s:%s_%s_change'
                            % (admin_site.name,
                               opts.app_label,
                               opts.object_name.lower()),
                            None, (quote(obj._get_pk_val()),))
    except NoReverseMatch:
        admin_url = '%s%s/%s/%s/' % ('../'*levels_to_root,
                                     opts.app_label,
                                     opts.object_name.lower(),
                                     quote(obj._get_pk_val()))
    if has_admin:
#        p = '%s.%s' % (opts.app_label,
#                       opts.get_delete_permission())
#        if not user.has_perm(p):
#            perms_needed.add(opts.verbose_name)
        # Display a link to the admin page.
        return mark_safe(u'%s: <a href="%s">%s</a>' %
                         (escape(capfirst(opts.verbose_name)),
                          admin_url,
                          escape(obj)))
    else:
        # Don't display link to edit, because it either has no
        # admin or is edited inline.
        return u'%s: %s' % (capfirst(opts.verbose_name),
                            force_unicode(obj))