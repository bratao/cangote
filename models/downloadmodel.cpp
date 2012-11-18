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

#include "downloadmodel.h"
#include "core/gnunet/gnunet_includes.h"
#include "core/gnunet/filesharing/transfer/downloaditem.h"

DownloadModel::DownloadModel(QObject *parent) :
    QAbstractListModel(parent)
{
}


int DownloadModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}
int DownloadModel::columnCount(const QModelIndex& parent) const
{
    return DownloadItem::NB_COLUMNS;
}

int DownloadModel::rowCount()
{
    return m_data.size();
}
int DownloadModel::columnCount()
{
    return DownloadItem::NB_COLUMNS;
}



QVariant DownloadModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
      {


         switch(index.column())
         {
         case DownloadItem::TR_NAME:
             return m_data[index.row()]->getFilename();
             break;
         case DownloadItem::TR_SIZE:
             return m_data[index.row()]->getSize();
             break;
         case DownloadItem::TR_PROGRESS:
             return m_data[index.row()]->getCompletedPercentage();
             break;
         case DownloadItem::TR_STATUS:
             return m_data[index.row()]->getState();
             break;
         case DownloadItem::TR_DLSPEED:
             return m_data[index.row()]->getFilename();
             break;
         case DownloadItem::TR_ETA:
             return m_data[index.row()]->getFilename();
             break;
         case DownloadItem::TR_LABEL:
             return m_data[index.row()]->getFilename();
             break;
         case DownloadItem::TR_ADD_DATE:
             return m_data[index.row()]->getFilename();
             break;
         case DownloadItem::TR_AMOUNT_DOWNLOADED:
             return m_data[index.row()]->getCompleted();
             break;
         case DownloadItem::TR_AMOUNT_LEFT:
             return m_data[index.row()]->getRemainingDownload();
             break;
         case DownloadItem::TR_TIME_ELAPSED:
             return m_data[index.row()]->getFilename();
             break;
         default:
               return QVariant::Invalid;
     }

  }

return QVariant::Invalid;
}


QVariant DownloadModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case DownloadItem::TR_NAME:
                return "Name";
                break;
            case DownloadItem::TR_SIZE:
                return "Size";
                break;
            case DownloadItem::TR_PROGRESS:
                return "Progress";
                break;
            case DownloadItem::TR_STATUS:
                return "Status";
                break;
            case DownloadItem::TR_DLSPEED:
                return "Download Speed";
                break;
            case DownloadItem::TR_ETA:
                return "Estimated Time";
                break;
            case DownloadItem::TR_LABEL:
                return "Label";
                break;
            case DownloadItem::TR_ADD_DATE:
                return "Date Added";
                break;
            case DownloadItem::TR_AMOUNT_DOWNLOADED:
                return "Amount Downloaded";
                break;
            case DownloadItem::TR_AMOUNT_LEFT:
                return "Amout Left";
                break;
            case DownloadItem::TR_TIME_ELAPSED:
                return "Time elapsed";
                break;
            default:
                  return QVariant::Invalid;
        }
    }
    return QVariant();

}



DownloadItem* DownloadModel::addDownload(DownloadItem *pde, struct GNUNET_FS_DownloadContext *dc,
                                     const struct GNUNET_FS_Uri *uri, QString filename,
                                     const struct GNUNET_CONTAINER_MetaData *meta,uint64_t size,
                                     uint64_t completed )
{

    int count = m_data.count();

    //Convert
    QString strUri;
    char* tempuri = GNUNET_FS_uri_to_string (uri);
    strUri = strUri.fromUtf8(tempuri);

    DownloadItem* download = new DownloadItem(strUri,count, this);

    download->setParent(pde);
    download->setContext(dc);
    download->setFilename(filename);
    download->setMetadata(meta);
    download->setSize(size);
    download->setCompleted(completed);




    beginInsertRows(QModelIndex(), count, count);

    m_data.append(download);

    connect(download, SIGNAL(modifiedSignal(int)),SLOT(resultModifiedSlot(int)));


    endInsertRows();

    return download;

}

void DownloadModel::resultModifiedSlot(int indexRow)
{
    emit dataChanged(index(indexRow,0), index(indexRow,DownloadItem::NB_COLUMNS));

}
