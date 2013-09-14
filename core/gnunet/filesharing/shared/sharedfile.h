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

class SharedFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(uint64_t size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString hash READ hash WRITE setHash NOTIFY hashChanged)
public:
    explicit SharedFile(QObject *parent = 0);
    


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

signals:
    void filenameChanged(QString);
    void pathChanged(QString);
    void hashChanged(QString);
    void sizeChanged(uint64_t);
public slots:


private:
    QString m_filename;
    QString m_path;
    QString m_hash;
    uint64_t m_size;
    
};

#endif // SHAREDFILE_H
