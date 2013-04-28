#ifndef CANGOTE_H
#define CANGOTE_H

#include <QObject>

class CangoteCore;
class Utils;
class Preferences;
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
extern Utils* theUtils;
extern Preferences* thePrefs;
#endif // CANGOTE_H
