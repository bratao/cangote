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

#include "DownloadsModel.h"
#include "core/gnunet/gnunet_includes.h"
#include "core/gnunet/filesharing/transfer/downloaditem.h"

DownloadsModel::DownloadsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(this, &DownloadsModel::addDownloadSignal, this, &DownloadsModel::addDownloadSlot);
}


int DownloadsModel::rowCount(const QModelIndex& parent) const
{
    return m_data.size();
}

int DownloadsModel::rowCount()
{
    return m_data.size();
}


QVariant DownloadsModel::data(const QModelIndex& index, int role) const
{

    DownloadItem* download = m_data[index.row()];

    switch(role)
    {
    case NAME:
        return m_data[index.row()]->getFilename();
        break;
    case SIZE:
        return m_data[index.row()]->getSize();
        break;
    case PROGRESS:
        return m_data[index.row()]->getCompletedPercentage();
        break;
    case STATUS:
    {
        int state = m_data[index.row()]->getState();
        if(state == DownloadItem::STATE_ERROR)
            return tr("Error");
        else if (state == DownloadItem::STATE_STOP)
            return tr("Stop");
        else if (state == DownloadItem::STATE_PAUSED)
            return tr("Paused");
        else if (state == DownloadItem::STATE_QUEUED)
            return tr("Error");
        else if (state == DownloadItem::STATE_DOWNLOADING)
            return tr("Downloading");
        else if (state == DownloadItem::STATE_COMPLETE)
            return tr("Complete");
        else
            return tr("Invalid");
        break;
    }
    case DLSPEED:
        return m_data[index.row()]->getFilename();
        break;
    case ETA:
        return m_data[index.row()]->getFilename();
        break;
    case LABEL:
        return m_data[index.row()]->getFilename();
        break;
    case ADD_DATE:
        return m_data[index.row()]->getFilename();
        break;
    case AMOUNT_DOWNLOADED:
        return m_data[index.row()]->getCompleted();
        break;
    case AMOUNT_LEFT:
        return m_data[index.row()]->getRemainingDownload();
        break;
    case TIME_ELAPSED:
        return m_data[index.row()]->getFilename();
        break;
    default:
        return QVariant::Invalid;
    }

}




DownloadItem* DownloadsModel::addDownload(DownloadItem *pde, struct GNUNET_FS_DownloadContext *dc,
                                          const struct GNUNET_FS_Uri *uri, QString filename,
                                          const struct GNUNET_CONTAINER_MetaData *meta, qint64 size,
                                          qint64 completed )
{


    //Convert uri to Key
    GNUNET_HashCode hashcode;
    GNUNET_FS_uri_to_key(uri,&hashcode);

    //Get as QString
    const char * hash = GNUNET_h2s_full(&hashcode);
    QString strHash = QString(hash);



    DownloadItem* download = new DownloadItem(strHash);

    download->setParent(pde);
    download->setContext(dc);
    char* fancyName =  GNUNET_CONTAINER_meta_data_get_first_by_types (meta,
                                                                 EXTRACTOR_METATYPE_PACKAGE_NAME,
                                                                 EXTRACTOR_METATYPE_TITLE,
                                                                 EXTRACTOR_METATYPE_BOOK_TITLE,
                                                                 EXTRACTOR_METATYPE_GNUNET_ORIGINAL_FILENAME,
                                                                 EXTRACTOR_METATYPE_FILENAME,
                                                                 EXTRACTOR_METATYPE_DESCRIPTION,
                                                                 EXTRACTOR_METATYPE_SUMMARY,
                                                                 EXTRACTOR_METATYPE_ALBUM,
                                                                 EXTRACTOR_METATYPE_COMMENT,
                                                                 EXTRACTOR_METATYPE_SUBJECT,
                                                                 EXTRACTOR_METATYPE_KEYWORDS,
                                                                 -1);


    download->setPath(filename);

    download->setFilename(QString(fancyName));
    download->setMetadata(meta);
    download->setSize(size);
    download->setCompleted(completed);


    emit addDownloadSignal(download);

    return download;


}

QHash<int, QByteArray> DownloadsModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NAME]                   = "name";
    roles[SIZE]                   = "size";
    roles[PROGRESS]               = "downloadProgress";
    roles[STATUS]                 = "status";
    roles[DLSPEED]                = "downSpeed";
    roles[ETA]                    = "eta";
    roles[LABEL]                  = "label";
    roles[ADD_DATE]               = "addDate";
    roles[AMOUNT_DOWNLOADED]      = "amountDownloaded";
    roles[AMOUNT_LEFT]            = "amoutLeft";
    roles[TIME_ELAPSED]           = "timeElapsed";


    return roles;
}


void DownloadsModel::addDownloadSlot(DownloadItem* download)
{

    int count = m_data.count();




    beginInsertRows(QModelIndex(), count, count);

    m_hashData.insert(download->getHash(),count);

    m_data.append(download);
    connect(download, &DownloadItem::modifiedSignal,this, &DownloadsModel::resultModifiedSlot);
    download->setIndex(count);

    endInsertRows();


}

void DownloadsModel::resultModifiedSlot(int indexRow)
{
    emit dataChanged(index(indexRow,0), index(indexRow,0));
}

DownloadItem* DownloadsModel::get(int index)
{
    if ((index < 0) || (index >= m_data.count()))
        return NULL;


    return m_data.at(index);

}

/**
 * @brief Get index for specified hash
 * @param hash
 * @return -1 for not found, >0 otherwise.
 */
int DownloadsModel::get(QString hash)
{

    if(m_hashData.contains(hash))
        return m_hashData[hash];
    else
        return -1;

}

