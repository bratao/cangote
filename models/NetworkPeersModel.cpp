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


#include <sstream>
#include "core/gnunet/network/NetworkManager.h"
#include "models/NetworkPeersModel.h"



NetworkPeersModel::NetworkPeersModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(this, &NetworkPeersModel::addNewPeerSignal, this, &NetworkPeersModel::addNewPeerSlot, Qt::BlockingQueuedConnection);
}


int NetworkPeersModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int NetworkPeersModel::columnCount(const QModelIndex& parent) const
{
    return NB_PEERS_COLUMNS;
}

QModelIndex NetworkPeersModel::idToIndex(QString id){
    if(!m_lookupIndex.contains(id))
        return QModelIndex();
    int ind = m_lookupIndex[id];
    // it'd be 2 times faster using iterators, but it's just an example, so...
    return index(ind, 0);
}

bool NetworkPeersModel::contains(QString id)
{
    return m_lookupIndex.contains(id);
}


QVariant NetworkPeersModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    Peer* peer = m_data[index.row()];


    switch(role)
    {
    case ID:
        return peer->getId();
        break;
    case INCOMING_BANDWIDTH:
        return peer->getIncomingBandwidth();
        break;
    case OUTGOING_BANDWIDTH:
        return peer->getOutgoingBandwidth();
        break;
    case HOSTNAME:
        return peer->getHostname();
        break;
    case INCOMING_TRAFFIC:
        return peer->getIncomingTraffic();
        break;
    case OUTGOING_TRAFFIC:
        return peer->getOutgoingTraffic();
        break;
    case CONNECTED:
        return peer->isConnected();
        break;
    case TRANSPORT:
        return peer->getTransportName();
        break;
    default:
        return QVariant::Invalid;
    }


    return QVariant::Invalid;
}

QHash<int, QByteArray> NetworkPeersModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ID]                   = "id";
    roles[INCOMING_BANDWIDTH]   = "incomingBand";
    roles[OUTGOING_BANDWIDTH]   = "outgoingBand";
    roles[HOSTNAME]             = "hostname";
    roles[INCOMING_TRAFFIC]     = "incomingTraffic";
    roles[OUTGOING_TRAFFIC]     = "outgoingTraffic";
    roles[CONNECTED]            = "connected";
    roles[TRANSPORT]            = "transport";


    return roles;
}

void NetworkPeersModel::setPeerModified(int id)
{
    if(id < minIndex)
        minIndex = id;
    if(id > maxIndex)
        maxIndex = id;
}


void NetworkPeersModel::modifiedSlot(int indexRow)
{
    emit dataChanged(index(indexRow,0), index(indexRow,0));


}


Peer* NetworkPeersModel::addNewPeer(const struct GNUNET_PeerIdentity  *peerIdent, QString key)
{
    Peer* item = new Peer(peerIdent,key);
    emit addNewPeerSignal(item,key);
    return item;
}




Peer* NetworkPeersModel::addNewPeerSlot(Peer* item, QString key)
{


    if (m_lookupIndex.contains(key))
    {
        return NULL;
    }
    else
    {
        int index = m_data.count();
        beginInsertRows(QModelIndex(), index, index);
        m_data.append(item);
        item->setIndex(index);

        connect(item, &Peer::modifiedSignal,this, &NetworkPeersModel::modifiedSlot);

        m_lookupIndex[key] = index;
        endInsertRows();
        return item;
    }


}

Peer* NetworkPeersModel::getPeer(QString key)
{
    if (m_lookupIndex.contains(key))
    {
        return m_data[m_lookupIndex[key]];
    }
    else
        return NULL;
}

Peer* NetworkPeersModel::getPeer(QModelIndex index)
{

    if(GetCount() < index.row())
        return NULL;

    return m_data[index.row()];

}



int NetworkPeersModel::GetCount()
{
    return m_data.count();
}


/**
 * Get the total bandwidth
 * Delete the returned struct !
 **/
Bandwidth_Info_Struct* NetworkPeersModel::getTotalBandwidth()
{
    Bandwidth_Info_Struct* info = new Bandwidth_Info_Struct();
    int sumIncoming = 0;
    int sumOutgoing = 0;
    foreach(Peer* peer, m_data)
    {
        sumIncoming+= peer->getIncomingBandwidth();
        sumOutgoing+= peer->getOutgoingBandwidth();
    }

    info->incoming = sumIncoming;
    info->outgoing = sumOutgoing;

    return info;

}



