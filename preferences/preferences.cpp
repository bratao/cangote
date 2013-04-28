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
Preferences::Preferences(QObject *parent) :
    QSettings(QSettings::IniFormat, QSettings::UserScope,"Cangote Team","Cangote", parent)
{



}

void Preferences::convertToGnunet()
{
    QFile data("cangote.conf");
    if (!data.open(QFile::WriteOnly | QFile::Truncate))
    {
        qWarning() << "Failed to create config";
        return;
    }

    QTextStream out(&data);
/*
    [arm]
    PORT = 2087
            [ats]
            AUTOSTART = YES
             PORT = 2098
        # Designated assigment mode: simplistic / MLP
        MODE = simplistic
        # Network specific inbound/outbound quotas
        UNSPECIFIED_QUOTA_IN = 64 KiB
        UNSPECIFIED_QUOTA_OUT = 64 KiB
        # LOOPBACK
        LOOPBACK_QUOTA_IN = unlimited
        LOOPBACK_QUOTA_OUT = unlimited
        # LAN
        LAN_QUOTA_IN = unlimited
        LAN_QUOTA_OUT = unlimited
        # WAN
        WAN_QUOTA_IN = 64 KiB
        WAN_QUOTA_OUT = 64 KiB
        # WLAN
        WLAN_QUOTA_IN = 1 MiB
        WLAN_QUOTA_OUT = 1 MiB


            [core]
            AUTOSTART = YES
            PORT = 2092
            DISABLEV6 =

            [datastore]
            QUOTA = 100000000
             PORT = 2093
            QUOTA = 5 GB
            BLOOMFILTER = $SERVICEHOME/datastore/bloomfilter
            DATABASE = sqlite
            [datastore-sqlite]
            FILENAME = $SERVICEHOME/datastore/sqlite.db
            [datastore-heap]
            HASHMAPSIZE = 1024


            [dht]
            AUTOSTART = YES
            PORT = 2095
            BUCKET_SIZE = 4
            [dhtcache]
            DATABASE = heap
            QUOTA = 50 MB

            [fs]
            AUTOSTART = YES
            INDEXDB = $SERVICEHOME/fs/idxinfo.lst
            RESPECT = $SERVICEHOME/fs/credit/
            IDENTITY_DIR = $SERVICEHOME/fs/identities/
            STATE_DIR = $SERVICEHOME/fs/persistence/
            UPDATE_DIR = $SERVICEHOME/fs/updates/
             PORT = 2094

        # Do we introduce artificial delays? (may improve anonymity)
        DELAY = YES

        # Do we cache content from other nodes? (may improve anonymity)
        CONTENT_CACHING = YES

        # Do we send unsolicited data to other nodes if we have excess bandwidth?
        # (may improve anonymity, probably not a good idea if content_caching is NO)
        CONTENT_PUSHING = YES

        # Maximum number of requests this peer tracks (important for
        # memory consumption; 2k RAM/request is not unusual)
        MAX_PENDING_REQUESTS = 65536

        # How many requests do we have at most waiting in the queue towards
        # the datastore? (important for memory consumption)
        DATASTORE_QUEUE_SIZE = 1024

        # Maximum frequency we're allowed to poll the datastore
        # for content for migration (can be used to reduce
        # GNUnet's disk-IO rate)
        MIN_MIGRATION_DELAY = 100 ms

        # For how many neighbouring peers should we allocate hash maps?
        EXPECTED_NEIGHBOUR_COUNT = 128



        # Maximum number of non-anonymous transfers this peer will support
        # at the same time.  Excessive values mostly have the problem that
        # the service might use more memory, so we need to bound this at
        # some reasonable level.  And if we have a very, very large
        # number, we probably won't have enough bandwidth to suppor them
        # well anyway, so better have a moderate cap.
        MAX_STREAM_CLIENTS = 128



            [hostlist]
            # port for hostlist http server
            HTTPPORT = 8080
            HOME = $SERVICEHOME
            HOSTLISTFILE = $SERVICEHOME/hostlist/learned.data
            BINARY = gnunet-daemon-hostlist
            # consider having "-e" as default as well once implemented
            OPTIONS = -b
            SERVERS = http://v10.gnunet.org/hostlist
        # proxy for downloading hostlists
        HTTP-PROXY =


            [lockmanager]
            AUTOSTART = YES
             PORT = 2100
            HOSTNAME = localhost

            [mesh]
            AUTOSTART = YES
            PORT = 2096
            REFRESH_PATH_TIME = 30 min
            APP_ANNOUNCE_TIME = 1 h
            ID_ANNOUNCE_TIME = 1 h
            CONNECT_TIMEOUT = 30 s
            DEFAULT_TTL = 64
            DHT_REPLICATION_LEVEL = 3
            MAX_TUNNELS = 1000
            MAX_MSGS_QUEUE = 10000
            MAX_PEERS=1000


            [nat]
            # Are we behind NAT?
            BEHIND_NAT = NO

            # Is the NAT hole-punched?
            PUNCHED_NAT = NO

            # Enable UPNP by default?
            ENABLE_UPNP = NO

            # Use addresses from the local network interfaces (inluding loopback, but also others)
            USE_LOCALADDR = YES

            # Use address obtained from a DNS lookup of our hostname
            USE_HOSTNAME = NO

            # External IP address of the NAT box (if known); IPv4 dotted-decimal ONLY at this time (should allow DynDNS!)
            # normal interface IP address for non-NATed peers;
            # possibly auto-detected (using UPnP) if possible if not specified
            # EXTERNAL_ADDRESS =

            # Should we use ICMP-based NAT traversal to try connect to NATed peers
            # or, if we are behind NAT, to allow connections to us?
            ENABLE_ICMP_CLIENT = NO
            ENABLE_ICMP_SERVER = NO

            # IP address of the interface connected to the NAT box; IPv4 dotted-decimal ONLY;
            # normal interface IP address for non-NATed peers;
            # likely auto-detected (via interface list) if not specified (!)
            # INTERNAL_ADDRESS =

            # Disable IPv6 support
            DISABLEV6 = NO

            # Do we use addresses from localhost address ranges? (::1, 127.0.0.0/8)
            RETURN_LOCAL_ADDRESSES = NO

            # How often do we query the DNS resolver
            # for our hostname (to get our own IP), in ms
            HOSTNAME_DNS_FREQUENCY = 1200000

            # How often do we iterate over our
            # network interfaces to check for changes
            # in our IP address? in ms
            IFC_SCAN_FREQUENCY = 3000000

            # How often do we query the DNS resolver
            # for our hostname (to get our own IP), in ms
            DYNDNS_FREQUENCY = 140000

            [gnunet-nat-server]
            HOSTNAME = gnunet.org
            PORT = 5724


            [nse]
            AUTOSTART = YES
            PORT = 2097
            PROOFFILE = $SERVICEHOME/.nse-proof
        # The directory where the NSE services logs timestamps everytime
        # a size estime flooding message is received
        # This option is only used for benchmarking, not in production.
        HISTOGRAM_DIR = $SERVICEHOME

        # How 'slowly' should the proof-of-work be constructed (delay
        # between rounds); sane values between 0 and ~1000.
        # It should rarely make sense to change this value.
        # Only systems with slow CPUs where 5ms is a long time might
        # want it to be reduced.
        WORKDELAY = 5 ms

        # Note: changing any of the values below will make this peer
        # completely incompatible with other peers!

        # How often do peers exchange network size messages?
        # Note that all peers MUST use the same interval.
        # DO NOT CHANGE THIS VALUE, doing so will break the protocol!
        INTERVAL = 1 h

        # 2^22 hash operations take about 2-3h on a modern i7 (single-core)
        # for SCRYPT; with 2ms/op and 5ms workdelay, we can expect
        # the POW calculation to be done by a high-end peer in about 6h
        # DO NOT CHANGE THIS VALUE, doing so will break the protocol!
        WORKBITS = 22



            [peerinfo]
            AUTOSTART = YES
            PORT = 2090
            HOME = $SERVICEHOME
            HOSTS = $SERVICEHOME/peerinfo/
            [uri]
            hello = gnunet-peerinfo
            friend-hello = gnunet-peerinfo

            [resolver]
            AUTOSTART = YES
            PORT = 2089
            HOSTNAME = localhost
            HOME = $SERVICEHOME

            [statistics]
            AUTOSTART = YES
            PORT = 2088
            HOSTNAME = localhost
            HOME = $SERVICEHOME

            [topology]
            MINIMUM-FRIENDS = 0
            FRIENDS-ONLY = NO
            TARGET-CONNECTION-COUNT = 16
            FRIENDS = $SERVICEHOME/friends

            [transport]
            AUTOSTART = YES
             PORT = 2091
            HOSTNAME = localhost
            HOME = $SERVICEHOME

            NEIGHBOUR_LIMIT = 50
            PLUGINS = tcp udp
            BLACKLIST_FILE = $SERVICEHOME/blacklist

            [transport-tcp]
            # Use 0 to ONLY advertise as a peer behind NAT (no port binding)
            PORT = 2086
            ADVERTISED_PORT = 2086
            TESTING_IGNORE_KEYS = ACCEPT_FROM;
            # Maximum number of open TCP connections allowed
            MAX_CONNECTIONS = 128
                    TIMEOUT = 5 s


                    [transport-udp]
                    PORT = 2086
                    BROADCAST = YES
                    BROADCAST_INTERVAL = 30 s
                    MAX_BPS = 1000000
                    TESTING_IGNORE_KEYS = ACCEPT_FROM;


            [PATHS]
            SERVICEHOME = ~/.gnunet/

                    [PEER]
                    PRIVATE_KEY = $SERVICEHOME/private.ecc
*/

    out << "[ats]";

    out << "[datastore]";

    out << "[dhtcache]";

    out << "[topology]";

    out << "[transport-udp]";




}

void Preferences::save()
{
    sync();
}







