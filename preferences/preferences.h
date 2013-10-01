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

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QObject>
#include <QDebug>
#include <QSettings>

class Preferences : public QSettings
{
    Q_OBJECT
    Q_DISABLE_COPY (Preferences)


  /*
   *
   * DIRECTORIES
   *
   *
   */
   Q_PROPERTY(QString downloadDirectory READ getDownloadDirectory WRITE setDownloadDirectory NOTIFY preferencesChangedSignal)

    /*
     *
     * FILE SHARING
     *
     *
     */
    Q_PROPERTY(bool pushingContent READ isPushingContentEnabled WRITE setPushingContent NOTIFY preferencesChangedSignal)
    Q_PROPERTY(bool cachingContent READ isCachingContentEnabled WRITE setCachingContent NOTIFY preferencesChangedSignal)
    Q_PROPERTY(float datastoreSize READ getDatastoreSize WRITE setDatastoreSize NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int datacacheSize READ getDatacacheSize WRITE setDatacacheSize NOTIFY preferencesChangedSignal)

    /*
     * Friend to Friend
     */
    Q_PROPERTY(bool friendToFriendOnly READ isFriendToFriendOnlyEnabled WRITE setFriendToFriendOnly NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int minimalNumberOfFriends READ getMinimalNumberOfFriends WRITE setMinimalNumberOfFriends NOTIFY preferencesChangedSignal)

    /*
     * HostList
     */
    Q_PROPERTY(bool hostlistsEnabled READ isHostlistsEnabled WRITE setHostlistsEnabled NOTIFY preferencesChangedSignal)
    Q_PROPERTY(bool learnHostslistsFromNetworkEnabled READ isLearnHostslistsFromNetworkEnabled WRITE setLearnHostslistsFromNetworkEnabled NOTIFY preferencesChangedSignal)
    Q_PROPERTY(QString hostlist READ getHostlist WRITE setHostlist NOTIFY preferencesChangedSignal)

    /*
     *
     * NETWORK
     *
     */
    Q_PROPERTY(bool ipv6Enabled READ isIpv6Enabled WRITE setIpv6Enabled NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int uploadSpeed READ getUploadSpeed WRITE setUploadSpeed NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int downloadSpeed READ getDownloadSpeed WRITE setDownloadSpeed NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int neighboursLimit READ getNeighboursLimit WRITE setNeighboursLimit NOTIFY preferencesChangedSignal)


    /*
     * TCP
     */
    Q_PROPERTY(int tcpPort READ getTcpPort WRITE setTcpPort NOTIFY preferencesChangedSignal)
    Q_PROPERTY(bool tcpEnabled READ isTcpEnabled WRITE setTcpEnabled NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int tcpAdvertisedPort READ getTcpAdvertisedPort WRITE setTcpAdvertisedPort NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int tcpMaxConnections READ getTcpMaxConnections WRITE setTcpMaxConnections NOTIFY preferencesChangedSignal)
    /*
     * UDP
     */
    Q_PROPERTY(int udpPort READ getUdpPort WRITE setTcpPort NOTIFY preferencesChangedSignal)
    Q_PROPERTY(bool udpEnabled READ isUdpEnabled WRITE setUdpEnabled NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int udpAdvertisedPort READ getUdpAdvertisedPort WRITE setUdpAdvertisedPort NOTIFY preferencesChangedSignal)
    Q_PROPERTY(int udpMaxSpeed READ getUdpMaxSpeed WRITE setUdpMaxSpeed NOTIFY preferencesChangedSignal)

    /*
     * NAT
     *
     */
    Q_PROPERTY(bool behindNat READ isBehindNat WRITE setBehindNat NOTIFY preferencesChangedSignal)
    Q_PROPERTY(bool portsOpen READ isPortsOpen WRITE setPortsOpen NOTIFY preferencesChangedSignal)
    Q_PROPERTY(bool UPNPEnabled READ isUPNPEnabled WRITE setUPNPEnabled NOTIFY preferencesChangedSignal)
    Q_PROPERTY(bool ICMPMethod READ isICMPMethodEnabled WRITE setICMPMethodEnabled NOTIFY preferencesChangedSignal)
    Q_PROPERTY(QString externalIpv4Address READ getExternalIpv4Address WRITE setExternalIpv4Address NOTIFY preferencesChangedSignal)

public:
    explicit Preferences(QObject *parent = 0);


  /*
   *
   * DIRECTORIES
   *
   *
   */
  QString getDownloadDirectory()
  {
    return value("core/directories/downloadDirectory","").toString();
  }

  void setDownloadDirectory(QString dir)
  {

      setValue("core/directories/downloadDirectory",dir);
      emit preferencesChangedSignal();
  }


    /*
     *
     * FILE SHARING
     *
     *
     */

    void setPushingContent(bool enabled)
    {
        setValue("core/filesharing/pushingContent",enabled);
        emit preferencesChangedSignal();
    }


    bool isPushingContentEnabled()
    {
        return value("core/filesharing/pushingContent",true).toBool();
    }

    void setCachingContent(bool enabled)
    {
        setValue("core/filesharing/cachingContent",enabled);
        emit preferencesChangedSignal();
    }

    bool isCachingContentEnabled()
    {
        return value("core/filesharing/cachingContent",true).toBool();
    }


    float getDatastoreSize()
    {
        return value("core/filesharing/datastoreSize",5).toFloat();
    }

    /**
     * @brief setDatastoreSize In GB
     * @param size
     */
    void setDatastoreSize(float size)
    {

        setValue("core/filesharing/datastoreSize",size);
        emit preferencesChangedSignal();
    }


    int getDatacacheSize()
    {

        return value("core/filesharing/datacacheSize",1).toInt();
    }

    void setDatacacheSize(int size)
    {
        setValue("core/filesharing/datacacheSize",size);
        emit preferencesChangedSignal();
    }


    /*
     * Friend to Friend
     */

    void setFriendToFriendOnly(bool enabled)
    {
        setValue("core/filesharing/friendToFriend/friendToFriendOnly",enabled);
        emit preferencesChangedSignal();
    }

    bool isFriendToFriendOnlyEnabled()
    {
        return value("core/filesharing/friendToFriend/friendToFriendOnly",true).toBool();
    }

    int getMinimalNumberOfFriends()
    {
        return value("core/filesharing/friendToFriend/minimalNumberOfFriends",0).toInt();
    }

    void setMinimalNumberOfFriends(int number)
    {
        setValue("core/filesharing/friendToFriend/minimalNumberOfFriends",number);
        emit preferencesChangedSignal();
    }


    /*
     * HostList
     */
    void setHostlistsEnabled(bool enabled)
    {
        setValue("core/filesharing/hostlist/hostlistsEnabled",enabled);
        emit preferencesChangedSignal();
    }

    bool isHostlistsEnabled()
    {
        return value("core/filesharing/hostlist/hostlistsEnabled",true).toBool();
    }

    void setLearnHostslistsFromNetworkEnabled(bool enabled)
    {
        setValue("core/filesharing/hostlist/learnHostslistsFromNetworkEnabled",enabled);
        emit preferencesChangedSignal();
    }

    bool isLearnHostslistsFromNetworkEnabled()
    {
        return value("core/filesharing/hostlist/learnHostslistsFromNetworkEnabled",true).toBool();
    }

    void setHostlist(QString hostslist)
    {
        setValue("core/filesharing/hostlist/hostlist",hostslist);
        emit preferencesChangedSignal();
    }

    QString getHostlist()
    {
        return value("core/filesharing/hostlist/hostlist","http://gnunet.org/hostlist http://ioerror.gnunet.org:65535/").toString();
    }


    /*
     *
     * NETWORK
     *
     */



    void setIpv6Enabled(bool enabled)
    {
        setValue("core/network/Ipv6Enabled",enabled);
        emit preferencesChangedSignal();
    }


    bool isIpv6Enabled()
    {
        return value("core/network/Ipv6Enabled",true).toBool();
    }

    void setUploadSpeed(int speed)
    {
        setValue("core/network/uploadSpeed",speed);
        emit preferencesChangedSignal();
    }

    int getUploadSpeed()
    {
        return value("core/network/uploadSpeed",1000000).toInt();
    }

    void setDownloadSpeed(int speed)
    {
        setValue("core/network/downloadSpeed",speed);
        emit preferencesChangedSignal();
    }

    int getDownloadSpeed()
    {
        return value("core/network/downloadSpeed",1000000).toInt();
    }

    void setNeighboursLimit(int neighbours)
    {
        setValue("core/network/neighboursLimit",neighbours);
        emit preferencesChangedSignal();
    }

    int getNeighboursLimit()
    {
        return value("core/network/neighboursLimit",50).toInt();
    }




    /*
     * TCP
     */

    int getTcpPort() const
    {
        return value("core/network/tcp/port",8927).toInt();
    }

    void setTcpPort(int port)
    {
        setValue("core/network/tcp/port",port);
        emit preferencesChangedSignal();
    }

    bool isTcpEnabled() const
    {
        return value("core/network/tcp/enabled",true).toBool();
    }

    void setTcpEnabled(bool enabled)
    {
        setValue("core/network/tcp/enabled",enabled);
        emit preferencesChangedSignal();
    }

    int getTcpAdvertisedPort() const
    {
        return value("core/network/tcp/advertisedPort",8927).toInt();
    }

    void setTcpAdvertisedPort(int port)
    {
        setValue("core/network/tcp/advertisedPort",port);
        emit preferencesChangedSignal();
    }

    int getTcpMaxConnections() const
    {
        return value("core/network/tcp/maxConnections",128).toInt();
    }

    void setTcpMaxConnections(int connections)
    {
        setValue("core/network/tcp/maxConnections",connections);
        emit preferencesChangedSignal();
    }

    /*
     * UDP
     */

    int getUdpPort() const
    {
        return value("core/network/udp/port",8928).toInt();
    }

    void setUdpPort(int port)
    {
        setValue("core/network/udp/port",port);
        emit preferencesChangedSignal();
    }

    bool isUdpEnabled() const
    {
        return value("core/network/udp/enabled",true).toBool();
    }

    void setUdpEnabled(bool enabled)
    {
        setValue("core/network/udp/enabled",enabled);
        emit preferencesChangedSignal();
    }

    int getUdpAdvertisedPort() const
    {
        return value("core/network/udp/advertisedPort",8928).toInt();
    }

    void setUdpAdvertisedPort(int port)
    {
        setValue("core/network/udp/advertisedPort",port);
        emit preferencesChangedSignal();
    }

    int getUdpMaxSpeed() const
    {
        return value("core/network/udp/maxSpeed",1000000).toInt();
    }

    void setUdpMaxSpeed(int speed)
    {
        setValue("core/network/udp/maxSpeed",speed);
        emit preferencesChangedSignal();
    }

    /*
     * NAT
     *
     */
    void setBehindNat(bool enabled)
    {
        setValue("core/network/nat/behindNat",enabled);
        emit preferencesChangedSignal();
    }


    bool isBehindNat()
    {
        return value("core/network/nat/behindNat",false).toBool();
    }

    void setPortsOpen(bool enabled)
    {
        setValue("core/network/nat/portsOpen",enabled);
        emit preferencesChangedSignal();
    }


    bool isPortsOpen()
    {
        return value("core/network/nat/portsOpen",false).toBool();
    }


    void setUPNPEnabled(bool enabled)
    {
        setValue("core/network/nat/UPNPEnabled",enabled);
        emit preferencesChangedSignal();
    }


    bool isUPNPEnabled()
    {
        return value("core/network/nat/UPNPEnabled",false).toBool();
    }


    void setICMPMethodEnabled(bool enabled)
    {
        setValue("core/network/nat/ICMPMethod",enabled);
        emit preferencesChangedSignal();
    }


    bool isICMPMethodEnabled()
    {
        return value("core/network/nat/ICMPMethod",false).toBool();
    }

    void setExternalIpv4Address(QString address)
    {
        setValue("core/network/nat/externalIpv4Address",address);
        emit preferencesChangedSignal();
    }


    QString getExternalIpv4Address()
    {
        return value("core/network/nat/externalIpv4Address","").toString();
    }




    Q_INVOKABLE void save();
    void convertToGnunet();
signals:
    void  preferencesChangedSignal();
    
public slots:
    

};

#endif // PREFERENCES_H
