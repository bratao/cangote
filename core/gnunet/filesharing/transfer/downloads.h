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

#ifndef DOWNLOADS_H
#define DOWNLOADS_H

#include <QObject>

class DownloadItem;
class DownloadModel;
struct GNUNET_FS_DownloadContext;
struct GNUNET_FS_Uri;
struct GNUNET_CONTAINER_MetaData;

class Downloads : public QObject
{
    Q_OBJECT
public:
    explicit Downloads(QObject *parent = 0);
    
    DownloadItem *setup_download(DownloadItem *de, DownloadItem *pde, GNUNET_FS_DownloadContext *dc, const GNUNET_FS_Uri *uri, const char *filename, const GNUNET_CONTAINER_MetaData *meta, uint64_t size, uint64_t completed);
    DownloadModel* model;
    void stop_download(DownloadItem *de);
    void pause_download(DownloadItem *de);
    void mark_download_progress(DownloadItem *de, const char *filename, uint64_t size, uint64_t completed, const void *block_data, uint64_t offset, uint64_t block_size, unsigned int depth);
    void mark_download_error(DownloadItem *de, const char *emsg);
    void mark_download_completed(DownloadItem *de, uint64_t size);
    void setDownloadActive(DownloadItem *de);
    void setDownloadInactive(DownloadItem *de);
signals:
    
public slots:
    

private:

};

#endif // DOWNLOADS_H
