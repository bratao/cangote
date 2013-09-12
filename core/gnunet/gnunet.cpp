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
#include "filesharing/publish/publish.h"
//#include "core/servicestatus.h"
#include "core/gnunet/filesharing/transfer/downloads.h"

#include <math.h>
#include <QElapsedTimer>
#include <QWaitCondition>



GNUNet::GNUNet(QObject *parent) :
    ServiceObject(parent)
{

    m_connected = false;

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
    gnunetInstance->processEvents();
    gnunetInstance->filesharing()->ProcessEvents();

    //Call again in 500 millisecond.
    GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_relative_multiply (GNUNET_TIME_UNIT_MILLISECONDS, 500), &keepaliveTask, gnunetInstance);
}

static void
armConnectionStateChangeCallback (void *cls,
                             int connected)
{
    char *service_list;
    GNUNet* gnunetInstance = (GNUNet*)cls;
    Q_ASSERT(cls);


    gnunetInstance->armConnectionStateChange(connected);

}

static void
serviceStatusChange (void *cls,
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




void GNUNet::start()
{


    m_filesharing = new FileSharing(this);
    m_network = new NetworkManager(this);
    m_publish = new Publish(this);

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
    char *fn;
    struct GNUNET_CRYPTO_EccPrivateKey *priv;

    //Create our configuration
    m_config = GNUNET_CONFIGURATION_create ();
    GNUNET_CONFIGURATION_load (m_config, "cangote.conf");

    //Get my information

    /* load private key */
    if (GNUNET_OK !=
            GNUNET_CONFIGURATION_get_value_filename (m_config, "PEER", "PRIVATE_KEY",
                                                     &fn))
    {
        qWarning() << QString("Could not find option `GNUNETD:HOSTKEYFILE' in configuration.\n");
        return;
    }
    if (NULL == (priv = GNUNET_CRYPTO_ecc_key_create_from_file (fn)))
    {
        qWarning() << QString("Loading hostkey from %1 failed.\n").arg(fn);
        GNUNET_free (fn);
        return;
    }
    GNUNET_free (fn);
    GNUNET_CRYPTO_ecc_key_get_public (priv, &m_myPublicKey);
    GNUNET_free (priv);
    GNUNET_CRYPTO_hash (&m_myPublicKey, sizeof (m_myPublicKey), &m_myPeerIdentity.hashPubKey);



    //A update function to process our messages
    GNUNET_SCHEDULER_add_now ( keepaliveTask, this);


    //Start arm
    m_arm = GNUNET_ARM_connect (m_config, &armConnectionStateChangeCallback, this);
    m_armon = GNUNET_ARM_monitor (m_config, serviceStatusChange, this);


    //Start the services when arm is connected
    connect(this,&GNUNet::gnunetConnected, this, &GNUNet::startServices);


}

void GNUNet::armConnectionStateChange (int connected)
{

    if (connected)
    {

        setConnected(true);

        emit gnunetConnected();

        //TODO: Implement working services list retrival.
    }
    else
    {
        setConnected(false);
        qWarning() << tr("Failed to connect to GNUNet arm");
    }

}



void GNUNet::startServices()
{
    m_network->start(m_config);
    m_filesharing->start(m_config);



    emit gnunetStarted();
}

void GNUNet::processEvents()
{
    QCoreApplication::processEvents();
    m_filesharing->ProcessEvents();
}


GNUNET_CRYPTO_EccPublicKey GNUNet::myPublicKey() const
{
    return m_myPublicKey;
}

void GNUNet::setMyPublicKey(const GNUNET_CRYPTO_EccPublicKey &myPublicKey)
{
    m_myPublicKey = myPublicKey;
}
