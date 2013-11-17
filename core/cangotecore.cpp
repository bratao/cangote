#include <QDebug>
#include "cangotecore.h"
#include "gnunet/gnunet.h"
#include "models/models.h"
#include "status.h"
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

    m_launcher = new GNUNetLauncher();

    m_models = new Models(this);



    //Launcher services
    startLauncher();


    //Timer to try to connect to arm
    m_armConnectTimer = new QTimer(this);
    m_armConnectTimer->setSingleShot(true);
    connect(m_armConnectTimer, &QTimer::timeout, this, &CangoteCore::armTimeOut);


    //The processing timer
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CangoteCore::process);
    m_timer->start(1000);

    //Finally start gnunet
    startGNUNet();

    //Start the Status. It need to load after all
    m_status = new Status(this);

}



CangoteCore::~CangoteCore()
{
    m_launcher->stop();
    m_models = NULL;
}

void CangoteCore::process()
{
    //TODO: Timer !

}

void CangoteCore::armTimeOut()
{

    qWarning() << "Connection lost, trying again in:" << m_armConnectTimer->interval() << "ms \n";

    if(m_connected == false)
      m_launcher->relaunchServices();

    //Exponential backoff
    m_armConnectTimer->start(m_armConnectTimer->interval()*2);


}

void CangoteCore::startLauncher()
{
    //New thread where the will be run on.
    m_launcherThread = new QThread();

    m_launcher->moveToThread(m_launcherThread);

    // Call the start function after our thread is ready to run
    connect(m_launcherThread,
                    &QThread::started,
                    m_launcher,
                    &GNUNetLauncher::start);

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
    connect(m_gnunetThread,
                      &QThread::started,
                      m_gnunet,
                      &GNUNet::start);

    m_gnunetThread->start();

    connect(m_gnunet, &GNUNet::connectedChanged, this, &CangoteCore::setConnected, Qt::QueuedConnection);

}



void CangoteCore::setConnected(bool connected)
{
    m_connected = connected;
    if((connected == false) && !m_armConnectTimer->isActive())
    {
        qWarning() << "Starting Gnunet again;";
        m_armConnectTimer->start(4000);
    }
    else if (m_armConnectTimer->isActive())
    {
        m_armConnectTimer->stop();
    }
    emit connectedChanged(m_connected);
}

