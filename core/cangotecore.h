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


private:
    GNUNet* m_gnunet;
    Models* m_models;
    QThread *m_gnunetThread;
    GNUNetLauncher* m_launcher;
    int m_connectedPeers;
    bool m_connected;
    QTimer *m_armConnectTimer ;
    void startGNUNet();
signals:
    void connectedChanged(bool connected);
    void connectedPeersChanged(int connected);
    
public slots:
    void setConnected(bool connected);
    void setConnectedPeers(int connected);
    
    void armTimeOut();
};
extern CangoteCore* theApp;
#endif // CANGOTECORE_H

