from django.contrib.contenttypes.models import ContentType

def get_add_issue_link(request, object_list):
    """Given a list of persisted model objects it returns the current url to add a issue
    related to this objects.
    
    @param object_list: list of persisted model objects
    @return: string with the url for add issue to the objects
    """
    objects_str = []
    for obj in object_list:
        ctypename = ContentType.objects.get_for_model(obj).name
        objects_str.append('objects=%s_%s' % (ctypename, obj.id))
    add_issue_link = '/~esa/splmt/admin/bugtracker/issue/add/?%s' % '&'.join(objects_str)
    return add_issue_link