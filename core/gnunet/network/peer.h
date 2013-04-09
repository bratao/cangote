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

#ifndef PEER_H
#define PEER_H

#include <QObject>
#include <QString>
#include "peerbandwidth.h"



class NetworkPeersModel;
class Peer : public QObject
{
  Q_OBJECT
public:
  explicit Peer(const struct GNUNET_PeerIdentity *peerIdent, QString id, QObject *parent = 0);
  


public:

    /**
     * Handle to an active lookup for addresses of this peer, or NULL.
     */
    struct GNUNET_TRANSPORT_PeerIterateContext *palc;

    /**
     * Handle for address to string conversion.
     */
    struct GNUNET_TRANSPORT_AddressToStringContext *tos;

    /**
     * Did we get any address?
     */

    QString getId();

    QString getHostname();
    void setHostname(QString hostname);

    int ATS_bandwidth_in;
    int ATS_bandwidth_out;
    int got_address;


    void setATSInfo(unsigned int bandIn, unsigned int bandOut);
    void addIncomingTraffic(int msgSize);
    unsigned int getIncomingTraffic();
    void addOutgoingTraffic(int msgSize);
    unsigned int getOutgoingTraffic();
    bool connected;
    QString transportUsed;
    void setConnected();
    bool isConnected();
    void setDisconnected();
    void setTransportName(QString name);
    QString getTransportName();
    struct GNUNET_TRANSPORT_PeerIterateContext * peerActiveAddressCallback;
    float getIncomingBandwidth();
    void modified();
    float getOutgoingBandwidth();
    QString getURI();
signals:

    void modifiedSignal(QString id);
public slots:
  
private:

    PeerBandwidth* bandIncoming;
    PeerBandwidth* bandOutgoing;

    const struct GNUNET_PeerIdentity *peerIdent;

    QString id;

    QString hostname;




};

#endif // PEER_H
