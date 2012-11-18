/*
     This file is part of Cangote
     (C) 2012 Bruno Cabral (and other contributing authors)

     Cangote is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 3, or (at your
     option) any later version.

     Cangote is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with Cangote; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.
*/


#include "cangoteDlg.h"
#include "ui_cangoteDlg.h"
#include "settings/settingswnd.h"
#include "core/cangote.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/filesharing/filesharing.h"


#include "network/networkwnd.h"
#include "transfer/transferwnd.h"
#include "search/searchwnd.h"
#include "statusbar/friendstatus.h"
#include "statusbar/peerstatus.h"
#include "statusbar/ratesstatus.h"
#include "browser/browserwnd.h"
#include "shared/sharedwnd.h"
#include "core/gnunet/network/gnetwork.h"



#include "log/logwnd.h"
#include "utils/log.h"
#include <QStringListModel>
#include <QMenu>

CangoteDlg::CangoteDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CangoteDlg)
{
    ui->setupUi(this);
    createTrayIcon();

    InitDialogs();
}

CangoteDlg::~CangoteDlg()
{
    delete ui;
}


void CangoteDlg::Connect()
{
 //   connect( theApp->gnunetMgr, SIGNAL(PeerAdded(QString)), networkWnd, SLOT(PeerEvent(QString)) );


    connect(&theApp->_log, SIGNAL(LogAddedSignal(int, QString)), logWnd, SLOT(AddLog(int,QString)));

}

void CangoteDlg::GNUNetConnected()
{
    //connect( theApp->gnunet->filesharing, SIGNAL(GNUNetSignalNewSearch(QString,GNUnetFsSearchResultsModel*)), searchWnd, SLOT(NewSearchSlot(QString,GNUnetFsSearchResultsModel*)) );
    networkWnd->connectedGNUnet();
    searchWnd->GNUNetConnected();
    transferWnd->GNUnetConnected();

}


void CangoteDlg::process()
{

    int incoming = theApp->gnunet->network->getIncomingBand();
    int outgoing = theApp->gnunet->network->getOutgoingBand();

    int estimated = theApp->gnunet->network->getEstimateNetworkSize();
    int connected = theApp->gnunet->network->getConnectedNodes();

    ratesstatus->setRatesStatus(incoming,outgoing);

    //TODO:: Detect if gnunet is not started
    peerStatus->setStatus(true,connected,estimated);


}

void CangoteDlg::on_actionSettings_triggered()
{
    SettingsWnd dialog;
    dialog.exec();
}

void CangoteDlg::InitDialogs()
{






    //BROWSER_WND
    browserWnd = new BrowserWnd(this);
    ui->stackedWidget->addWidget(browserWnd);
    //NETWORK_WND
    networkWnd = new NetworkWnd(this);
    ui->stackedWidget->addWidget(networkWnd);
    //SEARCH_WND
    searchWnd = new SearchWnd(this);
    ui->stackedWidget->addWidget(searchWnd);
    //TRANSFER_WND
    transferWnd = new TransferWnd(this);
    ui->stackedWidget->addWidget(transferWnd);
    //SHARED_WND
    sharedWnd = new SharedWnd(this);
    ui->stackedWidget->addWidget(sharedWnd);
    //LOG_WND
    logWnd = new LogWnd(this);
    ui->stackedWidget->addWidget(logWnd);




    ui->stackedWidget->setCurrentIndex(NETWORK_WND);




    /** StatusBar section ********/

    friendStatus = new FriendStatus();
    statusBar()->addWidget(friendStatus);


    peerStatus = new PeerStatus();
    statusBar()->addWidget(peerStatus);


    ratesstatus = new RatesStatus();
    statusBar()->addPermanentWidget(ratesstatus);


    /** Status Bar end ******/


    //Our process timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    timer->start(1000);



}


void CangoteDlg::createTrayIcon()
{
   m_trayIcon = new QSystemTrayIcon(QIcon(":/images/config.png"), this);

   connect( m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_trayAction(QSystemTrayIcon::ActivationReason)) );

   QAction *quit_action = new QAction( "Exit", m_trayIcon );
   connect( quit_action, SIGNAL(triggered()), qApp, SLOT(quit()) );

   QMenu *tray_icon_menu = new QMenu;
   tray_icon_menu->addAction( quit_action );

   m_trayIcon->setContextMenu( tray_icon_menu );

   m_trayIcon->show();
 }

void CangoteDlg::on_trayAction( QSystemTrayIcon::ActivationReason reason )
{
    if( reason )
    {
        if( reason != QSystemTrayIcon::DoubleClick )
        return;
    }

    if( isVisible() )
    {
        hide();
    }
    else
    {
        show();
        raise();
        setFocus();
    }
}

void CangoteDlg::on_actionBrowser_triggered()
{
    ui->stackedWidget->setCurrentIndex(BROWSER_WND);
}

void CangoteDlg::on_actionNetwork_triggered()
{
    ui->stackedWidget->setCurrentIndex(NETWORK_WND);
}

void CangoteDlg::on_actionSearch_triggered()
{
    ui->stackedWidget->setCurrentIndex(SEARCH_WND);
}

void CangoteDlg::on_actionTransfer_triggered()
{
    ui->stackedWidget->setCurrentIndex(TRANSFER_WND);
}

void CangoteDlg::on_actionLogs_triggered()
{
    ui->stackedWidget->setCurrentIndex(LOG_WND);
}

void CangoteDlg::on_actionShared_Files_triggered()
{
    ui->stackedWidget->setCurrentIndex(SHARED_WND);
}

void CangoteDlg::on_actionSettings_2_triggered()
{
    SettingsWnd dialog;
    dialog.exec();
}
