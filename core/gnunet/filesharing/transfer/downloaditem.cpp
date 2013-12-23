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

#include "downloaditem.h"
#include "core/gnunet/gnunet_includes.h"

DownloadItem::DownloadItem(QString hash, QObject *parent) :
    QObject(parent)
{
    m_hash = hash;
    m_index = 0;

    m_eta = 0;
    m_dateAdded = 0;
    m_completed = 0;
    m_size = 0;
    m_state = STATE_INVALID;
}


void DownloadItem::modified()
{
  emit modifiedSignal(m_index);

}


DownloadItem * DownloadItem::getParent()
{
    return m_parent;
}


void DownloadItem::setParent(DownloadItem * parent, bool notifyModified)
{
    m_parent = parent;

    if(notifyModified)
        modified();
}


GNUNET_FS_DownloadContext * DownloadItem::getContext()
{
    return m_context;
}


void DownloadItem::setContext(GNUNET_FS_DownloadContext *context, bool notifyModified)
{
    m_context = context;

    if(notifyModified)
        modified();
}

QString DownloadItem::getUri()
{
    return m_uri;
}


const GNUNET_CONTAINER_MetaData* DownloadItem::getMetadata()
{
    return m_meta;
}


void DownloadItem::setMetadata(const GNUNET_CONTAINER_MetaData *meta, bool notifyModified)
{
    m_meta = meta;

    if(notifyModified)
        modified();
}

qint64 DownloadItem::getSize()
{
    return m_size;
}


void DownloadItem::setSize(qint64 size, bool notifyModified)
{
    m_size = size;

    if(notifyModified)
        modified();
}

qint64 DownloadItem::getCompleted()
{
    return m_completed;
}


void DownloadItem::setCompleted(qint64 completed, bool notifyModified)
{
    m_completed = completed;

    if(notifyModified)
        modified();
}



qint64 DownloadItem::getRemainingDownload()
{
    return m_size-m_completed;
}

int DownloadItem::getCompletedPercentage()
{
    float percentage = 0.0;

    if((m_completed == 0) || (m_size == 0))
        percentage = 0.0;

    percentage = m_completed/(float)m_size;

    return (int)(percentage*100);
}

void DownloadItem::setStopped()
{
    m_state = STATE_STOP;

    modified();
}

void DownloadItem::setPaused()
{
    m_state = STATE_PAUSED;

    modified();
}

void DownloadItem::setCompleted()
{
    m_state = STATE_COMPLETE;

    modified();
}

void DownloadItem::setError()
{
    m_state = STATE_ERROR;

    modified();
}


void DownloadItem::setComplete()
{
    m_state = STATE_COMPLETE;

    modified();
}

void DownloadItem::setDownloading()
{
    m_state = STATE_DOWNLOADING;

    modified();
}


int DownloadItem::getETA()
{
    return m_eta;

}

void DownloadItem::setETA(int eta)
{
   m_eta = eta ;

}

int DownloadItem::getDataAdded()
{
    return m_dateAdded;

}

void DownloadItem::setDataAdded(int date)
{
   m_dateAdded = date ;

}

int DownloadItem::getState()
{
    return m_state;
}

QString DownloadItem::getHash()
{
    return m_hash;
}







