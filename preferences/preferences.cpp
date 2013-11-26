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

#include "preferences.h"
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QDir>
Preferences::Preferences(QObject *parent) :
  QSettings(QSettings::IniFormat, QSettings::UserScope,"Cangote","Cangote", parent)
{
  convertToGnunet();
  sync();


}

QString Preferences::getFolder()
{
  QString filepath = fileName();
  QFileInfo fi(filepath);

  QDir fileDir = fi.dir();
  QString fileDirStr = fileDir.absolutePath();

  return fileDirStr;
}

QString Preferences::getGNUNetConfig()
{
  return getFolder() + "/" + "cangote.conf";
}



void Preferences::convertToGnunet()
{

  QFile data(getGNUNetConfig());
  if (!data.open(QFile::WriteOnly | QFile::Truncate))
    {
      qWarning() << "Failed to create config";
      return;
    }

  QTextStream out(&data);



  out << "[arm]\n";
  out << QString("PORT = %1\n").arg(armPort());

  out << "[ats]\n";
  out << QString("PORT = %1\n").arg(atsPort());
  out << QString("WAN_QUOTA_IN = %1 KiB\n").arg(getDownloadSpeed());
  out << QString("WAN_QUOTA_OUT = %1 KiB\n").arg(getUploadSpeed());


  out << "[core]\n";
  out << QString("PORT = %1\n").arg(corePort());

  out << "[datastore]\n";
  out << QString("PORT = %1\n").arg(datastorePort());
  int datastoremb = (int)(getDatastoreSize()* 1000);
  out << QString("QUOTA = %1 MB\n").arg(datastoremb);

  out << "[dht]\n";
  out << QString("PORT = %1\n").arg(dhtPort());

  out << "[dhtcache]\n";
  out << QString("QUOTA = %1 MB\n").arg(getDatacacheSize());

  out << "[dv]\n";
  out << QString("PORT = %1\n").arg(dvPort());

  out << "[fs]\n";
  out << QString("PORT = %1\n").arg(fsPort());
  out << QString("DELAY = %1\n").arg(fsDelay() ? "YES" : "NO");
  out << QString("CONTENT_CACHING = %1\n").arg(isCachingContentEnabled() ? "YES" : "NO");
  out << QString("CONTENT_PUSHING = %1\n").arg(isPushingContentEnabled() ? "YES" : "NO");
  out << QString("MAX_PENDING_REQUESTS = %1\n").arg(fsPendingRequests());
  out << QString("DATASTORE_QUEUE_SIZE = %1\n").arg(fsDataStoreQueueSize());
  out << QString("MIN_MIGRATION_DELAY = %1\n").arg(fsMinMigrationDelay());
  out << QString("EXPECTED_NEIGHBOUR_COUNT = %1\n").arg(fsExpectedNeighbourCount());
  out << QString("MAX_MESH_CLIENTS = %1\n").arg(fsMaxMeshClients());

  out << "[gns]\n";
  out << QString("PORT = %1\n").arg(gnsPort());
  out << QString("MAX_PARALLEL_BACKGROUND_QUERIES = %1\n").arg(gnsMaxParallelBackgroundQueries());
  out << QString("ZONE_PUBLISH_TIME_WINDOW = %1\n").arg(gnsZonePublishTimeWindow());


  out << "[hostlist]\n";
  out << QString("HTTPPORT = %1\n").arg(gnsPort());
  out << QString("HTTP-PROXY = %1\n").arg(hostlistHttpProxy());

  QString hostlistOptions;
  if(isHostlistsEnabled())
    hostlistOptions+= " -b";

  if(isLearnHostslistsFromNetworkEnabled())
    hostlistOptions+= " -e";

  out << QString("OPTIONS = %1\n").arg(hostlistOptions);
  out << QString("SERVERS = %1\n").arg(getHostlist());


  out << "[identity]\n";
  out << QString("PORT = %1\n").arg(identityPort());

  out << "[mesh]\n";
  out << QString("PORT = %1\n").arg(meshPort());
  out << QString("MAX_CONNECTIONS = %1\n").arg(meshMaxConnections());
  out << QString("MAX_MSGS_QUEUE = %1\n").arg(meshMsgsQueue());
  out << QString("MAX_PEERS = %1\n").arg(meshPeers());

  out << "[namecache]\n";
  out << QString("PORT = %1\n").arg(namecachePort());

  out << "[namestore]\n";
  out << QString("PORT = %1\n").arg(namestorePort());


  out << "[nat]\n";
  out << QString("BEHIND_NAT = %1\n").arg(isBehindNat() ? "YES" : "NO");
  out << QString("PUNCHED_NAT = %1\n").arg(isPortsOpen() ? "YES" : "NO");
  out << QString("ENABLE_UPNP = %1\n").arg(isUPNPEnabled() ? "YES" : "NO");

  out << QString("ENABLE_ICMP_CLIENT = %1\n").arg(isICMPMethodEnabled() ? "YES" : "NO");
  out << QString("ENABLE_ICMP_SERVER = %1\n").arg(isICMPMethodEnabled() ? "YES" : "NO");


  if(getExternalIpv4Address().length() > 2)
    out << QString("EXTERNAL_ADDRESS = %1\n").arg(getExternalIpv4Address());
  if(internalIpv4Address().length() > 2)
    out << QString("INTERNAL_ADDRESS = %1\n").arg(internalIpv4Address());
  out << QString("USE_LOCALADDR = %1\n").arg(natUseLocalAddresses() ? "YES" : "NO");


  out << QString("USE_HOSTNAME = %1\n").arg(natUseHostname() ? "YES" : "NO");
  out << QString("DISABLEV6 = %1\n").arg(isIpv6Enabled() ? "YES" : "NO");
  out << QString("RETURN_LOCAL_ADDRESSES = %1\n").arg(natReturnLocalAddresses() ? "YES" : "NO");
  out << QString("HOSTNAME_DNS_FREQUENCY = %1 min\n").arg(natHostnameDnsFrequency());
  out << QString("IFC_SCAN_FREQUENCY = %1 min\n").arg(natIfcScanFrequency());
  out << QString("DYNDNS_FREQUENCY = %1 min\n").arg(natDynDnsFrequency());


  out << "[nse]\n";
  out << QString("PORT = %1\n").arg(nsePort());
  out << QString("WORKDELAY = %1\n").arg(nseWorkDelay());


  out << "[peerinfo]\n";
  out << QString("PORT = %1\n").arg(peerinfoPort());


  out << "[regex]\n";
  out << QString("PORT = %1\n").arg(regexPort());


  out << "[resolver]\n";
  out << QString("PORT = %1\n").arg(resolverPort());

  out << "[revocation]\n";
  out << QString("PORT = %1\n").arg(revocationPort());


  out << "[statistics]\n";
  out << QString("PORT = %1\n").arg(statisticsPort());


  out << "[topology]\n";
  out << QString("MINIMUM-FRIENDS = %1\n").arg(getMinimalNumberOfFriends());
  out << QString("FRIENDS-ONLY = %1\n").arg(isFriendToFriendOnlyEnabled() ? "YES" : "NO");




  out << "[transport]\n";
  out << QString("PORT = %1\n").arg(transportPort());
  out << QString("NEIGHBOUR_LIMIT = %1\n").arg(getNeighboursLimit());

  QString plugins;
  if(isTcpEnabled())
    plugins += " tcp";
  if(isUdpEnabled())
    plugins += " udp";

  out << QString("PLUGINS = %1\n").arg(plugins);


  out << "[transport-tcp]\n";
  out << QString("PORT = %1\n").arg(getTcpPort());
  out << QString("ADVERTISED_PORT = %1\n").arg(getTcpAdvertisedPort());
  out << QString("MAX_CONNECTIONS = %1\n").arg(getTcpMaxConnections());
  out << QString("TIMEOUT = %1 s\n").arg(tcpTimeout());

  out << "[transport-udp]\n";
  out << QString("PORT = %1\n").arg(getUdpPort());
  out << QString("ADVERTISED_PORT = %1\n").arg(getUdpAdvertisedPort());
  out << QString("MAX_BPS = %1\n").arg(getUdpMaxSpeed());



  out << "[PATHS]\n";
  out << QString("HOME = %1 \n").arg(getFolder() + "/gnunet");
  //out << QString("GNUNET_HOME = %1 \n").arg(getFolder() + "/gnunet");
/*  out << QString("GNUNET_DATA_HOME = %1 \n").arg(getFolder() + "/gnunet/");
  out << QString("GNUNET_CONFIG_HOME = %1 \n").arg(getFolder() + "/gnunet/");
  out << QString("GNUNET_CACHE_HOME = %1 \n").arg(getFolder() + "/gnunet/");
*/

  out.flush();
  data.flush();


}

void Preferences::save()
{
  convertToGnunet();
  sync();
}







