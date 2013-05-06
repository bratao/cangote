from django.forms.models import ModelForm
from reqtool.bugtracker.models import Issue, IssuedAsset
        
#class IssueAdminForm(forms.ModelForm):
#    def __init__(self, *args, **kwargs):
#        super(ProductAdminForm, self).__init__(*args, **kwargs)
#        print dir(self.instance)
#        try:
#            #Try and set the selected_cat field from instance if it exists
#            self.fields['selected_cat'].initial = self.instance.subcategory.category.id
#        except:
#            pass
#    #The product model is defined with out the category, so add one in for display
#    category = forms.ModelChoiceField(queryset=Category.objects.all().order_by('name'), 
#                                      widget=forms.Select(attrs={'id':'category'}), required=False)
#    #This field is used exclusively for the javascript so that I can select the 
#    #correct category when editing an existing product
#    selected_cat = forms.CharField(widget=forms.HiddenInput, required=False)
#
#    class Meta:
#        model = Product
#
#    class Media:
#        #Alter these paths depending on where you put your media 
#        js = (
#            'js/mootools-1.2-core-yc.js',
#            'js/product.js',
#        )