QT += widgets qml quick
TARGET = cangote
CONFIG+=qml_debug

#QMAKE_CXXFLAGS+=-Wall -Wextra #-Werror
QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS_RELEASE += -g
QMAKE_LFLAGS_RELEASE =


!win32 {
   LIBS += -L/home/bratao/gnunet/gnunet-bin/lib -lgnunetutil -lgnunetfs -lgnunetpeerinfo -lgnunetcore -lgnunettransport -lgnunetats -lgnunetnse -lextractor

}
win32 {
   LIBS += -lgnunetutil -lgnunetfs -lgnunetpeerinfo -lgnunetcore -lgnunettransport -lgnunetats -lgnunetnse -lgnunetarm -lws2_32 -lintl -lextractor
    INCLUDEPATH += C:/sbuild/mingw/include
}

RC_ICONS = asserts\CangoteHead.ico

SOURCES += \
    main.cpp \
    core/cangotecore.cpp \
    cangote.cpp \
    core/gnunet/gnunet.cpp \
    core/gnunet/filesharing/search/searchresult.cpp \
    core/gnunet/filesharing/search/search.cpp \
    core/gnunet/filesharing/shared/sharedfiles.cpp \
    core/gnunet/filesharing/transfer/downloads.cpp \
    core/gnunet/filesharing/transfer/downloaditem.cpp \
    core/gnunet/filesharing/filesharing.cpp \
    core/gnunet/launcher/gnunetlauncher.cpp \
    core/gnunet/network/peerbandwidth.cpp \
    core/gnunet/network/peer.cpp \
    core/gnunet/util/helpers.cpp \
    models/gnunet_fs_search_results_metadata.cpp \
    service.cpp \
    models/NetworkPeersModel.cpp \
    core/gnunet/network/NetworkManager.cpp \
    models/SearchModel.cpp \
    models/SearchResultModel.cpp \
    core/gnunet/filesharing/shared/sharedfile.cpp \
    models/DownloadsModel.cpp \
    models/models.cpp \
    models/SharedFilesModel.cpp \
    preferences/preferences.cpp \
    utils/utils.cpp \
    models/PublishFileModel.cpp \
    core/publish/publishfile.cpp

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
    qml/Sidebar/MenuButton.qml \
    qml/Publish/PublishFile.qml \
    qml/preferences/Advanced.qml \
    qml/Network/AddPeer.qml \
    qml/Search/Tooltip.qml

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
    models/gnunet_fs_search_results_metadata.h \
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
    models/PublishFileModel.h \
    core/publish/publishfile.h
