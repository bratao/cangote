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


#include "peer.h"
//#include "core/cangote.h"
#include "models/NetworkPeersModel.h"
#include <QTimer>
#include <QTime>
#include <QDebug>

#define TIMER_FREQUENCY 1000


Peer::Peer(const struct GNUNET_PeerIdentity *peerIdent, QString id, QObject *parent) :
    QObject(parent)
{
    m_id = id;
    m_peerIdent = peerIdent;

    m_connected = false;
    m_transportName = "";
    m_peerActiveAddressCallback = NULL;
    m_atsBandwidthIn = 0;
    m_atsBandwidthOut = 0;
    m_gotAddress = false;
    m_tos = NULL;
    m_palc = NULL;


    m_bandwidthIncoming = new PeerBandwidth();
    m_bandwidthOutgoing = new PeerBandwidth();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,this, &Peer::timerSlot);

}


void Peer::timerSlot()
{
    modified();
    m_timer->stop();
}

void Peer::modified()
{

    //model->peerModifiedSlot(id);
    //model->setPeerModified(modelIndex);
    m_lastUpdated = QTime::currentTime();
    emit modifiedSignal(m_index);

}




QString Peer::getURI()
{
    /*
    struct GetUriContext *guc;
        char *pkey;

        guc = GNUNET_malloc (sizeof (struct GetUriContext));
        pkey = GNUNET_CRYPTO_rsa_public_key_to_string (&my_public_key);
        GNUNET_asprintf (&guc->uri,
                 "%s%s",
                 HELLO_URI_PREFIX,
                 pkey);
        GNUNET_free (pkey);
        GPI_plugins_load (cfg);
        pic = GNUNET_PEERINFO_iterate (peerinfo, &my_peer_identity,
                       TIMEOUT,
                       &print_my_uri, guc);
        get_uri = GNUNET_NO;
        */
    //FIXME:: Implement get URL
    return "Not implemented";
}



void Peer::setATSInfo(unsigned int bandIn,unsigned int bandOut)
{
    m_atsBandwidthIn = bandIn;
    m_atsBandwidthOut = bandOut;
    modified();
}

void Peer::addIncomingTraffic(int msgSize)
{
    m_bandwidthIncoming->addMsg(msgSize);
    modified();
}

unsigned int Peer::getIncomingTraffic()
{
    return m_bandwidthIncoming->getTotalTraffic();
}


void Peer::addOutgoingTraffic(int msgSize)
{
    m_bandwidthOutgoing->addMsg(msgSize);
    modified();
}

unsigned int Peer::getOutgoingTraffic()
{
    return m_bandwidthOutgoing->getTotalTraffic();
}

float Peer::getIncomingBandwidth()
{
    float band = m_bandwidthIncoming->getBandwidth();

    //Set to update the calculation in case we have any traffic
    if ((band > 1) && !m_timer->isActive()){
        qWarning() << "Starting incoming timer";
        m_timer->start(TIMER_FREQUENCY);
    }

    return band;
}

float Peer::getOutgoingBandwidth()
{
    float band = m_bandwidthOutgoing->getBandwidth();

    //Set to update the calculation in case we have any traffic
    if ((band > 1) && !m_timer->isActive()){
        qWarning() << "Starting outgoing timer";
        m_timer->start(TIMER_FREQUENCY);
    }

    return band;
}

