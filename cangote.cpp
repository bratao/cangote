#include <QQmlEngine>
#include <QtQml/qqml.h>


#include "cangote.h"
#include "utils/utils.h"
#include "preferences/preferences.h"



#include "core/cangotecore.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/network/NetworkManager.h"
#include "core/gnunet/filesharing/search/search.h"
#include "core/gnunet/filesharing/filesharing.h"
#include "core/gnunet/filesharing/publish/publish.h"
#include "core/gnunet/filesharing/publish/publishfile.h"
#include "core/gnunet/filesharing/transfer/downloaditem.h"
#include "core/status.h"

#include "models/SearchModel.h"
#include "models/models.h"
#include "models/SearchResultModel.h"
#include "models/NetworkPeersModel.h"
#include "models/DownloadsModel.h"
#include "models/SharedFilesModel.h"
#include "models/PublishModel.h"
#include "models/MetadataModel.h"
#include "models/KeywordModel.h"

#include "core/gnunet/filesharing/search/searchresult.h"


#define URI "Cangote"

/* Static member variables */
Utils* theUtils;
Preferences* thePrefs;
QQuickWindow* theWindow;

Cangote::Cangote(QObject *parent) :
    QObject(parent)
{
    thePrefs = new Preferences(this);
    m_core = new CangoteCore(this);
    theUtils = new Utils(this);


    registerQmlTypes();
}


//Define the theApp singleton type provider.
static QObject *theApp_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);


    return theApp;
}

static QObject *theUtils_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);


    return theUtils;
}

static QObject *thePrefs_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);


    return thePrefs;
}




void Cangote::registerQmlTypes()
{

    qmlRegisterSingletonType<CangoteCore>(URI, 1, 0, "Utils", theUtils_provider);
    qmlRegisterSingletonType<CangoteCore>(URI, 1, 0, "Preferences", thePrefs_provider);
    qmlRegisterSingletonType<CangoteCore>(URI, 1, 0, "Cangote", theApp_provider);


    qmlRegisterUncreatableType<GNUNet>(URI, 1, 0, "GNUNet", QLatin1String("Use the cangote core proprety."));
    qmlRegisterUncreatableType<NetworkManager>(URI, 1, 0, "NetworkManager", QLatin1String("Use calling the gnunet method."));

    qmlRegisterUncreatableType<Status>(URI, 1, 0, "Status", QLatin1String("Use calling the gnunet method."));


    qmlRegisterUncreatableType<FileSharing>(URI, 1, 0, "FileSharing", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<Search>(URI, 1, 0, "Search", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<Publish>(URI, 1, 0, "Publish", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<PublishFile>(URI, 1, 0, "PublishFile", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<SharedFile>(URI, 1, 0, "SharedFile", QLatin1String("Use calling the gnunet method."));


    //Register models
    qmlRegisterUncreatableType<Models>(URI, 1, 0, "Models", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<SearchModel>(URI, 1, 0, "SearchesModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<SearchResultsModel>(URI, 1, 0, "SearchResultsModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<DownloadsModel>(URI, 1, 0, "DownloadsModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<SharedFilesModel>(URI, 1, 0, "SharedFilesModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<NetworkPeersModel>(URI, 1, 0, "NetworkPeersModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<PublishModel>(URI, 1, 0, "PublishModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<MetaModel>(URI, 1, 0, "MetaModel", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<KeywordModel>(URI, 1, 0, "KeywordModel", QLatin1String("Use calling the gnunet method."));


    qmlRegisterUncreatableType<SearchResult>(URI, 1, 0, "SearchResult", QLatin1String("Use calling the gnunet method."));
    qmlRegisterUncreatableType<DownloadItem>(URI, 1, 0, "DownloadItem", QLatin1String("Use calling the gnunet method."));




}

void Cangote::registerImageProvider(QQmlEngine *engine)
{
    engine->addImageProvider("publishThumbnail",theApp->models()->publishModel()->thumbnailProvider());
    engine->addImageProvider("searchResultThumbnail",theApp->models()->searchModel()->thumbnailProvider());
    engine->addImageProvider("downloadsThumbnail",theApp->models()->downloadsModel()->thumbnailProvider());
    engine->addImageProvider("sharedFilesThumbnail",theApp->models()->sharedModel()->thumbnailProvider());


}

