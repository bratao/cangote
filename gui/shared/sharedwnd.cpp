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


#include "sharedwnd.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QStandardItemModel>
#include <QStandardItem>

#include "sharedfileswidget.h"
#include "sharedtreewidget.h"

#include "core/cangote.h"
#include "core/gnunet/gnunet.h"


SharedWnd::SharedWnd(QWidget *parent) :
    QWidget(parent)
{

  Init();

}


void SharedWnd::Init()
{
    InitSideList();
    InitMainList();


    QHBoxLayout *layout = new QHBoxLayout(this);

    QSplitter* spl = new QSplitter(this);


    spl->addWidget(m_sideList);
    spl->addWidget(m_mainList);


    layout->addWidget(spl);

    setLayout(layout);
}

void SharedWnd::GNUnetConnected()
{
    //transferList->setModel(theApp->gnunet->getDownloadsModel());
}


void SharedWnd::InitSideList()
{
    m_sideList = new SharedTreeWidget(this);


    QStandardItemModel* model = new QStandardItemModel(this);
    QStandardItem *parentItem = model->invisibleRootItem();

    QStandardItem *item = new QStandardItem("Downloads");
    item->setEditable(false);
    item->setIcon(QIcon(":/res/statusbar/grayled.png"));
    parentItem->appendRow(item);

    item = new QStandardItem("Shared Files");
    item->setEditable(false);
    item->setIcon(QIcon(":/res/statusbar/grayled.png"));
    parentItem->appendRow(item);


    m_sideList->setModel(model);
    m_sideList->setHeaderHidden(true);
}

void SharedWnd::InitMainList()
{
    m_mainList = new SharedFilesWidget(this);

}
