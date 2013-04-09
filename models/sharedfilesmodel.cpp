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

#include "SharedFilesModel.h"

SharedFilesModel::SharedFilesModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(this,&SharedFilesModel::addFileSignal,this,&SharedFilesModel::addFileSlot);
}

int SharedFilesModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}


QVariant SharedFilesModel::data(const QModelIndex& index, int role) const
{
    SharedFile* file = m_data.at(index.row());

    switch(role)
    {
    case FILENAME:
        return file->filename();

    default:
        return QVariant::Invalid;
    }


    return QVariant::Invalid;
}


void SharedFilesModel::addFile(QString filename, QString filehash)
{
    emit addFileSignal(filename, filehash);
}


void SharedFilesModel::addFileSlot(QString filename, QString filehash)
{
    SharedFile* file = new SharedFile(this);
    file->setFilename(filename);
    file->setHash(filehash);

    int count = m_data.count();


    beginInsertRows(QModelIndex(), count, count);


    m_data.append(file);

    endInsertRows();

}


QHash<int, QByteArray> SharedFilesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FILENAME]             = "filename";
    roles[FILESIZE]             = "filesize";
    roles[AVAILIABILITY]        = "availiability";
    roles[APPLICABILITYTRANK]   = "availiabilityRank";


    return roles;
}


