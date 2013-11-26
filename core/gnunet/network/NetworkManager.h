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
class GnunetTransportPlugins;
class NetworkManager : public ServiceObject
{
  Q_OBJECT
  Q_PROPERTY(int connectedPeers READ getConnectedPeers WRITE setConnectedPeers NOTIFY connectedPeersChanged)
  Q_PROPERTY(int estimatedNodes READ getEstimatedNodes WRITE setEstimatedNodes NOTIFY estimatedNodesChanged)
  Q_PROPERTY(int outgoingBand READ getOutgoingBand WRITE setOutgoingBand NOTIFY outgoingBandChanged)
  Q_PROPERTY(int incomingBand READ getIncomingBand WRITE setIncomingBand NOTIFY incomingBandChanged)
  Q_PROPERTY(QString myHelloStr READ myHelloStr WRITE setMyHelloStr NOTIFY myHelloStrChanged)

public: 

  //Connected peers
  int getConnectedPeers() const
  { return m_connectedPeers; }
  void setConnectedPeers(int connected)
  {
    m_connectedPeers = connected;
    emit connectedPeersChanged(connected);
  }

  //Estimated Nodes
  int getEstimatedNodes() const
  {
    return m_numEstimateNodes;
  }
  void setEstimatedNodes(int nodes)
  {
    m_numEstimateNodes = nodes;
    emit estimatedNodesChanged(nodes);
  }

  //Outgoing Band
  int getOutgoingBand() const
  { return m_outgoingBand; }
  void setOutgoingBand(int outgoing)
  {
    m_outgoingBand = outgoing;
    emit outgoingBandChanged(outgoing);
  }

  //Incoming band
  int getIncomingBand() const
  { return m_incomingBand; }
  void setIncomingBand(int incoming)
  {
    m_incomingBand = incoming;
    emit incomingBandChanged(incoming);
  }

  //Public Key Str
  QString myHelloStr() const
  { return m_myHelloStr; }
  void setMyHelloStr(QString hello)
  {
    m_myHelloStr = hello;
    emit myHelloStrChanged(hello);
  }


signals:
  void connectedPeersChanged(int connected);
  void estimatedNodesChanged(int nodes);
  void outgoingBandChanged(int outgoing);
  void incomingBandChanged(int incoming);
  void myHelloStrChanged(QString hello);


  //////////////////////////


public:
  explicit NetworkManager(QObject *parent = 0);



  /**
     *Static callbacks to GNUNnet functions.
     */
private:
  static void checkNseMessageCallback (void *cls, struct GNUNET_TIME_Absolute timestamp,
                                       double estimate, double std_dev);

  static int incomeMsgCallback(void *cls, const struct GNUNET_PeerIdentity *other,
                               const struct GNUNET_MessageHeader *message);

  static int outcomeMsgCallback(void *cls, const struct GNUNET_PeerIdentity *other,
                                const struct GNUNET_MessageHeader *message);

  static void notifyConnectCallback(void *cls, const struct GNUNET_PeerIdentity *peer);

  static void notifyDisconnectCallback(void *cls, const struct GNUNET_PeerIdentity *peer);

  static void gotActiveAddressCallback(void *cls, const struct GNUNET_PeerIdentity *peer,
                                       const struct GNUNET_HELLO_Address *address);

  static void peerinfoProcessorCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                         const struct GNUNET_HELLO_Message *hello,
                                         const char *err_msg);


  static void ATSstatusChangeCallback (void *cls,
                                       const struct GNUNET_HELLO_Address *address, int address_active,
                                       struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                                       struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                                       const struct GNUNET_ATS_Information *m_ats,
                                       uint32_t ats_count);

  static void peerAddressCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                   const struct GNUNET_HELLO_Address *address);

  static void peerAddressStringConvertCallback (void *cls, const char *address);

public:

  Q_INVOKABLE void putHello(QString helloUrl);

  void start(struct GNUNET_CONFIGURATION_Handle *config);

private:

  void peerinfoProcessor(const struct GNUNET_PeerIdentity *peer,
                         const struct GNUNET_HELLO_Message *hello,
                         const char *err_msg);

  void peerATSstatusChange (const struct GNUNET_HELLO_Address *address, int address_active,
                            struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                            struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                            const struct GNUNET_ATS_Information *m_ats,
                            uint32_t ats_count);

  void       newPeerAddress (const struct GNUNET_PeerIdentity *peer,
                             const struct GNUNET_HELLO_Address *address);
  void       peerNewAddressString (QString id, const char *address);

  void checkNseMessage(GNUNET_TIME_Absolute timestamp, double estimate, double std_dev);

  int incomeMsg(const GNUNET_PeerIdentity *other, const GNUNET_MessageHeader *message);

  int outcomeMsg(const GNUNET_PeerIdentity *other, const GNUNET_MessageHeader *message);

  void notifyConnect(const GNUNET_PeerIdentity *peerIdent);

  void notifyDisconnect(const GNUNET_PeerIdentity *peerIdent);

  void gotActiveAddress(const GNUNET_PeerIdentity *peerIdent, const GNUNET_HELLO_Address *address);


  void getGlobalBandwidth();

public slots:

signals:
  void putHelloSignal(QString helloUrl);


private slots:
  void putHelloSlot(QString helloUrl);


private:

  int m_connectedPeers;
  int m_numEstimateNodes;
  int m_outgoingBand;
  int m_incomingBand;
  QTime m_nextBandwidthRetrive;


  /**
     * Handle to ATS service.
     */
  struct GNUNET_ATS_PerformanceHandle *m_ats;

  /**
     * Handle for our notifications from peerinfo about new peers.
     */
  struct GNUNET_PEERINFO_NotifyContext *m_peerInfoNotify;

  /**
     * Handle to peerinfo service.
     */
  struct GNUNET_PEERINFO_Handle *m_peerInfo;



  struct GNUNET_CONFIGURATION_Handle *m_config;

  GnunetTransportPlugins* m_gnunetTransportPlugins;


  /**
     * My GNUNet Hello.
     */
  QString m_myHelloStr;



};

#endif // PEERSINFO_H
