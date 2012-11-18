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


#include "searchwnd.h"
#include "core/cangote.h"
#include "core/gnunet/gnunet.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeView>
#include <QTabWidget>
#include <QSortFilterProxyModel>
#include "models/gnunet_fs_search_results.h"
#include "models/gnunetfssearchmodel.h"
#include "core/gnunet/filesharing/search/search.h"

#include "searchdetailspanel.h"
#include "searchresulttab.h"
#include <QSplitter>


SearchWnd::SearchWnd(QWidget *parent) :
    QWidget(parent)
{



    QVBoxLayout *searchVGlobalLayout = new QVBoxLayout;
    QHBoxLayout *searchBoxLayout = new QHBoxLayout;



    QSplitter* spl = new QSplitter(this);




    searchTermBox =   new QLineEdit(this);
    searchBtn =     new QPushButton(this);
    //searchResultList = new QTreeView(this);
    searchTab = new QTabWidget(this);

    searchTab->setTabsClosable(true);


    searchBtn->setText("Search");

    searchBoxLayout->addWidget(searchTermBox);
    searchBoxLayout->addWidget(searchBtn);
    searchVGlobalLayout->addLayout(searchBoxLayout);



    panel = new SearchDetailsPanel(this);


    spl->setOrientation(Qt::Vertical);
    spl->addWidget(searchTab);
    spl->addWidget(panel);


    searchVGlobalLayout->addWidget(spl);







    setLayout(searchVGlobalLayout);



    Connect();

}

void SearchWnd::CreateNewSearchTab(QString name, GNUnetFsSearchResultsModel* model)
{

  SearchResultTab* newTab = new SearchResultTab(name,model,panel, this);



 int tabno=  searchTab->addTab(newTab, name);



 connect(newTab, SIGNAL(Closed(SearchResultTab* )),
                this,   SLOT(CloseTab(SearchResultTab* )));

 connect(newTab, SIGNAL(SetName(SearchResultTab*, QString)),
                this,   SLOT(SetTabName(SearchResultTab*, QString)));



}

void SearchWnd::GNUNetConnected()
{
    model = theApp->gnunet->getSearchModel();


    int count = model->getCount();
    if(count > 0)
    {
        for(int i = 0; i< count; i++)
        {
            Search* search = model->getSearch(i);
            CreateNewSearchTab(search->getTerm(), search->getModel());
        }
    }

    connect(model,SIGNAL(rowsInserted(const QModelIndex & , int , int)),SLOT(newSearchSlot(const QModelIndex & , int , int)));
}


void SearchWnd::newSearchSlot(const QModelIndex & parent, int start, int end)
{
    for(int i = start; i<= end; i++)
    {
        Search* search = model->getSearch(i);
        CreateNewSearchTab(search->getTerm(), search->getModel());
    }
}


void SearchWnd::Connect()
{
    connect(searchBtn, SIGNAL(clicked()), this,SLOT(OnSearch()));
    connect(searchTab, SIGNAL(tabCloseRequested(int )),
                   this,   SLOT(RequestedClose(int )));
}


void SearchWnd::OnSearch()
{
    QString keywords = searchTermBox->text();
    theApp->Search(keywords);
}

void SearchWnd::NewSearchSlot(QString term, GNUnetFsSearchResultsModel *model)
{
  CreateNewSearchTab(term, model);

}
void SearchWnd::RequestedClose(int index)
{


    QWidget* tab=  searchTab->widget(index);

    if(!tab)
      {

        gWarn("Try to close an index that don't exist");
        return;
      }


    ((SearchResultTab*)tab)->AskToClose();
    CloseTab((SearchResultTab*)tab);
    gDebug("Send a Close request to GNUnet");
    //searchTab->removeTab(index);
   // delete tab;
}

void SearchWnd::CloseTab(SearchResultTab* tab)
{
  int tabPos = GetTabIndex(tab);
  searchTab->removeTab(tabPos);
}

int SearchWnd::GetTabIndex(SearchResultTab* tab)
{
  return searchTab->indexOf(tab);
}

void SearchWnd::SetTabName(SearchResultTab* tab, QString newname)
{
  int tabPos = GetTabIndex(tab);
  searchTab->setTabText(tabPos, newname);
}




