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

#include "PublishFileModel.h"


PublishFileModel::PublishFileModel(QObject *parent) :
    QAbstractListModel(parent)
{



}
int PublishFileModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

QVariant PublishFileModel::data(const QModelIndex& index, int role) const
{

    //Search* search = m_data[index.row()];


    switch(role)
    {

    case TERM:
        //return search->getTerm();
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


QHash<int, QByteArray> PublishFileModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TERM]                   = "term";
    roles[NUM_RESULTS]            = "numResults";
    roles[SEARCH]                 = "Search";



    return roles;
}


PublishFile*  PublishFileModel::addFile(QString path )
{

    return NULL;
}




PublishFile* PublishFileModel::getPublishedFile(int index)
{
    if ((index < 0) || (index >= m_data.count()))
        return NULL;


    return m_data.at(index);

}

int PublishFileModel::getCount()
{
    return m_data.count();
}
