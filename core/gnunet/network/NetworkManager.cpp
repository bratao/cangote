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

#include "NetworkManager.h"
#include "core/cangotecore.h"
#include "cangote.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/gnunet_includes.h"
#include "models/NetworkPeersModel.h"
#include "models/models.h"
#include "gnunettransportplugins.h"
#include "core/status.h"

//Struct that join
struct PeerAddressStringConversionConteiner{
    NetworkManager* networkInstance;
    QString id;
};




///////////////////////STATIC CALLBACKS START//////////////////////////////////////////////////

/**
 * Static Callback called when network size estimate is updated.
 */
void NetworkManager::checkNseMessageCallback (void *cls, struct GNUNET_TIME_Absolute timestamp,
                                              double estimate, double std_dev)
{
    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->checkNseMessage(timestamp,estimate,std_dev);
}


/**
 * Static Callback called when a we recieve an incoming message.
 */

int NetworkManager::incomeMsgCallback (void *cls,
                                       const struct GNUNET_PeerIdentity *
                                       other,
                                       const struct GNUNET_MessageHeader *
                                       message)
{

    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);


    networkInstance->incomeMsg(other,message);

    return GNUNET_OK;

}

/**
 * Static Callback called when a we recieve an outcome message.
 */

int NetworkManager::outcomeMsgCallback (void *cls,
                                        const struct GNUNET_PeerIdentity *
                                        other,
                                        const struct GNUNET_MessageHeader *
                                        message)
{

    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);


    networkInstance->outcomeMsg(other,message);

    return GNUNET_OK;

}
/**
 * Static Callback called when a peer got connected
 */

void
NetworkManager::notifyConnectCallback (void *cls, const struct GNUNET_PeerIdentity *peer)
{
    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->notifyConnect(peer);
}

/**
 * Static Callback called when a peer got disconnected
 */
void
NetworkManager::notifyDisconnectCallback(void *cls, const struct GNUNET_PeerIdentity *peer)
{
    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);


    networkInstance->notifyDisconnect(peer);
}

/**
 * Static Callback called when a peer get an active address
 */
void
NetworkManager::gotActiveAddressCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                          const struct GNUNET_HELLO_Address *address)
{
    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->gotActiveAddress(peer,address);
}


/**
 * Static Callback called when we have a information about a peer.
 */
void NetworkManager::peerinfoProcessorCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                                const struct GNUNET_HELLO_Message *hello,
                                                const char *err_msg)
{
    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->peerinfoProcessor(peer, hello, err_msg);
}

/**
 * Static Callback called when a peer has a QoS status change.
 */

void NetworkManager::ATSstatusChangeCallback (void *cls,
                                              const struct GNUNET_HELLO_Address *address,
                                              int address_active,
                                              struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                                              struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                                              const struct GNUNET_ATS_Information *ats,
                                              uint32_t ats_count)
{

    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->peerATSstatusChange(address,address_active, bandwidth_in, bandwidth_out, ats,ats_count);

}

/**
 * Static Callback called when a peer get a address.
 */
int NetworkManager::peerAddressCallback (void *cls, const struct GNUNET_HELLO_Address *address,
                                          struct GNUNET_TIME_Absolute expiration)
{
    Peer* peer = (Peer*)cls;
    Q_ASSERT(peer);

    peer->addAddress(address, expiration);
    return GNUNET_OK;
}


///////////////////////STATIC CALLBACKS END//////////////////////////////////////////////////




NetworkManager::NetworkManager(QObject *parent) :
    ServiceObject(parent)
{

    m_connectedPeers = 0;
    m_numEstimateNodes = 0;
    m_nextBandwidthRetrive = QTime::currentTime();

    connect(this,&NetworkManager::putHelloSignal,this,&NetworkManager::putHelloSlot);

    connect(this, &NetworkManager::estimatedNodesChanged, theApp->status(), &Status::setEstimatedNodes, Qt::QueuedConnection);
    connect(this, &NetworkManager::outgoingBandChanged, theApp->status(), &Status::setOutgoingBand, Qt::QueuedConnection);
    connect(this, &NetworkManager::incomingBandChanged, theApp->status(), &Status::setIncomingBand, Qt::QueuedConnection);
    connect(this, &NetworkManager::myHelloStrChanged, theApp->status(), &Status::setMyHelloStr, Qt::QueuedConnection);

}



/**
 * Continuation called from 'GNUNET_PEERINFO_add_peer'
 *
 * @param cls closure, NULL
 * @param emsg error message, NULL on success
 */
static void
add_continuation (void *cls,
                  const char *emsg)
{
    if (NULL != emsg)
        fprintf (stderr,
                 _("Failure adding HELLO: %s\n"),
                 emsg);

}



/**
 * Insert a peer in our list
 */
void NetworkManager::putHelloSlot (QString helloUrl)
{

    struct GNUNET_HELLO_Message *hello = NULL;

    const char *put_uri = helloUrl.toUtf8().constData();



    GNUNET_CRYPTO_EddsaPublicKey mypublickey = theApp->gnunet()->myPeer()->public_key;

    int ret = GNUNET_HELLO_parse_uri(put_uri, &mypublickey, &hello, &m_gnunetTransportPlugins->GPI_plugins_find);

    if (NULL != hello) {
        // WARNING: this adds the address from URI WITHOUT verification!
        if (GNUNET_OK == ret)
            GNUNET_PEERINFO_add_peer (m_peerInfo, hello, &add_continuation, NULL);

        GNUNET_free (hello);
    }
    else
    {
        qWarning() << tr("Failed to process the url");
    }


}

void NetworkManager::putHello (QString helloUrl)
{

    emit putHelloSignal(helloUrl);
}


/**
 * Function to call to start our services
 */
void NetworkManager::start(struct GNUNET_CONFIGURATION_Handle *config)
{
    m_config = config;


    //Connect to peerinfo
    if (NULL == (m_peerInfo = GNUNET_PEERINFO_connect (config)))
    {
        qWarning("Failed to connect to PeerInfo service");
    }

    //Initialize transport plugins
    m_gnunetTransportPlugins = new GnunetTransportPlugins(config,this);

    //Connect to peerinfo notifications
    m_peerInfoNotify =   GNUNET_PEERINFO_notify (config, NULL, peerinfoProcessorCallback, this);
    if (m_peerInfoNotify == NULL) {
        qWarning("Failed to connect to PeerInfo Notify service");
    }

    //Connect to the ats service
    m_ats = GNUNET_ATS_performance_init (config, ATSstatusChangeCallback, this);
    if (m_ats == NULL) {
        qWarning("Failed to connect to ATS service");
    }

    //Monitor peer for connected transports
    m_peerMonitoring = GNUNET_TRANSPORT_monitor_peers (config,
                                                       NULL,
                                                       GNUNET_NO,
                                                       GNUNET_TIME_UNIT_FOREVER_REL,
                                                       &transportPeerChangeCallback,
                                                       NULL);

    //Monitor peer for validated transports
    m_peerTransportValidation = GNUNET_TRANSPORT_monitor_validation_entries (config,
                                                                             NULL,
                                                                             GNUNET_NO,
                                                                             GNUNET_TIME_UNIT_FOREVER_REL,
                                                                             &validationMonitorCallback,
                                                                             NULL);

    //Connect to core to receive all income and outcome messages ( for bandwidth calculation)
    m_core = GNUNET_CORE_connect (m_config, this, NULL,
                                  notifyConnectCallback, notifyDisconnectCallback,
                                  incomeMsgCallback, GNUNET_YES, outcomeMsgCallback, GNUNET_YES, NULL);

    //Inicialize NSE
    struct GNUNET_NSE_Handle *nse;
    nse = GNUNET_NSE_connect (config, checkNseMessageCallback, this);






    if(m_peerInfoNotify && m_ats && nse)
    {
        //status->setOkState();
    }



}


int NetworkManager::incomeMsg (const struct GNUNET_PeerIdentity *
                               other,
                               const struct GNUNET_MessageHeader *
                               message)

{
    const char* key = GNUNET_i2s_full (other);
    QString peerIdStr(key);



    if(!theApp->models()->networkModel())
        return GNUNET_OK;

    Peer* peer = theApp->models()->networkModel()->getPeer(peerIdStr);

    if(peer == NULL)
        return GNUNET_OK;

    unsigned int size;
    unsigned int type;


    size = ntohs(message->size);
    type = ntohs(message->type);


    QTime time = QTime::currentTime();

    peer->addIncomingTraffic(size);

    return GNUNET_OK;
}

/**
 * Called when a we recieve an outcome message.
 */

int NetworkManager::outcomeMsg (const struct GNUNET_PeerIdentity *
                                other,
                                const struct GNUNET_MessageHeader *
                                message)

{


    const char* key = GNUNET_i2s_full (other);
    QString peerIdStr(key);




    if(!theApp->models()->networkModel())
        return GNUNET_OK;


    Peer* peer = theApp->models()->networkModel()->getPeer(peerIdStr);

    if(peer == NULL)
        return GNUNET_OK;

    unsigned int size;
    unsigned int type;


    size = ntohs(message->size);
    type = ntohs(message->type);


    QTime time = QTime::currentTime();

    peer->addOutgoingTraffic(size);

    return GNUNET_OK;
}



/**
 * Function called to notify transport users that another
 * peer connected to us.
 *
 * @param peer the peer that connected
 * @param ats performance data
 * @param ats_count number of entries in ats (excluding 0-termination)
 */


void
NetworkManager::notifyConnect(const struct GNUNET_PeerIdentity *peerIdent)
{

    const char* key = GNUNET_i2s_full (peerIdent);
    QString peerIdStr(key);


    if(!theApp->models()->networkModel())
    {

        qWarning() << tr("Tried to add a peer while the network model was not created");
        return;
    }

    //Do not show my own.
    if(theApp->gnunet()->myPublicKeyStr() == peerIdStr)
    {

        //Call peerinfo iterate to get my own hello, to create my share-link.
        GNUNET_PEERINFO_iterate (m_peerInfo, false, peerIdent,
                                 GNUNET_TIME_relative_multiply (GNUNET_TIME_UNIT_SECONDS, 10),
                                 &peerinfoProcessorCallback, this);
        return;
    }


    Peer* peer = theApp->models()->networkModel()->getPeer(peerIdStr);

    //If peer do not exist, create it.
    if(peer == NULL)
        peer = theApp->models()->networkModel()->addNewPeer(peerIdent,peerIdStr);


    //Just set as connected if the previous status was disconnected
    if(!peer->isConnected())
        setConnectedPeers(++m_connectedPeers);

    peer->setConnected(true);

}



/**
 * Function called to notify transport users that another
 * peer disconnected from us.
 *
 * @param peer the peer that disconnected
 */
void
NetworkManager::notifyDisconnect(const struct GNUNET_PeerIdentity *peerIdent)
{
    //struct GNUNET_CRYPTO_HashAsciiEncoded enc;


    const char* key = GNUNET_i2s_full (peerIdent);
    QString peerIdStr(key);

    if(!theApp->models() || !theApp->models()->networkModel())
    {
        qWarning() << tr("Tried to remove a peer while the network model was not created");
        return;
    }
    Peer* peer = theApp->models()->networkModel()->getPeer(peerIdStr);
    if(peer == NULL)
        return;

    peer->setConnected(false);
    setConnectedPeers(--m_connectedPeers);


}


/**
 * Function to call with information about a peer
 *
 * @param cts closure
 * @param peer peer this update is about,
 *      NULL if this is the final last callback for a iteration operation
 * @param address address, NULL for disconnect notification in monitor mode
 * @param state current state this peer is in
 * @param state_timeout timeout for the current state of the peer
 */

void
NetworkManager::transportPeerChangeCallback (void *cts,
                                             const struct GNUNET_PeerIdentity *peer,
                                             const struct GNUNET_HELLO_Address *address,
                                             enum GNUNET_TRANSPORT_PeerState state,
                                             struct GNUNET_TIME_Absolute state_timeout)
{
}

void
NetworkManager::transportPeerChange (const struct GNUNET_PeerIdentity *peer,
                                     const struct GNUNET_HELLO_Address *address,
                                     enum GNUNET_TRANSPORT_PeerState state,
                                     struct GNUNET_TIME_Absolute state_timeout)
{
    /*
  struct PeerInfo *info;
  GtkTreeIter iter;
  gboolean con;
  const char *tos;
  struct PeerAddress *pa;

  info = get_peer_info (peer);
  info->state = state;
  info->state_timeout = state_timeout;
  con = (GNUNET_YES == GNUNET_TRANSPORT_is_connected (state));
  get_iter_from_rr (info->rr, &iter);
  tos = GNUNET_STRINGS_absolute_time_to_string (state_timeout);
  gtk_tree_store_set (ts, &iter,
                      PEERINFO_MC_NEIGHBOUR_CONNECTED_STATUS, con,
                      PEERINFO_MC_NEIGHBOUR_CONNECTIVITY_TIMEOUT_AS_STRING, con ? tos : NULL,
                      PEERINFO_MC_NEIGHBOUR_CONNECTIVITY_LED, (con ? led_green : led_red),
                      PEERINFO_MC_NEIGHBOUR_STATE_AS_STRING, GNUNET_TRANSPORT_ps2s (state),
                      PEERINFO_MC_NEIGHBOUR_STATE_TIMEOUT_AS_STRING, tos,
                      -1);
  for (pa = info->pa_head; NULL != pa; pa = pa->next)
  {
    get_iter_from_rr (pa->rr, &iter);
    gtk_tree_store_set (ts, &iter,
                        PEERINFO_MC_NEIGHBOUR_CONNECTED_STATUS, FALSE,
                        PEERINFO_MC_NEIGHBOUR_CONNECTIVITY_TIMEOUT_AS_STRING, NULL,
                        PEERINFO_MC_NEIGHBOUR_CONNECTIVITY_LED, led_red,
                        PEERINFO_MC_NEIGHBOUR_STATE_AS_STRING, NULL,
                        PEERINFO_MC_NEIGHBOUR_STATE_TIMEOUT_AS_STRING, NULL,
                        -1);
  }
  if (NULL == address)
    return;
  pa = get_address (info, address);
  get_iter_from_rr (pa->rr, &iter);
  gtk_tree_store_set (ts, &iter,
                      PEERINFO_MC_NEIGHBOUR_CONNECTED_STATUS, con,
                      PEERINFO_MC_NEIGHBOUR_CONNECTIVITY_TIMEOUT_AS_STRING, con ? tos : NULL,
                      PEERINFO_MC_NEIGHBOUR_CONNECTIVITY_LED, (con ? led_green : led_red),
                      PEERINFO_MC_NEIGHBOUR_STATE_AS_STRING, GNUNET_TRANSPORT_ps2s (state),
                      PEERINFO_MC_NEIGHBOUR_STATE_TIMEOUT_AS_STRING, tos,
                      -1);*/
}


/**
 * Function to call with validation information about a peer
 *
 * @param cts closure
 * @param peer peer this update is about,
 *      NULL if this is the final last callback for a iteration operation
 * @param address address, NULL for disconnect notification in monitor mode
 * @param valid_until when does this address expire
 * @param next_validation time of the next validation operation
 *
 */

void
NetworkManager::validationMonitorCallback (void *cls,
                                           const struct GNUNET_PeerIdentity *peer,
                                           const struct GNUNET_HELLO_Address *address,
                                           struct GNUNET_TIME_Absolute last_validation,
                                           struct GNUNET_TIME_Absolute valid_until,
                                           struct GNUNET_TIME_Absolute next_validation,
                                           enum GNUNET_TRANSPORT_ValidationState state)
{
}
void
NetworkManager::validationMonitor (const struct GNUNET_PeerIdentity *peer,
                                   const struct GNUNET_HELLO_Address *address,
                                   struct GNUNET_TIME_Absolute valid_until,
                                   struct GNUNET_TIME_Absolute next_validation)
{
    /*struct PeerInfo *info;
  struct PeerAddress *pa;
  GtkTreeIter iter;
  const char *tos;
  gboolean valid;

  GNUNET_assert (NULL != peer);
  info = get_peer_info (peer);
  if (NULL == address)
  {
    // disconnect, mark all as down
    for (pa = info->pa_head; NULL != pa; pa = pa->next)
    {
      get_iter_from_rr (pa->rr, &iter);
      gtk_tree_store_set (ts, &iter,
                          PEERINFO_MC_VALIDATION_IS_VALID, FALSE,
                          PEERINFO_MC_VALIDATION_TIMEOUT_AS_STRING, NULL,
                          PEERINFO_MC_VALIDATION_STATE_LED, NULL,
                          -1);
    }
    return;
  }
  valid = GNUNET_TIME_absolute_get_remaining (valid_until).rel_value_us > 0;
  pa = get_address (info, address);
  get_iter_from_rr (pa->rr, &iter);
  tos = GNUNET_STRINGS_absolute_time_to_string (valid_until);
  gtk_tree_store_set (ts, &iter,
                      PEERINFO_MC_VALIDATION_IS_VALID, valid,
                      PEERINFO_MC_VALIDATION_TIMEOUT_AS_STRING, tos,
                      PEERINFO_MC_VALIDATION_STATE_LED, (valid ? led_green : led_red),
                      -1);

  */
}




/**
 * Function called for peers that we know about.
 *
 * @param peer id of the peer, NULL for last call
 * @param hello hello message for the peer (can be NULL)
 * @param err_msg NULL if successful, otherwise contains error message
 */
void NetworkManager::peerinfoProcessor(const struct GNUNET_PeerIdentity *peer,
                                       const struct GNUNET_HELLO_Message *hello,
                                       const char *err_msg)
{

    if(peer == NULL)
    {
        qWarning() << QString("Got a NULL peer in peerinfoProcessor. %1").arg(err_msg ? err_msg : "");
        return;
    }


    const char* key = GNUNET_i2s_full (peer);
    QString peerIdStr(key);


    if(!theApp->models()->networkModel())
    {
        qWarning() << tr("Got a info about a peer while the network model was not created");
        return;
    }


    //If is myself, update my Hello string to display to the user.
    if(theApp->gnunet()->myPublicKeyStr() == peerIdStr)
    {
        if(!hello)
        {
            qWarning() << tr("Got a info about myself without a hello");
            return;
        }

        //Save my hello URL
        char *uri = GNUNET_HELLO_compose_uri(hello, &m_gnunetTransportPlugins->GPI_plugins_find);
        setMyHelloStr(QString(uri));
        return;
    }


    Peer* newPeer = NULL;

    //See if peer already exists.If not, create a new one.
    if(!theApp->models()->networkModel()->contains(peerIdStr)) {
        newPeer = theApp->models()->networkModel()->addNewPeer(peer, peerIdStr);
    } else {
        newPeer =theApp->models()->networkModel()->getPeer(peerIdStr);
    }

    Q_ASSERT(newPeer);



    if(hello){
        GNUNET_HELLO_iterate_addresses (hello, GNUNET_NO,
                                    &peerAddressCallback, newPeer);
    }

}

/**
 * Function to call with a binary address
 *
 * @param peer identity of the peer
 * @param address binary address (NULL on disconnect)
 */
void
NetworkManager::gotActiveAddress(const struct GNUNET_PeerIdentity *peerIdent,
                                 const struct GNUNET_HELLO_Address *address)
{



    if (address == NULL)
    {
        qDebug() << tr("Peer removed because dont have an active address");
        notifyDisconnect(peerIdent);
        return;
    }

    //We have an address so is connected

    notifyConnect(peerIdent);

    if(!theApp->models()->networkModel())
    {
        qWarning() << tr("Got an active address for a peer while the network model was not created");
        return;
    }

    const char* key = GNUNET_i2s_full (peerIdent);
    QString peerIdStr(key);

    Peer* peer = theApp->models()->networkModel()->getPeer(peerIdStr);
    if(peer == NULL)
    {
        qDebug() << "Received a address to a peer that do not exist";
    }
    QString peerTransportName((char *)address->transport_name);



    peer->setTransportName(peerTransportName);

}


/**
 * Method called whenever a given peer has a QoS status change.
 *
 * @param address the address
 * @param bandwidth_in available amount of inbound bandwidth
 * @param bandwidth_out available amount of outbound bandwidth
 * @param ats performance data for the address (as far as known)
 * @param ats_count number of performance records in 'ats'
 */
void
NetworkManager::peerATSstatusChange (const struct GNUNET_HELLO_Address *address,
                                     int address_active,
                                     struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                                     struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                                     const struct GNUNET_ATS_Information *ats,
                                     uint32_t ats_count)
{
    const char* key = GNUNET_i2s_full (&address->peer);
    QString peerId(key);



    if(!theApp->models()->networkModel()){
        qWarning() << "Recivied a peerATSstatus without network Model";
        return;
    }

    Peer *peer = theApp->models()->networkModel()->getPeer(peerId);

    if (NULL == peer)
    {
        qWarning() << "Recivied a peerATSstatus, but the peer do not exist : " << peerId;
        return;
    }


    //TODO:: See what ATS can give to us

    GNUNET_ATS_Information * atsinfo = new GNUNET_ATS_Information[ats_count];
    for(unsigned int i = 0 ; i < ats_count ; i++){

        memcpy(&atsinfo[i], &ats[i], sizeof(GNUNET_ATS_Information));
        qWarning() << QString("ATS - Type : %1 , Value: %2 ").arg( GNUNET_ATS_print_property_type(ntohl(atsinfo[i].type))).arg(atsinfo[i].value);

    }

    delete[] atsinfo;

    unsigned int bandIn = (unsigned int)ntohl(bandwidth_in.value__);
    unsigned int bandOut = (unsigned int)ntohl(bandwidth_out.value__);

    peer->setATSInfo(bandIn,bandOut);
}



/**
 * Callback to notify that the network size estimate is updated.
 *
 * @param timestamp time when the estimate was received from the server (or created by the server)
 * @param estimate the value of the current network size estimate
 * @param std_dev standard deviation (rounded down to nearest integer)
 *                of the size estimation values seen
 *
 */
void NetworkManager::checkNseMessage (struct GNUNET_TIME_Absolute timestamp,
                                      double estimate, double std_dev)
{

    setEstimatedNodes(pow(2,estimate));
    QString msg;
    msg = "Estimated number of nodes %1";
    msg= msg.arg(m_numEstimateNodes);
    qDebug() << msg;
    //gDebug(msg);
}



void NetworkManager::getGlobalBandwidth()
{

    Bandwidth_Info_Struct* band = theApp->models()->networkModel()->getTotalBandwidth();

    m_incomingBand = band->incoming;
    m_outgoingBand = band->outgoing;

    m_nextBandwidthRetrive = QTime::currentTime().addSecs(3);

    delete band;



}


