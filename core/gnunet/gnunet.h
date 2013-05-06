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


#ifndef GNUNET_H
#define GNUNET_H
#include <QtCore>
#include <QString>

#include "service.h"
#include "gnunet_includes.h"


class FileSharing;
class NetworkManager;
class SearchModel;
class NetworkPeersModel;
//class ServiceStatus;
class Downloads;
class GNUNet : public ServiceObject
{
    Q_OBJECT
    Q_PROPERTY(FileSharing * filesharing READ filesharing CONSTANT)
    Q_PROPERTY(NetworkManager* network READ network CONSTANT)
    Q_PROPERTY(GNUNET_CONFIGURATION_Handle * config READ config)

    Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int connectedPeers READ getConnectedPeers WRITE setConnectedPeers NOTIFY connectedPeersChanged)



public:
    explicit GNUNet(QObject *parent = 0);

    FileSharing* filesharing() const
    { return m_filesharing; }

    NetworkManager* network() const
    { return m_network; }

    GNUNET_CONFIGURATION_Handle* config() const
    { return m_config; }



    bool isConnected() const
    { return m_connected; }

    void setConnected(bool connected)
    {
        m_connected = connected;
        emit connectedChanged(m_connected);
    }


    //Connected peers
    int getConnectedPeers() const
    { return m_connectedPeers; }
    void setConnectedPeers(int connected)
    {
        m_connectedPeers = connected;
        emit connectedPeersChanged(connected);
    }


    static void mainLoopCallback(void *cls, char *const *args, const char *cfgfile,
                                 const struct GNUNET_CONFIGURATION_Handle *cfg);
    static void keepaliveTask (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc);

signals:
    void connectedChanged(bool connected);
    void connectedPeersChanged(int connected);
public slots:
    void Start();

public:


    int m_numEstimateNodes;


    void StartServices();

    void mainLoop(char *const*args, const char *cfgfile, const GNUNET_CONFIGURATION_Handle *cfg);

private:
    void ProcessEvents();
    FileSharing* m_filesharing;
    NetworkManager*  m_network;
    int m_connectedPeers;
    static struct GNUNET_CONFIGURATION_Handle *m_config;

    bool m_connected;
    /**
     * Handle for ARM monitoring.
     */
    struct GNUNET_ARM_MonitorHandle *m_armon;

    /**
     * Handle for ARM controlling.
     */
    struct GNUNET_ARM_Handle *m_arm;

    /**
     * My peer identity.
     */
    static struct GNUNET_PeerIdentity m_myPeerIdentity;

    /**
     * My public key.
     */
    static struct GNUNET_CRYPTO_EccPublicKeyBinaryEncoded m_myPublicKey;



};

#endif // GNUNET_H
