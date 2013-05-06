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

//#include "core/cangote.h"
#include "searchresult.h"


SearchResult::SearchResult(QObject *parent) :
    QObject(parent)
{
    m_index = NULL;
    availability_certainty = 0;
    availability_rank = 0;
    m_fileSize = 0;
    m_meta = NULL;
    m_uri = NULL;
}


void SearchResult::modified()
{
    emit modifiedSignal(m_index->row());
    
}

int SearchResult::getPercentAvail()
{
    int percent_avail;
    
    if (availability_certainty > 0)
        percent_avail = 50 + (int)(availability_rank * 50.0 / availability_certainty);
    // percent_avail = availability_rank;
    else
        percent_avail = 0;
    
    return percent_avail;
    
}



void SearchResult::setMetadata(GNUNET_CONTAINER_MetaData *meta, bool notifyModified)
{
    this->m_meta = meta;
    
    if(notifyModified)
        modified();
}

GNUNET_CONTAINER_MetaData* SearchResult::getMeta()
{
    return m_meta;
}


void SearchResult::setAvailabilityRank(int availability_rank, bool notifyModified)
{
    this->availability_rank = availability_rank;
    if(notifyModified)
        modified();
    
}

void SearchResult::setApplicabilityRank(int applicability_rank, bool notifyModified)
{
    this->m_applicabilityRank = applicability_rank;
    if(notifyModified)
        modified();
    
}

int SearchResult::getApplicabilityRank()
{
    return m_applicabilityRank;
}


void SearchResult::setFilesize(unsigned int fileSize, bool notifyModified)
{
    m_fileSize = fileSize;
    if(notifyModified)
        modified();
}



void SearchResult::setFilename(QString filename, bool notifyModified)
{
    m_filename = filename;
    if(notifyModified)
        modified();
}

QString SearchResult::getFilename()
{
    return m_filename;
}


unsigned int SearchResult::getFilesize()
{
    return m_fileSize;
}

void SearchResult::setOwner(Search* owner, bool notifyModified)
{
    this->m_owner = owner;
    if(notifyModified)
        modified();
}

Search* SearchResult::getOwner()
{
    return m_owner;
}



void SearchResult::setParent(SearchResult* parent, bool notifyModified)
{
    this->m_parent = parent;
    if(notifyModified)
        modified();
}


void SearchResult::setAvailabilityCertainty(int availability_certainty, bool notifyModified)
{
    this->availability_certainty = availability_certainty;
    if(notifyModified)
        modified();
}

void SearchResult::setPreview(void* preview, bool notifyModified)
{
    this->m_preview = preview;
    if(notifyModified)
        modified();
}


void SearchResult::setUri(GNUNET_FS_Uri * uri, bool notifyModified)
{
    this->m_uri = uri;
    if(notifyModified)
        modified();
}

const GNUNET_FS_Uri * SearchResult::getUri()
{
    return this->m_uri;
}


void SearchResult::setResult(GNUNET_FS_SearchResult *result, bool notifyModified)
{
    this->m_result = result;
    if(notifyModified)
        modified();
}


void SearchResult::setIndex(QPersistentModelIndex *index, bool notifyModified)
{
    this->m_index = index;
    
    if(notifyModified)
        modified();
}


QPersistentModelIndex* SearchResult::getIndex()
{
    Q_ASSERT(m_index);
    return m_index;
}



void SearchResult::download()
{
    //GNUNET_FS_download_start (fs,
    //                       de->uri,
    //                       NULL /* meta data */,
    //                                           de->filename, NULL /* tempname */ ,
    //                                           0 /* offset */ ,
    //                                           len,
    //                       de->anonymity, opt,
    //                       de,
    //                                           (NULL != de->pde) ? de->pde->dc : NULL));
    
    //gWarn("Download not implemented");
    emit requestDownload(this);
}
