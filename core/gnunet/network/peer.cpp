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
#include "core/cangote.h"
#include "models/gnunet_peers.h"

Peer::Peer(const struct GNUNET_PeerIdentity *peerIdent, QString id,GNUNetPeersModel* model,int modelIndex, QObject *parent) :
  QObject(parent)
{
    this->id = id;
    this->model = model;
    this->modelIndex = modelIndex;
    connected = false;
    transportUsed = "";
    peerActiveAddressCallback = NULL;

    ATS_bandwidth_in = 0;
    ATS_bandwidth_out = 0;
    got_address = false;
    tos = NULL;
    palc = NULL;


    bandIncoming = new PeerBandwidth();
    bandOutgoing = new PeerBandwidth();



    this->peerIdent = peerIdent;

}


void Peer::modified()
{

    //model->peerModifiedSlot(id);
    model->setPeerModified(modelIndex);
  //emit modifiedSignal(id);


}



QString Peer::getId()
{
    return id;
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
    return "Not implamented";
}


QString Peer::getHostname()
{
    return hostname;
}

void Peer::setHostname(QString hostname)
{
    this->hostname = hostname;
    modified();
}

void Peer::setATSInfo(unsigned int bandIn,unsigned int bandOut)
{
    this->ATS_bandwidth_in = bandIn;
    this->ATS_bandwidth_out = bandOut;
    modified();
}

void Peer::addIncomingTraffic(int msgSize)
{
    bandIncoming->addMsg(msgSize);
    modified();
}

unsigned int Peer::getIncomingTraffic()
{
    return bandIncoming->getTotalTraffic();
}


void Peer::addOutgoingTraffic(int msgSize)
{
    bandOutgoing->addMsg(msgSize);
    modified();
}

unsigned int Peer::getOutgoingTraffic()
{
    return bandOutgoing->getTotalTraffic();
}

void Peer::setConnected()
{
    connected =  true;
    modified();
}

void Peer::setDisconnected()
{
    connected = false;
    modified();
}

bool Peer::isConnected()
{
    return connected;
}

void Peer::setTransportName(QString name)
{
    this->transportUsed = name;
    modified();
}

QString Peer::getTransportName()
{
    return this->transportUsed;
}

float Peer::getIncomingBandwidth()
{
    return bandIncoming->getBandwidth();
}

float Peer::getOutgoingBandwidth()
{
    return bandOutgoing->getBandwidth();
}

