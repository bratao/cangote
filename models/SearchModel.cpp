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

#include "SearchModel.h"
#include "core/gnunet/filesharing/search/search.h"
#include "models/SearchResultModel.h"

SearchModel::SearchModel(QObject *parent) :
    QAbstractListModel(parent)
{

    // connect signal-slots for decoupling
    connect (this, &SearchModel::addNewSearchSignal, this,
             &SearchModel::addNewSearchSlot,Qt::BlockingQueuedConnection);

    connect (this, &SearchModel::closeSearchSignal, this,
             &SearchModel::closeSearchSlot,Qt::QueuedConnection);

}
int SearchModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

QVariant SearchModel::data(const QModelIndex& index, int role) const
{

    Search* search = m_data[index.row()];


    switch(role)
    {

    case TERM:
        return search->getTerm();
        break;
    case NUM_RESULTS:
        return 0;//search->num_results;
        break;
    case SEARCH:
        //return search;
        break;
    default:
        return QVariant::Invalid;
    }


    return QVariant::Invalid;
}


QHash<int, QByteArray> SearchModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TERM]                   = "term";
    roles[NUM_RESULTS]            = "numResults";
    roles[SEARCH]                 = "Search";



    return roles;
}


Search*  SearchModel::addNewSearch(void *sc,QString term )
{

    Search* search = new Search((GNUNET_FS_SearchContext*)sc,term );
    emit addNewSearchSignal(search);
    return search;
}

void  SearchModel::addNewSearchSlot(Search* search)
{

    SearchResultsModel* resultModel = new SearchResultsModel(this);
    search->setModel(resultModel);

    int count = m_data.count();

    beginInsertRows(QModelIndex(), count, count);


    m_data.append(search);

    endInsertRows();


}

void SearchModel::closeSearch(int index )
{

    emit closeSearchSignal(index);

}

void  SearchModel::closeSearchSlot(int index)
{

    beginRemoveRows(QModelIndex(), index, index);

    Search* search = getSearch(index);
    search->Stop();

    //Model was allocated here because QML can't work with cross-tread models.
    if(search->model())
        delete search->model();

    m_data.removeAt(index);

    endRemoveRows();






}


Search* SearchModel::getSearch(int index)
{
    if ((index < 0) || (index >= m_data.count()))
        return NULL;


    return m_data.at(index);

}

int SearchModel::getCount()
{
    return m_data.count();
}
