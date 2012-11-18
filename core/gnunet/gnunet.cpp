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

#include "core/cangote.h"
#include "gnunet.h"
#include "filesharing/filesharing.h"
#include "network/gnetwork.h"
#include "core/servicestatus.h"
#include "core/gnunet/filesharing/transfer/downloads.h"

#include <math.h>
#include <QElapsedTimer>
#include <QWaitCondition>



//Initialize static
GNUNET_CONFIGURATION_Handle * GNUNet::config;



GNUNet::GNUNet(QObject *parent) :
    QObject(parent)
{

    status = new ServiceStatus();

}


/**
 * Static callback. Is the first function executed when GNUNet is running.
 */
void GNUNet::mainLoopCallback(void *cls, char *const *args, const char *cfgfile,
                       const struct GNUNET_CONFIGURATION_Handle *cfg)
{


    GNUNet* gnunetInstance = (GNUNet*)cls;
    Q_ASSERT(cls);

    gnunetInstance->mainLoop(args,cfgfile,cfg);




}




/**
 * Static task to process our messages.Is needed as the GNUNet loop locks our internal qt Loop.
 */
void GNUNet::keepaliveTask (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc)
{
    GNUNet* gnunetInstance = (GNUNet*)cls;
    Q_ASSERT(cls);

    //Process the events
    gnunetInstance->ProcessEvents();

    //Call again in 500 millisecond.
    GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_relative_multiply (GNUNET_TIME_UNIT_MILLISECONDS, 700), &keepaliveTask, gnunetInstance);
}




void GNUNet::Start()
{


    filesharing = new FileSharing();
    network = new GNetwork();

    status->setChildrenService(filesharing->getStatus());
    status->setChildrenService(network->getStatus());


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

static int
gnunet_W32_select (void *cls, struct GNUNET_NETWORK_FDSet *rfds,
                   struct GNUNET_NETWORK_FDSet *wfds,
                   struct GNUNET_NETWORK_FDSet *efds,
                   const struct GNUNET_TIME_Relative timeout)
{
    GNUNet* gnunetInstance = (GNUNet*)cls;

    if(!timer.hasExpired(150))
    {
       // gWarn("Will sleep !");
        Sleep(150- timer.elapsed());
    }


    //Process the events
    gnunetInstance->ProcessEvents();


    //gWarn("Processing the events !");
    //Reset timer
    timer.start();
    return GNUNET_NETWORK_socket_select(rfds,wfds,efds,timeout);

}

/**
 * Is the first function executed when GNUNet is running.
 */
void GNUNet::mainLoop(char *const *args, const char *cfgfile,
                       const struct GNUNET_CONFIGURATION_Handle *cfg)
{


    status->setOkState();

    //Create our configuration
    config = GNUNET_CONFIGURATION_create ();
    GNUNET_CONFIGURATION_load (config, "cangote.conf");


    //A update function to process our messages
    GNUNET_SCHEDULER_add_now ( keepaliveTask, this);

    //Set our Scheduler on W32
#ifdef Q_WS_WIN
   // GNUNET_SCHEDULER_set_select (&gnunet_W32_select, this);
#endif



    StartServices();


}


void GNUNet::StartServices()
{
    network->start(config);
    filesharing->start(config);
}


GNUNetPeersModel* GNUNet::getPeersModel()
{
    return network->getModel();
}



void GNUNet::ProcessEvents()
{
    QCoreApplication::processEvents();
}

ServiceStatus* GNUNet::getStatus()
{
    return status;
}

GNUnetFsSearchModel* GNUNet::getSearchModel()
{
    return filesharing->searchModel;
}

DownloadModel* GNUNet::getDownloadsModel()
{
    return filesharing->downloads->model;
}

