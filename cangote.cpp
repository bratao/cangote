#include <QQmlEngine>
#include <QtQml/qqml.h>

#include "cangote.h"
#include "core/cangotecore.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/network/NetworkManager.h"
#include "models/NetworkPeersModel.h"
#include "core/gnunet/filesharing/filesharing.h"
#include "models/SearchModel.h"
#include "models/models.h"
#include "models/SearchResultModel.h"
#include "core/gnunet/filesharing/search/search.h"
#include "models/DownloadsModel.h"
#include "models/SharedFilesModel.h"


#define URI "Cangote"


Cangote::Cangote(QObject *parent) :
    QObject(parent)
{
    m_core = new CangoteCore();
    registerQmlTypes();
}


//Define the singleton type provider function (callback).
static QObject *singleton_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);


    return theApp;
}

void Cangote::registerQmlTypes()
{


    qmlRegisterSingletonType<CangoteCore>(URI, 1, 0, "Cangote", singleton_provider);
    qmlRegisterUncreatableType<GNUNet>(URI, 1, 0, "GNUNet", QLatin1String("Use the cangote core proprety."));
    qmlRegisterUncreatableType<NetworkManager>(URI, 1, 0, "NetworkManager", QLatin1String("Use calling the gnunet method."));


    qmlRegisterUncreatableType<FileSharing>(URI, 1, 0, "FileSharing", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<Search>(URI, 1, 0, "Search", QLatin1String("Use calling the gnunet method."));

    //Register models
    qmlRegisterUncreatableType<Models>(URI, 1, 0, "Models", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<SearchModel>(URI, 1, 0, "SearchesModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<SearchResultsModel>(URI, 1, 0, "SearchResultsModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<DownloadsModel>(URI, 1, 0, "DownloadsModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<SharedFilesModel>(URI, 1, 0, "SharedFilesModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<NetworkPeersModel>(URI, 1, 0, "NetworkPeersModel", QLatin1String("Use calling the gnunet method."));

}





