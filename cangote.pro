QT += widgets qml quick
!macx {
TARGET = cangote
}
macx{
TARGET = Cangote
}
CONFIG+=qml_debug

QMAKE_CXXFLAGS+=-Wall -Wextra #-Werror
QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS_RELEASE += -g
QMAKE_LFLAGS_RELEASE =


LIBS += -lgnunetutil -lgnunetfs -lgnunetpeerinfo -lgnunethello -lgnunetcore -lgnunetidentity -lgnunettransport -lgnunetats -lgnunetnse -lgnunetarm -lextractor

macx{
CONFIG   += c++11
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
INCLUDEPATH+= "/usr/local/include"
LIBPATH+= "/usr/local/lib"
}

!win32 {
   LIBS +=

}
win32 {
   LIBS += -lws2_32 -lintl
}

RC_ICONS = asserts\CangoteHead.ico

SOURCES += \
    main.cpp \
    service.cpp \
    cangote.cpp \
    core/cangotecore.cpp \
    core/status.cpp \
    core/gnunet/gnunet.cpp \
    core/gnunet/filesharing/search/searchresult.cpp \
    core/gnunet/filesharing/search/search.cpp \
    core/gnunet/filesharing/shared/sharedfiles.cpp \
    core/gnunet/filesharing/transfer/downloads.cpp \
    core/gnunet/filesharing/transfer/downloaditem.cpp \
    core/gnunet/filesharing/filesharing.cpp \
    core/gnunet/filesharing/shared/sharedfile.cpp \
    core/gnunet/filesharing/publish/publish.cpp \
    core/gnunet/filesharing/publish/publishfile.cpp \
    core/gnunet/launcher/gnunetlauncher.cpp \
    core/gnunet/network/peerbandwidth.cpp \
    core/gnunet/network/peer.cpp \
    core/gnunet/network/gnunettransportplugins.cpp \
    core/gnunet/network/NetworkManager.cpp \
    core/gnunet/util/helpers.cpp \
    models/NetworkPeersModel.cpp \
    models/SearchModel.cpp \
    models/SearchResultModel.cpp \
    models/DownloadsModel.cpp \
    models/models.cpp \
    models/SharedFilesModel.cpp \
    models/PublishModel.cpp \
    models/MetadataModel.cpp \
    models/KeywordModel.cpp \
    preferences/preferences.cpp \
    utils/utils.cpp \
    utils/QLogger.cpp \
    utils/update_checker.cpp \
    core/gnunet/filesharing/search/searchmanager.cpp



OTHER_FILES += \
    qml/main.qml \
    qml/Transfers.qml \
    qml/SideBar.qml \
    qml/Network.qml \
    qml/Header.qml \
    qml/Footer.qml \
    qml/CustomButton.qml \
    qml/Center.qml \
    qml/Browser.qml \
    qml/preferences/PreferencesWindow.qml \
    qml/preferences/ScrollBar.qml \
    qml/preferences/CategoryDelegate.qml \
    qml/preferences/General.qml \
    qml/preferences/Connection.qml \
    qml/preferences/Directories.qml \
    qml/preferences/Network.qml \
    qml/Network/Network.qml \
    qml/Search/Search.qml \
    qml/Search/SearchResultPage.qml \
    qml/Transfer/Transfers.qml \
    qml/Shared/Shared.qml \
    qml/Sidebar/SideBar.qml \
    qml/Sidebar/Block.qml \
    qml/Sidebar/BlockDelegate.qml \
    qml/Publish/PublishFile.qml \
    qml/preferences/Advanced.qml \
    qml/Network/AddPeer.qml \
    qml/Search/Tooltip.qml \
    qml/Publish/PublishDetails.qml \
    qml/Wizard/FirstRun.qml \
    qml/Wizard/Welcome.qml

RESOURCES += \
    resources.qrc

MOC_DIR = ./.moc
OBJECTS_DIR = ./.obj
UI_DIR = ./.ui
RCC_DIR = ./.rcc

HEADERS += \
    core/cangotecore.h \
    cangote.h \
    core/gnunet/gnunet_includes.h \
    core/gnunet/gnunet.h \
    core/gnunet/filesharing/search/searchresult.h \
    core/gnunet/filesharing/search/search.h \
    core/gnunet/filesharing/shared/sharedfiles.h \
    core/gnunet/filesharing/transfer/downloads.h \
    core/gnunet/filesharing/transfer/downloaditem.h \
    core/gnunet/filesharing/filesharing.h \
    core/gnunet/launcher/gnunetlauncher.h \
    core/gnunet/network/peerbandwidth.h \
    core/gnunet/network/peer.h \
    core/gnunet/util/helpers.h \
    service.h \
    models/NetworkPeersModel.h \
    core/gnunet/network/NetworkManager.h \
    models/SearchModel.h \
    models/SearchResultModel.h \
    core/gnunet/filesharing/shared/sharedfile.h \
    models/DownloadsModel.h \
    models/models.h \
    models/SharedFilesModel.h \
    preferences/preferences.h \
    utils/utils.h \
    core/gnunet/network/gnunettransportplugins.h \
    core/publish/publishfiles.h \
    core/gnunet/filesharing/publish/publish.h \
    models/PublishModel.h \
    core/gnunet/filesharing/publish/publishfile.h \
    core/status.h \
    models/MetadataModel.h \
    models/KeywordModel.h \
    utils/QLogger.h \
    utils/update_checker.h \
    core/gnunet/filesharing/search/searchmanager.h


!macx{
qmlfilesdebug.files   = qml
qmlfilesrelease.files   = qml
qmlfilesrelease.path    = $$OUT_PWD/debug
qmlfilesdebug.path    = $$OUT_PWD/release
INSTALLS       += qmlfilesrelease qmlfilesdebug
}
macx{
qmlfiles.files   = qml
qmlfiles.path  = "Contents/MacOS"
QMAKE_BUNDLE_DATA+= qmlfiles
}



