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

class DownloadItem;
class DownloadModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DownloadModel(QObject *parent = 0);
    
signals:
    
public slots:
    void resultModifiedSlot(int indexRow);
public:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    int rowCount();
    int columnCount();
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QList<DownloadItem*> m_data;
    
    DownloadItem *addDownload(DownloadItem *pde,struct GNUNET_FS_DownloadContext *dc, const struct GNUNET_FS_Uri *uri, QString filename, const struct GNUNET_CONTAINER_MetaData *meta, uint64_t size, uint64_t completed);
};

#endif // DOWNLOADMODEL_H
