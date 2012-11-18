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

#include "searchresulttab.h"
#include "core/cangote.h"
#include <QTreeView>
#include <QHBoxLayout>
#include <QSortFilterProxyModel>
#include "models/gnunet_fs_search_results.h"
#include "searchdetailspanel.h"
#include "searchresultsdelegate.h"
#include "core/gnunet/filesharing/search/searchresult.h"
#include <QDebug>

SearchResultTab::SearchResultTab(QString name, GNUnetFsSearchResultsModel* model, SearchDetailsPanel *detailsPanel, QWidget *parent) :
  QWidget(parent)
{



  this->model = model;
  this->name = name;
  this->detailsPanel = detailsPanel;




  QTreeView* searchList = new QTreeView(this);

  searchList->setAlternatingRowColors(true);
  searchList->setItemsExpandable(false);
  searchList->setRootIsDecorated(false);
  searchList->setUniformRowHeights(true);

  QHBoxLayout *serverLayout = new QHBoxLayout;
  serverLayout->addWidget(searchList);
  setLayout(serverLayout);


  proxyModel = new QSortFilterProxyModel(this);
  proxyModel->setSourceModel(model);
  proxyModel->setDynamicSortFilter(true);

//TODO : Implement filter
  searchList->setModel(proxyModel);
    searchList->setSortingEnabled(true);


  SearchResultDelegate* delegate = new SearchResultDelegate(this);
  searchList->setItemDelegate(delegate);




  // Connect to the selection
   connect(searchList->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                  this,   SLOT(SelectionChanged(QModelIndex,QModelIndex)));

   // Connect to a slot that will return the view to the bookMarked spot...
    connect(searchList, SIGNAL(doubleClicked(const QModelIndex & )),
                   this,   SLOT(ResultDblClick(const QModelIndex&)));


   connect(model,SIGNAL(destroyed()), this, SLOT(Close()));
   connect(model,SIGNAL(rowsInserted ( const QModelIndex & , int , int  )), this, SLOT(ResultsChangeSlot()));


}

inline QModelIndex SearchResultTab::mapToSource(const QModelIndex &index) const {
  Q_ASSERT(index.isValid());
  return proxyModel->mapToSource(index);
}


void SearchResultTab::SelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{


    int index = mapToSource(current).row();


    SearchResult* result = model->getResult(index);

    if(result)
        detailsPanel->SetMetadata(result->getMeta());
    else
        return;
    //TODO:: Set a empty panel if no meta
}



void SearchResultTab::ResultDblClick(const QModelIndex& current)
{
    int index = mapToSource(current).row();

    SearchResult* result = model->getResult(index);
    result->download();
}


void SearchResultTab::ResultsChangeSlot()
{
  int numResults = model->getSize();
  QString numStr;
  numStr.setNum(numResults);

  QString title = QString("%1(%2)").arg(name).arg(numStr);

  emit SetName(this,title);
}

void SearchResultTab::AskToClose()
{
  model->RequestToDie();
}

void SearchResultTab::Close()
{
  emit Closed(this);
}
