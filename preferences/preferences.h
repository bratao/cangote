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
#include <QStandardPaths>
#include <QDir>

class Preferences : public QSettings
{
  Q_OBJECT
  Q_DISABLE_COPY (Preferences)


  /*
   *
   * GENERAL
   *
   *
   */
  Q_PROPERTY(bool checkNewVersion READ checkNewVersion WRITE setCheckNewVersion NOTIFY checkNewVersionChangedSignal)
  Q_PROPERTY(QString nextCheckDate READ nextCheckDate WRITE setNextCheckDate)




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


  /*
   *ADVANCED
   *
   */
  Q_PROPERTY(int armPort READ armPort WRITE setArmPort NOTIFY armPortChangedSignal)
  Q_PROPERTY(int atsPort READ atsPort WRITE setAtsPort NOTIFY atsPortChangedSignal)
  Q_PROPERTY(int corePort READ corePort WRITE setCorePort NOTIFY corePortChangedSignal)

  Q_PROPERTY(int datastorePort READ datastorePort WRITE setDatastorePort NOTIFY datastorePortChangedSignal)


  Q_PROPERTY(int dhtPort READ dhtPort WRITE setDhtPort NOTIFY dhtPortChangedSignal)
  Q_PROPERTY(int dvPort READ dvPort WRITE setDvPort NOTIFY dvPortChangedSignal)


  Q_PROPERTY(int fsPort READ fsPort WRITE setFsPort NOTIFY fsPortChangedSignal)
  Q_PROPERTY(bool fsDelay READ fsDelay WRITE setFsDelay NOTIFY fsDelayChangedSignal)
  Q_PROPERTY(int fsPendingRequests READ fsPendingRequests WRITE setFsPendingRequests NOTIFY fsPendingRequestsChangedSignal)
  Q_PROPERTY(int fsDataStoreQueueSize READ fsDataStoreQueueSize WRITE setFsDataStoreQueueSize NOTIFY fsDataStoreQueueSizeChangedSignal)
  Q_PROPERTY(int fsMinMigrationDelay READ fsMinMigrationDelay WRITE setFsMinMigrationDelay NOTIFY fsMinMigrationDelayChangedSignal)
  Q_PROPERTY(int fsExpectedNeighbourCount READ fsExpectedNeighbourCount WRITE setFsExpectedNeighbourCount NOTIFY fsExpectedNeighbourCountChangedSignal)
  Q_PROPERTY(int fsMaxMeshClients READ fsMaxMeshClients WRITE setFsMaxMeshClients NOTIFY fsMaxMeshClientsChangedSignal)



  Q_PROPERTY(int gnsPort READ gnsPort WRITE setGnsPort NOTIFY gnsPortChangedSignal)
  Q_PROPERTY(int gnsMaxParallelBackgroundQueries READ gnsMaxParallelBackgroundQueries WRITE setGnsMaxParallelBackgroundQueries NOTIFY gnsMaxParallelBackgroundQueriesChangedSignal)
  Q_PROPERTY(int gnsZonePublishTimeWindow READ gnsZonePublishTimeWindow WRITE setGnsZonePublishTimeWindow NOTIFY gnsZonePublishTimeWindowChangedSignal)

  Q_PROPERTY(int hostlistHttpPort READ hostlistHttpPort WRITE setHostlistHttpPort NOTIFY hostlistHttpPortChangedSignal)
  Q_PROPERTY(QString hostlistHttpProxy READ hostlistHttpProxy WRITE setHostlistHttpProxy NOTIFY hostlistHttpProxyChangedSignal)



  Q_PROPERTY(int identityPort READ identityPort WRITE setIdentityPort NOTIFY identityPortChangedSignal)
  Q_PROPERTY(int meshPort READ meshPort WRITE setMeshPort NOTIFY meshPortChangedSignal)
  Q_PROPERTY(int meshMaxConnections READ meshMaxConnections WRITE setMeshMaxConnections NOTIFY meshMaxConnectionsChangedSignal)
  Q_PROPERTY(int meshMsgsQueue READ meshMsgsQueue WRITE setMeshMsgsQueue NOTIFY meshMsgsQueueChangedSignal)
  Q_PROPERTY(int meshPeers READ meshPeers WRITE setMeshPeers NOTIFY meshPeersChangedSignal)



  Q_PROPERTY(int namecachePort READ namecachePort WRITE setNamecachePort NOTIFY namecachePortChangedSignal)
  Q_PROPERTY(int namestorePort READ namestorePort WRITE setNamestorePort NOTIFY namestorePortChangedSignal)


  /*
   * NAT
   */
  Q_PROPERTY(QString externalIpv4Address READ getExternalIpv4Address WRITE setExternalIpv4Address NOTIFY externalIpv4AddressChangedSignal)
  Q_PROPERTY(QString internalIpv4Address READ internalIpv4Address WRITE setInternalIpv4Address NOTIFY internalIpv4AddresssChangedSignal)
  Q_PROPERTY(bool natUseLocalAddresses READ natUseLocalAddresses WRITE setNatUseLocalAddresses NOTIFY natUseLocalAddressesChangedSignal)
  Q_PROPERTY(bool natUseHostname READ natUseHostname WRITE setNatUseHostname NOTIFY natUseHostnameChangedSignal)
  Q_PROPERTY(bool natReturnLocalAddresses READ natReturnLocalAddresses WRITE setNatReturnLocalAddresses NOTIFY natReturnLocalAddressesChangedSignal)
  Q_PROPERTY(int natHostnameDnsFrequency READ natHostnameDnsFrequency WRITE setNatHostnameDnsFrequency NOTIFY natHostnameDnsFrequencyChangedSignal)
  Q_PROPERTY(int natIfcScanFrequency READ natIfcScanFrequency WRITE setNatIfcScanFrequency NOTIFY natIfcScanFrequencyChangedSignal)
  Q_PROPERTY(int natDynDnsFrequency READ natDynDnsFrequency WRITE setNatDynDnsFrequency NOTIFY natDynDnsFrequencyChangedSignal)


  /*
   * NSE
   */
  Q_PROPERTY(int nsePort READ nsePort WRITE setNsePort NOTIFY nsePortChangedSignal)
  Q_PROPERTY(int nseWorkDelay READ nseWorkDelay WRITE setNseWorkDelay NOTIFY nseWorkDelayChangedSignal)




  Q_PROPERTY(int peerinfoPort READ peerinfoPort WRITE setPeerinfoPort NOTIFY peerinfoPortChangedSignal)
  Q_PROPERTY(int regexPort READ regexPort WRITE setRegexPort NOTIFY regexPortChangedSignal)
  Q_PROPERTY(int resolverPort READ resolverPort WRITE setResolverPort NOTIFY resolverPortChangedSignal)
  Q_PROPERTY(int revocationPort READ revocationPort WRITE setRevocationPort NOTIFY revocationPortChangedSignal)
  Q_PROPERTY(int statisticsPort READ statisticsPort WRITE setStatisticsPort NOTIFY statisticsPortChangedSignal)
  Q_PROPERTY(int transportPort READ transportPort WRITE setTransportPort NOTIFY transportPortChangedSignal)

  Q_PROPERTY(int tcpTimeout READ tcpTimeout WRITE setTcpTimeout NOTIFY tcpTimeoutChangedSignal)




public:
  explicit Preferences(QObject *parent = 0);




  /*
   *
   * GENERAL
   *
   *
   */

  bool checkNewVersion()
  {

    return value("core/checkNewVersion",true).toBool();
  }

  void setCheckNewVersion(bool flag)
  {

    setValue("core/checkNewVersion",flag);
    emit checkNewVersionChangedSignal(flag);
  }

  QString nextCheckDate()
  {

    return value("core/nextCheckDate","").toString();
  }

  void setNextCheckDate(QString date)
  {

    setValue("core/setNextCheckDate",date);
  }
  /*
   *
   * DIRECTORIES
   *
   *
   */
  QString getDownloadDirectory()
  {
    QString dirStr = value("core/directories/downloadDirectory","").toString();

    //If is NULL create on user home directory
    if (dirStr.isEmpty())
      {
        dirStr = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/Cangote";
      }

    QDir dir(dirStr);
    if (!dir.exists()) {
        dir.mkpath(".");
      }

    return dirStr;
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

    return value("core/filesharing/datacacheSize",50).toInt();
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
    return value("core/filesharing/friendToFriend/friendToFriendOnly",false).toBool();
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
    return value("core/network/tcp/port",2086).toInt();
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
    return value("core/network/tcp/advertisedPort",2086).toInt();
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








  /*
     * Advanced
     */

  void setArmPort(int port)
  {
    setValue("core/advanced/armPort",port);
    emit armPortChangedSignal(port);
  }


  int armPort()
  {
    return value("core/advanced/armPort",2087).toInt();
  }

  void setAtsPort(int port)
  {
    setValue("core/advanced/atsPort",port);
    emit atsPortChangedSignal(port);
  }

  int atsPort()
  {
    return value("core/advanced/atsPort",2098).toInt();
  }

  void setCorePort(int port)
  {
    setValue("core/advanced/corePort",port);
    emit corePortChangedSignal(port);
  }

  int corePort()
  {
    return value("core/advanced/corePort",2092).toInt();
  }

  void setDatastorePort(int port)
  {
    setValue("core/advanced/datastorePort",port);
    emit datastorePortChangedSignal(port);
  }

  int datastorePort()
  {
    return value("core/advanced/datastorePort",2093).toInt();
  }

  void setDhtPort(int port)
  {
    setValue("core/advanced/dhtPort",port);
    emit dhtPortChangedSignal(port);
  }

  int dhtPort()
  {
    return value("core/advanced/dhtPort",2095).toInt();
  }

  void setDvPort(int port)
  {
    setValue("core/advanced/dvPort",port);
    emit dvPortChangedSignal(port);
  }

  int dvPort()
  {
    return value("core/advanced/dvPort",2571).toInt();
  }

  /*
   * FS
   */
  void setFsPort(int port)
  {
    setValue("core/advanced/fsPort",port);
    emit fsPortChangedSignal(port);
  }

  int fsPort()
  {
    return value("core/advanced/fsPort",2094).toInt();
  }

  void setFsDelay(bool enable)
  {
    setValue("core/advanced/fsPort",enable);
    emit fsDelayChangedSignal(enable);
  }

  bool fsDelay()
  {
    return value("core/advanced/fsDelay",true).toBool();
  }

  void setFsPendingRequests(int requests)
  {
    setValue("core/advanced/fsPendingRequests",requests);
    emit fsPendingRequestsChangedSignal(requests);
  }

  int fsPendingRequests()
  {
    return value("core/advanced/fsPendingRequests",65536).toInt();
  }

  void setFsDataStoreQueueSize(int queue)
  {
    setValue("core/advanced/fsDataStoreQueueSize",queue);
    emit fsDataStoreQueueSizeChangedSignal(queue);
  }

  int fsDataStoreQueueSize()
  {
    return value("core/advanced/fsDataStoreQueueSize",1024).toInt();
  }

  void setFsMinMigrationDelay(int delay)
  {
    setValue("core/advanced/fsMinMigrationDelay",delay);
    emit fsMinMigrationDelayChangedSignal(delay);
  }

  int fsMinMigrationDelay()
  {
    return value("core/advanced/fsMinMigrationDelay",100).toInt();
  }

  void setFsExpectedNeighbourCount(int neighbours)
  {
    setValue("core/advanced/fsExpectedNeighbourCount",neighbours);
    emit fsExpectedNeighbourCountChangedSignal(neighbours);
  }

  int fsExpectedNeighbourCount()
  {
    return value("core/advanced/fsExpectedNeighbourCount",128).toInt();
  }

  void setFsMaxMeshClients(int clients)
  {
    setValue("core/advanced/fsMaxMeshClients",clients);
    emit fsMaxMeshClientsChangedSignal(clients);
  }

  int fsMaxMeshClients()
  {
    return value("core/advanced/fsMaxMeshClients",128).toInt();
  }




  /*
   * GNS
   */

  void setGnsPort(int port)
  {
    setValue("core/advanced/gnsPort",port);
    emit gnsPortChangedSignal(port);
  }

  int gnsPort()
  {
    return value("core/advanced/gnsPort",2102).toInt();
  }


  void setGnsMaxParallelBackgroundQueries(int number)
  {
    setValue("core/advanced/gnsMaxParallelBackgroundQueries",number);
    emit gnsMaxParallelBackgroundQueriesChangedSignal(number);
  }

  int gnsMaxParallelBackgroundQueries()
  {
    return value("core/advanced/gnsMaxParallelBackgroundQueries",1000).toInt();
  }

  void setGnsZonePublishTimeWindow(int time)
  {
    setValue("core/advanced/gnsZonePublishTimeWindow",time);
    emit gnsZonePublishTimeWindowChangedSignal(time);
  }

  int gnsZonePublishTimeWindow()
  {
    return value("core/advanced/gnsZonePublishTimeWindow",4).toInt();
  }



  /*
   * Hostlist
   */
  void setHostlistHttpPort(int port)
  {
    setValue("core/advanced/hostlistHttpPort",port);
    emit hostlistHttpPortChangedSignal(port);
  }

  int hostlistHttpPort()
  {
    return value("core/advanced/hostlistHttpPort",8080).toInt();
  }


  void setHostlistHttpProxy(QString proxy)
  {
    setValue("core/advanced/hostlistHttpProxy",proxy);
    emit hostlistHttpProxyChangedSignal(proxy);
  }

  QString hostlistHttpProxy()
  {
    return value("core/advanced/hostlistHttpProxy","").toString();
  }



  void setIdentityPort(int port)
  {
    setValue("core/advanced/identityPort",port);
    emit identityPortChangedSignal(port);
  }

  int identityPort()
  {
    return value("core/advanced/identityPort",2108).toInt();
  }

  /*
   * Mesh
   */

  void setMeshPort(int port)
  {
    setValue("core/advanced/meshPort",port);
    emit meshPortChangedSignal(port);
  }

  int meshPort()
  {
    return value("core/advanced/meshPort",2096).toInt();
  }

  void setMeshMaxConnections(int connections)
  {
    setValue("core/advanced/meshMaxConnections",connections);
    emit meshMaxConnectionsChangedSignal(connections);
  }

  int meshMaxConnections()
  {
    return value("core/advanced/meshMaxConnections",1000).toInt();
  }

  void setMeshMsgsQueue(int queue)
  {
    setValue("core/advanced/meshMsgsQueue",queue);
    emit meshMsgsQueueChangedSignal(queue);
  }

  int meshMsgsQueue()
  {
    return value("core/advanced/meshMsgsQueue",10000).toInt();
  }

  void setMeshPeers(int peers)
  {
    setValue("core/advanced/meshPeers",peers);
    emit meshPeersChangedSignal(peers);
  }

  int meshPeers()
  {
    return value("core/advanced/meshPeers",1000).toInt();
  }









  void setNamecachePort(int port)
  {
    setValue("core/advanced/namecachePort",port);
    emit namecachePortChangedSignal(port);
  }

  int namecachePort()
  {
    return value("core/advanced/namecachePort",2113).toInt();
  }

  void setNamestorePort(int port)
  {
    setValue("core/advanced/namestorePort",port);
    emit namestorePortChangedSignal(port);
  }

  int namestorePort()
  {
    return value("core/advanced/namestorePort",2099).toInt();
  }





  /*
   * NAT
   */
  void setExternalIpv4Address(QString address)
  {
    setValue("core/network/nat/externalIpv4Address",address);
    emit externalIpv4AddressChangedSignal(address);
  }
  QString getExternalIpv4Address()
  {
    return value("core/network/nat/externalIpv4Address","").toString();
  }


  void setInternalIpv4Address(QString address)
  {
    setValue("core/network/nat/internalIpv4Address",address);
    emit internalIpv4AddresssChangedSignal(address);
  }
  QString internalIpv4Address()
  {
    return value("core/network/nat/internalIpv4Address","").toString();
  }


  void setNatUseLocalAddresses(bool enable)
  {
    setValue("core/network/nat/natUseLocalAddresses",enable);
    emit natUseLocalAddressesChangedSignal(enable);
  }
  bool natUseLocalAddresses()
  {
    return value("core/network/nat/natUseLocalAddresses",true).toBool();
  }


  void setNatUseHostname(bool enable)
  {
    setValue("core/network/nat/natUseHostname",enable);
    emit natUseHostnameChangedSignal(enable);
  }
  bool natUseHostname()
  {
    return value("core/network/nat/natUseHostname",false).toBool();
  }


  void setNatReturnLocalAddresses(bool enable)
  {
    setValue("core/network/nat/natReturnLocalAddresses",enable);
    emit natReturnLocalAddressesChangedSignal(enable);
  }
  bool natReturnLocalAddresses()
  {
    return value("core/network/nat/natReturnLocalAddresses",false).toBool();
  }


  void setNatHostnameDnsFrequency(int value)
  {
    setValue("core/network/nat/natHostnameDnsFrequency",value);
    emit natHostnameDnsFrequencyChangedSignal(value);
  }
  int natHostnameDnsFrequency()
  {
    return value("core/network/nat/natHostnameDnsFrequency",20).toInt();
  }


  void setNatIfcScanFrequency(int value)
  {
    setValue("core/network/nat/natIfcScanFrequency",value);
    emit natIfcScanFrequencyChangedSignal(value);
  }
  int natIfcScanFrequency()
  {
    return value("core/network/nat/natIfcScanFrequency",15).toInt();
  }


  void setNatDynDnsFrequency(int value)
  {
    setValue("core/network/nat/natDynDnsFrequency",value);
    emit natDynDnsFrequencyChangedSignal(value);
  }
  int natDynDnsFrequency()
  {
    return value("core/network/nat/natDynDnsFrequency",7).toInt();
  }



  /*
   * NSE
   */

  void setNsePort(int port)
  {
    setValue("core/advanced/nsePort",port);
    emit nsePortChangedSignal(port);
  }
  int nsePort()
  {
    return value("core/advanced/nsePort",2097).toInt();
  }


  void setNseWorkDelay(int delay)
  {
    setValue("core/advanced/nseWorkDelay",delay);
    emit nseWorkDelayChangedSignal(delay);
  }
  int nseWorkDelay()
  {
    return value("core/advanced/nseWorkDelay",5).toInt();
  }






  void setPeerinfoPort(int port)
  {
    setValue("core/advanced/peerinfoPort",port);
    emit peerinfoPortChangedSignal(port);
  }
  int peerinfoPort()
  {
    return value("core/advanced/peerinfoPort",2090).toInt();
  }

  void setRegexPort(int port)
  {
    setValue("core/advanced/regexPort",port);
    emit regexPortChangedSignal(port);
  }
  int regexPort()
  {
    return value("core/advanced/regexPort",2107).toInt();
  }

  void setResolverPort(int port)
  {
    setValue("core/advanced/resolverPort",port);
    emit resolverPortChangedSignal(port);
  }
  int resolverPort()
  {
    return value("core/advanced/resolverPort",2089).toInt();
  }

  void setRevocationPort(int port)
  {
    setValue("core/advanced/revocationPort",port);
    emit revocationPortChangedSignal(port);
  }
  int revocationPort()
  {
    return value("core/advanced/revocationPort",2112).toInt();
  }

  void setStatisticsPort(int port)
  {
    setValue("core/advanced/statisticsPort",port);
    emit statisticsPortChangedSignal(port);
  }
  int statisticsPort()
  {
    return value("core/advanced/statisticsPort",2088).toInt();
  }

  void setTransportPort(int port)
  {
    setValue("core/advanced/transportPort",port);
    emit transportPortChangedSignal(port);
  }
  int transportPort()
  {
    return value("core/advanced/transportPort",2091).toInt();
  }

  /*
   * TCP
   */
  void setTcpTimeout(int timeout)
  {
    setValue("core/advanced/tcpTimeout",timeout);
    emit tcpTimeoutChangedSignal(timeout);
  }
  int tcpTimeout()
  {
    return value("core/advanced/tcpTimeout",5).toInt();
  }




  Q_INVOKABLE void save();
  void convertToGnunet();
  QString getFolder();
  QString getGNUNetConfig();
signals:
  /*
   *
   * GENERAL
   *
   *
   */
  void checkNewVersionChangedSignal(bool flag);


  void preferencesChangedSignal();
  void armPortChangedSignal(int port);
  void atsPortChangedSignal(int port);
  void corePortChangedSignal(int port);
  void datastorePortChangedSignal(int port);
  void dhtPortChangedSignal(int port);
  void dvPortChangedSignal(int port);
  void fsPortChangedSignal(int port);


  void fsPortChangedSignal(bool enable);
  void fsDelayChangedSignal(bool enable);
  void fsPendingRequestsChangedSignal(int requests);
  void fsDataStoreQueueSizeChangedSignal(int queue);
  void fsMinMigrationDelayChangedSignal(int delay);
  void fsExpectedNeighbourCountChangedSignal(int neighbours);
  void fsMaxMeshClientsChangedSignal(int clients);


  void gnsPortChangedSignal(int port);
  void gnsMaxParallelBackgroundQueriesChangedSignal(int number);
  void gnsZonePublishTimeWindowChangedSignal(int time);

  void hostlistHttpPortChangedSignal(int port);
  void hostlistHttpProxyChangedSignal(QString proxy);


  void identityPortChangedSignal(int port);

  void meshPortChangedSignal(int port);
  void meshMaxConnectionsChangedSignal(int connections);
  void meshMsgsQueueChangedSignal(int queue);
  void meshPeersChangedSignal(int peers);

  void namecachePortChangedSignal(int port);
  void namestorePortChangedSignal(int port);

  void externalIpv4AddressChangedSignal(QString address);
  void internalIpv4AddresssChangedSignal(QString address);
  void natUseLocalAddressesChangedSignal(bool enable);
  void natUseHostnameChangedSignal(bool enable);
  void natReturnLocalAddressesChangedSignal(bool enable);
  void natHostnameDnsFrequencyChangedSignal(int value);
  void natIfcScanFrequencyChangedSignal(int value);
  void natDynDnsFrequencyChangedSignal(int value);


  void nsePortChangedSignal(int port);
  void nseWorkDelayChangedSignal(int delay);



  void peerinfoPortChangedSignal(int port);
  void regexPortChangedSignal(int port);
  void resolverPortChangedSignal(int port);
  void revocationPortChangedSignal(int port);
  void statisticsPortChangedSignal(int port);
  void transportPortChangedSignal(int port);

  void tcpTimeoutChangedSignal(int timeout);


public slots:


};

#endif // PREFERENCES_H
