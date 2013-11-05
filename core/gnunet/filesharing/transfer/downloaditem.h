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
    Q_PROPERTY(int index READ index WRITE setIndex)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString fancyName READ fancyName WRITE setFancyName NOTIFY fancyNameChanged)


public:
    explicit DownloadItem(QString hash, QObject *parent = 0);

    enum State {STATE_ERROR, STATE_STOP ,STATE_PAUSED, STATE_QUEUED,STATE_DOWNLOADING, STATE_COMPLETE, STATE_INVALID};


  //Index
    int index() const
    { return m_index; }

    void setIndex(int index)
    {
        m_index = index;
    }

  //Path
    QString path() const
    { return m_path; }

    void setPath(QString path)
    {
        m_path = path;
        emit pathChanged();
    }

    //FileName
    QString fileName() const
    { return m_filename; }

    void setFileName(QString filename)
    {
        m_filename = filename;
        emit fileNameChanged(filename);
    }

    //FancyName
    QString fancyName() const
    { return m_fancyName; }

    void setFancyName(QString fancyName)
    {
        m_fancyName = fancyName;
        emit fancyNameChanged(fancyName);
    }



signals:
    void modifiedSignal(int index);
    void fileNameChanged(QString filename);
    void fancyNameChanged(QString fancyName);
    void pathChanged();
public slots:

public:
    void setCompleted(qint64 completed, bool notifyModified = true);
    qint64 getCompleted();
    void setSize(qint64 size, bool notifyModified = true);
    qint64 getSize();
    void setMetadata(const struct GNUNET_CONTAINER_MetaData *meta, bool notifyModified = true);
    const GNUNET_CONTAINER_MetaData *getMetadata();
    QString getUri();
    void setContext(struct GNUNET_FS_DownloadContext *context, bool notifyModified = true);
    struct GNUNET_FS_DownloadContext *getContext();
    void setParent(DownloadItem *parent, bool notifyModified = true);
    DownloadItem *getParent();
    void modified();
    qint64 getRemainingDownload();
    int getCompletedPercentage();
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


    QString getHash();
private:
    DownloadItem * m_parent;
    struct GNUNET_FS_DownloadContext *m_context;
    struct GNUNET_FS_Uri *uri;
    //struct GNUNET_FS_DownloadContext *dc;
    const struct GNUNET_CONTAINER_MetaData *m_meta;


    State m_state;


    QString m_uri;
    QString m_filename;
    QString m_fancyName;
    QString m_path;
    QString m_hash;

    qint64 m_size;
    qint64 m_completed;
    qint32 m_eta;
    qint32 m_dateAdded;




    DownloadItem *pde;





    int m_index;

};

#endif // DOWNLOADITEM_H
