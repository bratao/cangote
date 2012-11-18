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

#ifndef DOWNLOADITEM_H
#define DOWNLOADITEM_H

#include <QObject>
#include <QPersistentModelIndex>

class DownloadItem : public QObject
{
    Q_OBJECT
public:
    explicit DownloadItem(QString uri, int index, QObject *parent = 0);

    enum State {STATE_ERROR, STATE_STOP ,STATE_PAUSED, STATE_QUEUED,STATE_DOWNLOADING, STATE_COMPLETE, STATE_INVALID};
    enum Column {TR_NAME, TR_SIZE, TR_PROGRESS, TR_STATUS, TR_DLSPEED, TR_ETA, TR_LABEL, TR_ADD_DATE, TR_AMOUNT_DOWNLOADED, TR_AMOUNT_LEFT, TR_TIME_ELAPSED, NB_COLUMNS};

    
signals:
        void modifiedSignal(int index);
public slots:

public:
    void setCompleted(uint64_t completed, bool notifyModified = true);
    uint64_t getCompleted();
    void setSize(uint64_t size, bool notifyModified = true);
    uint64_t getSize();
    void setMetadata(const struct GNUNET_CONTAINER_MetaData *meta, bool notifyModified = true);
    const GNUNET_CONTAINER_MetaData *getMetadata();
    void setFilename(QString filename, bool notifyModified = true);
    QString getFilename();
    QString getUri();
    void setContext(struct GNUNET_FS_DownloadContext *context, bool notifyModified = true);
    struct GNUNET_FS_DownloadContext *getContext();
    void setParent(DownloadItem *parent, bool notifyModified = true);
    DownloadItem *getParent();
    void modified();
    uint64_t getRemainingDownload();
    float getCompletedPercentage();
    void setStopped();
    void setPaused();
    void setCompleted();
    void setError();
    void setComplete();
    int getState();
    void setDownloading();
    int getETA();
    void setETA(int eta);
    int getDataAdded();
    void setDataAdded(int date);
private:
    DownloadItem * m_parent;
    struct GNUNET_FS_DownloadContext *m_context;
    QString m_uri;
    QString m_filename;
    const struct GNUNET_CONTAINER_MetaData *m_meta;
    uint64_t m_size;
    uint64_t m_completed;

    uint64_t m_eta;
    uint64_t m_dateAdded;

    struct GNUNET_FS_Uri *uri;
    struct GNUNET_FS_DownloadContext *dc;
    DownloadItem *pde;



    State m_state;

    int index;

};

#endif // DOWNLOADITEM_H
