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

#include "MetadataModel.h"

MetaModel::MetaModel(QObject *parent) :
    QAbstractListModel(parent)
{

    connect(this, &MetaModel::addSignal, this, &MetaModel::addSlot);


}
int MetaModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

QVariant MetaModel::data(const QModelIndex& index, int role) const
{

    Metadata* metadata = m_data[index.row()];


    switch(role)
    {

    case NAME:
        return metadata->name;
        break;
    case VALUE:
        return metadata->value;//search->num_results;
        break;
    default:
        return QVariant::Invalid;
    }


    return QVariant::Invalid;
}


QHash<int, QByteArray> MetaModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NAME]                 = "name";
    roles[VALUE]                = "value";



    return roles;
}


Metadata *MetaModel::add(QString name, QString value )
{

    Metadata* metadata = new Metadata;
    metadata->name = name;
    metadata->value = value;

    emit addSignal(metadata);

    return metadata;

}

void  MetaModel::addSlot(Metadata* metadata)
{
    int count = m_data.count();

    beginInsertRows(QModelIndex(), count, count);

    m_data.append(metadata);
    //connect(download, &DownloadItem::modifiedSignal,this, &DownloadsModel::resultModifiedSlot);
    //download->setIndex(count);

    endInsertRows();


}



Metadata* MetaModel::getMetadata(int index)
{
    if ((index < 0) || (index >= m_data.count()))
        return NULL;


    return m_data.at(index);

}

int MetaModel::getCount()
{
    return m_data.count();
}


void MetaModel::clear()
{
    beginResetModel();

    m_data.clear();

    endResetModel();
}

