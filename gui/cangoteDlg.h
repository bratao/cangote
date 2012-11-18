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

#ifndef CANGOTEDLG_H
#define CANGOTEDLG_H

#include <QMainWindow>
#include <QSystemTrayIcon>

struct GNUnetManager;



//Opaque definitions
class NetworkWnd;
class TransferWnd;
class SearchWnd;
class LogWnd;
class FriendStatus;
class NATStatus;
class PeerStatus;
class RatesStatus;
class BrowserWnd;
class SharedWnd;
namespace Ui {
class CangoteDlg;
}

class CangoteDlg : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CangoteDlg(QWidget *parent = 0);

    enum Pages{BROWSER_WND, NETWORK_WND,SEARCH_WND,TRANSFER_WND,SHARED_WND, LOG_WND,NB_WND};

    ~CangoteDlg();

    void Connect();

    //Dialogs
    NetworkWnd* networkWnd;
    TransferWnd* transferWnd;
    SearchWnd* searchWnd;
    SharedWnd* sharedWnd;
    LogWnd* logWnd;
    BrowserWnd* browserWnd;

    void GNUNetConnected();
private slots:
    void on_actionSettings_triggered();
    void on_trayAction( QSystemTrayIcon::ActivationReason reason );

    void on_actionNetwork_triggered();

    void on_actionTransfer_triggered();

    void on_actionSearch_triggered();

    void on_actionLogs_triggered();

    void process();

    void on_actionBrowser_triggered();

    void on_actionShared_Files_triggered();

    void on_actionSettings_2_triggered();

private:
    Ui::CangoteDlg *ui;

    FriendStatus*   friendStatus;
    NATStatus*    natstatus;
    PeerStatus*    peerStatus;
    RatesStatus*  ratesstatus;
    QTimer *timer;

    void InitDialogs();

    //Tray
    QSystemTrayIcon * m_trayIcon;

    void createTrayIcon();


};

#endif // CANGOTEDLG_H
