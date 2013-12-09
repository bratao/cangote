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
#include "searchresult.h"

#include "cangote.h"
#include "core/cangotecore.h"
#include "models/models.h"
#include "models/MetadataModel.h"
#include "models/DownloadsModel.h"
#include "utils/utils.h"


SearchResult::SearchResult(QObject *parent) :
    QObject(parent)
{
    m_index = NULL;
    m_availabilityCertainty = 0;
    m_availabilityRank = 0;
    m_fileSize = 0;
    m_meta = NULL;
    m_uri = NULL;
    m_thumbnail = NULL;

    m_metadataModel = new MetaModel(this);
    QQmlEngine::setObjectOwnership(m_metadataModel, QQmlEngine::CppOwnership);

}



static int
addMetadataCallBack (void *cls, const char *plugin_name,
                     enum EXTRACTOR_MetaType type,
                     enum EXTRACTOR_MetaFormat format,
                     const char *data_mime_type,
                     const char *data, size_t data_len)
{
    SearchResult* result = (SearchResult*)cls;

    result->addMetadata(plugin_name,type,format,data_mime_type,data,data_len);

    return 0; // Zero to continue
}

void SearchResult::modified()
{
    emit modifiedSignal(m_index->row());
    
}

int SearchResult::getPercentAvail()
{
    int percent_avail;
    
    if (m_availabilityCertainty > 0)
        percent_avail = 50 + (int)(m_availabilityRank * 50.0 / m_availabilityCertainty);
    // percent_avail = availability_rank;
    else
        percent_avail = 0;
    
    return percent_avail;
    
}



void SearchResult::setMetadata(GNUNET_CONTAINER_MetaData *meta, bool notifyModified)
{
    this->m_meta = meta;

    /* import meta data */
    if (NULL != meta)
    {
        m_thumbnail = theUtils->getThumbnailFromMetaData( meta);
        GNUNET_CONTAINER_meta_data_iterate (meta,
                                            &addMetadataCallBack,
                                            this);
    }
    
    if(notifyModified)
        modified();
}

int
SearchResult::addMetadata (const char *plugin_name,
                          EXTRACTOR_MetaType type,
                          EXTRACTOR_MetaFormat format,
                          const char *data_mime_type,
                          const char *data, size_t data_len)
{

    QString name = QString(EXTRACTOR_metatype_to_string (type));
    QString value = QString(data);
    m_metadataModel->add(name,value);
}



GNUNET_CONTAINER_MetaData* SearchResult::getMeta()
{
    return m_meta;
}


void SearchResult::setAvailabilityRank(int availability_rank, bool notifyModified)
{
    this->m_availabilityRank = availability_rank;
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
    this->m_availabilityCertainty = availability_certainty;
    if(notifyModified)
        modified();
}



void SearchResult::setUri(GNUNET_FS_Uri * uri, bool notifyModified)
{
    this->m_uri = uri;

    //Convert uri to Key
    GNUNET_HashCode hashcode;
    GNUNET_FS_uri_to_key(uri,&hashcode);

    //Get as QString
    const char * hash = GNUNET_h2s_full(&hashcode);
    m_hash = QString(hash);

    checkDownloaded();

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

/**
 * @brief Check if this file was already downloaded or is downloading.
 */
void SearchResult::checkDownloaded(){
    //TODO:: Implement me
    if(theApp->models()->downloadsModel()->get(m_hash) != -1)
        m_name = "DOWNLOADED";
}


void SearchResult::download()
{
    emit requestDownload(this);
}
