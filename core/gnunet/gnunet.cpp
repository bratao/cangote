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


    m_filesharing = new FileSharing();
    m_network = new NetworkManager();

    //status->setChildrenService(filesharing->getStatus());
    // status->setChildrenService(network->getStatus());


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


void GNUNet::StartServices()
{
    m_network->start(m_config);
    m_filesharing->start(m_config);
}

void GNUNet::ProcessEvents()
{
    QCoreApplication::processEvents();
    m_filesharing->ProcessEvents();
}

