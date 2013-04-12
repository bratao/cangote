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

#ifndef PEERSINFO_H
#define PEERSINFO_H

#include <QObject>
#include <QHash>
#include <stdint.h>

#include "peer.h"
#include "service.h"


struct Bandwidth_Info_Struct{

    int incoming;
    int outgoing;
};


class NetworkPeersModel;
class NetworkManager : public ServiceObject
{
    Q_OBJECT


public:



    static void
    peerAddressCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                  const struct GNUNET_HELLO_Address *address);
    static void
    peerAddressStringConvertCallback (void *cls, const char *address);



    //////////////////////////


public:
    explicit NetworkManager(QObject *parent = 0);


public:
    void peerinfoProcessor(const struct GNUNET_PeerIdentity *peer,
                           const struct GNUNET_HELLO_Message *hello,
                           const char *err_msg);
    void peerATSstatusChange (const struct GNUNET_HELLO_Address *address,
                              struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                              struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                              const struct GNUNET_ATS_Information *m_ats,
                              uint32_t ats_count);

    void       newPeerAddress (const struct GNUNET_PeerIdentity *peer,
                                const struct GNUNET_HELLO_Address *address);
    void       peerNewAddressString (QString id, const char *address);



    static void peerinfoProcessorCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                           const struct GNUNET_HELLO_Message *hello,
                                           const char *err_msg);


    static void ATSstatusChangeCallback (void *cls,
                                    const struct GNUNET_HELLO_Address *address,
                                    struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                                    struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                                    const struct GNUNET_ATS_Information *m_ats,
                                    uint32_t ats_count);


    static void
    checkNseMessageCallback (void *cls, struct GNUNET_TIME_Absolute timestamp,
                       double estimate, double std_dev);

    void checkNseMessage(GNUNET_TIME_Absolute timestamp, double estimate, double std_dev);


    void start(struct GNUNET_CONFIGURATION_Handle *config);

    /**
     * Handle to ATS service.
     */
    static struct GNUNET_ATS_PerformanceHandle *m_ats;

    /**
     * Handle for our notifications from peerinfo about new peers.
     */
    static struct GNUNET_PEERINFO_NotifyContext *m_peerInfo;


    struct GNUNET_CONFIGURATION_Handle *m_config;



    static int incomeMsgCallback(void *cls, const struct GNUNET_PeerIdentity *other, const struct GNUNET_MessageHeader *message,
                                 const struct GNUNET_ATS_Information *atsi, unsigned int atsi_count);

    static int outcomeMsgCallback(void *cls, const struct GNUNET_PeerIdentity *other, const struct GNUNET_MessageHeader *message,
                                  const struct GNUNET_ATS_Information *atsi, unsigned int atsi_count);
    int incomeMsg(const GNUNET_PeerIdentity *other, const GNUNET_MessageHeader *message, const GNUNET_ATS_Information *atsi, unsigned int atsi_count);
    int outcomeMsg(const GNUNET_PeerIdentity *other, const GNUNET_MessageHeader *message, const GNUNET_ATS_Information *atsi, unsigned int atsi_count);
    static void notifyConnectCallback(void *cls, const GNUNET_PeerIdentity *peer, const GNUNET_ATS_Information *m_ats, uint32_t ats_count);
    static void notifyDisconnectCallback(void *cls, const GNUNET_PeerIdentity *peer);
    void notifyConnect(const GNUNET_PeerIdentity *peerIdent, const GNUNET_ATS_Information *m_ats, uint32_t ats_count);
    void notifyDisconnect(const GNUNET_PeerIdentity *peerIdent);
    void gotActiveAddress(const GNUNET_PeerIdentity *peerIdent, const GNUNET_HELLO_Address *address);
    static void gotActiveAddressCallback(void *cls, const GNUNET_PeerIdentity *peer, const GNUNET_HELLO_Address *address);

    int getIncomingBand();
    int getOutgoingBand();
    int getEstimateNetworkSize();
    int getConnectedNodes();
    //ServiceStatus *getStatus();
private:
        void getGlobalBandwidth();

public slots:

private:


    //Statistics
private:
    int m_connectionsCounter;
    int numEstimateNodes;
    int outcomingBand;
    int incomingBand;
    QTime nextBandwidthRetrive;


};

#endif // PEERSINFO_H
