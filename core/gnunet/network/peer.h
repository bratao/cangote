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
#include <QVector>
#include "peerbandwidth.h"



class NetworkPeersModel;
class QTimer;
class Peer : public QObject
{


    typedef struct PeerAddress{
        QString address;
        QString strAddress;
        QString transport;
        QString expiration;
        Peer*  parent;//Just used in the callback
    }PeerAddress;

    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId)
    Q_PROPERTY(QString transportName READ getTransportName WRITE setTransportName)
    Q_PROPERTY(QString hostname READ getHostname WRITE setHostname)
    Q_PROPERTY(bool connected READ isConnected WRITE setConnected)
    Q_PROPERTY(int index READ getIndex WRITE setIndex)



public:
    //Id
    QString getId() const
    { return m_id; }
    void setId (QString id)
    {
        m_id = id;
        emit modifiedSignal(m_index);
    }

    //Transport Name
    QString getTransportName() const
    { return m_transportName; }
    void setTransportName(QString transportName)
    {
        m_transportName = transportName;
        emit modifiedSignal(m_index);
    }

    //Host Name
    QString getHostname() const
    { return m_hostname; }
    void setHostname(QString hostname)
    {
        m_hostname = hostname;
        emit modifiedSignal(m_index);
    }


    //Host Name
    bool isConnected() const
    { return m_connected; }
    void setConnected(bool connected)
    {
        m_connected = connected;
        emit modifiedSignal(m_index);
    }


    //Index
    int getIndex() const
    { return m_index; }
    void setIndex(int index)
    {
        m_index = index;
    }


public:
    explicit Peer(const struct GNUNET_PeerIdentity *m_peerIdent, QString m_id, QObject *parent = 0);



public:



    void setATSInfo(unsigned int bandIn, unsigned int bandOut);
    void addIncomingTraffic(int msgSize);
    unsigned int getIncomingTraffic();
    void addOutgoingTraffic(int msgSize);
    unsigned int getOutgoingTraffic();


    float getIncomingBandwidth();
    float getOutgoingBandwidth();



    QString getURI();
signals:

    void modifiedSignal(int index);
public slots:
    void modified();
    void timerSlot();
public:
    struct GNUNET_TRANSPORT_PeerIterateContext * m_peerActiveAddressCallback;

    /**
     * Handle for address to string conversion.
     */
    struct GNUNET_TRANSPORT_AddressToStringContext *m_tos;

    int m_gotAddress;

    void addAddress(const struct GNUNET_HELLO_Address *address, struct GNUNET_TIME_Absolute expiration);

    static void peerAddressStringConvertCallback (void *cls, const char *address);

    void peerNewAddressString(PeerAddress *peerAdd, const char *address);
private:

    QString m_id;
    int m_index;
    QString m_hostname;
    int m_atsBandwidthIn;
    int m_atsBandwidthOut;

    bool m_connected;
    QString m_transportName;

    PeerBandwidth* m_bandwidthIncoming;
    PeerBandwidth* m_bandwidthOutgoing;

    const struct GNUNET_PeerIdentity *m_peerIdent;

    QTimer *m_timer;

    QTime m_lastUpdated;

    QVector<PeerAddress*> m_addresses;



};

#endif // PEER_H
