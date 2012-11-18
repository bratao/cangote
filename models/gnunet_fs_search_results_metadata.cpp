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

#include "gnunet_fs_search_results_metadata.h"
#include <sstream>

GNUnetFsSearchResultsMetadataModel::GNUnetFsSearchResultsMetadataModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}



int GNUnetFsSearchResultsMetadataModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int GNUnetFsSearchResultsMetadataModel::columnCount(const QModelIndex& parent) const
{
    return 2;
}

QVariant GNUnetFsSearchResultsMetadataModel::data(const QModelIndex& index, int role) const
{
  if(role == Qt::DisplayRole)
    {


       switch(index.column())
       {
           case 0:
               return m_data[index.row()]->name;
               break;
           case 1:
               return m_data[index.row()]->value;
               break;
                     default:
                 return QVariant::Invalid;
       }

    }

  return QVariant::Invalid;
}

QVariant GNUnetFsSearchResultsMetadataModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return tr("Name");
                    break;

                case 1:
                    return tr("Value");
                    break;


                default:
                    return QVariant();
            }
        }
        return QVariant();

}

bool GNUnetFsSearchResultsMetadataModel::addMetadata(Metadata* result)
{


        int count = m_data.count();


        beginInsertRows(QModelIndex(), count, count);

        m_data.append(result);

        endInsertRows();






        return true;



}

