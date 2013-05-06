from django.contrib import admin, messages
from reqtool.fur.models import Priority, Feature, UseCase, Requirement,\
    BindingType, Module, Product, Variant,\
    VariationPoint, UseCaseSecondaryFlow, Actor, UseCaseVariabilityType,\
    FeatureVariabilityType, RequirementVariabilityType, TestCase, TestSuite, TestPlan

from django.contrib.admin.util import NestedObjects
from django import template
from django.shortcuts import render_to_response
from django.contrib.admin import helpers
from django.utils.translation import ugettext as _
from django.utils.encoding import force_unicode
from reqtool.fur.formsets import RequiredInlineFormset, RequiredFeaturesForm,\
    ExcludedFeaturesForm
from reqtool.fur.util import _my_format_callback, render_to_latex,\
    ProductMapGraph, ProductModulesGraph, FeatureModelGraph

import codecs
from django.template.context import RequestContext
from reqtool.bugtracker.views import add_issue
from reqtool.bugtracker import get_add_issue_link
from django.http import HttpResponse

import re

class ActorAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description', 'project__name')
    list_display = ('project', 'name', 'description')
    ordering= ('name',)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            actor = Actor.objects.get(id=object_id)
            context = {
                'actor': actor,
                'add_issue_link': get_add_issue_link(request, [actor]),
                'title': _('Actor: %s') % force_unicode(actor.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/actor/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(ActorAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(Actor, ActorAdmin)


class BindingTypeAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    list_display = ('name', 'description')
    ordering= ('name',)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            bindingType = BindingType.objects.get(id=object_id)
            context = {
                'bindingType': bindingType,
                'add_issue_link': get_add_issue_link(request, [bindingType]),
                'title': _('Binding Type: %s') % force_unicode(bindingType.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/bindingtype/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(BindingTypeAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(BindingType, BindingTypeAdmin)

class FeatureVariabilityTypeAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    list_display = ('name', 'description')
    ordering= ('name',)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            featureVariabilityType = FeatureVariabilityType.objects.get(id=object_id)
            context = {
                'featureVariabilityType': featureVariabilityType,
                'add_issue_link': get_add_issue_link(request, [featureVariabilityType]),
                'title': _('Feature Variability Type: %s') % force_unicode(featureVariabilityType.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/featurevariabilitytype/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(FeatureVariabilityTypeAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(FeatureVariabilityType, FeatureVariabilityTypeAdmin)

class PriorityAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    list_display = ('name', 'description')
    ordering= ('name',)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            priority = Priority.objects.get(id=object_id)
            context = {
                'priority': priority,
                'add_issue_link': get_add_issue_link(request, [priority]),
                'title': _('Priority: %s') % force_unicode(priority.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/priority/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(PriorityAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(Priority, PriorityAdmin)

class RequirementVariabilityTypeAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    list_display = ('name', 'description')
    ordering= ('name',)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            requirementVariabilityType = RequirementVariabilityType.objects.get(id=object_id)
            context = {
                'requirementVariabilityType': requirementVariabilityType,
                'add_issue_link': get_add_issue_link(request, [requirementVariabilityType]),
                'title': _('Requirement Variability Type: %s') % force_unicode(requirementVariabilityType.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/requirementvariabilitytype/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(RequirementVariabilityTypeAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(RequirementVariabilityType, RequirementVariabilityTypeAdmin)

class UseCaseVariabilityTypeAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    list_display = ('name', 'description')
    ordering= ('name',)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            useCaseVariabilityType = UseCaseVariabilityType.objects.get(id=object_id)
            context = {
                'useCaseVariabilityType': useCaseVariabilityType,
                'add_issue_link': get_add_issue_link(request, [useCaseVariabilityType]),
                'title': _('UseCase Variability Type: %s') % force_unicode(useCaseVariabilityType.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/useCaseVariabilityType/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(UseCaseVariabilityTypeAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(UseCaseVariabilityType, UseCaseVariabilityTypeAdmin)

class UseCaseSecondaryFlowAdmin(admin.TabularInline):
    model = UseCaseSecondaryFlow
    extra = 0


class FeatureRequireAdminInline(admin.TabularInline):
    model = Feature.requires.through
    verbose_name_plural = 'Required features'
    verbose_name = 'Required feature'
    #I gor the fk_name using the django shell, by inspecting the objet Feature
    fk_name = 'from_feature'
    extra = 0
    form = RequiredFeaturesForm

class FeatureExcludeAdminInline(admin.TabularInline):
    model = Feature.excludes.through
    verbose_name_plural = 'Excluded features'
    verbose_name = 'Excluded feature'
    #I got the fk_name using the django shell, by inspecting the objet Feature
    fk_name = 'from_feature'
    extra = 0
    form = ExcludedFeaturesForm
    
class ModuleAdminInline(admin.TabularInline):
    formset = RequiredInlineFormset
    model = Feature.modules.through
    verbose_name_plural = 'Modules'
    verbose_name = 'Module'
    extra = 0

class FeatureAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description', 'project__name')
    list_select_related = True
    list_display = ('id', 'name', 'project', 'description', 'bindingType', 'priority', 
                    'variabilityType', 'parent')
    actions = ['show_features_hierarchy', 
               'pdf_report', 
               'show_feature_model']
    exclude = ('requires', 'excludes', 'modules')
    inlines = [FeatureRequireAdminInline, FeatureExcludeAdminInline,
               ModuleAdminInline]
    list_per_page = 50
    ordering= ('name',)
    
    def save_model(self, request, obj, form, change):
#        print obj.excludes.all()
#        print obj.requires.all()
#        from django.core.exceptions import ValidationError
#        has_equal = len([f for f in obj.requires.all() if f in obj.excludes.all()]) > 0
#        if has_equal:
#            raise ValidationError('You cannot have the same features both in DEPENDS ON and DUPLICATE FOR fields')
        super(FeatureAdmin, self).save_model(request, obj, form, change)
    
    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            feature = Feature.objects.get(id=object_id)
            context = {
                'feature': feature,
                'add_issue_link': get_add_issue_link(request, [feature]),
                'title': _('Feature: %s') % force_unicode(feature.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/feature/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(FeatureAdmin, self).change_view(request, object_id, extra_context)
    
    def pdf_report(self, request, queryset):
        context_instance=RequestContext(request)
        context_instance.autoescape=False
        mycontext = {'features': queryset.order_by('name'),
                   'autoescape': False}
        body = render_to_latex("admin/fur/feature/report_features.tex", 
                               mycontext, context_instance)
        resp = HttpResponse(body, mimetype='application/pdf')
        resp['Content-Disposition'] = 'attachment; filename=features_latex_report.pdf'
        return resp
    
    def show_feature_model(self, request, queryset):
        resp = HttpResponse(FeatureModelGraph(queryset).get_png_graph().read(), 
                            mimetype='application/png')
        resp['Content-Disposition'] = 'attachment; filename=feature_model.png'
        return resp
    
    def show_features_hierarchy(self, request, queryset):
        all_features = []
        
        for obj in queryset:
            #f = Feature.objects.get(id=id)
            if obj.parent is None:
                all_features.append(obj)
        
        collector = NestedObjects()
        opts = self.model._meta
        
        for feature in all_features:
            feature._collect_sub_objects(collector)
        
        nested_features = collector.nested(_my_format_callback,
                                     user=request.user,
                                     admin_site=self.admin_site,
                                     levels_to_root=4
                                     )
        context = {
            "title": _("Features Hierarchy (a feature model?)"),
            "nested_features": [nested_features],
            "root_path": self.admin_site.root_path,
            'action_checkbox_name': helpers.ACTION_CHECKBOX_NAME,
            "app_label": opts.app_label,
            "object_name": force_unicode(opts.verbose_name),
            "opts": opts,
        }
        
        return render_to_response(
              "admin/fur/feature/show_features_hierarchy.html" , context, 
              context_instance=template.RequestContext(request))
        
admin.site.register(Feature, FeatureAdmin)

class RequirementAdminInline(admin.TabularInline):
    formset = RequiredInlineFormset
    model = UseCase.requirements.through
    verbose_name_plural = 'Requirements'
    verbose_name = 'Requirement'
    extra = 0

class ActorAdminInline(admin.TabularInline):
    model = UseCase.actors.through
    verbose_name_plural = 'Actors'
    verbose_name = 'Actor'
    extra = 0

class UseCaseAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    list_display = ('id', 'name', 'description')
    actions = ('pdf_report', 'generate_test_case')
    inlines = [ActorAdminInline, RequirementAdminInline, 
               UseCaseSecondaryFlowAdmin]
    exclude = ('requirements', 'actors')
    ordering= ('name',)

    def pdf_report(self, request, queryset):
        context_instance=RequestContext(request)
        context_instance.autoescape=False
        mycontext = {'usecase': queryset.order_by('name'), 
        'usecasesecondaryflow': UseCaseSecondaryFlow.objects.all(),
        'usecasevariabilitytype': UseCaseVariabilityType.objects.all(), 'autoescape': False}

        body = render_to_latex("admin/fur/usecase/report_usecase.tex", 
                               mycontext, context_instance)
        
        resp = HttpResponse(body, mimetype='application/pdf')
        resp['Content-Disposition'] = 'attachment; filename=usecase_latex_report.pdf'
        return resp
    
    def generate_test_case(self, request, queryset):
        selected = request.POST.getlist(admin.ACTION_CHECKBOX_NAME)
        all_usecases = []
        created_testcases = []
          
        for id in selected:
            all_usecases.append(UseCase.objects.get(id=id))
        
        opts = self.model._meta
        
        all_testcases = TestCase.objects.all()
        
        all_usecaseSecondaryFlow = UseCaseSecondaryFlow.objects.all()
        
        usecase_tests = {}
        
        for usecase in all_usecases:
            test_names = []
            #metodo para verificar se o test case ja existe
            for testcase in all_testcases:
                if testcase.usecase == usecase:
                    useCase = UseCase.objects.get(id=usecase.id)
                    context = {
                        'useCase': useCase,
                        'add_issue_link': get_add_issue_link(request, [useCase]),
                        'title': _('Use Case: %s') % force_unicode(useCase.name),
                        'opts': opts,
                        'object_id': usecase.id,
                        'is_popup': request.REQUEST.has_key('_popup'),
                        'root_path': self.admin_site.root_path,
                        'app_label': opts.app_label,
                        }
                    return render_to_response('admin/fur/usecase/exist.html',
                                      context, 
                                      context_instance=RequestContext(request))
            
            for requirement in usecase.requirements.all():  
                numero = 1
                testName = usecase.name + ', Positive Test Case %d' % numero    
                #metodo para quando tiver dois requisitos
                testcase = TestCase(name=testName, summary=usecase.description,
                                                        variabilityType=usecase.variabilityType, preCondition=usecase.preCondition,
                                                        posCondition=usecase.posCondition, usecase=usecase,
                                                        steps=usecase.mainFlow, screenPath=usecase.screenPath, 
                                                        priority=requirement.priority, testType='positive')
                testcase.save()
                created_testcases.append(TestCase.objects.get(id=testcase.id))
                numero += 1
            
                for usecasesecondaryflow in all_usecaseSecondaryFlow:
                    if usecasesecondaryflow.useCase == usecase:
                        if usecasesecondaryflow.type == 'alternative':
                            testName = usecase.name + ', Positive Test Case %d' % numero
                            match = re.search(r'(.*)%s(.*)' % usecasesecondaryflow.alias, usecase.mainFlow, re.DOTALL)
                            testSteps = match.group(1) + usecasesecondaryflow.flow + match.group(2)
                            testcasePositive = TestCase(name=testName, summary=usecase.description,
                                                        variabilityType=usecase.variabilityType, preCondition=usecase.preCondition,
                                                        posCondition=usecase.posCondition, usecase=usecase,
                                                        steps=testSteps, screenPath=usecase.screenPath,
                                                        priority=requirement.priority, testType='positive')
                            testcasePositive.save()
                            created_testcases.append(TestCase.objects.get(id=testcasePositive.id))
                            numero += 1
                        
                        if usecasesecondaryflow.type == 'exception':
                            testName = usecase.name + ', Negative Test Case %d' % numero
                            match = re.search(r'(.*)%s(.*)' % usecasesecondaryflow.alias, usecase.mainFlow, re.DOTALL)
                            testSteps = match.group(1) + usecasesecondaryflow.flow + match.group(2)
                            testcaseNegative = TestCase(name=testName, summary=usecase.description,
                                                        variabilityType=usecase.variabilityType, preCondition=usecase.preCondition,
                                                        posCondition=usecase.posCondition, usecase=usecase,
                                                        steps=testSteps, screenPath=usecase.screenPath,
                                                        priority=requirement.priority, testType='negative')
                            testcaseNegative.save()
                            created_testcases.append(TestCase.objects.get(id=testcaseNegative.id))
                            numero += 1
                

                #verificar com calma, entender e melhorar!
                for created_testcase in created_testcases:
                    test_names.append(_my_format_callback(created_testcase, request.user,
                                                          self.admin_site, None))
                usecase_tests[created_testcase.name] = test_names

        context = {
            'title': _('Tests Cases Creation Successful!'),
            'usecase_tests': usecase_tests,
            "root_path": self.admin_site.root_path,
            'action_checkbox_name': helpers.ACTION_CHECKBOX_NAME,
            "app_label": opts.app_label,
            "object_name": force_unicode(opts.verbose_name),
            "opts": opts,
            "all_usecases": all_usecases
            }
        return render_to_response('admin/fur/usecase/created.html',
                          context, 
                          context_instance=template.RequestContext(request))

        return super(UseCaseAdmin, self)
        

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            useCase = UseCase.objects.get(id=object_id)
            context = {
                'useCase': useCase,
                'add_issue_link': get_add_issue_link(request, [useCase]),
                'title': _('Use Case: %s') % force_unicode(useCase.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/usecase/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(UseCaseAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(UseCase, UseCaseAdmin)

class TestCaseAdmin(admin.ModelAdmin):
    search_fields = ('name', 'summary')
    list_display = ('id', 'name', 'summary', 'variabilityType', 'priority')
    actions = ['pdf_report']
    ordering = ('name',)
    
    def pdf_report(self, request, queryset):
        context_instance = RequestContext(request)
        context_instance.autoescape = False
        mycontext = {'testcase': queryset.order_by('name'),
                     'usecasevariabilitytype': UseCaseVariabilityType.objects.all(), 
                     'autoscape': False
                     }
        
        body = render_to_latex("admin/fur/testcase/report_testcase.tex",
                               mycontext, context_instance)
        
        resp = HttpResponse(body, mimetype='application/pdf')
        resp['Content-Disposition'] = 'attachment; filename=testcase_latex_report.pdf'
        return resp
    
    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            testCase = TestCase.objects.get(id=object_id)
            context = {
                       'testCase': testCase,
                       'add_issue_link': get_add_issue_link(request, [testCase]),
                       'title': _('Test Case: %s') % force_unicode(testCase.name),
                       'opts': opts,
                       'object_id': object_id,
                       'is_popup': request.REQUEST.has_key('_popup'),
                       'root_path': self.admin_site.root_path,
                       'app_label': opts.app_label,
                       }
            return render_to_response('admin/fur/testcase/view.html',
                                      context,
                                      context_instance=RequestContext(request))
        return super(TestCaseAdmin, self).change_view(request, object_id, extra_context)
            
admin.site.register(TestCase, TestCaseAdmin)


class TestSuiteAdmin(admin.ModelAdmin):
    search_fields = ('name', 'summary')
    list_display = ('id', 'name', 'summary', 'priority')
    ordering = ('name',) 

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            testSuite = TestSuite.objects.get(id=object_id)
            context = {
                       'testSuite': testSuite,
                       'add_issue_link': get_add_issue_link(request, [testSuite]),
                       'title': _('Test Suite: %s') % force_unicode(testSuite.name),
                       'opts': opts,
                       'object_id': object_id,
                       'is_popup': request.REQUEST.has_key('_popup'),
                       'root_path': self.admin_site.root_path,
                       'app_label': opts.app_label,
                       }
            return render_to_response('admin/fur/testsuite/view.html',
                                      context,
                                      context_instance=RequestContext(request))
        return super(TestSuiteAdmin, self).change_view(request, object_id, extra_context)
            
admin.site.register(TestSuite, TestSuiteAdmin) 


class TestPlanAdmin(admin.ModelAdmin):
    search_fields = ('name', 'summary')
    list_display = ('id', 'name', 'summary')  
    ordering = ('name',)
    
    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            testPlan = TestPlan.objects.get(id=object_id)
            context = {
                       'testPlan': testPlan,
                       'add_issue_link': get_add_issue_link(request, [testPlan]),
                       'title': _('Test Plan: %s') % force_unicode(testPlan.name),
                       'opts': opts,
                       'object_id': object_id,
                       'is_popup': request.REQUEST.has_key('_popup'),
                       'root_path': self.admin_site.root_path,
                       'app_label': opts.app_label,
                       }
            return render_to_response('admin/fur/testplan/view.html',
                                      context,
                                      context_instance=RequestContext(request))
        return super(TestPlanAdmin, self).change_view(request, object_id, extra_context)
            
admin.site.register(TestPlan, TestPlanAdmin)    


class FeatureAdminInline(admin.TabularInline):
    formset = RequiredInlineFormset
    model = Requirement.features.through
    verbose_name_plural = 'Related features'
    verbose_name = 'Related feature'
    extra = 0

class VariationPointAdminInline(admin.TabularInline):
    model = VariationPoint
    verbose_name_plural = 'Variation Points'
    verbose_name = 'Variation Point'
    extra = 0

class RequirementAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    actions = ('pdf_report',)
    list_select_related = True
    list_display = ('id', 'name', 'description', 'variabilityType', 'priority')
    inlines = [FeatureAdminInline, VariationPointAdminInline]
    exclude = ('features',)
    ordering= ('name',)
    
    def pdf_report(self, request, queryset):
        context_instance=RequestContext(request)
        context_instance.autoescape=False
        mycontext = {'requirements': queryset.order_by('name'),
                   'autoescape': False}
        body = render_to_latex("admin/fur/requirement/report_requirement.tex", 
                               mycontext, context_instance)
        resp = HttpResponse(body, mimetype='application/pdf')
        resp['Content-Disposition'] = 'attachment; filename=requirement_latex_report.pdf'
        return resp

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            requirement = Requirement.objects.get(id=object_id)
            context = {
                'requirement': requirement,
                'add_issue_link': get_add_issue_link(request, [requirement]),
                'title': _('Requirement: %s') % force_unicode(requirement.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/requirement/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(RequirementAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(Requirement, RequirementAdmin)

class ModuleAdmin(admin.ModelAdmin):
    actions= ['show_features', 'features_pdf_report', 'requirements_pdf_report']
    list_display = ('name', 'description')
    ordering= ('name',)
    
    def features_pdf_report(self, request, queryset):
        context_instance=RequestContext(request)
        context_instance.autoescape=False
        module = queryset[0]
        mycontext = {'module': module,
                     'features': module.feature_set.order_by('name'),
                   'autoescape': False}
        body = render_to_latex("admin/fur/module/report_features.tex", 
                               mycontext, context_instance)
        resp = HttpResponse(body, mimetype='application/pdf')
        resp['Content-Disposition'] = 'attachment; filename=features_latex_report.pdf'
        return resp
    
    def requirements_pdf_report(self, request, queryset):
        context_instance=RequestContext(request)
        context_instance.autoescape=False
        module = queryset[0]
        
        requirements = []
        for feature in module.feature_set.all():
            requirements.extend(feature.requirement_set.order_by('name'))
        
        requirements = sorted(requirements, cmp=lambda x, y: cmp(x.name, y.name))
        mycontext = {'module': module,
                     'requirements': requirements,
                   'autoescape': False}
        body = render_to_latex("admin/fur/module/report_requirement.tex", 
                               mycontext, context_instance)
        resp = HttpResponse(body, mimetype='application/pdf')
        resp['Content-Disposition'] = 'attachment; filename=requirements_latex_report.pdf'
        return resp
    
    def show_features(self, request, queryset):
        selected = request.POST.getlist(admin.ACTION_CHECKBOX_NAME)
        all_modules = []
        modules_nested_features = {}
        
        for id in selected:
            all_modules.append(Module.objects.get(id=id))

        opts = self.model._meta
        
        for module in all_modules:
            collector = NestedObjects()
            
            for f in module.feature_set.all():
                f._collect_sub_objects(collector)

            modules_nested_features[module.name] = \
                    [collector.nested(_my_format_callback,
                                     user=request.user,
                                     admin_site=self.admin_site,
                                     levels_to_root=4
                                     )]
        context = {
            "title": _("Showing features hierarchy for module(s)"),
            "modules_nested_features": modules_nested_features,
            "root_path": self.admin_site.root_path,
            'action_checkbox_name': helpers.ACTION_CHECKBOX_NAME,
            "app_label": opts.app_label,
            "object_name": force_unicode(opts.verbose_name),
            "opts": opts,
            "all_modules": all_modules
        }
        
        return render_to_response(
              "admin/fur/module/show_features_hierarchy.html" , context, 
              context_instance=template.RequestContext(request))

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            module = Module.objects.get(id=object_id)
            context = {
                'module': module,
                'add_issue_link': get_add_issue_link(request, [module]),
                'title': _('Module: %s') % force_unicode(module.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/module/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(ModuleAdmin, self).change_view(request, object_id, extra_context)    

admin.site.register(Module, ModuleAdmin)

class ProductModulesAdminInline(admin.TabularInline):
    formset = RequiredInlineFormset
    model = Product.modules.through
    verbose_name_plural = 'Modules'
    verbose_name = 'Module'
    extra = 0

class ProductAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description', 'project__name')
    list_display = ('name', 'project', 'description')
    inlines = [ProductModulesAdminInline]
    exclude = ('modules',)
    actions = ('show_modules', 'product_map_graph', 'product_modules_graph', 'pdf_report')
    ordering= ('name',)
    
    def pdf_report(self, request, queryset):
        context_instance=RequestContext(request)
        context_instance.autoescape=False
        template = "admin/fur/product/report_product.tex"
        mycontext = {'autoescape': False}
        
        if len(queryset) > 1:
            template = "admin/fur/product/report_products.tex"
            mycontext['products'] = queryset
        else:
            mycontext = {'product': queryset[0]}
            
        body = render_to_latex(template, mycontext, context_instance)
        resp = HttpResponse(body, mimetype='application/pdf')
        resp['Content-Disposition'] = 'attachment; filename=product_latex_report.pdf'
        return resp
    
    def product_modules_graph(self, request, queryset):
        resp = HttpResponse(ProductModulesGraph(queryset).get_png_graph().read(), 
                            mimetype='application/png')
        resp['Content-Disposition'] = 'attachment; filename=product_modelules.png'
        return resp
    
    def product_map_graph(self, request, queryset):
        resp = HttpResponse(ProductMapGraph(queryset).get_png_graph().read(), 
                            mimetype='application/png')
        resp['Content-Disposition'] = 'attachment; filename=product_map.png'
        return resp
    
    def show_modules(self, request, queryset):
        selected = request.POST.getlist(admin.ACTION_CHECKBOX_NAME)
        all_products = []
        
        for id in selected:
            all_products.append(Product.objects.get(id=id))

        opts = self.model._meta
        product_modules = {}
        for product in all_products:
            modules_names = []
            for module in product.modules.all():
                modules_names.append(_my_format_callback(module, request.user, 
                                                      self.admin_site, None))
            product_modules[product.name] = modules_names

        context = {
            "title": _("Showing modules for product(s)"),
            "products_modules": product_modules,
            "root_path": self.admin_site.root_path,
            'action_checkbox_name': helpers.ACTION_CHECKBOX_NAME,
            "app_label": opts.app_label,
            "object_name": force_unicode(opts.verbose_name),
            "opts": opts,
            "all_products": all_products
        }
        
        return render_to_response(
              "admin/fur/product/show_modules.html" , context, 
              context_instance=template.RequestContext(request))

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            product = Product.objects.get(id=object_id)
            context = {
                'product': product,
                'add_issue_link': get_add_issue_link(request, [product]),
                'title': _('Product: %s') % force_unicode(product.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/product/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(ProductAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(Product, ProductAdmin)

class VariantAdmin(admin.TabularInline):
    model = Variant
    extra = 0
    search_fields = ('name', 'description')

class VariationPointAdmin(admin.ModelAdmin):
    search_fields = ('name', 'description')
    inlines = [VariantAdmin]
    ordering= ('name',)

    def change_view(self, request, object_id, extra_context=None):
        opts = self.model._meta
        if not request.REQUEST.has_key("_change"):
            variationPoint = VariationPoint.objects.get(id=object_id)
            context = {
                'variationPoint': variationPoint,
                'add_issue_link': get_add_issue_link(request, [variationPoint]),
                'title': _('Variation Point: %s') % force_unicode(variationPoint.name),
                'opts': opts,
                'object_id': object_id,
                'is_popup': request.REQUEST.has_key('_popup'),
                'root_path': self.admin_site.root_path,
                'app_label': opts.app_label,
                }
            return render_to_response('admin/fur/variationpoint/view.html',
                                      context, 
                                      context_instance=RequestContext(request))
        return super(VariationPointAdmin, self).change_view(request, object_id, extra_context)

admin.site.register(VariationPoint, VariationPointAdmin)
