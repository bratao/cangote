#ifndef CANGOTECORE_H
#define CANGOTECORE_H

#include <QObject>
#include <QDebug>



class GNUNet;
class Models;
class GNUNetLauncher;
class QTimer;
class CangoteCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GNUNet * gnunet READ gnunet CONSTANT)
    Q_PROPERTY(Models * models READ models CONSTANT)
    Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int connectedPeers READ getConnectedPeers WRITE setConnectedPeers NOTIFY connectedPeersChanged)
    Q_PROPERTY(int estimatedNodes READ getEstimatedNodes WRITE setEstimatedNodes NOTIFY estimatedNodesChanged)
    Q_PROPERTY(int outgoingBand READ getOutgoingBand WRITE setOutgoingBand NOTIFY outgoingBandChanged)
    Q_PROPERTY(int incomingBand READ getIncomingBand WRITE setIncomingBand NOTIFY incomingBandChanged)




public:
    explicit CangoteCore(QObject *parent = 0);
    ~CangoteCore();



    bool isConnected() const
    { return m_connected; }



    GNUNet* gnunet() const
        { return m_gnunet; }
    Models* models() const
        { return m_models; }



    //Connected peers
    int getConnectedPeers() const
    { return m_connectedPeers; }

    //Estimated Nodes
    int getEstimatedNodes() const
    {
        return m_numEstimateNodes;
    }


    //Outgoing Band
    int getOutgoingBand() const
    { return m_outgoingBand; }


    //Incoming band
    int getIncomingBand() const
    { return m_incomingBand; }


private slots:
    void setConnected(bool connected);
    void setConnectedPeers(int connected)
    {
        m_connectedPeers = connected;
        emit connectedPeersChanged(connected);
    }
    void setEstimatedNodes(int nodes)
    {
        m_numEstimateNodes = nodes;
        emit estimatedNodesChanged(nodes);
    }
    void setOutgoingBand(int outgoing)
    {
        m_outgoingBand = outgoing;
        emit outgoingBandChanged(outgoing);
    }
    void setIncomingBand(int incoming)
    {
        m_incomingBand = incoming;
        emit incomingBandChanged(incoming);
    }

    void gnunetStarted();
    void process();
private:
    GNUNet* m_gnunet;
    Models* m_models;
    QThread *m_gnunetThread;
    QThread *m_launcherThread;
    GNUNetLauncher* m_launcher;
    QTimer *m_armConnectTimer;
    QTimer *m_timer;

    bool m_connected;
    int m_connectedPeers;
    int m_numEstimateNodes;
    int m_outgoingBand;
    int m_incomingBand;


    void startGNUNet();
    void startLauncher();
signals:
    void connectedChanged(bool connected);
    void connectedPeersChanged(int connected);
    void estimatedNodesChanged(int nodes);
    void outgoingBandChanged(int outgoing);
    void incomingBandChanged(int incoming);
    
public slots:    
    void armTimeOut();
};
extern CangoteCore* theApp;
#endif // CANGOTECORE_H

