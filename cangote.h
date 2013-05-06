#ifndef CANGOTE_H
#define CANGOTE_H

#include <QObject>

class CangoteCore;
class Utils;
class Preferences;
class QQuickWindow;
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

//Those are the externals visible to the whole application ( globals)
extern Utils* theUtils;
extern Preferences* thePrefs;
extern QQuickWindow* theWindow;
#endif // CANGOTE_H
