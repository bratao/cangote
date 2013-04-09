#ifndef CANGOTE_H
#define CANGOTE_H

#include <QObject>

class CangoteCore;
class Cangote : public QObject
{
    Q_OBJECT
public:
    explicit Cangote(QObject *parent = 0);

signals:
    
public slots:

private:
    CangoteCore *m_core;
    void registerQmlTypes();
    
};

#endif // CANGOTE_H
