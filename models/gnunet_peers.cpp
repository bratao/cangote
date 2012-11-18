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

#include "models/gnunet_peers.h"
#include <sstream>
#include "core/gnunet/network/gnetwork.h"
#include "utils/misc.h"
#include "core/cangote.h"

#define REFRESH_RATE 500

GNUNetPeersModel::GNUNetPeersModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    cacheTimer = NULL;

    cacheTimer = new QTimer(this);
    connect(cacheTimer, SIGNAL(timeout()), this, SLOT(process()));
    cacheTimer->start(REFRESH_RATE);

}


int GNUNetPeersModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int GNUNetPeersModel::columnCount(const QModelIndex& parent) const
{
    return NB_PEERS_COLUMNS;
}

QModelIndex GNUNetPeersModel::idToIndex(QString id){
    if(!m_lookupIndex.contains(id))
        return QModelIndex();
    int ind = m_lookupIndex[id];
    // it'd be 2 times faster using iterators, but it's just an example, so...
    return index(ind, 0);
}

bool GNUNetPeersModel::contains(QString id)
{
    return m_lookupIndex.contains(id);
}


QVariant GNUNetPeersModel::data(const QModelIndex& index, int role) const
{
  if(role == Qt::DisplayRole)
    {

       switch(index.column())
       {
           case ID:
               return m_data[index.row()]->getId();
               break;
           case INCOMING_BANDWIDTH:
               return m_data[index.row()]->getIncomingBandwidth();
               break;
           case OUTGOING_BANDWIDTH:
               return m_data[index.row()]->getOutgoingBandwidth();
               break;
           case HOSTNAME:
               return m_data[index.row()]->getHostname();
               break;
           case INCOMING_TRAFFIC:
               return m_data[index.row()]->getIncomingTraffic();
               break;
           case OUTGOING_TRAFFIC:
               return m_data[index.row()]->getOutgoingTraffic();
               break;
           case CONNECTED:
               return m_data[index.row()]->connected;
               break;
           case TRANSPORT:
               return m_data[index.row()]->getTransportName();
               break;
           default:
                 return QVariant::Invalid;
       }

    }

  return QVariant::Invalid;
}

QVariant GNUNetPeersModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case ID:
                    return tr("ID");
                    break;

                case INCOMING_BANDWIDTH:
                    return tr("Bandwidth In");
                    break;

                case OUTGOING_BANDWIDTH:
                    return tr("Bandwidth Out");
                    break;
                case HOSTNAME:
                    return tr("Address");
                    break;
                case INCOMING_TRAFFIC:
                    return tr("Traffic in");
                    break;
                case OUTGOING_TRAFFIC:
                    return tr("Traffic Out");
                    break;
                case CONNECTED:
                    return tr("Connected");
                    break;
                case TRANSPORT:
                    return tr("Transport Name");
                    break;

                default:
                    return QVariant();
            }
        }
        return QVariant();
}


void GNUNetPeersModel::setPeerModified(int id)
{
    if(id < minIndex)
        minIndex = id;
    if(id > maxIndex)
        maxIndex = id;
}


void GNUNetPeersModel::process()
{
    //No changes
    if(minIndex > maxIndex)
        return;

    emit dataChanged(index(minIndex, 0), index(maxIndex, NB_PEERS_COLUMNS-1));

    minIndex = GetCount();
    maxIndex = 0;
}


Peer* GNUNetPeersModel::AddNewPeer(const struct GNUNET_PeerIdentity  *peerIdent, QString key)
{


    if (m_lookupIndex.contains(key))
    {
      return NULL;
    }
    else
    {
        int index = m_data.count();
        beginInsertRows(QModelIndex(), index, index);
        Peer* item = new Peer(peerIdent,key,this,index,this);

        m_data.append(item);

        //connect(item, SIGNAL(modifiedSignal(QString)),SLOT(peerModifiedSlot(QString)));

        m_lookupIndex[key] = index;
        endInsertRows();
        return item;
    }


}

Peer* GNUNetPeersModel::getPeer(QString key)
{
    if (m_lookupIndex.contains(key))
    {
        return m_data[m_lookupIndex[key]];
    }
    else
        return NULL;
}

Peer* GNUNetPeersModel::getPeer(QModelIndex index)
{

    if(GetCount() < index.row())
        return NULL;

    return m_data[index.row()];

}



int GNUNetPeersModel::GetCount()
{
  return m_data.count();
}


/**
 * Get the total bandwidth
 * Delete the returned struct !
 **/
Bandwidth_Info_Struct* GNUNetPeersModel::getTotalBandwidth()
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


