from django.db import models

# Create your models here.

class Project(models.Model):
    name = models.CharField(max_length=200)
    description = models.TextField()
    members = models.ManyToManyField('Member')
    #phases = models.ManyToManyField('Requirement')
    
    def __unicode__(self):
        return self.name
    
class Member(models.Model):
    name = models.CharField(max_length=200)
    description = models.TextField()
    roles = models.ManyToManyField('Role')
    
    def __unicode__(self):
        return self.name

class Role(models.Model):
    name = models.CharField(max_length=200)
    description = models.TextField()
    def __unicode__(self):
        return self.name

class Risk(models.Model):
    name = models.CharField(max_length=200)
    description = models.TextField()
    explanantion = models.TextField()
    strategy = models.CharField(max_length=10, choices=[('evitar', 'evitar'), 
                                         ('transmitir', 'transmitir'),
                                         ('mitigar', 'mitigar'),
                                         ('aceitar', 'aceitar')])
    associated_risks = models.ManyToManyField('self', related_name='associated_risks')
    causes = models.TextField()
    mitigation_strategies = models.TextField()
    contigence_strategy = models.TextField()
    risk_type = models.CharField(max_length=10, choices=[('Organizational risks','Organizational risks'),('Business risks','Business risks'), ('Staff risks','Staff risks'),('Project risks','Project risks'),('Process risks','Process risks'),('Product risks','Product risks')])
    when_indentification = models.DateField()
    phase =  models.ForeignKey('Phase')
    def __unicode__(self):
        return self.name

class Occurrence(models.Model): 
    risk = models.ForeignKey('Risk') 
    Originator = models.CharField(max_length=50)
    Responsible = models.ForeignKey('Member')
    when = models.DateField()
    description = models.TextField()
    status = models.CharField(max_length=10, 
                              choices=[('corrigido', 'corrigido'), 
                                       ('cancelado', 'cancelado'), 
                                       ('pendente', 'pendente')])

    def __unicode__(self):
        return self.name

class LikelihoodImpactHistory(models.Model):
    risk = models.ForeignKey('Risk')
    likelihood = models.IntegerField(choices = [(1, 'baixa'), 
                                                (2, 'media'), (3, 'alta')])
    impact = models.IntegerField(choices = [(1, 'baixa'), 
                                                (2, 'media'), (3, 'alta')])
    when = models.DateField()

class Phase(models.Model):
    name = models.CharField(max_length=200)
    description = models.TextField()
    project = models.ForeignKey('Project')

class Decision(models.Model):
    name = models.CharField(max_length=200)
    member = models.ManyToManyField('Member')
    phase =  models.ForeignKey('Phase')
    description = models.TextField()
    alternatives = models.TextField()
    justification = models.TextField()
    notes = models.TextField()
    when = models.DateField()
