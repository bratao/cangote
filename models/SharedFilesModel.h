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

#ifndef SHAREDFILESMODEL_H
#define SHAREDFILESMODEL_H

#include <QAbstractTableModel>
#include <QQuickImageProvider>
#include "core/gnunet/filesharing/shared/sharedfile.h"


/***
 * Thumbnail Provider for QML
 **/

class SharedFilesThumbnailImageProvider : public QQuickImageProvider
{
public:
    SharedFilesThumbnailImageProvider()
        : QQuickImageProvider(QQuickImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};



class SharedFile;
class SharedFilesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SharedFilesThumbnailImageProvider* thumbnailProvider READ thumbnailProvider CONSTANT)

public:
    explicit SharedFilesModel(QObject *parent = 0);

    SharedFilesThumbnailImageProvider* thumbnailProvider() const
    { return m_thumbnailProvider; }

    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data(const QModelIndex& index, int role) const;
    enum SearchRoles { NAME,STATUS, SIZE ,PATH, NB_SEARCH_COLUMNS };


    SharedFile *addFile(QString filename, QString filehash);
    SharedFile *addFile(QString filename, uint64_t filesize);

    Q_INVOKABLE SharedFile *get(int index);
    SharedFile *getByFileName(QString filename);
signals:
     void addFileSignal(SharedFile *file);
private slots:
    void addFileSlot(SharedFile *file);
    void fileModifiedSlot(int indexRow);

private:
    QList<SharedFile*> m_data;
    QHash<int, QByteArray> roleNames() const;
    SharedFile *createFile();
    SharedFilesThumbnailImageProvider* m_thumbnailProvider;

};

#endif // SHAREDFILESMODEL_H
