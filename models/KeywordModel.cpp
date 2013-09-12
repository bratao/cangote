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

#include "KeywordModel.h"
#include "core/gnunet/filesharing/publish/publish.h"
#include "core/gnunet/filesharing/publish/publishfile.h"
KeywordModel::KeywordModel(QObject *parent) :
    QAbstractListModel(parent)
{

    connect(this, &KeywordModel::addSignal, this, &KeywordModel::addSlot);


}
int KeywordModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

QVariant KeywordModel::data(const QModelIndex& index, int role) const
{

    QString value = m_data[index.row()];


    switch(role)
    {

    case NAME:
        return value;
        break;
    default:
        return QVariant::Invalid;
    }


    return QVariant::Invalid;
}


QHash<int, QByteArray> KeywordModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NAME]                   = "name";


    return roles;
}


void KeywordModel::add(QString name)
{

    emit addSignal(name);


}

void  KeywordModel::addSlot(QString name)
{
    int count = m_data.count();

    beginInsertRows(QModelIndex(), count, count);

    m_data.append(name);

    endInsertRows();


}



int KeywordModel::getCount()
{
    return m_data.count();
}

