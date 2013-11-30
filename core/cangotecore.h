#ifndef CANGOTECORE_H
#define CANGOTECORE_H

#include <QObject>
#include <QDebug>



class GNUNet;
class Models;
class GNUNetLauncher;
class QTimer;
class Status;
class UpdateChecker;
class CangoteCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GNUNet * gnunet READ gnunet CONSTANT)
    Q_PROPERTY(Models * models READ models CONSTANT)
    Q_PROPERTY(Status * status READ status CONSTANT)
    Q_PROPERTY(bool connected READ isConnected WRITE setConnected NOTIFY connectedChanged)




public:
    explicit CangoteCore(QObject *parent = 0);
    ~CangoteCore();



    bool isConnected() const
    { return m_connected; }



    GNUNet* gnunet() const
        { return m_gnunet; }
    Models* models() const
        { return m_models; }
    Status* status() const
        { return m_status; }


private slots:
    void setConnected(bool connected);
    void process();
private:
    GNUNet* m_gnunet;
    Models* m_models;
    Status* m_status;
    QThread *m_gnunetThread;
    QThread *m_launcherThread;
    GNUNetLauncher* m_launcher;
    QTimer *m_armConnectTimer;
    QTimer *m_timer;

    bool m_connected;

    UpdateChecker* m_update;



    void startGNUNet();
    void startLauncher();
signals:
    void connectedChanged(bool connected);

    
public slots:    
    void armTimeOut();
};
extern CangoteCore* theApp;
#endif // CANGOTECORE_H

