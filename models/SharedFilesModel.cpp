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
#include "models/models.h"
#include "utils/utils.h"
#include "cangote.h"
#include "core/cangotecore.h"

/***
 * Thumbnail Provider for QML
 **/


QImage SharedFilesThumbnailImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

  int width = requestedSize.width() > 0 ? requestedSize.width() : 200;
  int height = requestedSize.height() > 0 ? requestedSize.height() :100;

  if (size)
    *size = QSize(width, height);


  //Default image
  QImage image(width,
               height,QImage::Format_ARGB32);

  image.fill(qRgba(0, 0, 0, 0));



  int transferId = id.toInt();



  //Load from file
  SharedFile* file = theApp->models()->sharedModel()->get(transferId);

  Q_ASSERT(file);
  if(file == NULL)
    return image;

  QString type = theUtils->getFileExtension(file->filename());

  return theUtils->getFileTypeImage(type,width,height);



}


SharedFilesModel::SharedFilesModel(QObject *parent) :
  QAbstractListModel(parent)
{
  m_thumbnailProvider = new SharedFilesThumbnailImageProvider();

  connect(this,&SharedFilesModel::addFileSignal,this,&SharedFilesModel::addFileSlot, Qt::BlockingQueuedConnection);
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
    case NAME:
      return file->filename();
    case STATUS:
      return file->getFancyStatus();
    case SIZE:
      return file->size();
    case PATH:
      return file->path();

    default:
      return QVariant::Invalid;
    }


  return QVariant::Invalid;
}




SharedFile* SharedFilesModel::createFile()
{
  SharedFile* file = new SharedFile();
  file->moveToThread(this->thread());
  //Connect to monitor modification
  connect(file,&SharedFile::progressChanged,this,&SharedFilesModel::fileModifiedSlot);
  connect(file,&SharedFile::statusChanged,this,&SharedFilesModel::fileModifiedSlot);
  return file;
}


void SharedFilesModel::fileModifiedSlot(int indexRow){
  emit dataChanged(index(indexRow,0), index(indexRow,0));
}


SharedFile* SharedFilesModel::addFile(QString filename, QString filehash)
{
  SharedFile* file = createFile();
  file->setPath(filename);
  file->setHash(filehash);
  emit addFileSignal(file);

  return file;
}

SharedFile* SharedFilesModel::addFile(QString filename, uint64_t filesize)
{

  SharedFile* file = createFile();

  file->setPath(filename);
  file->setSize(filesize);
  emit addFileSignal(file);

  return file;
}




void SharedFilesModel::addFileSlot(SharedFile* file)
{

  int count = m_data.count();

  beginInsertRows(QModelIndex(), count, count);
  file->setIndex(count);

  m_data.append(file);

  endInsertRows();

}


QHash<int, QByteArray> SharedFilesModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NAME]             = "name";
  roles[STATUS]           = "status";
  roles[SIZE]             = "size";
  roles[PATH]             = "path";


  return roles;
}

SharedFile* SharedFilesModel::get(int index)
{
    if ((index < 0) || (index >= m_data.count()))
        return NULL;


    SharedFile* sharedFile = m_data.at(index);
    QQmlEngine::setObjectOwnership(sharedFile, QQmlEngine::CppOwnership);


    return sharedFile;

}

SharedFile* SharedFilesModel::getByFileName(QString filename)
{

    //TODO: Improve lookup performance
    foreach (SharedFile* file, m_data) {
        if(file->filename().compare(filename) == 0)
          return file;

      }

    return NULL;

}
