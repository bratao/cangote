from django.contrib import admin
from reqtool.bugtracker.models import Issue, Comment, IssuedAsset, Attachment
from django import forms
from django.http import HttpResponseRedirect, QueryDict, HttpRequest
from django.forms.formsets import formset_factory
from django.forms.models import modelformset_factory
from django.contrib.contenttypes.models import ContentType
from django.shortcuts import render_to_response, redirect
from django.template.context import RequestContext
from django.contrib.admin.options import InlineModelAdmin
from reqtool.bugtracker import get_add_issue_link
from django.utils.translation import ugettext as _
from django.utils.encoding import force_unicode
from django.db.models.signals import post_save
from django.core.mail import send_mail
import threading
from reqtool import settings

class IssuedAssetInline(admin.TabularInline):
    model = IssuedAsset
    extra = 0

class CommentInline(admin.TabularInline):
    model = Comment
    extra = 0
    
    def save_model(self, request, obj, form, change):
        obj.creator = request.user
        obj.save()

class AttachmentInline(admin.TabularInline):
    model = Attachment
    extra = 0

class IssueAdmin(admin.ModelAdmin):
    search_fields = ('summary', 'description', 'status', 'project__name', 'responsible__first_name', 'priority')
    inlines = [IssuedAssetInline, AttachmentInline, CommentInline]
    list_display = ('id', 'project', 'summary', 'status', 'priority', 'creator', 'responsible', 'date_modified')
    ordering= ('-date_modified', '-date_added')
    
    def add_view(self, request, form_url='', extra_context=None):
        if request.REQUEST.has_key('objects'):
            objects = request.REQUEST.getlist('objects')
            ctypes = []
            ctype = None
            for obj in objects:
                ctypename, obj_id = obj.split('_')
                ctype = ContentType.objects.get(name=ctypename)
                ctype_obj = ctype.get_object_for_this_type(id=obj_id)
                ctypes.append(ctype_obj)
            extra_context = {'objects': ctypes, 
                             'content_type': ctype,
                             'add_bug_report_action': True,
                             }
            return super(IssueAdmin, self).add_view(request, extra_context=extra_context)
        return super(IssueAdmin, self).add_view(request, form_url)
    
    def save_model(self, request, obj, form, change):
        if obj.depends_on and obj.duplicate_for:
            if obj.depends_on == obj.duplicate_for:
                self.message_user(request, 'You cannot set the same bug for DUPLICATE FOR and DEPENDS ON.')
        if not change:
            obj.creator = request.user
            obj.save()
            for ctypename_id in request.REQUEST.getlist('objects'):
                ctypename, obj_id = ctypename_id.split('_')
                ctype = ContentType.objects.get(name=ctypename)
                ctypeobj = ctype.get_object_for_this_type(id=obj_id)
                issued_asset = IssuedAsset.objects.create(content_object=ctypeobj,issue=obj)
        obj.save()
        
    def save_formset(self, request, form, formset, change):
        if formset.model == Attachment:
            instance = formset.save(commit=False)
            if instance:
                instance[0].creator = request.user
        elif formset.model ==  Comment:
            instance = formset.save(commit=False)
            if instance:
                instance[0].creator = request.user
            
        return super(IssueAdmin, self).save_formset(request, form, formset, change)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            issue = Issue.objects.get(id=object_id)
            context = {
                'issue': issue,
                'title': _('Issue: %s') % force_unicode(issue.summary),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/bugtracker/issue/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(IssueAdmin, self).change_view(request, object_id, extra_context)

def add_bug_report_action(admin_, request, queryset):
#    content_type = ContentType.objects.get_for_model(queryset[0])
#    objects = []
#    for obj in queryset:
#        objects.append('objects=%s_%s' % (ContentType.objects.get_for_model(obj).name, obj.id))
#    url = '/bugtracker/issue/add/?%s' % ('&'.join(objects))
    return redirect(get_add_issue_link(request, queryset))
      
admin.site.register(Issue, IssueAdmin)
admin.site.add_action(add_bug_report_action, 'Add issue')

def issue_saved_send_email_callback(sender, **kwargs):
    issue = kwargs['instance']
    subject = None
    body = None
    if kwargs['created']:
        subject = '[reqtool bugtracker] New issue created: #%d' % issue.id
        body = ('The issue <a href="bugtracker/issue/%d/">#%d</a>, created by %s %s, has been assigned to you.'
                % (issue.id, issue.id, issue.creator.first_name, issue.creator.last_name))
    else:
        subject = '[reqtool bugtracker] Issue #%d modified' % issue.id
        body = ('The issue <a href="bugtracker/issue/%d/">#%d</a>, assigned to you, has been modified.'
                % (issue.id, issue.id))
    
    recipients = []
    if issue.creator.email: 
        recipients.append(issue.creator.email)
    if issue.responsible and issue.responsible.email: 
        recipients.append(issue.responsible.email)
    
    try:
        t = threading.Thread(target=send_mail,
                             args = [subject, body, settings.EMAIL_HOST_USER, recipients],
                             kwargs={'fail_silently': True})
        t.setDaemon(True)
        t.start()
    except Exception, e:
        print e

post_save.connect(issue_saved_send_email_callback, Issue, dispatch_uid="issue_saved_send_email_dispapatch_uid")