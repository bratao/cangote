# Create your views here.
from reqtool.bugtracker.admin import IssueAdmin
from reqtool.bugtracker.models import Issue
from django.contrib.admin.sites import AdminSite
from django.contrib import admin

def add_issue(request, queryset):
    issue_admin = IssueAdmin(Issue, AdminSite())
    return issue_admin.add_view(request)