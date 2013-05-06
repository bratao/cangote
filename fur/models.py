from django.db import models
import reqtool
from django.conf import settings
from management.models import Project


STATUS_CHOICES = (('new', 'New'),
                    ('inspected', 'Inspected'),
                    ('being_corrected', 'Being corrected'),
                    ('accepted','Accepted'))


class RequirementVariabilityType(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    
    class Meta:
        ordering = ('name',)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/requirementvariabilitytype/%i/" % self.id
               
    def __unicode__(self):
        return self.name

class UseCaseVariabilityType(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    
    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name

class FeatureVariabilityType(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    
    class Meta:
        ordering = ('name',)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/featurevariabilitytype/%i/" % self.id
        
    def __unicode__(self):
        return self.name

class BindingType(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    
    class Meta:
        ordering = ('name',)
        
    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/bindingtype/%i/" % self.id

    def __unicode__(self):
        return self.name

class Priority(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    
    class Meta:
        ordering = ('name',)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/priority/%i/" % self.id
        
    def __unicode__(self):
        return self.name

class Feature(models.Model):
    #criar campo para identificador da feature manual?
    project = models.ForeignKey(Project, related_name='features', editable=True)
    name = models.CharField(max_length=100)
    description = models.TextField(blank=True)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='new')
    bindingType = models.ForeignKey(BindingType)
    priority = models.ForeignKey(Priority)
    variabilityType = models.ForeignKey(FeatureVariabilityType)
    requires = models.ManyToManyField("self", blank=True, symmetrical=False, 
                                      related_name='requires_features')
    excludes = models.ManyToManyField("self", blank=True, symmetrical=False, 
                                      related_name='excludes_features')
    parent = models.ForeignKey('self', blank=True, null=True)
    modules = models.ManyToManyField('Module')
    observations = models.TextField(blank=True)

    
    def children(self):
        for f in Feature.objects.all():
            if f.parent == self:
                yield f
    
    class Meta:
        unique_together = (('name', 'parent'),)
        ordering = ('name',)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/feature/%i/" % self.id

    def __unicode__(self):
        return self.name

class Actor(models.Model):
    project = models.ForeignKey(Project, related_name='actors', editable=True)
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    
    class Meta:
        ordering = ('name',)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/actor/%i/" % self.id
        
    def __unicode__(self):
        return self.name

#class UseCaseSecondaryFlowType(MetaInfo):
#    pass

class UseCaseSecondaryFlow(models.Model):
    alias = models.CharField(max_length=100)
    type = models.CharField(max_length=12, choices=[('alternative','alternative'), 
                                                    ('exception', 'exception')])
    flow = models.TextField(blank=True)
    useCase = models.ForeignKey('UseCase')
    
    class Meta:
        ordering = ('alias',) 
    def __unicode__(self):
        return self.alias

class UseCase(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='new')
    actors = models.ManyToManyField(Actor, blank=True)
    variabilityType = models.ForeignKey(UseCaseVariabilityType)
    preCondition = models.TextField()
    posCondition = models.TextField()
    requirements = models.ManyToManyField('Requirement')
    mainFlow = models.TextField()
    screenPath = models.CharField(max_length=50, blank=True)
    
    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/usecase/%i/" % self.id

    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name
    
    
class TestCase(models.Model):
    name = models.CharField(max_length=100, unique=True)
    summary = models.TextField(blank=True)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='new')
    variabilityType = models.ForeignKey(UseCaseVariabilityType)
    preCondition = models.TextField(blank=True)
    posCondition = models.TextField(blank=True)
    usecase = models.ForeignKey(UseCase)
    steps = models.TextField()
    screenPath = models.CharField(max_length=50, blank=True)
    testType = models.CharField(max_length=20, choices=[('positive','Positive'), 
                                                        ('negative', 'Negative'),
                                                        ('undefined', 'Undefined')], 
                                                        default='undefined')
    priority = models.ForeignKey(Priority)
    responsible = models.CharField(max_length=50, blank=True)
                                                        
    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/testcase/%i/" % self.id
    
    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name
    
    
class TestSuite(models.Model):
    name = models.CharField(max_length=100, unique=True)
    summary = models.TextField(blank=True)
    priority = models.ForeignKey(Priority)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='new')
    testCases = models.ManyToManyField(TestCase)
    responsible = models.CharField(max_length=50, blank=True)
    
    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/testsuite/%i/" % self.id
    
    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name
    
    
class TestPlan(models.Model):
    name = models.CharField(max_length=100, unique=True)
    summary = models.TextField(blank=True)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='new')
    release = models.CharField(max_length=50, blank=True)
    testSuites = models.ManyToManyField(TestSuite)
    features = models.ManyToManyField(Feature)
    responsible = models.CharField(max_length=50, blank=True)
    acceptance_criteria = models.CharField(max_length=4, blank=True)
    creation_date = models.DateField()
    
    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/testplan/%i/" % self.id
    
    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name 
 

class Requirement(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='new')
    variabilityType = models.ForeignKey(RequirementVariabilityType)
    priority = models.ForeignKey(Priority)
    features = models.ManyToManyField(Feature)
    screenPath = models.CharField(max_length=50, blank=True)
    observations = models.TextField(blank=True)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/requirement/%i/" % self.id
    
    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name
     

class VariationPoint(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    cardinalityMin = models.PositiveIntegerField()
    cardinalityMax = models.PositiveIntegerField()
    variantParent = models.OneToOneField('Variant', blank=True, null=True)
    requirement = models.ForeignKey(Requirement)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/variationpoint/%i/" % self.id
    
    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name
    
class Variant(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    variationPoint = models.ForeignKey(VariationPoint)
    feature = models.ForeignKey(Feature, blank=True, null=True, unique=False)
    
    class Meta:
        ordering = ('name',)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/variant/%i/" % self.id
        
    def __unicode__(self):
        return self.name
    
class Module(models.Model):
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)

    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/module/%i/" % self.id

    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name
    
class Product(models.Model):
    project = models.ForeignKey(Project, related_name='products', editable=True)
    name = models.CharField(max_length=100, unique=True)
    description = models.TextField(blank=True)
    modules = models.ManyToManyField(Module, blank=True)
    #As features isoladas devem ser movidas para um modulo. Assim nao teremos
    #produtos com features isoladas.
    #features = models.ManyToManyField(Feature, blank=True)
    
    def get_absolute_url(self):
        return '/'+ settings.OUR_URL+ "fur/product/%i/" % self.id

    class Meta:
        ordering = ('name',)
        
    def __unicode__(self):
        return self.name
