#ifndef CANGOTE_H
#define CANGOTE_H

#include <QObject>

class CangoteCore;
class Utils;
class Preferences;
class QQuickWindow;
class QQmlEngine;
class Cangote : public QObject
{
    Q_OBJECT
public:
    explicit Cangote(QObject *parent = 0);
    void registerQmlTypes();
    void registerImageProvider(QQmlEngine *engine);
signals:
    
public slots:

private:
    CangoteCore *m_core;


    
};

//Those are the externals visible to the whole application ( globals)
extern Utils* theUtils;
extern Preferences* thePrefs;
extern QQuickWindow* theWindow;
#endif // CANGOTE_H
