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
    m_launcher = new GNUNetLauncher(this);

    m_models = new Models(this);


    startGNUNet();



    m_armConnectTimer = new QTimer(this);
    connect(m_armConnectTimer, SIGNAL(timeout()), this, SLOT(armTimeOut()));



}



CangoteCore::~CangoteCore()
{
}


void CangoteCore::armTimeOut()
{

    qWarning() << "Connection lost, trying again in:" << m_armConnectTimer->interval() << "ms \n";

    m_launcher->relaunchServices();

    //Exponential backoff
    m_armConnectTimer->setInterval(m_armConnectTimer->interval()*2);


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
                    SLOT(Start()));

    m_gnunetThread->start();

    connect(m_gnunet, &GNUNet::connectedChanged, this, &CangoteCore::setConnected, Qt::QueuedConnection);
    connect(m_gnunet, &GNUNet::connectedPeersChanged, this, &CangoteCore::setConnectedPeers, Qt::QueuedConnection);
}

void CangoteCore::setConnectedPeers(int connected)
{

    m_connectedPeers = connected;
    emit connectedPeersChanged(m_connectedPeers);
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

