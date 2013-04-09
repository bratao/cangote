#include <QDebug>
#include "cangotecore.h"
#include "gnunet/gnunet.h"
#include "models/models.h"
#include "core/gnunet/launcher/gnunetlauncher.h"

/* Static member variables */
CangoteCore* theApp;



CangoteCore::CangoteCore(QObject *parent) :
    QObject(parent)
{
    theApp = this;

    m_models = new Models(this);
    startGNUNet();
    m_launcher = new GNUNetLauncher(this);

}


CangoteCore::~CangoteCore()
{
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

    //connect(m_gnunet->getStatus(),SIGNAL(stateChangedSignal(int)),SLOT(GNUNetStatusChangedSlot(int)));
}
