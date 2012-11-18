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

#include "gnetwork.h"
#include "core/cangote.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/gnunet_includes.h"
#include "models/gnunet_peers.h"

//Initialize static
GNUNET_ATS_PerformanceHandle * GNetwork::ats;
GNUNET_PEERINFO_NotifyContext* GNetwork::pnc;


//Struct that join
struct PeerAddressStringConversionConteiner{
    GNetwork* networkInstance;
    QString id;
};



GNetwork::GNetwork(QObject *parent) :
    QObject(parent)
{

    //Create our model.
    this->model = new GNUNetPeersModel();
    connections_counter = 0;
    numEstimateNodes = 0;
    nextBandwidthRetrive = QTime::currentTime();

    status = new ServiceStatus();
}

GNUNetPeersModel *GNetwork::getModel()
{
    Q_ASSERT(model);
    return model;
}

/**
 * Static Callback called when we have a information about a peer.
 */
void GNetwork::peerinfoProcessorCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                             const struct GNUNET_HELLO_Message *hello,
                                             const char *err_msg)
{
    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->peerinfoProcessor(peer, hello, err_msg);
}

/**
 * Static Callback called when a peer has a QoS status change.
 */
void GNetwork::ATSstatusChangeCallback (void *cls,
                                    const struct GNUNET_HELLO_Address *address,
                                    struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                                    struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                                    const struct GNUNET_ATS_Information *ats,
                                    uint32_t ats_count)
{

    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->peerATSstatusChange(address, bandwidth_in, bandwidth_out, ats,ats_count);

}


/**
 * Static Callback called when a we recieve an incoming message.
 */
int GNetwork::incomeMsgCallback (void *cls,
                                  const struct GNUNET_PeerIdentity *
                                  other,
                                  const struct GNUNET_MessageHeader *
                                  message,
                                  const struct GNUNET_ATS_Information
                                  * atsi, unsigned int atsi_count)
{

    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);


    networkInstance->incomeMsg(other,message,atsi,atsi_count);

    return GNUNET_OK;

}

/**
 * Static Callback called when a we recieve an outcome message.
 */
int GNetwork::outcomeMsgCallback (void *cls,
                                  const struct GNUNET_PeerIdentity *
                                  other,
                                  const struct GNUNET_MessageHeader *
                                  message,
                                  const struct GNUNET_ATS_Information
                                  * atsi, unsigned int atsi_count)
{

    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);


    networkInstance->outcomeMsg(other,message,atsi,atsi_count);

    return GNUNET_OK;

}




/**
 * Static Callback called when a peer get a address.
 */
void GNetwork::peerAddressCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
        const struct GNUNET_HELLO_Address *address)
{
    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);


    networkInstance->newPeerAddress(peer,address);
}


/**
 * Static Callback called when a peer get a address in a hostname string format
 */
void GNetwork::peerAddressStringConvertCallback (void *cls, const char *address)
{
    PeerAddressStringConversionConteiner* peersinfoConteiner = (PeerAddressStringConversionConteiner*)cls;
    Q_ASSERT(peersinfoConteiner);


    peersinfoConteiner->networkInstance->peerNewAddressString(peersinfoConteiner->id,address);

    //FIXME:: I need to delete this conteiner ! Doing here will crash !
    //delete peersinfoConteiner;
}


/**
 * Static Callback called when a peer get an active address
 */
void
GNetwork::gotActiveAddressCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                 const struct GNUNET_HELLO_Address *address)
{
    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->gotActiveAddress(peer,address);
}






/**
 * Static Callback called when a peer got connected
 */
void
GNetwork::notifyConnectCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                const struct GNUNET_ATS_Information *ats, uint32_t ats_count)
{
    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->notifyConnect(peer,ats,ats_count);
}



/**
 * Static Callback called when a peer got disconnected
 */
void
GNetwork::notifyDisconnectCallback(void *cls, const struct GNUNET_PeerIdentity *peer)
{
    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);


   networkInstance->notifyDisconnect(peer);
}


/**
 * Static Callback called when network size estimate is updated.
 */
void GNetwork::checkNseMessageCallback (void *cls, struct GNUNET_TIME_Absolute timestamp,
                                    double estimate, double std_dev)
{
    GNetwork* networkInstance = (GNetwork*)cls;
    Q_ASSERT(networkInstance);

    networkInstance->checkNseMessage(timestamp,estimate,std_dev);
}




/**
 * Function to call to start our services
 */
void GNetwork::start(struct GNUNET_CONFIGURATION_Handle *config)
{
    this->config = config;


    //Connect to peerinfo notifications
    pnc =   GNUNET_PEERINFO_notify (config, peerinfoProcessorCallback, this);
    if (pnc == NULL) {
        qWarning("Failed to connect to PeerInfo service");
        status->setErrorState("Failed to connect to Peerinfo");
    }

    //Connect to the ats service
    ats = GNUNET_ATS_performance_init (config, ATSstatusChangeCallback, this);
    if (ats == NULL) {
        qWarning("Failed to connect to ATS service");
        status->setErrorState("Failed to connect to ATS service");
    }

    //Connect to core to receive all income and outcome messages ( for bandwidth calculation)
    GNUNET_CORE_connect (config, this, NULL,
                         notifyConnectCallback, notifyDisconnectCallback,
                         incomeMsgCallback, GNUNET_YES, outcomeMsgCallback, GNUNET_YES, NULL);

    //Inicialize NSE
    struct GNUNET_NSE_Handle *nse;
    nse = GNUNET_NSE_connect (config, checkNseMessageCallback, this);


    if(pnc && ats && nse)
    {
        status->setOkState();
    }



}


int GNetwork::incomeMsg (const struct GNUNET_PeerIdentity *
                                  other,
                                  const struct GNUNET_MessageHeader *
                                  message,
                                  const struct GNUNET_ATS_Information
                                  * atsi, unsigned int atsi_count)
{
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&other->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);


    Peer* peer = model->getPeer(peerIdStr);

    if(peer == NULL)
        return GNUNET_OK;

    unsigned int size;
    unsigned int type;


    size = ntohs(message->size);
    type = ntohs(message->type);


    QTime time = QTime::currentTime();

    peer->addIncomingTraffic(size);

    return GNUNET_OK;

    ;
}

/**
 * Static Callback called when a we recieve an outcome message.
 */
int GNetwork::outcomeMsg (const struct GNUNET_PeerIdentity *
                                  other,
                                  const struct GNUNET_MessageHeader *
                                  message,
                                  const struct GNUNET_ATS_Information
                                  * atsi, unsigned int atsi_count)
{


    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&other->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);


    Peer* peer = model->getPeer(peerIdStr);

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
GNetwork::notifyConnect(const struct GNUNET_PeerIdentity *peerIdent,
                const struct GNUNET_ATS_Information *ats, uint32_t ats_count)
{
  connections_counter++;

  struct GNUNET_CRYPTO_HashAsciiEncoded enc;
  GNUNET_CRYPTO_hash_to_enc (&peerIdent->hashPubKey, &enc);
  QString peerIdStr((char *)&enc);


  Peer* peer = model->getPeer(peerIdStr);

  if(peer == NULL)
      peer = model->AddNewPeer(peerIdent,peerIdStr);


  if(!peer->peerActiveAddressCallback)
      peer->peerActiveAddressCallback = GNUNET_TRANSPORT_peer_get_active_addresses (config, peerIdent, GNUNET_YES,
                                                  GNUNET_TIME_relative_multiply (GNUNET_TIME_UNIT_SECONDS, 30),
                                                  &gotActiveAddressCallback, this);



  peer->setConnected();
}



/**
 * Function called to notify transport users that another
 * peer disconnected from us.
 *
 * @param peer the peer that disconnected
 */
void
GNetwork::notifyDisconnect(const struct GNUNET_PeerIdentity *peerIdent)
{
  connections_counter --;

  struct GNUNET_CRYPTO_HashAsciiEncoded enc;
  GNUNET_CRYPTO_hash_to_enc (&peerIdent->hashPubKey, &enc);
  QString peerIdStr((char *)&enc);


  Peer* peer = model->getPeer(peerIdStr);
  if(peer == NULL)
      return;

  peer->setDisconnected();


}





/**
 * Function called for peers that we know about.
 *
 * @param peer id of the peer, NULL for last call
 * @param hello hello message for the peer (can be NULL)
 * @param err_msg NULL if successful, otherwise contains error message
 */
void GNetwork::peerinfoProcessor(const struct GNUNET_PeerIdentity *peer,
                                   const struct GNUNET_HELLO_Message *hello,
                                   const char *err_msg)
{
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&peer->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);




    Peer* newPeer = NULL;

    if(!model->contains(peerIdStr)) {
        newPeer = model->AddNewPeer(peer, peerIdStr);
    } else {
        newPeer =model->getPeer(peerIdStr);
    }

    Q_ASSERT(newPeer);


    //Get The address
    if(newPeer->palc == NULL) {
        newPeer->palc = GNUNET_TRANSPORT_peer_get_active_addresses (theApp->gnunet->config, peer,
                        GNUNET_NO,
                        GNUNET_TIME_UNIT_FOREVER_REL,
                        peerAddressCallback, this);
    }


}

/**
 * Function to call with a binary address
 *
 * @param peer identity of the peer
 * @param address binary address (NULL on disconnect)
 */
void
GNetwork::gotActiveAddress(const struct GNUNET_PeerIdentity *peerIdent,
                            const struct GNUNET_HELLO_Address *address)
{


    if (peerIdent == NULL)
    {
        /* done */
        return;
    }

    if (address == NULL)
    {
        //TODO:: Disconnected ??
        return;
    }


    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&peerIdent->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);
    Peer* peer = model->getPeer(peerIdStr);

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
GNetwork::peerATSstatusChange (const struct GNUNET_HELLO_Address *address,
                      struct GNUNET_BANDWIDTH_Value32NBO bandwidth_in,
                      struct GNUNET_BANDWIDTH_Value32NBO bandwidth_out,
                      const struct GNUNET_ATS_Information *ats,
                      uint32_t ats_count)
{

    Peer *peer;
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&address->peer.hashPubKey, &enc);
    QString peerId((char *)&enc);


    peer = model->getPeer(peerId);

    if (NULL == peer)
        return;


    //TODO:: See what ATS can give to us
    /*
    GNUNET_ATS_Information * atsinfo = new GNUNET_ATS_Information[ats_count];
    for(unsigned int i = 0 ; i < ats_count ; i++)
        memcpy(&atsinfo[i], &ats[i], sizeof(GNUNET_ATS_Information));
    */

    unsigned int bandIn = (unsigned int)ntohl(bandwidth_in.value__);
    unsigned int bandOut = (unsigned int)ntohl(bandwidth_out.value__);

    peer->setATSInfo(bandIn,bandOut);
}



/**
 * Function to call with a binary format of an address
 *
 * @param peer peer the update is about
 * @param address NULL on disconnect, otherwise 0-terminated printable UTF-8 string
 */
void
GNetwork::newPeerAddress ( const struct GNUNET_PeerIdentity *peer,
                             const struct GNUNET_HELLO_Address *address)
{

    struct GNUNET_CRYPTO_HashAsciiEncoded enc;


    if (NULL == address) {
        /* disconnect */
        // gtk_list_store_set (ls, &iter,
        //         PEERINFO_MC_NUMBER_OF_ADDRESSES, (guint) 0,
        //         PEERINFO_MC_CONNECTIVITY_LED, led_red,
        //         PEERINFO_MC_CONNECTED_STATUS, FALSE,
        //                     -1);
        return;
    }
    GNUNET_CRYPTO_hash_to_enc (&address->peer.hashPubKey, &enc);
    QString peerIdStr((char *)&enc);


    Peer *peerp = model->getPeer(peerIdStr);

    if(peerp == NULL)
    {
        gWarn(QString("Recieve an address for a peer that is not on our list. Peer %1").arg(peerIdStr));
        return;
    }


    // gtk_list_store_set (ls, &iter,
    //           PEERINFO_MC_NUMBER_OF_ADDRESSES, 1,
    //           PEERINFO_MC_CONNECTIVITY_LED, led_green,
    //           PEERINFO_MC_CONNECTED_STATUS, TRUE,
    //           -1);
    if (NULL != peerp->tos)
        GNUNET_TRANSPORT_address_to_string_cancel (peerp->tos);
    peerp->got_address = GNUNET_NO;


    //Create the conteiner to aggregate the peerid and the callback.
    PeerAddressStringConversionConteiner* conteiner = new PeerAddressStringConversionConteiner;

    conteiner->id = peerIdStr;
    conteiner->networkInstance = this;

    peerp->tos =
        GNUNET_TRANSPORT_address_to_string (theApp->gnunet->config, address,
                                            GNUNET_NO,
                                            GNUNET_TIME_UNIT_FOREVER_REL,
                                            peerAddressStringConvertCallback, conteiner);

}

/**
 * Function to call with the text format of an address
 *
 * @param id , the ID of the peer that got updated
 * @param address address as a string, NULL on error
 */
void
GNetwork::peerNewAddressString (QString id, const char *address)
{
    Peer *peer = model->getPeer(id);

    QString hostname;

    if(peer == NULL)
    {
        gWarn("Got a result for a peer address string that dont exist on our map !");
        return;
    }


    if (NULL == address) {
        /* error */
        if (GNUNET_NO == peer->got_address)
        {
            hostname =  "<no address>";
            peer->setHostname(hostname);
        }

        peer->tos = NULL;
    }
    else
    {
        hostname = (char *)address;
        peer->got_address = GNUNET_YES;
        peer->setHostname(hostname);
    }


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
void GNetwork::checkNseMessage (struct GNUNET_TIME_Absolute timestamp,
                           double estimate, double std_dev)
{

    numEstimateNodes = pow(2,estimate);
    QString msg;
    msg = "Estimated number of nodes %1";
    msg= msg.arg(numEstimateNodes);
    gDebug(msg);
}



void GNetwork::getGlobalBandwidth()
{

    Bandwidth_Info_Struct* band = model->getTotalBandwidth();

    incomingBand = band->incoming;
    outcomingBand = band->outgoing;

    nextBandwidthRetrive = QTime::currentTime().addSecs(3);

    delete band;



}

int GNetwork::getIncomingBand()
{
    if(QTime::currentTime() >= nextBandwidthRetrive)
        getGlobalBandwidth();
    return incomingBand;
}

int GNetwork::getOutgoingBand()
{
    if(QTime::currentTime() >= nextBandwidthRetrive)
        getGlobalBandwidth();
    return outcomingBand;
}

int GNetwork::getEstimateNetworkSize()
{
    if(connections_counter > numEstimateNodes)
        return connections_counter;
    else
        return numEstimateNodes;
}

int GNetwork::getConnectedNodes()
{
    return connections_counter;
}

ServiceStatus* GNetwork::getStatus()
{
    return status;
}
