#-- encoding: utf8--
"""Yguaratã"""
import ooolib
from reqtool.fur.models import Feature, Module, FeatureVariabilityType,\
    Priority, BindingType, Product

FEATURES_COLS = range(3, 9)
DOCTOR_COL = 9
CLIN_COL = 10
LAB_COL = 11
HEALTH_COL = 12
MODULE_COL = 13
VARIABILITY_COL = 14

DOCTOR_NAME = 'Doctor'
CLIN_NAME = 'Clin'
LAB_NAME = 'Lab'
HEALTH_NAME = 'Health'

for f in Feature.objects.all():
    f.delete()

doc = ooolib.Calc(opendoc='features.ods')
doc.set_sheet_index(1)
(COLS, ROWS) = doc.get_sheet_dimensions()

try:
    phealth = Product.objects.get(name=HEALTH_NAME)
except:
    phealth = Product(name=HEALTH_NAME)
    phealth.save()

try:
    plab = Product.objects.get(name=LAB_NAME)
except:
    plab = Product(name=LAB_NAME)
    plab.save()

try:
    pclin = Product.objects.get(name=CLIN_NAME)
except:
    pclin = Product(name=CLIN_NAME)
    pclin.save()

try:
    pdoctor = Product.objects.get(name=DOCTOR_NAME)
except:
    pdoctor = Product(name=DOCTOR_NAME)
    pdoctor.save()
    
try:
    priority = Priority(name='High')
    priority.save()
except Exception, e:
    print e
    priority = Priority.objects.get(name='High')

try:
    bindingTime = BindingType(name='Compile time')
    bindingTime.save()
except Exception, e:
    print e
    bindingTime = BindingType.objects.get(name='Compile time')

def create_feature(row, col, fparent):
    try:
        f = Feature()
        f.name = doc.get_cell_value(col, row)[1]
        f.parent = fparent
        f.bindingType = bindingTime
        f.priority = priority
        try:
            variability_name = doc.get_cell_value(VARIABILITY_COL, row)[1]
            f.variabilityType = FeatureVariabilityType.objects.get(name=variability_name)
        except Exception, e:
            variability = FeatureVariabilityType(name=variability_name)
            variability.save()
            f.variabilityType = variability
        f.save()
        
        module = None
        try:
            module_name = doc.get_cell_value(MODULE_COL, row)[1]
            module = Module.objects.get(name=module_name)
            f.modules.add(module)
        except Exception, e:
            module = Module(name = module_name)
            module.save()
            f.modules.add(module)
        
        if doc.get_cell_value(DOCTOR_COL, row):
            if module not in pdoctor.modules.all():
                pdoctor.modules.add(module)
        if doc.get_cell_value(HEALTH_COL, row):
            if module not in phealth.modules.all():
                phealth.modules.add(module)
        if doc.get_cell_value(CLIN_COL, row):
            if module not in pclin.modules.all():
                pclin.modules.add(module)
        if doc.get_cell_value(LAB_COL, row):
            if module not in plab.modules.all():
                plab.modules.add(module)
        
        f.save()
        print row, col, f.name
        return f
    except Exception, e:
        print row, col, e
#        raise e

def do(row=6, col=3, parent=None):
    if row >= ROWS:
        return
    
    if doc.get_cell_value(col+1, row+1):
        parent = create_feature(row, col, parent)
        do(row+1, col+1, parent)
    elif doc.get_cell_value(col, row):
        create_feature(row, col, parent)
        do(row+1, col, parent)
    elif col > 3 and doc.get_cell_value(col-1, row):
        if parent:
            do(row, col-1, parent.parent)
        else:
            do(row, col-1, parent)
    else:
        col = 3
        create_feature(row, col, None)
        do(row+1, col, None)

if __name__ == '__main__':
    do()
