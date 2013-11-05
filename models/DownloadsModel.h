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

#ifndef DOWNLOADMODEL_H
#define DOWNLOADMODEL_H

#include <QAbstractListModel>
#include <QQuickImageProvider>


/***
 * Thumbnail Provider for QML
 **/

class TransferThumbnailImageProvider : public QQuickImageProvider
{
public:
    TransferThumbnailImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};




class DownloadItem;
class DownloadsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TransferThumbnailImageProvider* thumbnailProvider READ thumbnailProvider CONSTANT)
public:
    explicit DownloadsModel(QObject *parent = 0);
    DownloadItem *addDownload(DownloadItem *pde,struct GNUNET_FS_DownloadContext *dc, const struct GNUNET_FS_Uri *uri,
                              QString filePath, const struct GNUNET_CONTAINER_MetaData *meta, qint64 size, qint64 completed);


    TransferThumbnailImageProvider* thumbnailProvider() const
    { return m_thumbnailProvider; }




private:
    enum DownloadRoles {NAME = Qt::UserRole + 1, SIZE, PROGRESS, STATUS, DLSPEED, ETA, LABEL,
                        ADD_DATE, AMOUNT_DOWNLOADED, AMOUNT_LEFT, TIME_ELAPSED, NB_COLUMNS};

signals:
    void addDownloadSignal(DownloadItem* download);
public slots:
    void resultModifiedSlot(int indexRow);

private slots:
    void addDownloadSlot(DownloadItem* download);

public:
    int rowCount(const QModelIndex& parent) const;
    int rowCount();
    QVariant data(const QModelIndex& index, int role) const;


    Q_INVOKABLE DownloadItem *get(int index);
    int get(QString hash);
private:
    QHash<int, QByteArray> roleNames() const;
    QList<DownloadItem*> m_data;

    QHash<QString, int> m_hashData;
    TransferThumbnailImageProvider* m_thumbnailProvider;
    
 };

#endif // DOWNLOADMODEL_H
