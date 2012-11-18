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

#ifndef GNUNETNETWORKPEERSMODEL_H
#define GNUNETNETWORKPEERSMODEL_H

#include <QAbstractTableModel>
#include <QTimer>


class Peer;
class GNUNetPeersModel : public QAbstractTableModel
{
    Q_OBJECT


public:
  enum PeerColumn { ID, INCOMING_BANDWIDTH, OUTGOING_BANDWIDTH, HOSTNAME, INCOMING_TRAFFIC, OUTGOING_TRAFFIC,
                    CONNECTED, TRANSPORT, NB_PEERS_COLUMNS };


public:
    explicit GNUNetPeersModel(QObject *parent = 0);
    Peer *AddNewPeer(const struct GNUNET_PeerIdentity *peerIdent, QString key);
    int GetCount();
    Peer *getPeer(QString key);
    bool contains(QString id);

    struct Bandwidth_Info_Struct *getTotalBandwidth();
    Peer *getPeer(QModelIndex index);

    void setPeerModified(int id);

signals:
    
public slots:
            void process();

private:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex idToIndex(QString id);

private:
        QHash<QString, int> m_lookupIndex;
        int minIndex;
        int maxIndex;
        QList<Peer*> m_data;
        QTimer *cacheTimer;
    
};

#endif // GNUNETNETWORKPEERSMODEL_H
