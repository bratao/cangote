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

#include "gnunetfssearchmodel.h"
#include "core/gnunet/filesharing/search/search.h"


GNUnetFsSearchModel::GNUnetFsSearchModel(QObject *parent) :
    QAbstractListModel(parent)
{
}
int GNUnetFsSearchModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

QVariant GNUnetFsSearchModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
      {


         switch(index.column())
         {

         //case FILENAME:
         //return m_data[index.row()]->getApplicabilityRank();
           //  break;
         default:
               return QVariant::Invalid;
     }

  }

return QVariant::Invalid;
}


QVariant GNUnetFsSearchModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case FILENAME:
                    return tr("Filename");
                    break;
            default:
                return QVariant();
        }
    }
    return QVariant();

}

Search*  GNUnetFsSearchModel::addNewSearch(struct GNUNET_FS_SearchContext *sc,QString term )
{

    int count = m_data.count();


    beginInsertRows(QModelIndex(), count, count);

    Search* search = new Search(sc,term );

    m_data.append(search);

    endInsertRows();



    return search;


}

Search* GNUnetFsSearchModel::getSearch(int index)
{
    if ((index < 0) || (index >= m_data.count()))
        return NULL;

    return m_data.at(index);

}

int GNUnetFsSearchModel::getCount()
{
    return m_data.count();
}
