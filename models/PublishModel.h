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

#ifndef PUBLISHMODEL_H
#define PUBLISHMODEL_H

#include <QAbstractListModel>
#include <QQuickImageProvider>
#include <QImage>
#include "core/cangotecore.h"
#include "models.h"



class QQuickImageProvider;
class ThumbnailImageProvider : public QQuickImageProvider
{
public:
    ThumbnailImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

class PublishFile;
class PublishModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ThumbnailImageProvider* thumbnailProvider READ thumbnailProvider CONSTANT)
public:
    explicit PublishModel(QObject *parent = 0);

    enum SearchRoles { NAME, PATH, TYPE, NB_SEARCH_TABS };

    int getCount();


    ThumbnailImageProvider* thumbnailProvider() const
    { return m_thumbnailProvider; }


    PublishFile* add(QString name, struct GNUNET_FS_FileInformation *fi, PublishFile *parent);
    Q_INVOKABLE PublishFile* getPublishedFile(int index);
public slots:

signals:
    void addFileSignal(PublishFile *file);

private slots:
    PublishFile *addFileSlot(PublishFile *file);
private:
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QList<PublishFile*> m_data;
    ThumbnailImageProvider* m_thumbnailProvider;
    
};

#endif // PUBLISHMODEL_H
