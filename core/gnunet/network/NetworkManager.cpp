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
void NetworkManager::peerAddressCallback (void *cls, const struct GNUNET_PeerIdentity *peer,
                                          const struct GNUNET_HELLO_Address *address)
{
    NetworkManager* networkInstance = (NetworkManager*)cls;
    Q_ASSERT(networkInstance);


    networkInstance->newPeerAddress(peer,address);
}

/**
 * Static Callback called when a peer get a address in a hostname string format
 */
void NetworkManager::peerAddressStringConvertCallback (void *cls, const char *address)
{
    PeerAddressStringConversionConteiner* peersinfoConteiner = (PeerAddressStringConversionConteiner*)cls;
    Q_ASSERT(peersinfoConteiner);


    peersinfoConteiner->networkInstance->peerNewAddressString(peersinfoConteiner->id,address);

    //FIXME:: I need to delete this conteiner ! Doing here will crash !
    //delete peersinfoConteiner;
}


///////////////////////STATIC CALLBACKS END//////////////////////////////////////////////////




NetworkManager::NetworkManager(QObject *parent) :
    ServiceObject(parent)
{

    m_connectedPeers = 0;
    m_numEstimateNodes = 0;
    m_nextBandwidthRetrive = QTime::currentTime();

    connect(this,&NetworkManager::putHelloSignal,this,&NetworkManager::putHelloSlot);
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

    const char *put_uri = helloUrl.toLatin1().constData();
    GNUNET_CRYPTO_EccPublicKeyBinaryEncoded mypublickey = theApp->gnunet()->myPublicKey();

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



    //Connect to peerinfo notifications

    m_peerInfoNotify =   GNUNET_PEERINFO_notify (config,NULL, peerinfoProcessorCallback, this);


    if (m_peerInfoNotify == NULL) {
        qWarning("Failed to connect to PeerInfo Notify service");
    }

    //Connect to the ats service
    m_ats = GNUNET_ATS_performance_init (config, ATSstatusChangeCallback, this);
    if (m_ats == NULL) {
        qWarning("Failed to connect to ATS service");
        //status->setErrorState("Failed to connect to ATS service");
    }

    //Connect to core to receive all income and outcome messages ( for bandwidth calculation)
    GNUNET_CORE_connect (m_config, this, NULL,
                         notifyConnectCallback, notifyDisconnectCallback,
                         incomeMsgCallback, GNUNET_YES, outcomeMsgCallback, GNUNET_YES, NULL);

    //Inicialize NSE
    struct GNUNET_NSE_Handle *nse;
    nse = GNUNET_NSE_connect (config, checkNseMessageCallback, this);


    //Initialize transport plugins
    m_gnunetTransportPlugins = new GnunetTransportPlugins(config,this);



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
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&other->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);

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


    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&other->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);


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



    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&peerIdent->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);

    if(!theApp->models()->networkModel())
    {

        qWarning() << tr("Tried to add a peer while the network model was not created");
        return;
    }
    Peer* peer = theApp->models()->networkModel()->getPeer(peerIdStr);

    if(peer == NULL)
        peer = theApp->models()->networkModel()->addNewPeer(peerIdent,peerIdStr);


    //TODO :: Cancel the request
    if(!peer->m_peerActiveAddressCallback)
        peer->m_peerActiveAddressCallback = GNUNET_TRANSPORT_peer_get_active_addresses (m_config, peerIdent, GNUNET_NO,
                                                                                        GNUNET_TIME_UNIT_FOREVER_REL,
                                                                                        &gotActiveAddressCallback, this);



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
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&peerIdent->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);

    if(!theApp->models()->networkModel())
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
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&peer->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);

    if(!theApp->models()->networkModel())
    {
        qWarning() << tr("Got a info about a peer while the network model was not created");
        return;
    }


    Peer* newPeer = NULL;

    if(!theApp->models()->networkModel()->contains(peerIdStr)) {
        newPeer = theApp->models()->networkModel()->addNewPeer(peer, peerIdStr);
    } else {
        newPeer =theApp->models()->networkModel()->getPeer(peerIdStr);
    }

    Q_ASSERT(newPeer);


    //Get The address
    if(newPeer->m_palc == NULL) {
        newPeer->m_palc = GNUNET_TRANSPORT_peer_get_active_addresses ((const GNUNET_CONFIGURATION_Handle*)theApp->gnunet()->config(), peer,
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

    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&peerIdent->hashPubKey, &enc);
    QString peerIdStr((char *)&enc);
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

    Peer *peer;
    struct GNUNET_CRYPTO_HashAsciiEncoded enc;
    GNUNET_CRYPTO_hash_to_enc (&address->peer.hashPubKey, &enc);
    QString peerId((char *)&enc);

    if(!theApp->models()->networkModel())
        return;

    peer = theApp->models()->networkModel()->getPeer(peerId);

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
NetworkManager::newPeerAddress ( const struct GNUNET_PeerIdentity *peer,
                                 const struct GNUNET_HELLO_Address *address)
{

    struct GNUNET_CRYPTO_HashAsciiEncoded enc;


    if (NULL == address) {
        qWarning() << tr("Null address at newPeerAddress");
        notifyDisconnect(peer);
        return;
    }

    if(!theApp->models()->networkModel())
    {
        qDebug() << tr("Peer got a new address, but the model was not created");
        return;
    }


    GNUNET_CRYPTO_hash_to_enc (&address->peer.hashPubKey, &enc);
    QString peerIdStr((char *)&enc);


    Peer *peerp = theApp->models()->networkModel()->getPeer(peerIdStr);

    if(peerp == NULL)
    {
        qWarning() << QString("Recieve an address for a peer that is not on our list. Peer %1").arg(peerIdStr);
        return;
    }


    //Set as a connected peer
    notifyConnect(peer);

    if (NULL != peerp->m_tos)
        GNUNET_TRANSPORT_address_to_string_cancel (peerp->m_tos);
    peerp->m_gotAddress = GNUNET_NO;


    //Create the conteiner to aggregate the peerid and the callback.
    PeerAddressStringConversionConteiner* conteiner = new PeerAddressStringConversionConteiner;

    conteiner->id = peerIdStr;
    conteiner->networkInstance = this;

    peerp->m_tos =
            GNUNET_TRANSPORT_address_to_string (theApp->gnunet()->config(), address,
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
NetworkManager::peerNewAddressString (QString id, const char *address)
{

    if(!theApp->models()->networkModel())
        return;


    Peer *peer = theApp->models()->networkModel()->getPeer(id);

    QString hostname;

    if(peer == NULL)
    {
        qWarning() << tr("Got a result for a peer address string that dont exist on our map !");
        return;
    }


    if (NULL == address) {
        /* error */
        if (GNUNET_NO == peer->m_gotAddress)
        {
            hostname =  "<no address>";
            peer->setHostname(hostname);
        }

        peer->m_tos = NULL;
    }
    else
    {
        hostname = (char *)address;
        peer->m_gotAddress = GNUNET_YES;
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


