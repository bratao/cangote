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

#include "networkwnd.h"
#include "core/cangote.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/network/peer.h"

#include <QTreeView>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QSortFilterProxyModel>
#include <QAction>


#include "models/gnunet_peers.h"
#include "networkpeerdelegate.h"

NetworkWnd::NetworkWnd(QWidget *parent) :
    QWidget(parent)
{

    peerlist = new QTreeView(this);

    peerlist->setAlternatingRowColors(true);
    peerlist->setItemsExpandable(false);
    peerlist->setRootIsDecorated(false);
    peerlist->setUniformRowHeights(true);
    //peerlist->verticalHeader()->hide();

    QHBoxLayout *serverLayout = new QHBoxLayout;
    serverLayout->addWidget(peerlist);
    setLayout(serverLayout);







    NetworkPeerDelegate *delegate = new NetworkPeerDelegate(this);

    peerlist->setItemDelegate(delegate);


    //Set the right click

    peerlist->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* getUrl;
    getUrl = new QAction("Get Url",this);
    peerlist->addAction(getUrl);

    connect(getUrl, SIGNAL(triggered()), this, SLOT(getUrl()));


}

void NetworkWnd::connectedGNUnet()
{

    peersModel = theApp->gnunet->getPeersModel();

   QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setSourceModel(peersModel);




    peerlist->setModel(proxyModel);
    //peerlist->setModel(peersModel);
    peerlist->setSortingEnabled(true);
}

void NetworkWnd::getUrl()
{
    QModelIndexList list = peerlist->selectionModel()->selectedIndexes();
    if(list.count() <1)
        return;

    QModelIndex index = list.at(0);

    Peer* peer = peersModel->getPeer(index);

    gWarn(peer->getURI());

}


void NetworkWnd::PeerEvent(QString id)
{

    //listModel->setStringList(theApp->gnunetMgr->GetPeerStringList());


    //peerlist->setModel(model);

    //peerlist->setModel(NULL);
    //peerlist->setModel(peersModel);

}

