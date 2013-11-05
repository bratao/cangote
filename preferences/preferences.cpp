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
HOSTNAME = localhost
BINARY = gnunet-service-arm


[ats]
PORT = 2098
HOSTNAME = localhost
BINARY = gnunet-service-ats

# Designated assigment mode: PROPORTIONAL / MLP / RIL
MODE = PROPORTIONAL

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
# BLUETOOTH
BLUETOOTH_QUOTA_IN = 128 KiB
BLUETOOTH_QUOTA_OUT = 128 KiB


[core]
AUTOSTART = YES
PORT = 2092
HOSTNAME = localhost
BINARY = gnunet-service-core


[datastore]
AUTOSTART = YES
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-datastore.sock
PORT = 2093
HOSTNAME = localhost
BINARY = gnunet-service-datastore
QUOTA = 5 GB
BLOOMFILTER = $GNUNET_DATA_HOME/datastore/bloomfilter
DATABASE = sqlite

[datastore-sqlite]
FILENAME = $GNUNET_DATA_HOME/datastore/sqlite.db



[dht]
AUTOSTART = YES
PORT = 2095
HOSTNAME = localhost
BINARY = gnunet-service-dht
BUCKET_SIZE = 4
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-dht.sock

# Should the DHT cache results that we are routing in the DATACACHE as well?
CACHE_RESULTS = YES

[dhtcache]
DATABASE = heap
QUOTA = 50 MB


[dns]
AUTOSTART = YES
HOSTNAME = localhost
BINARY = gnunet-service-dns
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-dns.sock


[dv]
AUTOSTART = YES
ACCEPT_FROM6 = ::1;
ACCEPT_FROM = 127.0.0.1;
BINARY = gnunet-service-dv
HOSTNAME = localhost
PORT = 2571
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-dv.sock

[fs]
AUTOSTART = YES
INDEXDB = $GNUNET_DATA_HOME/fs/idxinfo.lst
RESPECT = $GNUNET_DATA_HOME/fs/credit/
STATE_DIR = $GNUNET_DATA_HOME/fs/persistence/
UPDATE_DIR = $GNUNET_DATA_HOME/fs/updates/
PORT = 2094
HOSTNAME = localhost

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
MAX_MESH_CLIENTS = 128


[gns]
AUTOSTART = YES
HOSTNAME = localhost
BINARY = gnunet-service-gns
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-gns.sock
PORT = 2102


# How many queries is GNS allowed to perform in the background at the same time?
MAX_PARALLEL_BACKGROUND_QUERIES = 1000

# How frequently do we try to publish our full zone?
ZONE_PUBLISH_TIME_WINDOW = 4 h


[hostlist]
# port for hostlist http server
HTTPPORT = 8080
HOSTLISTFILE = $GNUNET_CONFIG_HOME/hostlist/learned.txt
BINARY = gnunet-daemon-hostlist
# consider having "-e" as default as well once implemented
OPTIONS = -b
SERVERS = http://v10.gnunet.org/hostlist
# http://ioerror.gnunet.org:65535/
# proxy for downloading hostlists
HTTP-PROXY =
# bind hostlist http server to a specific IPv4 or IPv6
# BINDTOIP =

[identity]
AUTOSTART = YES
USER_SERVICE = YES
PORT = 2108
HOSTNAME = localhost
BINARY = gnunet-service-identity
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-identity.unix
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = YES

# Directory where we store information about our egos
EGODIR = $GNUNET_DATA_HOME/identity/egos/

# File where we store default identities for subsystems
SUBSYSTEM_CFG = $GNUNET_CONFIG_HOME/identity/subsystem_defaults.conf


[mesh]
AUTOSTART = YES
PORT = 2096
HOSTNAME = localhost
BINARY = gnunet-service-mesh
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-mesh.sock
UNIX_MATCH_UID = YES
UNIX_MATCH_GID = YES
REFRESH_CONNECTION_TIME = 5 min
# PATH_TIME deprecated, remove soon
REFRESH_PATH_TIME = 30 min
ID_ANNOUNCE_TIME = 1 h
APP_ANNOUNCE_TIME = 1 h
CONNECT_TIMEOUT = 30 s
DEFAULT_TTL = 64
DHT_REPLICATION_LEVEL = 3
MAX_TUNNELS = 1000
# MAX_TUNNELS deprecated
MAX_CONNECTIONS = 1000
MAX_MSGS_QUEUE = 10000
MAX_PEERS = 1000


[namecache]
AUTOSTART = YES
USER_SERVICE = NO
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-namecache.sock
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = YES
 PORT = 2113
HOSTNAME = localhost
BINARY = gnunet-service-namecache
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
DATABASE = sqlite

[namecache-sqlite]
FILENAME = $GNUNET_DATA_HOME/namecache/sqlite.db

[namecache-postgres]
CONFIG = connect_timeout=10; dbname=gnunet
TEMPORARY_TABLE = NO



[namestore]
AUTOSTART = YES
USER_SERVICE = YES
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-namestore.sock
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = YES
 PORT = 2099
HOSTNAME = localhost
BINARY = gnunet-service-namestore
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
DATABASE = sqlite

[namestore-sqlite]
FILENAME = $GNUNET_DATA_HOME/namestore/sqlite.db

[namestore-postgres]
CONFIG = connect_timeout=10; dbname=gnunet
TEMPORARY_TABLE = NO

[uri]
gns = gnunet-namestore



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
# for our hostname (to get our own IP)
HOSTNAME_DNS_FREQUENCY = 20 min

# How often do we iterate over our
# network interfaces to check for changes
# in our IP address?
IFC_SCAN_FREQUENCY = 15 min

# How often do we query the DNS resolver
# for our hostname (to get our own IP)
DYNDNS_FREQUENCY = 7 min

[gnunet-nat-server]
HOSTNAME = gnunet.org
PORT = 5724

[nse]
AUTOSTART = YES
PORT = 2097
HOSTNAME = localhost
BINARY = gnunet-service-nse
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-nse.unix
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = YES
PROOFFILE = $GNUNET_DATA_HOME/nse/proof.dat

# The directory where the NSE services logs timestamps everytime
# a size estime flooding message is received
# This option is only used for benchmarking, not in production.
HISTOGRAM_DIR = $GNUNET_CACHE_HOME/nse/histogram/

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
HOSTNAME = localhost
BINARY = gnunet-service-peerinfo
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-peerinfo.sock
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = YES
# DISABLE_SOCKET_FORWARDING = NO
# USERNAME =
# MAXBUF =
# TIMEOUT =
# DISABLEV6 =
# BINDTO =
# REJECT_FROM =
# REJECT_FROM6 =
# PREFIX =
HOSTS = $GNUNET_DATA_HOME/peerinfo/hosts/

# Option to disable all disk IO; only useful for testbed runs
# (large-scale experiments); disables persistence of HELLOs!
NO_IO = NO

# Load HELLOs shipped with GNUnet
USE_INCLUDED_HELLOS = YES

[uri]
hello = gnunet-peerinfo
friend-hello = gnunet-peerinfo


[regex]
AUTOSTART = YES
 PORT = 2107
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-regex.sock
HOSTNAME = localhost
BINARY = gnunet-service-regex
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;


[resolver]
AUTOSTART = YES
PORT = 2089
HOSTNAME = localhost
BINARY = gnunet-service-resolver
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-resolver.sock
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = NO
# DISABLE_SOCKET_FORWARDING = NO
# USERNAME =
# MAXBUF =
# TIMEOUT =
# DISABLEV6 =
# BINDTO =
# REJECT_FROM =
# REJECT_FROM6 =
# PREFIX =

[revocation]
AUTOSTART = YES
PORT = 2112
HOSTNAME = localhost
BINARY = gnunet-service-revocation
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-revocation.unix
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = YES

# 2^25 hash operations take about 16-24h on a modern i7
# (using only a single-core) with SCRYPT.
# DO NOT CHANGE THIS VALUE, doing so will break the protocol!
WORKBITS = 25

DATABASE = $GNUNET_DATA_HOME/revocation.dat


[statistics]
AUTOSTART = YES
PORT = 2088
HOSTNAME = localhost
BINARY = gnunet-service-statistics
ACCEPT_FROM = 127.0.0.1;
ACCEPT_FROM6 = ::1;
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-statistics.sock
UNIX_MATCH_UID = NO
UNIX_MATCH_GID = YES
DATABASE = $GNUNET_DATA_HOME/statistics.dat


[topology]
MINIMUM-FRIENDS = 0
FRIENDS-ONLY = NO
TARGET-CONNECTION-COUNT = 16
FRIENDS = $GNUNET_CONFIG_HOME/topology/friends.txt
BINARY = gnunet-daemon-topology

[transport]
AUTOSTART = YES
PORT = 2091
HOSTNAME = localhost
BINARY = gnunet-service-transport
NEIGHBOUR_LIMIT = 50
PLUGINS = tcp udp
UNIXPATH = $GNUNET_RUNTIME_DIR/gnunet-service-transport.sock
BLACKLIST_FILE = $GNUNET_CONFIG_HOME/transport/blacklist



[transport-unix]
PORT = 22086
TESTING_IGNORE_KEYS = ACCEPT_FROM;

[transport-tcp]
# Use 0 to ONLY advertise as a peer behind NAT (no port binding)
PORT = 2086
ADVERTISED_PORT = 2086
TESTING_IGNORE_KEYS = ACCEPT_FROM;

# Maximum number of open TCP connections allowed
MAX_CONNECTIONS = 128

TIMEOUT = 5 s
# ACCEPT_FROM =
# ACCEPT_FROM6 =
# REJECT_FROM =
# REJECT_FROM6 =
# BINDTO =
MAX_CONNECTIONS = 128

[transport-udp]
# Use PORT = 0 to autodetect a port available
PORT = 2086
BROADCAST = YES
BROADCAST_INTERVAL = 30 s
MAX_BPS = 1000000
TESTING_IGNORE_KEYS = ACCEPT_FROM;

[transport-http_client]
MAX_CONNECTIONS = 128
TESTING_IGNORE_KEYS = ACCEPT_FROM;

[transport-http_server]
#EXTERNAL_HOSTNAME = <your hostname/path>
PORT = 1080
ADVERTISED_PORT = 1080
MAX_CONNECTIONS = 128
TESTING_IGNORE_KEYS = ACCEPT_FROM;

[transport-https_client]
MAX_CONNECTIONS = 128
TESTING_IGNORE_KEYS = ACCEPT_FROM;

[transport-https_server]
# EXTERNAL_HOSTNAME = <your hostname/path>
# EXTERNAL_HOSTNAME_ONLY = YES
# If you have a valid SSL certificate for your external hostname tell,
# clients to verify it
# VERIFY_EXTERNAL_HOSTNAME = YES
# Does the external hostname use the same port?
# EXTERNAL_HOSTNAME_USE_PORT = YES
PORT = 4433
ADVERTISED_PORT = 4433
CRYPTO_INIT = NORMAL
KEY_FILE = $GNUNET_DATA_HOME/transport/https.key
CERT_FILE = $GNUNET_DATA_HOME/transport/https.cert
MAX_CONNECTIONS = 128
TESTING_IGNORE_KEYS = ACCEPT_FROM;


[PATHS]
# The PATHS section is special, as filenames including $-expression are
# expanded using the values from PATHS or the system environment (PATHS
# is checked first).  GNUnet also supports expanding $-expressions using
# defaults with the syntax "${VAR:-default}".  Here, "default" can again
# be a $-expression.
#
# We usually want $HOME for $GNUNET_HOME, but we allow testcases to
# easily override this by setting $GNUNET_TEST_HOME.
#
GNUNET_HOME = ${GNUNET_TEST_HOME:-$HOME}

# see XDG Base Directory Specification at
# http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
# for how these should be used.

# Persistant data storage
GNUNET_DATA_HOME = ${XDG_DATA_HOME:-$GNUNET_HOME/.local/share}/gnunet/

# Configuration files
GNUNET_CONFIG_HOME = ${XDG_CONFIG_HOME:-GNUNET_HOME/.config/}gnunet/

# Cached data, no big deal if lost
GNUNET_CACHE_HOME = ${XDG_CACHE_HOME:-$GNUNET_HOME/.cache/}gnunet/

# Runtime data (i.e UNIX domain sockets, locks, always lost on system boot)
GNUNET_RUNTIME_DIR = ${XDG_RUNTIME_DIR:-${TMPDIR:-${TMP:-/tmp}}}gnunet/

# Legacy option...
# GNUNET_TEST_HOME = ~/.gnunet/
# GNUNET_TEST_HOME = /var/lib/gnunet/

# DEFAULTCONFIG = /etc/gnunet.conf
# If 'DEFAULTCONFIG' is not defined, the current
# configuration file is assumed to be the default,
# which is what we want by default...


[PEER]
PRIVATE_KEY = $GNUNET_DATA_HOME/private_key.ecc


[TESTING]
SPEEDUP_INTERVAL = 0 ms
SPEEDUP_DELTA = 0 ms

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







