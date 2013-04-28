/*
     This file is part of Cangote
     (C) 2012 Bruno Cabral (and other contributing authors)

     Cangote is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 3, or (at your
     option) any later version.

     Cangote is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with Cangote; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.
*/

#include "gnunet.h"
#include "filesharing/filesharing.h"
#include "network/NetworkManager.h"
//#include "core/servicestatus.h"
#include "core/gnunet/filesharing/transfer/downloads.h"

#include <math.h>
#include <QElapsedTimer>
#include <QWaitCondition>



//Initialize static
GNUNET_CONFIGURATION_Handle * GNUNet::m_config;



GNUNet::GNUNet(QObject *parent) :
    ServiceObject(parent)
{

    m_connected = false;
    //status = new ServiceStatus();

}


/**
 * Static callback. Is the first function executed when GNUNet is running.
 */
void GNUNet::mainLoopCallback(void *cls, char *const *args, const char *cfgfile,
                              const struct GNUNET_CONFIGURATION_Handle *cfg)
{
    GNUNet* gnunetInstance = (GNUNet*)cls;
    Q_ASSERT(gnunetInstance);

    //Call our main loop
    gnunetInstance->mainLoop(args,cfgfile,cfg);

}


/**
 * Static function to process our messages.Is needed as the GNUNet loop locks our internal qt Loop.
 */
void GNUNet::keepaliveTask (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc)
{
    GNUNet* gnunetInstance = (GNUNet*)cls;
    Q_ASSERT(cls);

    //Process the events
    gnunetInstance->ProcessEvents();
    gnunetInstance->filesharing()->ProcessEvents();

    //Call again in 500 millisecond.
    GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_relative_multiply (GNUNET_TIME_UNIT_MILLISECONDS, 500), &keepaliveTask, gnunetInstance);
}




void GNUNet::Start()
{

    //TODO: Remove this sleep. Its here because we need so time after starting the process.
    //If we start too fast, we lose some messages.
    sleep(2);

    m_filesharing = new FileSharing();
    m_network = new NetworkManager();

    connect(m_network, &NetworkManager::connectedPeersChanged, this, &GNUNet::setConnectedPeers, Qt::QueuedConnection);


    static struct GNUNET_GETOPT_CommandLineOption options[] = {
        GNUNET_GETOPT_OPTION_END
    };

    char *const argv[] = {
        "cangote",
        // "-L", "DEBUG",
        NULL
    };



    char * teste = "cangote";
    int argc = (sizeof (argv) / sizeof (char *)) - 1;
    int ret =
            GNUNET_PROGRAM_run ((sizeof (argv) / sizeof (char *)) - 1,argv,
                                //GNUNET_PROGRAM_run ( 1, (char * const*)teste,
                                "cangote", "cangote help", options,
                                mainLoopCallback, this);



}

QElapsedTimer timer;


/**
 * Is the first function executed when GNUNet is running.
 */
void GNUNet::mainLoop(char *const *args, const char *cfgfile,
                      const struct GNUNET_CONFIGURATION_Handle *cfg)
{


    //status->setOkState();

    //Create our configuration
    m_config = GNUNET_CONFIGURATION_create ();
    GNUNET_CONFIGURATION_load (m_config, "cangote.conf");


    //A update function to process our messages
    GNUNET_SCHEDULER_add_now ( keepaliveTask, this);



    StartServices();


}

static void
arm_connection_state_change (void *cls,
                 int connected)
{
  char *service_list;
  GNUNet* gnunetInstance = (GNUNet*)cls;
  Q_ASSERT(cls);


  if (connected)
  {

      gnunetInstance->setConnected(true);
      /*
    service_list = format_service_list (0, NULL);
    GNUNET_FS_GTK_update_connection_indicator (cls, TRUE, service_list);
    GNUNET_free_non_null (service_list);
    GNUNET_ARM_request_service_list (arm, SERVICE_LIST_TIMEOUT,
                     &service_list_callback, cls);*/
  }
  else
  {
      gnunetInstance->setConnected(false);
      /*GNUNET_FS_GTK_update_connection_indicator (cls, FALSE,
          _("Can't connect to the Automatic Restart Manager service."));*/
  }

}

static void
service_status_change (void *cls,
               const char *service,
               enum GNUNET_ARM_ServiceStatus status)
{
  /* Very crude, we can probably do better.
   * Maybe keep a list of running services, and modify it in response
   * to service status changes, then update the indicator,
   * without requesting a list from ARM every goddamned time?
   */
 /* GNUNET_ARM_request_service_list (arm,
                   SERVICE_LIST_TIMEOUT,
                   &service_list_callback, cls);*/
}




void GNUNet::StartServices()
{
    m_network->start(m_config);
    m_filesharing->start(m_config);

    //Start arm
    arm = GNUNET_ARM_connect (m_config, &arm_connection_state_change, this);
    armon = GNUNET_ARM_monitor (m_config, service_status_change, this);
}

void GNUNet::ProcessEvents()
{
    QCoreApplication::processEvents();
    m_filesharing->ProcessEvents();
}

