#ifndef STATUS_H
#define STATUS_H

#include <QObject>

class Status : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)
  Q_PROPERTY(int connectedPeers READ getConnectedPeers WRITE setConnectedPeers NOTIFY connectedPeersChanged)
  Q_PROPERTY(int estimatedNodes READ getEstimatedNodes WRITE setEstimatedNodes NOTIFY estimatedNodesChanged)
  Q_PROPERTY(int outgoingBand READ getOutgoingBand WRITE setOutgoingBand NOTIFY outgoingBandChanged)
  Q_PROPERTY(int incomingBand READ getIncomingBand WRITE setIncomingBand NOTIFY incomingBandChanged)
  //Publish
  Q_PROPERTY(bool isPublishing READ isPublishing WRITE setPublishing NOTIFY publishingChanged)
  Q_PROPERTY(int publishingPercentage READ publishingPercentage WRITE setPublishingPercentage NOTIFY publishingPercentageChanged)
  Q_PROPERTY(QString myPublicKeyStr READ myPublicKeyStr WRITE setMyPublicKeyStr NOTIFY myPublicKeyStrChanged)
  Q_PROPERTY(QString myHelloStr READ myHelloStr WRITE setMyHelloStr NOTIFY myHelloStrChanged)

public:
  explicit Status(QObject *parent = 0);
  bool isConnected() const
  { return m_connected; }


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

  //Publishing
  bool isPublishing() const
  { return m_isPublishing; }

  int publishingPercentage() const
  { return m_publishingPercentage; }

  //Public Key Str
  QString myPublicKeyStr() const
  { return m_myPublicKeyStr; }

  //My Hello Str
  QString myHelloStr() const
  { return m_myHelloStr; }



signals:
  void connectedChanged(bool connected);
  void connectedPeersChanged(int connected);
  void estimatedNodesChanged(int nodes);
  void outgoingBandChanged(int outgoing);
  void incomingBandChanged(int incoming);
  //Publishing
  void publishingChanged(bool publishing);
  void publishingPercentageChanged(float percentage);
  void myHelloStrChanged(QString hello);
  void myPublicKeyStrChanged(QString key);


public slots:
  void setConnected(bool connected)
  {
    m_connected = connected;
    emit connectedChanged(connected);
  }
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

  //Publishing
  void setPublishing(bool publishing)
  {
    m_isPublishing = publishing;
    emit publishingChanged(publishing);
  }

  void setPublishingPercentage(int percentage)
  {
    m_publishingPercentage = percentage;
    emit publishingPercentageChanged(percentage);
  }



  void setMyHelloStr(QString hello)
  {
    m_myHelloStr = hello;
    emit myHelloStrChanged(hello);
  }

  //Public Key Str
  void setMyPublicKeyStr(QString key)
  {
    m_myPublicKeyStr = key;
    emit myPublicKeyStrChanged(key);
  }

  void gnunetStarted();
private:

  bool m_connected;
  int m_connectedPeers;
  int m_numEstimateNodes;
  int m_outgoingBand;
  int m_incomingBand;

  bool m_isPublishing;
  int m_publishingPercentage;
  /**
   * My public key.
   */
  QString m_myPublicKeyStr;
  /**
     * My GNUNet Hello.
     */
  QString m_myHelloStr;

};

#endif // STATUS_H
