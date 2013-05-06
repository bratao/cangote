from django.db import models
from django.contrib.auth.models import User
from django.contrib.contenttypes.models import ContentType
from django.contrib.contenttypes import generic
from management.models import Project

STATUS_CHOICES = (('new', 'New'), 
                   ('wont_fix', "Won't Fix"), 
                   ('duplicate', 'Duplicate'), 
                   ('accepted','Accepted'), 
                   ('in_progress', 'In Progress'),
                   ('resolved', 'Resolved'),
                   ('closed', 'Closed'),
                   ('Waiting_review', 'Waiting Review'))

PRIORITY_CHOICES = (('high', 'High'),
                    ('moderate', 'Moderate'),
                    ('low', 'Low'))


ATTACHMENT_STATUS_CHOICES= (
    ('current', 'Current'),
    ('superseded', 'Superseded'),
    ('irrelevant', 'No Longer Relevant'),
)

TYPE_CHOICES = (
                ('defect', 'Defect'),
                ('enhancement', 'Enhancement')
                )

class Issue(models.Model):
    project = models.ForeignKey(Project, related_name='issues', editable=True)
    summary = models.CharField(max_length=255)
    description = models.TextField()
    issue_type = models.CharField(max_length=20, choices=TYPE_CHOICES, default='defect')
    date_added = models.DateTimeField(auto_now_add=True)
    date_modified = models.DateTimeField(auto_now=True)
    date_due = models.DateTimeField(null=True, blank=True)
    creator = models.ForeignKey(User, related_name="created_issues", editable=False)
    responsible = models.ForeignKey(User, related_name="assigned_issues", null=True, blank=True)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='new')
    priority = models.CharField(max_length=10, choices=PRIORITY_CHOICES, default='high')
    duplicate_for = models.ForeignKey('self', related_name='duplicates', null=True, blank=True)
    depends_on = models.ForeignKey('self', related_name='dependents', null=True, blank=True)
    
    def clean(self):
        from django.core.exceptions import ValidationError
        if self.duplicate_for and self.depends_on:
            if self.duplicate_for == self.depends_on:
                raise ValidationError('You cannot have the same features both in DEPENDS ON and DUPLICATE FOR fields')
        super(Issue, self).clean()
    
    class Meta:
        ordering = ['-date_due', 'id']
        unique_together = (("duplicate_for", "depends_on"),)

    def __unicode__(self):
        return u'#%d %s' % (self.id, self.summary)

class IssuedAsset(models.Model):
    content_type = models.ForeignKey(ContentType, editable=True)
    object_id = models.PositiveIntegerField(editable=True)
    content_object = generic.GenericForeignKey('content_type', 'object_id')
    issue = models.ForeignKey(Issue, related_name="assets")
    
    def __unicode__(self):
        return self.content_type.name + ' - ' + unicode(self.content_object)

class Comment(models.Model):
    issue = models.ForeignKey(Issue)
    comment = models.TextField()
    creator = models.ForeignKey(User, related_name="bug_comments", editable=False)
    
    def __unicode__(self):
        return u'%s' % self.comment

class Attachment(models.Model):
    description = models.TextField()
    creator = models.ForeignKey(User, related_name="created_issue_attachments", editable=False)
    date_added = models.DateTimeField(auto_now_add=True)
    status = models.CharField(max_length=20, choices=ATTACHMENT_STATUS_CHOICES, default='current')
    attachment = models.FileField(upload_to='attachments/%Y/%m/%d')
    issue = models.ForeignKey(Issue, related_name="attachments")

    def __unicode__(self):
        return u'Attachment: %s' % self.attachment.name

    @models.permalink
    def get_absolute_url(self):
        return ('issues.views.attachment', [str(self.id)])
