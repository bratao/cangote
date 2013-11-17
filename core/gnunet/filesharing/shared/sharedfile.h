/**************************************************************************
** This file is part of Cangote
** (C)2/26/2013 2013 Bruno Cabral (and other contributing authors)
**
** Cangote is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published
** by the Free Software Foundation; either version 3, or (at your
** option) any later version.
**
** Cangote is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Cangote; see the file COPYING.  If not, write to the
** Free Software Foundation, Inc., 59 Temple Place - Suite 330,
** Boston, MA 02111-1307, USA.
**************************************************************************/

#ifndef SHAREDFILE_H
#define SHAREDFILE_H

#include <QObject>
#include <utils/utils.h>
#include "cangote.h"

class SharedFile : public QObject
{
    Q_OBJECT


public:
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(uint64_t size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString hash READ hash WRITE setHash NOTIFY hashChanged)
    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)


public:
    explicit SharedFile(QObject *parent = 0);
    
  enum Status { Publishing, Published,Indexed,Unindexing,Unindexed, Error, Unknown };
  Q_ENUMS(Status)

    QString filename() const
    { return m_filename; }
    void setFilename(QString filename)
    {
        m_filename = filename;
        emit filenameChanged(filename);
    }

    QString path() const
    { return m_path; }
    void setPath(QString path)
    {
        m_path = path;
        setFilename(theUtils->getFileName(path));

        emit pathChanged(path);
    }

    QString hash() const
    { return m_hash; }
    void setHash(QString hash)
    {
        m_hash = hash;
        emit hashChanged(hash);
    }

    uint64_t size() const
    { return m_size; }
    void setSize(uint64_t size)
    {
        m_size = size;
        emit sizeChanged(size);
    }

    int progress() const
    { return m_progress; }
    void setProgress(int progress)
    {
        m_progress = progress;
        emit progressChanged(m_index);
    }

    QString getFancyStatus();
signals:
    void filenameChanged(QString);
    void pathChanged(QString);
    void hashChanged(QString);
    void sizeChanged(uint64_t);
    void progressChanged(int index);
    void statusChanged(int index);

public slots:


public:
    void setStatus(Status status);

    void setIndex(int index);
private:
    QString m_filename;
    QString m_path;
    QString m_hash;
    uint64_t m_size;
    int m_progress;
    Status m_status;
    int m_index;
};

#endif // SHAREDFILE_H
