from django.contrib import admin
from management.models import Role, Risk, Phase, Decision, Project
from reqtool.management.models import LikelihoodImpactHistory
from reqtool.management.models import Occurrence
from reqtool.management.models import Member


class ProjectMembersAdminInline(admin.TabularInline):
    model = Project.members.through
    verbose_name = 'Member'
    verbose_name_plural = 'Members'
    extra = 0

class DecisionMembersAdminInline(admin.TabularInline):
    model = Decision.member.through
    verbose_name = 'Member'
    verbose_name_plural = 'Members'
    extra = 0

class MemberRolesAdminInline(admin.TabularInline):
    model = Member.roles.through
    verbose_name = 'Role'
    verbose_name_plural = 'Roles'
    extra = 0

class ProjectAdmin(admin.ModelAdmin):
    inlines = [ProjectMembersAdminInline]
    ordering = ('name',)
    search_fields = ('name', 'description')
    list_display = ('name', 'description')
    exclude = ('members',)

class MemberAdmin(admin.ModelAdmin):
    inlines = [MemberRolesAdminInline]
    ordering = ('name',)
    search_fields = ('name', 'description')
    list_display = ('name', 'description')
    exclude = ('roles',)

class RoleAdmin(admin.ModelAdmin):
    ordering = ('name',)
    search_fields = ('name', 'description')
    list_display = ('name', 'description')

class LikelihoodImpactHistoryAdmin(admin.TabularInline):
    model = LikelihoodImpactHistory
    extra = 0

class OccurrenceAdmin(admin.TabularInline):
    model = Occurrence
    extra = 0

class AssociatedRisksAdmin(admin.TabularInline):
    model = Risk.associated_risks.through
    verbose_name = 'Associated Risk'
    verbose_name_plural = 'Associated Risks'
    fk_name = 'from_risk'
    extra = 0

class RiskAdmin(admin.ModelAdmin):
    inlines = [LikelihoodImpactHistoryAdmin,OccurrenceAdmin,AssociatedRisksAdmin]
    ordering = ('name',)
    search_fields = ('name', 'description')
    list_display = ('name', 'strategy', 'risk_type', 
                    'when_indentification')
    exclude = ('associated_risks',)


class PhaseAdmin(admin.ModelAdmin):
    ordering = ('name',)
    search_fields = ('name', 'description')
    list_display = ('name',)

class DecisionAdmin(admin.ModelAdmin):
    inlines = [DecisionMembersAdminInline]
    ordering = ('when',)
    search_fields = ('name', 'description')
    list_display = ('name', 'description','notes','when',)
    exclude = ('member',)

admin.site.register(Project, ProjectAdmin)
admin.site.register(Member, MemberAdmin)
admin.site.register(Risk, RiskAdmin)
admin.site.register(Role, RoleAdmin)
admin.site.register(Phase, PhaseAdmin)
admin.site.register(Decision, DecisionAdmin)
#admin.site.register(LikelihoodImpactHistory)
