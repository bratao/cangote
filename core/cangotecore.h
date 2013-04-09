#ifndef CANGOTECORE_H
#define CANGOTECORE_H

#include <QObject>




class GNUNet;
class Models;
class GNUNetLauncher;
class CangoteCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GNUNet * gnunet READ gnunet CONSTANT)
    Q_PROPERTY(Models * models READ models CONSTANT)

public:
    explicit CangoteCore(QObject *parent = 0);
    ~CangoteCore();







    GNUNet* gnunet() const
        { return m_gnunet; }
    Models* models() const
        { return m_models; }



private:
    GNUNet* m_gnunet;
    Models* m_models;
    QThread *m_gnunetThread;
    GNUNetLauncher* m_launcher;


    void startGNUNet();
signals:
    
public slots:
    
};
extern CangoteCore* theApp;
#endif // CANGOTECORE_H

