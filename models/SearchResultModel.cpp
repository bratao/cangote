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


#include "SearchResultModel.h"
#include <QQmlEngine>
#include <sstream>
//#include "utils/misc.h"
#include "core/gnunet/filesharing/search/searchresult.h"




SearchResultsModel::SearchResultsModel(QObject *parent) :
    QAbstractListModel(parent)
{


    connect(this,&SearchResultsModel::addResultSignal,this, &SearchResultsModel::addResultSlot, Qt::BlockingQueuedConnection);

}

int SearchResultsModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}


QVariant SearchResultsModel::data(const QModelIndex& index, int role) const
{

    SearchResult* result = m_data[index.row()];

    switch(role)
    {
    case PREVIEW:
        return QString("image://searchResultThumbnail/%1/%2").arg(m_index->row()).arg(index.row());
        break;
    case FILENAME:
        return result->name();
        break;
    case FILESIZE:
        return result->getFilesize();
        break;
    case AVAILIABILITY:
        return  result->getPercentAvail();
        break;
    case APPLICABILITYTRANK:
        return result->getApplicabilityRank();
        break;
    default:
        return QVariant::Invalid;
    }


    return QVariant::Invalid;
}

QHash<int, QByteArray> SearchResultsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PREVIEW]             = "preview";
    roles[FILENAME]             = "filename";
    roles[FILESIZE]             = "filesize";
    roles[AVAILIABILITY]        = "availiability";
    roles[APPLICABILITYTRANK]   = "availiabilityRank";


    return roles;
}



SearchResult* SearchResultsModel::addResult()
{
    SearchResult* result = new SearchResult();

    emit addResultSignal(result);

    return result;

}


void SearchResultsModel::addResultSlot(SearchResult* result)
{
    int count = m_data.count();


    beginInsertRows(QModelIndex(), count, count);


    connect(result, SIGNAL(modifiedSignal(int)),SLOT(resultModifiedSlot(int)));
    connect(result, SIGNAL(destroyed(QObject *)),SLOT(removeResultSlot(QObject *)));

    m_data.append(result);

    endInsertRows();



    result->setIndex(new QPersistentModelIndex (index(count, 0)));

}



void SearchResultsModel::resultModifiedSlot(int indexRow)
{
    emit dataChanged(index(indexRow,0), index(indexRow,NB_SEARCH_COLUMNS-1));

}


void SearchResultsModel::removeResultSlot(QObject* result)
{

    SearchResult* searchResult  = (SearchResult*)result;
    beginRemoveRows(QModelIndex(), searchResult->getIndex()->row(), searchResult->getIndex()->row());
    m_data.removeOne(searchResult);
    endRemoveRows();

}




SearchResult* SearchResultsModel::getResult(int index)
{
    if(index >= m_data.count())
        return NULL;

    SearchResult* searchResult = m_data.at(index);

    QQmlEngine::setObjectOwnership(searchResult, QQmlEngine::CppOwnership);

    return m_data.at(index);
}




int SearchResultsModel::getSize()
{
    return m_data.size();
}


