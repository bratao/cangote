#include "status.h"
#include "core/cangotecore.h"
#include "gnunet/network/NetworkManager.h"
#include "gnunet/gnunet.h"
Status::Status(QObject *parent) :
    QObject(parent)
{
    m_connectedPeers = 0;
    m_numEstimateNodes = 0;
    m_outgoingBand = 0;
    m_incomingBand = 0;
    m_isPublishing = false;
    m_publishingPercentage = 0.0;

    connect(theApp->gnunet(), &GNUNet::connectedPeersChanged, this, &Status::setConnectedPeers, Qt::QueuedConnection);
    connect(theApp->gnunet(), &GNUNet::gnunetStarted, this, &Status::gnunetStarted, Qt::QueuedConnection);
}

void Status::gnunetStarted()
{



}
