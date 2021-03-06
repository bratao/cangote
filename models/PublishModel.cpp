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

#include "PublishModel.h"
#include "core/gnunet/filesharing/publish/publish.h"
#include "core/gnunet/filesharing/publish/publishfile.h"


/***
 * Thumbnail Provider for QML
 **/


QImage PublishThumbnailImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

    int width = 200;
    int height = 100;

    if (size)
        *size = QSize(width, height);


    //Default image
    QImage image(requestedSize.width() > 0 ? requestedSize.width() : width,
                 requestedSize.height() > 0 ? requestedSize.height() : height,QImage::Format_ARGB32);

    image.fill(QColor(id).rgba());

    //Load from file
    PublishFile* file = theApp->models()->publishModel()->getPublishedFile(id.toInt());
    if (file && file->thumbnail())
    {

        //If we ask for an specified size, do it. Scale to height otherwise.
        if((requestedSize.width() > 0 )&&(requestedSize.height() > 0)){
            image = file->thumbnail()->scaled(requestedSize.width() > 0 ? requestedSize.width() : width,
                                               requestedSize.height() > 0 ? requestedSize.height() : height);
        }
        else
        {
            image = file->thumbnail()->scaledToHeight(height,Qt::SmoothTransformation);
        }

    }

     return image;


}

//Thumbnail end



PublishModel::PublishModel(QObject *parent) :
    QAbstractListModel(parent)
{

    m_thumbnailProvider = new PublishThumbnailImageProvider();

    connect(this, &PublishModel::addFileSignal, this, &PublishModel::addFileSlot);


}
int PublishModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

QVariant PublishModel::data(const QModelIndex& index, int role) const
{

    PublishFile* file = m_data[index.row()];


    switch(role)
    {

    case NAME:
        return file->fileName();
        break;
    case PATH:
        return 0;//search->num_results;
        break;
    case TYPE:
        //return search;
        break;
    default:
        return QVariant::Invalid;
    }


    return QVariant::Invalid;
}


QHash<int, QByteArray> PublishModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NAME]                   = "name";
    roles[PATH]                   = "path";
    roles[TYPE]                   = "type";



    return roles;
}


PublishFile*  PublishModel::add(QString name, GNUNET_FS_FileInformation *fi, PublishFile* parent )
{

    PublishFile* file = new PublishFile(name, fi,parent);
    file->moveToThread(this->thread());
    emit addFileSignal(file);

    return file;

}

PublishFile*  PublishModel::addFileSlot(PublishFile* file)
{
    int count = m_data.count();

    beginInsertRows(QModelIndex(), count, count);

    m_data.append(file);
    //connect(download, &DownloadItem::modifiedSignal,this, &DownloadsModel::resultModifiedSlot);
    //download->setIndex(count);

    endInsertRows();


}



PublishFile* PublishModel::getPublishedFile(int index)
{
    if ((index < 0) || (index >= m_data.count()))
        return NULL;

    PublishFile* file = m_data.at(index);

    QQmlEngine::setObjectOwnership(file, QQmlEngine::CppOwnership);

    return file;

}

int PublishModel::getCount()
{
    return m_data.count();
}

int PublishModel::clean()
{
  beginResetModel();
  m_data.clear();
  endResetModel();
}

