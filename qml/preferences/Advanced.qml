import QtQuick 2.1
import QtQml.Models 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import Cangote 1.0

Rectangle {
    ObjectModel {
        id: itemModel
        Label{ text:"<b>Service ports:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"ARM service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.armPort;onValueChanged: {Preferences.armPort = value} }  }
        Row{ Label{ text:"ATS service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.atsPort;onValueChanged: {Preferences.atsPort = value} }  }
        Row{ Label{ text:"Core service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.corePort;onValueChanged: {Preferences.corePort = value} }  }
        Row{ Label{ text:"Datastore service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.datastorePort;onValueChanged: {Preferences.datastorePort = value} }  }
        Row{ Label{ text:"DHT service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.dhtPort;onValueChanged: {Preferences.dhtPort = value} }  }
        Row{ Label{ text:"DV service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.dvPort;onValueChanged: {Preferences.dvPort = value} }  }
        Row{ Label{ text:"FS service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.fsPort;onValueChanged: {Preferences.fsPort = value} }  }
        Row{ Label{ text:"GNS service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.gnsPort;onValueChanged: {Preferences.gnsPort = value} }  }
        Row{ Label{ text:"Identity service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.identityPort;onValueChanged: {Preferences.identityPort = value} }  }
        Row{ Label{ text:"Mesh service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.meshPort;onValueChanged: {Preferences.meshPort = value} }  }
        Row{ Label{ text:"Namecache service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.namecachePort;onValueChanged: {Preferences.namecachePort = value} }  }
        Row{ Label{ text:"Namestore service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.namestorePort;onValueChanged: {Preferences.namestorePort = value} }  }
        Row{ Label{ text:"NSE service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.nsePort;onValueChanged: {Preferences.nsePort = value} }  }
        Row{ Label{ text:"Peerinfo service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.peerinfoPort;onValueChanged: {Preferences.peerinfoPort = value} }  }
        Row{ Label{ text:"Regex service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.regexPort;onValueChanged: {Preferences.regexPort = value} }  }
        Row{ Label{ text:"Resolver service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.resolverPort;onValueChanged: {Preferences.resolverPort = value} }  }
        Row{ Label{ text:"Revocation service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.revocationPort;onValueChanged: {Preferences.revocationPort = value} }  }
        Row{ Label{ text:"Statistics service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.statisticsPort;onValueChanged: {Preferences.statisticsPort = value} }  }
        Row{ Label{ text:"Transport service port:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536;value: Preferences.transportPort;onValueChanged: {Preferences.transportPort = value} }  }
        Label{ text:"<b>Filesharing:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"Do we introduce artificial delays:"; font.pointSize: 10; width: 500;} CheckBox{checked: Preferences.fsDelay;onCheckedChanged: {Preferences.fsDelay = checked} }  }
        Row{ Label{ text:"Maximum number of requests this peer tracks :"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 1000000; value: Preferences.fsPendingRequests;onValueChanged: {Preferences.fsPendingRequests = value} }  }
        Row{ Label{ text:"Max Number of requests waiting in the queue towards the datastore:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.fsDataStoreQueueSize;onValueChanged: {Preferences.fsDataStoreQueueSize = value} }  }
        Row{ Label{ text:"Maximum frequency to poll the datastore for content for migration:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.fsMinMigrationDelay;onValueChanged: {Preferences.fsMinMigrationDelay = value} }  }
        Row{ Label{ text:"For how many neighbouring peers should we allocate hash maps:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.fsExpectedNeighbourCount;onValueChanged: {Preferences.fsExpectedNeighbourCount = value} }  }
        Row{ Label{ text:"Maximum number of non-anonymous transfers this peer will support:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.fsMaxMeshClients;onValueChanged: {Preferences.fsMaxMeshClients = value} }  }
        Label{ text:"<b>GNS:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"Max. queries GNS is allowed to perform in the background at the same time:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.gnsMaxParallelBackgroundQueries;onValueChanged: {Preferences.gnsMaxParallelBackgroundQueries = value} }  }
        Row{ Label{ text:"How frequently do we try to publish our full zone:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.gnsZonePublishTimeWindow;onValueChanged: {Preferences.gnsZonePublishTimeWindow = value} }  }
        Label{ text:"<b>HostList:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"Port for hostlist http server:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.hostlistHttpPort;onValueChanged: {Preferences.hostlistHttpPort = value} }  }
        Row{ Label{ text:"Proxy for downloading hostlists:"; font.pointSize: 10; width: 500;} TextField{text: Preferences.hostlistHttpProxy;onTextChanged: {Preferences.hostlistHttpProxy = text} }  }
        Label{ text:"<b>Mesh:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"Max. connections:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 10000; value: Preferences.meshMaxConnections;onValueChanged: {Preferences.meshMaxConnections = value} }  }
        Row{ Label{ text:"Max. message queue:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 100000; value: Preferences.meshMsgsQueue;onValueChanged: {Preferences.meshMsgsQueue = value} }  }
        Row{ Label{ text:"Max. Peers:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 10000; value: Preferences.meshPeers;onValueChanged: {Preferences.meshPeers = value} }  }
        Label{ text:"<b>NAT:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"External IP address:"; font.pointSize: 10; width: 500;} TextField{text: Preferences.getExternalIpv4Address;onTextChanged: {Preferences.getExternalIpv4Address = text} }  }
        Row{ Label{ text:"Internal IP address:"; font.pointSize: 10; width: 500;} TextField{text: Preferences.internalIpv4Address;onTextChanged: {Preferences.internalIpv4Address = text} }  }
        Row{ Label{ text:"Use addresses from the local network interfaces:"; font.pointSize: 10; width: 500;} CheckBox{checked: Preferences.natUseLocalAddresses;onCheckedChanged: {Preferences.natUseLocalAddresses = text} }  }
        Row{ Label{ text:"Use address obtained from a DNS lookup of our hostname:"; font.pointSize: 10; width: 500;} CheckBox{checked: Preferences.natUseHostname;onCheckedChanged: {Preferences.natUseHostname = text} }  }
        Row{ Label{ text:"Do we use addresses from localhost address ranges? :"; font.pointSize: 10; width: 500;} CheckBox{checked: Preferences.natReturnLocalAddresses;onCheckedChanged: {Preferences.natReturnLocalAddresses = checked} }  }
        Row{ Label{ text:"How often do we query the DNS resolver for our hostname :"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 10000; value: Preferences.natHostnameDnsFrequency;onValueChanged: {Preferences.natHostnameDnsFrequency = value} }  }
        Row{ Label{ text:"How often scan for changes in our IP address:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 10000; value: Preferences.natIfcScanFrequency;onValueChanged: {Preferences.natIfcScanFrequency = value} }  }
        Row{ Label{ text:"How often do we query the DNS resolver:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 10000; value: Preferences.natDynDnsFrequency;onValueChanged: {Preferences.natDynDnsFrequency = value} }  }
        Label{ text:"<b>NSE:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"How 'slowly' should the proof-of-work be constructed :"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.nseWorkDelay;onValueChanged: {Preferences.nseWorkDelay = value} }  }
        Label{ text:"<b>TCP-Transport:</b>"; font.pointSize: 11; width: 500;}
        Row{ Label{ text:"Timeout:"; font.pointSize: 10; width: 500;} SpinBox{maximumValue : 65536; value: Preferences.tcpTimeout;onValueChanged: {Preferences.tcpTimeout = value} }  }


    }


    ScrollView {
        anchors.fill: parent
        ListView {
            id:list
            anchors.fill: parent
            model: itemModel
            focus: true
        }
    }
}
