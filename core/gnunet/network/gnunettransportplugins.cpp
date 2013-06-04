#include "gnunettransportplugins.h"

//Initialize statics
struct GnunetTransportPlugins::TransportPlugin* GnunetTransportPlugins::plugins_head;
struct GnunetTransportPlugins::TransportPlugin* GnunetTransportPlugins::plugins_tail;


GnunetTransportPlugins::GnunetTransportPlugins(const struct GNUNET_CONFIGURATION_Handle *cfg, QObject *parent) :
    QObject(parent)
{
    pluginsLoad(cfg);
}

GnunetTransportPlugins::~GnunetTransportPlugins(){
    pluginsUnload();
}


/**
 * Load and initialize all plugins.  The respective functions will be
 * invoked by the plugins when the respective events happen.  The
 * closure will be set to a 'const char*' containing the name of the
 * plugin that caused the call.
 *
 * @param cfg configuration to use
 */
void
GnunetTransportPlugins::pluginsLoad (const struct GNUNET_CONFIGURATION_Handle *cfg)
{
  struct TransportPlugin *plug;
  struct TransportPlugin *next;
  char *libname;
  char *plugs;
  char *pos;

  if (NULL != plugins_head)
    return; /* already loaded */
  if (GNUNET_OK !=
      GNUNET_CONFIGURATION_get_value_string (cfg, "TRANSPORT", "PLUGINS",
                                             &plugs))
    return;
  GNUNET_log (GNUNET_ERROR_TYPE_INFO, _("Starting transport plugins `%s'\n"),
              plugs);
  for (pos = strtok (plugs, " "); pos != NULL; pos = strtok (NULL, " "))
  {
    GNUNET_log (GNUNET_ERROR_TYPE_INFO, _("Loading `%s' transport plugin\n"),
                pos);
    GNUNET_asprintf (&libname, "libgnunet_plugin_transport_%s", pos);
    plug = (TransportPlugin *)GNUNET_malloc (sizeof (struct TransportPlugin));
    plug->short_name = GNUNET_strdup (pos);
    plug->lib_name = libname;
    plug->env.cfg = cfg;
    plug->env.cls = plug->short_name;
    GNUNET_CONTAINER_DLL_insert (plugins_head, plugins_tail, plug);
  }
  GNUNET_free (plugs);
  next = plugins_head;
  while (next != NULL)
  {
    plug = next;
    next = plug->next;
    plug->api = (GNUNET_TRANSPORT_PluginFunctions *)GNUNET_PLUGIN_load (plug->lib_name, &plug->env);
    if (plug->api == NULL)
    {
      GNUNET_log (GNUNET_ERROR_TYPE_ERROR,
                  _("Failed to load transport plugin for `%s'\n"),
                  plug->lib_name);
      GNUNET_CONTAINER_DLL_remove (plugins_head, plugins_tail, plug);
      GNUNET_free (plug->short_name);
      GNUNET_free (plug->lib_name);
      GNUNET_free (plug);
    }
  }
}


/**
 * Unload all plugins
 */
void
GnunetTransportPlugins::pluginsUnload ()
{
  struct TransportPlugin *plug;

  while (NULL != (plug = plugins_head))
  {
    GNUNET_break (NULL == GNUNET_PLUGIN_unload (plug->lib_name, plug->api));
    GNUNET_free (plug->lib_name);
    GNUNET_free (plug->short_name);
    GNUNET_CONTAINER_DLL_remove (plugins_head, plugins_tail, plug);
    GNUNET_free (plug);
  }
}




/**
 * Obtain the plugin API based on a plugin name.
 *
 * @param name name of the plugin
 * @return the plugin's API, NULL if the plugin is not loaded
 */
struct GNUNET_TRANSPORT_PluginFunctions *
GnunetTransportPlugins::GPI_plugins_find (const char *name)
{
  struct TransportPlugin *head = plugins_head;

  char *stripped = GNUNET_strdup (name);
  char *sep = strchr (stripped, '_');
  if (NULL != sep)
    sep[0] = '\0';

  while (head != NULL)
  {
    if (head->short_name == strstr (head->short_name, stripped))
        break;
    head = head->next;
  }
  GNUNET_free (stripped);
  if (NULL == head)
    return NULL;
  return head->api;
}
