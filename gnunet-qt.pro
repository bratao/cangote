#-------------------------------------------------
#
# Project created by QtCreator 2012-08-31T08:23:22
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gnunet-qt
TEMPLATE = app

QMAKE_CFLAGS+=-ggdb -O1
QMAKE_CXXFLAGS+=-ggdb -O1
QMAKE_LFLAGS+=-ggdb -O1

TRANSLATIONS = cangote_pt.ts

SOURCES += \
    core/main.cpp \
    core/cangote.cpp \
    gui/network/networkwnd.cpp \
    gui/search/searchwnd.cpp \
    gui/transfer/transferwnd.cpp \
    gui/cangoteDlg.cpp \
    utils/log.cpp \
    core/gnunet/filesharing/filesharing.cpp \
    core/gnunet/filesharing/search/search.cpp \
    models/gnunet_fs_search_results.cpp \
    gui/search/searchdetailspanel.cpp \
    gui/log/logwnd.cpp \
    gui/search/searchresulttab.cpp \
    models/gnunet_fs_search_results_metadata.cpp \
    gui/statusbar/ratesstatus.cpp \
    utils/misc.cpp \
    core/gnunet/util/helpers.cpp \
    core/gnunet/gnunet.cpp \
    models/gnunet_peers.cpp \
    gui/statusbar/friendstatus.cpp \
    gui/statusbar/peerstatus.cpp \
    gui/network/networkpeerdelegate.cpp \
    gui/search/searchresultsdelegate.cpp \
    core/gnunet/launcher/gnunetlauncher.cpp \
    core/gnunet/filesharing/search/searchresult.cpp \
    core/gnunet/network/peerbandwidth.cpp \
    core/gnunet/network/peer.cpp \
    core/gnunet/network/gnetwork.cpp \
    core/servicestatus.cpp \
    models/gnunetfssearchmodel.cpp \
    gui/browser/browserwnd.cpp \
    gui/transfer/transferlistwidget.cpp \
    core/gnunet/filesharing/transfer/downloaditem.cpp \
    core/gnunet/filesharing/transfer/downloads.cpp \
    models/downloadmodel.cpp \
    gui/shared/sharedwnd.cpp \
    gui/shared/sharedtreewidget.cpp \
    gui/shared/sharedfileswidget.cpp \
    models/sharedfilesmodel.cpp \
    core/gnunet/filesharing/shared/sharedfiles.cpp \
    core/settings/settings.cpp \
    gui/settings/pages.cpp \
    gui/settings/settingswnd.cpp

HEADERS  += \
    core/gnunet/gnunet_includes.h \
    core/cangote.h \
    gui/network/networkwnd.h \
    gui/search/searchwnd.h \
    gui/transfer/transferwnd.h \
    gui/cangoteDlg.h \
    utils/log.h \
    core/gnunet/filesharing/filesharing.h \
    core/gnunet/filesharing/search/search.h \
    models/gnunet_fs_search_results.h \
    gui/search/searchdetailspanel.h \
    gui/log/logwnd.h \
    gui/search/searchresulttab.h \
    models/gnunet_fs_search_results_metadata.h \
    gui/statusbar/ratesstatus.h \
    utils/misc.h \
    core/gnunet/util/helpers.h \
    core/gnunet/gnunet.h \
    models/gnunet_peers.h \
    gui/statusbar/friendstatus.h \
    gui/statusbar/peerstatus.h \
    gui/network/networkpeerdelegate.h \
    gui/search/searchresultsdelegate.h \
    core/gnunet/launcher/gnunetlauncher.h \
    core/gnunet/filesharing/search/searchresult.h \
    core/gnunet/network/peerbandwidth.h \
    core/gnunet/network/peer.h \
    core/gnunet/network/gnetwork.h \
    core/servicestatus.h \
    models/gnunetfssearchmodel.h \
    gui/browser/browserwnd.h \
    gui/transfer/transferlistwidget.h \
    gui/transfer/transferlistdelegate.h \
    core/gnunet/filesharing/transfer/downloaditem.h \
    core/gnunet/filesharing/transfer/downloads.h \
    models/downloadmodel.h \
    gui/shared/sharedwnd.h \
    gui/shared/sharedtreewidget.h \
    gui/shared/sharedfileswidget.h \
    models/sharedfilesmodel.h \
    core/gnunet/filesharing/shared/sharedfiles.h \
    core/settings/settings.h \
    gui/settings/pages.h \
    gui/settings/settingswnd.h

FORMS    += \
    about.ui \
    cangoteDlg.ui \
    gui/settings/settingwnd.ui

OTHER_FILES += \
    images/update.png \
    images/query.png \
    images/config.png

RESOURCES += \
    resources.qrc

LIBS += -lgnunetutil -lgnunetfs -lgnunetpeerinfo -lgnunetcore -lgnunettransport -lgnunetats -lgnunetnse -lws2_32 -lintl -lextractor
