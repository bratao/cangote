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
class Publish;
class NetworkManager;
class SearchModel;
class NetworkPeersModel;
class Downloads;
class GNUNet : public ServiceObject
{
    Q_OBJECT
    Q_PROPERTY(FileSharing * filesharing READ filesharing CONSTANT)
    Q_PROPERTY(NetworkManager* network READ network CONSTANT)
    Q_PROPERTY(Publish* publish READ publish CONSTANT)
    Q_PROPERTY(GNUNET_CONFIGURATION_Handle * config READ config)

    Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int connectedPeers READ getConnectedPeers WRITE setConnectedPeers NOTIFY connectedPeersChanged)
    Q_PROPERTY(QString myPublicKeyStr READ myPublicKeyStr WRITE setMyPublicKeyStr NOTIFY myPublicKeyStrChanged)


public:
    explicit GNUNet(QObject *parent = 0);

    FileSharing* filesharing() const
    { return m_filesharing; }

    NetworkManager* network() const
    { return m_network; }

    Publish* publish() const
    { return m_publish; }


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

    //Connected peers
    QString myPublicKeyStr() const
    { return m_myPublicKeyStr; }
    void setMyPublicKeyStr(QString key)
    {
        m_myPublicKeyStr = key;
        emit myPublicKeyStrChanged(key);
    }

    GNUNET_CRYPTO_EddsaPublicKey myPublicKey() const;
    void setMyPublicKey(const GNUNET_CRYPTO_EddsaPublicKey &myPublicKey);



private:

    /**
      Static Definitions
     */
    static void mainLoopCallback(void *cls, char *const *args, const char *cfgfile,
                                 const struct GNUNET_CONFIGURATION_Handle *cfg);

    static void keepaliveTaskCallback (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc);

public:
    void armConnectionStateChange(int connected);

signals:
    void gnunetStarted();
    void gnunetConnected();
    void connectedChanged(bool connected);
    void connectedPeersChanged(int connected);
    void myPublicKeyStrChanged(QString key);

public slots:
    void start();

private slots:
    void startServices();

private:

    /**
     * Pointer to GNUnet filesharing.
     */
    FileSharing* m_filesharing;

    /**
     * Pointer to network manager class.
     */
    NetworkManager*  m_network;

    /**
     * Pointer to the Publish class.
     */
    Publish* m_publish;

    /**
     * Represent the number of connected peers
     */
    int m_connectedPeers;

    /**
     * @brief m_config
     */
    struct GNUNET_CONFIGURATION_Handle *m_config;

    /**
     * @brief m_connected
     */
    bool m_connected;

    /**
     * @brief m_numEstimateNodes
     */
    int m_numEstimateNodes;

    /**
     * Handle for ARM monitoring.
     */
    struct GNUNET_ARM_MonitorHandle *m_armon;

    /**
     * Handle for ARM controlling.
     */
    struct GNUNET_ARM_Handle *m_arm;


    /**
     * My public key.
     */
    struct GNUNET_CRYPTO_EddsaPublicKey m_myPublicKey;

    /**
     * My public key.
     */
    QString m_myPublicKeyStr;




    void processEvents();
    void mainLoop(char *const*args, const char *cfgfile, const GNUNET_CONFIGURATION_Handle *cfg);

};

#endif // GNUNET_H
