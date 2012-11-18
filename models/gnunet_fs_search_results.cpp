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


#include "gnunet_fs_search_results.h"
#include <sstream>
#include "utils/misc.h"
#include "core/gnunet/filesharing/search/searchresult.h"

GNUnetFsSearchResultsModel::GNUnetFsSearchResultsModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}



int GNUnetFsSearchResultsModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int GNUnetFsSearchResultsModel::columnCount(const QModelIndex& parent) const
{
    return NB_SEARCH_COLUMNS;
}

QVariant GNUnetFsSearchResultsModel::data(const QModelIndex& index, int role) const
{
  if(role == Qt::DisplayRole)
    {


       switch(index.column())
       {
           case FILENAME:
               return m_data[index.row()]->getFilename();
               break;
           case FILESIZE:
           return m_data[index.row()]->getFilesize();
               break;
           case AVAILIABILITY:
           return  m_data[index.row()]->getPercentAvail();
               break;
           case APPLICABILITYTRANK:
           return m_data[index.row()]->getApplicabilityRank();
               break;
           default:
                 return QVariant::Invalid;
       }

    }

  return QVariant::Invalid;
}

QVariant GNUnetFsSearchResultsModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case FILENAME:
                    return tr("Filename");
                    break;

                case FILESIZE:
                    return tr("Size");
                    break;

                case AVAILIABILITY:
                    return tr("Availability");
                    break;
                case APPLICABILITYTRANK:
                    return tr("#");
                    break;


                default:
                    return QVariant();
            }
        }
        return QVariant();

}





SearchResult* GNUnetFsSearchResultsModel::createResult()
{
    int count = m_data.count();


    beginInsertRows(QModelIndex(), count, count);

    SearchResult* newresult = new SearchResult(this);

    connect(newresult, SIGNAL(modifiedSignal(int)),SLOT(resultModifiedSlot(int)));
    connect(newresult, SIGNAL(destroyed(QObject *)),SLOT(removeResultSlot(QObject *)));

    m_data.append(newresult);

    endInsertRows();



    newresult->setIndex(new QPersistentModelIndex (index(count, 0)));

    return newresult;
}



void GNUnetFsSearchResultsModel::resultModifiedSlot(int indexRow)
{
    emit dataChanged(index(indexRow,0), index(indexRow,NB_SEARCH_COLUMNS-1));

}


void GNUnetFsSearchResultsModel::removeResultSlot(QObject* result)
{


    SearchResult* searchResult  = (SearchResult*)result;

        beginRemoveRows(QModelIndex(), searchResult->getIndex()->row(), searchResult->getIndex()->row());

        m_data.removeOne(searchResult);

        endRemoveRows();


}

 SearchResult* GNUnetFsSearchResultsModel::getResult(int index)
{
    if(m_data.count() <= index-1  )
      return NULL;
    return m_data[index];
}


void GNUnetFsSearchResultsModel::RequestToDie()
{

  emit AskedToDieSignal();
}

void GNUnetFsSearchResultsModel::Die()
{

  emit DeadSignal();
}

int GNUnetFsSearchResultsModel::getSize()
{
    return m_data.size();
}


