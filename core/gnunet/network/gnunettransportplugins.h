#ifndef GNUNETTRANSPORTPLUGINS_H
#define GNUNETTRANSPORTPLUGINS_H

#include <QObject>
#include "core/gnunet/gnunet_includes.h"

class GnunetTransportPlugins : public QObject
{
   Q_OBJECT



    /**
     * Entry in doubly-linked list of all of our plugins.
     */
    struct TransportPlugin
    {
      /**
       * This is a doubly-linked list.
       */
      struct TransportPlugin *next;

      /**
       * This is a doubly-linked list.
       */
      struct TransportPlugin *prev;

      /**
       * API of the transport as returned by the plugin's
       * initialization function.
       */
      struct GNUNET_TRANSPORT_PluginFunctions *api;

      /**
       * Short name for the plugin (i.e. "tcp").
       */
      char *short_name;

      /**
       * Name of the library (i.e. "gnunet_plugin_transport_tcp").
       */
      char *lib_name;

      /**
       * Environment this transport service is using
       * for this plugin.
       */
      struct GNUNET_TRANSPORT_PluginEnvironment env;

    };



public:
    explicit GnunetTransportPlugins(const GNUNET_CONFIGURATION_Handle *cfg,QObject *parent = 0);
    ~GnunetTransportPlugins();

    static GNUNET_TRANSPORT_PluginFunctions *GPI_plugins_find(const char *name);

signals:
    
public slots:

private:
    void pluginsLoad(const GNUNET_CONFIGURATION_Handle *cfg);


    /**
     * Head of DLL of all loaded plugins.
     */
    static struct TransportPlugin *plugins_head;

    /**
     * Head of DLL of all loaded plugins.
     */
    static struct TransportPlugin *plugins_tail;

    const GNUNET_CONFIGURATION_Handle *cfg;

    void pluginsUnload();

};

#endif // GNUNETTRANSPORTPLUGINS_H
