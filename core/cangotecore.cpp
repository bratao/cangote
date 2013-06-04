#include <QDebug>
#include "cangotecore.h"
#include "gnunet/gnunet.h"
#include "models/models.h"
#include "core/gnunet/launcher/gnunetlauncher.h"
#include "gnunet/network/NetworkManager.h"

#include <QTimer>

/* Static member variables */
CangoteCore* theApp;



CangoteCore::CangoteCore(QObject *parent) :
    QObject(parent)
{
    theApp = this;
    m_connected = false;
    m_connectedPeers = 0;
    m_numEstimateNodes = 0;
    m_outgoingBand = 0;
    m_incomingBand = 0;
    m_launcher = new GNUNetLauncher();

    m_models = new Models(this);


    //Launcher services
    startLauncher();


    //Timer to try to connect to arm
    m_armConnectTimer = new QTimer(this);
    connect(m_armConnectTimer, SIGNAL(timeout()), this, SLOT(armTimeOut()));

    //The processing timer
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(process()));
    m_timer->start(1000);

    //Finally start gnunet
    startGNUNet();

}



CangoteCore::~CangoteCore()
{
    m_launcher->stop();
}

void CangoteCore::process()
{
    //TODO: Timer !

}

void CangoteCore::armTimeOut()
{

    qWarning() << "Connection lost, trying again in:" << m_armConnectTimer->interval() << "ms \n";

    m_launcher->relaunchServices();

    //Exponential backoff
    m_armConnectTimer->setInterval(m_armConnectTimer->interval()*2);


}

void CangoteCore::startLauncher()
{
    //New thread where the will be run on.
    m_launcherThread = new QThread();

    m_launcher->moveToThread(m_launcherThread);

    // Call the start function after our thread is ready to run
    m_launcher->connect(m_launcherThread,
                    SIGNAL(started()),
                    SLOT(start()));

    m_launcherThread->start();


}

void CangoteCore::startGNUNet()
{
    //Create the Gnunet object
    m_gnunet = new GNUNet();

    //New thread where the Gnunet will be run on.
    m_gnunetThread = new QThread();

    m_gnunet->moveToThread(m_gnunetThread);

    // Call the start function after our thread is ready to run
    m_gnunet->connect(m_gnunetThread,
                    SIGNAL(started()),
                    SLOT(start()));

    m_gnunetThread->start();

    connect(m_gnunet, &GNUNet::connectedChanged, this, &CangoteCore::setConnected, Qt::QueuedConnection);
    connect(m_gnunet, &GNUNet::connectedPeersChanged, this, &CangoteCore::setConnectedPeers, Qt::QueuedConnection);
    connect(m_gnunet, &GNUNet::gnunetStarted, this, &CangoteCore::gnunetStarted, Qt::QueuedConnection);
}

void CangoteCore::gnunetStarted()
{

     connect(m_gnunet->network(), &NetworkManager::estimatedNodesChanged, this, &CangoteCore::setEstimatedNodes, Qt::QueuedConnection);
    connect(m_gnunet->network(), &NetworkManager::outgoingBandChanged, this, &CangoteCore::setOutgoingBand, Qt::QueuedConnection);
    connect(m_gnunet->network(), &NetworkManager::incomingBandChanged, this, &CangoteCore::setIncomingBand, Qt::QueuedConnection);

}


void CangoteCore::setConnected(bool connected)
{
    m_connected = connected;
    if(connected == false)
    {
        m_armConnectTimer->start(1000);
    }
    else
    {
        m_armConnectTimer->stop();
    }
    emit connectedChanged(m_connected);
}

