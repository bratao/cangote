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
#include "core/gnunet/filesharing/transfer/downloads.h"
#include "network/NetworkManager.h"
#include "filesharing/publish/publish.h"
#include "filesharing/filesharing.h"

#include "cangote.h"
#include "core/cangotecore.h"
#include "preferences/preferences.h"

#include <math.h>
#include <QElapsedTimer>
#include <QWaitCondition>


/***********************************
 * START STATIC CALLBACKS
 ***********************************/

/**
 * Static function.
 * The first function executed when GNUNet is running.
 */
void GNUNet::mainLoopCallback(void *cls, char *const *args, const char *cfgfile,
                              const struct GNUNET_CONFIGURATION_Handle *cfg)
{
    //Retrive our main funtion
    GNUNet* gnunetInstance = (GNUNet*)cls;
    Q_ASSERT(gnunetInstance);


    //Call our main loop
    gnunetInstance->mainLoop(args,cfgfile,cfg);

}

static void
teste (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc)
{

}

/**
 * Static function
 * Called to process our internal messages
 */
void GNUNet::keepaliveTaskCallback (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc)
{
    Q_UNUSED(tc);

    //Retrive our main funtion
    Q_ASSERT(cls);
    GNUNet* gnunetInstance = (GNUNet*)cls;

    //Process the events
    gnunetInstance->processEvents();

    //Call again in 500 millisecond.
    GNUNET_SCHEDULER_add_delayed (GNUNET_TIME_relative_multiply (GNUNET_TIME_UNIT_MILLISECONDS, 500), &keepaliveTaskCallback, gnunetInstance);
}


static void armConnectionStateChangeCallback (void *cls,
                                              int connected)
{
    GNUNet* gnunetInstance = (GNUNet*)cls;
    Q_ASSERT(cls);


    gnunetInstance->armConnectionStateChange(connected);

}

static void
serviceStatusChange (void *cls,
                     const char *service,
                     enum GNUNET_ARM_ServiceStatus status)
{
    Q_UNUSED(cls);
    Q_UNUSED(service);
    Q_UNUSED(status);

    //TODO:: Monitor services status change (#12)

}

/***********************************
 * END STATIC CALLBACKS
 ***********************************/


GNUNet::GNUNet(QObject *parent) :
    ServiceObject(parent)
{

    m_connected = false;
    m_myPeer = new GNUNET_PeerIdentity;


}

GNUNet::~GNUNet()
{
  delete m_myPeer;
}

/**
 * Start GNUnet
 */

void GNUNet::start()
{


    m_filesharing = new FileSharing(this);
    m_network = new NetworkManager(this);
    m_publish = new Publish(this);

    connect(m_network, &NetworkManager::connectedPeersChanged, this, &GNUNet::setConnectedPeers, Qt::QueuedConnection);


    static struct GNUNET_GETOPT_CommandLineOption options[] = {
        GNUNET_GETOPT_OPTION_END
    };


    QString gnunetConfig = thePrefs->getGNUNetConfig();
    QByteArray byteArray = gnunetConfig.toUtf8();
    const char* cString = byteArray.constData();


    const char *const argv[] = {
        "Cangote",
         "-c", cString,
        NULL
    };

    GNUNET_PROGRAM_run ((sizeof (argv) / sizeof (char *)) - 1,(char *const*)argv,
                        "Cangote", "cangote helper", options,
                        mainLoopCallback, this);


}

/**
 * It's the first function executed when GNUNet is running.
 */
void GNUNet::mainLoop(char *const *args, const char *cfgfile,
                      const struct GNUNET_CONFIGURATION_Handle *cfg)
{
    Q_UNUSED(args);
    Q_UNUSED(cfgfile);
    Q_UNUSED(cfg);



    char *privateKeyFileName;
    GNUNET_CRYPTO_EddsaPrivateKey *priv;

    //Create our configuration
    m_config = GNUNET_CONFIGURATION_create ();
    GNUNET_CONFIGURATION_load (m_config, cfgfile);

    //Get my information

    //load private key
    if (GNUNET_OK !=
            GNUNET_CONFIGURATION_get_value_filename (m_config, "PEER", "PRIVATE_KEY",
                                                     &privateKeyFileName))
    {
        qWarning() << QString("Could not find option `GNUNETD:HOSTKEYFILE' in configuration.\n");
        return;
    }
    if (NULL == (priv = GNUNET_CRYPTO_eddsa_key_create_from_file( (privateKeyFileName))))
    {
        qWarning() << QString("Loading hostkey from %1 failed.\n").arg(privateKeyFileName);
        GNUNET_free (privateKeyFileName);
        return;
    }

    GNUNET_free (privateKeyFileName);
    GNUNET_CRYPTO_eddsa_key_get_public(priv, &m_myPeer->public_key);

    char* str = GNUNET_CRYPTO_eddsa_public_key_to_string(&m_myPeer->public_key);
    setMyPublicKeyStr(QString(str));
    GNUNET_free (str);
    GNUNET_free (priv);


    //A update function to process our messages
    GNUNET_SCHEDULER_add_now ( keepaliveTaskCallback, this);


    //Start arm
    m_arm = GNUNET_ARM_connect (m_config, &armConnectionStateChangeCallback, this);
    m_armon = GNUNET_ARM_monitor (m_config, serviceStatusChange, this);


    //Start the services when arm is connected
    connect(this,&GNUNet::gnunetConnected, this, &GNUNet::startServices);


}

/**
 * Signal that a change in our connection happened
 */
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

/**
 * Start the services such as filesharing
 */

void GNUNet::startServices()
{
    m_network->start(m_config);
    m_filesharing->start(m_config);



    emit gnunetStarted();
}

/**
 * Process our internal pending messages.
 */
void GNUNet::processEvents()
{
    QCoreApplication::processEvents();
    m_filesharing->ProcessEvents();
}


GNUNET_PeerIdentity* GNUNet::myPeer() const
{
    return m_myPeer;
}

