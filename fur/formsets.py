from django import forms
from reqtool.fur.models import Feature

class RequiredFeaturesForm(forms.ModelForm):
    class Meta:
        model = Feature
        
    def clean(self):
        cleaned_data = self.cleaned_data
        return cleaned_data
    
ExcludedFeaturesForm = RequiredFeaturesForm

class RequiredInlineFormset(forms.models.BaseInlineFormSet):
    def clean(self):
        # get forms that actually have valid data
        count = 0
        for form in self.forms:
            try:
                if form.cleaned_data:
                    count += 1
            except AttributeError:
                # annoyingly, if a subform is invalid Django explicity raises
                # an AttributeError for cleaned_data
                pass
        if count < 1:
            raise forms.ValidationError('This field is required')