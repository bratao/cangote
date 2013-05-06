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

#include <QObject>
#include <QDebug>

#include "core/cangotecore.h"
#include "core/gnunet/gnunet.h"
#include "filesharing.h"
#include "search/search.h"


#include "models/SearchResultModel.h"
#include "models/SearchModel.h"
#include "search/searchresult.h"
//#include "core/servicestatus.h"

#include "transfer/downloaditem.h"
#include "transfer/downloads.h"
#include "models/DownloadsModel.h"

#include "shared/sharedfiles.h"
#include "models/models.h"


//Initialize statics
GNUNET_FS_Handle * FileSharing::fs;


FileSharing::FileSharing(QObject *parent) :
    ServiceObject(parent)
{
    m_search= theApp->models()->searchModel();
    m_downloads = new Downloads(this);
    m_sharedFiles = new SharedFiles(this);

    // connect signal-slots for decoupling
    connect (this, SIGNAL(searchSignal(QString, int)), this,
        SLOT(searchSlot(QString, int)),Qt::QueuedConnection);

}



void FileSharing::start(struct GNUNET_CONFIGURATION_Handle *config)
{


    this->config = config;

    unsigned int dl_parallel = 128;
    unsigned int req_parallel = 100000;


    /* initialize file-sharing */

    fs = GNUNET_FS_start (config, "gnunet-qt",
                          GNUNET_fs_event_handler_callback, NULL,
                          (GNUNET_FS_Flags)(GNUNET_FS_FLAGS_PERSISTENCE | GNUNET_FS_FLAGS_DO_PROBES),
                          GNUNET_FS_OPTIONS_DOWNLOAD_PARALLELISM,
                          (unsigned int) dl_parallel,
                          GNUNET_FS_OPTIONS_REQUEST_PARALLELISM,
                          (unsigned int) req_parallel,
                          GNUNET_FS_OPTIONS_END);

    if (fs == NULL)
    {
        qWarning("Fs failed");
        //status->setErrorState("FS failed to start");
    }
    else
    {
        //status->setOkState();
        m_sharedFiles->init(fs);
    }
}

void *
FileSharing::GNUNET_fs_event_handler_callback (void *cls,
                                               const struct GNUNET_FS_ProgressInfo *info)
{
    return theApp->gnunet()->filesharing()->GNUNET_fs_event_handler(cls,info);
}



/**
 * Setup an "inner" search, that is a subtree representing namespace
 * 'update' results.  We use a 'struct SearchTab' to represent this
 * sub-search.  In the GUI, the presentation is similar to search
 * results in a directory, except that this is for a namespace search
 * result that gave pointers to an alternative keyword to use and this
 * is the set of the results found for this alternative keyword.
 *
 * All of the 'widget' elements of the returned 'search tab' reference
 * the parent search.  The whole construction is essentially a trick
 * to allow us to store the FS-API's 'SearchContext' somewhere and to
 * find it when we get this kind of 'inner' search results (so that we
 * can then place them in the tree view in the right spot).
 *
 * FIXME-BUG-MAYBE: don't we need a bit more information then? Like exactly where
 * this 'right spot' is?  Not sure how just having 'sc' helps there,
 * as it is not a search result (!) to hang this up on!  This might
 * essentially boil down to an issue with the FS API, not sure...
 *
 * @param sc context with FS for the search
 * @param parent parent search tab
 * @return struct representing the search result (also stored in the tree
 *                model at 'iter')
 */
struct SearchResult *
        FileSharing::setup_inner_search (struct GNUNET_FS_SearchContext *sc,
                                         struct SearchResult *parent)
{

    //gError("Setup inner seach not implemented !");
    return NULL;

}


/**
 * Setup a new search tab.
 *
 * @param sc context with FS for the search, NULL for none (open-URI/orphan tab)
 * @param query the query, NULL for none (open-URI/orphan tab)
 * @return search tab handle
 */
Search*
        FileSharing::setup_search_tab (struct GNUNET_FS_SearchContext *sc,
                                       const struct GNUNET_FS_Uri *query)
{


    char * querytmp;



    if (query == NULL)
    {
        //no real query, tab is for non-queries, use special label
        querytmp = GNUNET_strdup ("*");
    }
    else
    {
        //FS_uri functions should produce UTF-8, so let them be
        if (GNUNET_FS_uri_test_ksk (query))
            querytmp = GNUNET_FS_uri_ksk_to_string_fancy (query);
        else
            querytmp = GNUNET_FS_uri_to_string (query);
    }


    QString queryStr(querytmp);


    Search* search = m_search->addNewSearch(sc,queryStr );




    return search;

}

/**
 * We received a search error message from the FS library.
 * Present it to the user in an appropriate form.
 *
 * @param tab search tab affected by the error
 * @param emsg the error message
 */
void
FileSharing::handle_search_error (struct SearchTab *tab,
                                  const char *emsg)
{
    /*
  gtk_label_set_text (tab->label, _("Error!"));
  gtk_widget_set_tooltip_text (GTK_WIDGET (tab->label), emsg);
  */
}


/**
 * We have received a search result from the FS API.  Add it to the
 * respective search tab.  The search result can be an 'inner'
 * search result (updated result for a namespace search) or a
 * top-level search result.  Update the tree view and the label
 * of the search tab accordingly.
 *
 * @param tab the search tab where the new result should be added
 * @param parent parent search result (if this is a namespace update result), or NULL
 * @param uri URI of the search result
 * @param meta meta data for the result
 * @param result FS API handle to the result
 * @param applicability_rank how applicable is the result to the query
 * @return struct representing the search result (also stored in the tree
 *                model at 'iter')
 */
struct SearchResult *
        FileSharing::process_search_result (Search* search,
                                            struct SearchResult *parent,
                                            const struct GNUNET_FS_Uri *uri,
                                            const struct GNUNET_CONTAINER_MetaData *meta,
                                            struct GNUNET_FS_SearchResult *result,
                                            uint32_t applicability_rank)
{

    struct SearchResult *sr;

    if(search == NULL)
    {
        qWarning() << "Got a result to a file that don't exist !";
        return NULL;
    }

    sr = search->AddResult(parent, uri,meta, result, applicability_rank);
    connect(sr,SIGNAL(requestDownload(SearchResult*)),SLOT(downloadFromSearch(SearchResult*)));

    return sr;

}





/**
 * Some additional information about a search result has been
 * received.  Update the view accordingly.
 *
 * @param sr search result that is being updated
 * @param meta updated meta data
 * @param availability_rank updated availability information
 * @param availability_certainty updated availability certainty
 * @param applicability_rank updated applicability information
 */
void
FileSharing::update_search_result (SearchResult *sr,
                                   const struct GNUNET_CONTAINER_MetaData *meta,
                                   int applicability_rank,
                                   int availability_rank,
                                   int availability_certainty)
{

    if (sr == NULL)
    {
        //gWarn("Try to update a search result that don't exist");
        return;
    }




    sr->setMetadata((GNUNET_CONTAINER_MetaData *)meta,false);
    sr->setApplicabilityRank(applicability_rank,false);
    sr->setAvailabilityRank(availability_rank,false);
    sr->setAvailabilityCertainty(availability_certainty,false);
    sr->modified();


}



/**
 * Close a search tab and free associated state.  Assumes that the
 * respective tree model has already been cleaned up (this just
 * updates the notebook and frees the 'tab' itself).
 *
 * @param tab search tab to close
 */
void
FileSharing::close_search_tab (struct Search *tab)
{

    tab->close();

}


/**
 * Free a particular search result and remove the respective
 * entries from the respective tree store.  This function
 * is called when a search is stopped to clean up the state
 * of the tab.
 *
 * @param sr the search result to clean up
 */
void
FileSharing::free_search_result (struct SearchResult *sr)
{

    if (NULL == sr)
        return;


    delete sr;




}




//
// Download Functions
//
//





void *
FileSharing::GNUNET_fs_event_handler (void *cls,
                                      const struct GNUNET_FS_ProgressInfo *info)
{
    void *ret;

    switch (info->status)
    {
    /*
     case GNUNET_FS_STATUS_PUBLISH_START:
         return setup_publish (info->value.publish.pc, info->value.publish.filename,
                               info->value.publish.size, info->value.publish.pctx);
     case GNUNET_FS_STATUS_PUBLISH_RESUME:
         ret =
                 setup_publish (info->value.publish.pc, info->value.publish.filename,
                                info->value.publish.size, info->value.publish.pctx);
         if (NULL == ret)
             return ret;
         if (NULL != info->value.publish.specifics.resume.message)
         {
             handle_publish_error (ret,
                                   info->value.publish.specifics.resume.message);
         }
         else if (NULL != info->value.publish.specifics.resume.chk_uri)
         {
             handle_publish_completed (ret,
                                       info->value.publish.specifics.resume.chk_uri);
         }
         return ret;
     case GNUNET_FS_STATUS_PUBLISH_SUSPEND:
         handle_publish_stop (info->value.publish.cctx);
         return NULL;
     case GNUNET_FS_STATUS_PUBLISH_PROGRESS:
         mark_publish_progress (info->value.publish.cctx,
                                info->value.publish.size,
                                info->value.publish.completed);
         return info->value.publish.cctx;
     case GNUNET_FS_STATUS_PUBLISH_ERROR:
         handle_publish_error (info->value.publish.cctx,
                               info->value.publish.specifics.error.message);
         return info->value.publish.cctx;
     case GNUNET_FS_STATUS_PUBLISH_COMPLETED:
         handle_publish_completed (info->value.publish.cctx,
                                   info->value.publish.specifics.completed.chk_uri);
         return info->value.publish.cctx;
     case GNUNET_FS_STATUS_PUBLISH_STOPPED:
         handle_publish_stop (info->value.publish.cctx);
         return NULL;

*/

    case GNUNET_FS_STATUS_DOWNLOAD_START:
        return m_downloads->setup_download ((DownloadItem *)info->value.download.cctx,
                                            (DownloadItem *)info->value.download.pctx, info->value.download.dc,
                                            info->value.download.uri,
                                            info->value.download.filename,
                                            info->value.download.specifics.start.meta,
                                            info->value.download.size,
                                            info->value.download.completed);
    case GNUNET_FS_STATUS_DOWNLOAD_RESUME:
    {
        ret = m_downloads->setup_download ((DownloadItem *)info->value.download.cctx, (DownloadItem *)info->value.download.pctx, info->value.download.dc,
                                           info->value.download.uri, info->value.download.filename,
                                           info->value.download.specifics.resume.meta,
                                           info->value.download.size,
                                           info->value.download.completed);

        if (NULL != info->value.download.specifics.resume.message)
            m_downloads->mark_download_error ((DownloadItem*)ret,
                                              info->value.download.specifics.resume.message);

        return ret;
    }
        break;
    case GNUNET_FS_STATUS_DOWNLOAD_SUSPEND:
        m_downloads->pause_download ((DownloadItem*)info->value.download.cctx);
        return NULL;
    case GNUNET_FS_STATUS_DOWNLOAD_PROGRESS:
        m_downloads->mark_download_progress ((DownloadItem*)info->value.download.cctx,
                                             info->value.download.filename,
                                             info->value.download.size,
                                             info->value.download.completed,
                                             info->value.download.specifics.progress.data,
                                             info->value.download.specifics.progress.
                                             offset,
                                             info->value.download.specifics.progress.
                                             data_len,
                                             info->value.download.specifics.progress.
                                             depth);
        return info->value.download.cctx;
    case GNUNET_FS_STATUS_DOWNLOAD_ERROR:
        m_downloads->mark_download_error ((DownloadItem*)info->value.download.cctx,
                                          info->value.download.specifics.error.message);
        return info->value.download.cctx;
    case GNUNET_FS_STATUS_DOWNLOAD_COMPLETED:
        m_downloads->mark_download_completed ((DownloadItem*)info->value.download.cctx,
                                              info->value.download.size);
        return info->value.download.cctx;
    case GNUNET_FS_STATUS_DOWNLOAD_STOPPED:
        m_downloads->stop_download ((DownloadItem*)info->value.download.cctx);
        return NULL;


    case GNUNET_FS_STATUS_DOWNLOAD_ACTIVE:
        m_downloads->setDownloadActive((DownloadItem*)info->value.download.cctx);
        return info->value.download.cctx;
    case GNUNET_FS_STATUS_DOWNLOAD_INACTIVE:
        m_downloads->setDownloadInactive((DownloadItem*)info->value.download.cctx);
        return info->value.download.cctx;

    case GNUNET_FS_STATUS_DOWNLOAD_LOST_PARENT:
        //TODO: Implement LOST PARENT (Directory/ recursive downloads)
        //  download_lost_parent (info->value.download.cctx);
        return info->value.download.cctx;



        //
        //  Search
        //
    case GNUNET_FS_STATUS_SEARCH_START:
        if (NULL != info->value.search.pctx)
            return setup_inner_search (info->value.search.sc,
                                              (SearchResult*)info->value.search.pctx);
        return (void*)setup_search_tab (info->value.search.sc, info->value.search.query);
    case GNUNET_FS_STATUS_SEARCH_RESUME:
        ret = (void*)setup_search_tab (info->value.search.sc, info->value.search.query);
        if (info->value.search.specifics.resume.message)
            handle_search_error ((SearchTab*)ret,
                                 info->value.search.specifics.resume.message);
        return ret;
    case GNUNET_FS_STATUS_SEARCH_RESUME_RESULT:
        ret =
                process_search_result ((Search*)info->value.search.cctx, (SearchResult*)info->value.search.pctx,
                                       info->value.search.specifics.resume_result.uri,
                                       info->value.search.specifics.resume_result.meta,
                                       info->value.search.specifics.resume_result.
                                       result,
                                       info->value.search.specifics.resume_result.
                                       applicability_rank);
        update_search_result ((SearchResult*)ret,
                              info->value.search.specifics.resume_result.
                              meta,
                              info->value.search.specifics.resume_result.
                              applicability_rank,
                              info->value.search.specifics.resume_result.
                              availability_rank,
                              info->value.search.specifics.resume_result.
                              availability_certainty);
        return ret;
    case GNUNET_FS_STATUS_SEARCH_SUSPEND:
        close_search_tab ((Search*)info->value.search.cctx);
        return NULL;
    case GNUNET_FS_STATUS_SEARCH_RESULT:
        return process_search_result ((Search*)info->value.search.cctx,
                                      (SearchResult*)info->value.search.pctx,
                                      info->value.search.specifics.result.uri,
                                      info->value.search.specifics.result.meta,
                                      info->value.search.specifics.result.result,
                                      info->value.search.specifics.result.
                                      applicability_rank);
    case GNUNET_FS_STATUS_SEARCH_RESULT_NAMESPACE:
        GNUNET_break (0);
        break;
    case GNUNET_FS_STATUS_SEARCH_UPDATE:
        update_search_result ((SearchResult*)info->value.search.specifics.update.cctx,
                              info->value.search.specifics.update.meta,
                              info->value.search.specifics.update.
                              applicability_rank,
                              info->value.search.specifics.update.
                              availability_rank,
                              info->value.search.specifics.update.
                              availability_certainty);
        return info->value.search.specifics.update.cctx;
    case GNUNET_FS_STATUS_SEARCH_ERROR:
        handle_search_error ((SearchTab*)info->value.search.cctx,
                             info->value.search.specifics.error.message);
        return info->value.search.cctx;
    case GNUNET_FS_STATUS_SEARCH_PAUSED:
        return info->value.search.cctx;
    case GNUNET_FS_STATUS_SEARCH_CONTINUED:
        return info->value.search.cctx;
    case GNUNET_FS_STATUS_SEARCH_RESULT_STOPPED:
        free_search_result ((SearchResult*)info->value.search.specifics.result_stopped.cctx);
        return NULL;
    case GNUNET_FS_STATUS_SEARCH_RESULT_SUSPEND:
        free_search_result ((SearchResult*)info->value.search.specifics.result_suspend.cctx);
        return NULL;
    case GNUNET_FS_STATUS_SEARCH_STOPPED:
        close_search_tab ((Search*)info->value.search.cctx);
        return NULL;
        /*
case GNUNET_FS_STATUS_UNINDEX_START:
return info->value.unindex.cctx;
case GNUNET_FS_STATUS_UNINDEX_RESUME:
return GNUNET_FS_GTK_unindex_handle_resume_ (info->value.unindex.uc,
info->value.unindex.filename,
info->value.unindex.size,
info->value.unindex.completed,
info->value.unindex.specifics.resume.message);
case GNUNET_FS_STATUS_UNINDEX_SUSPEND:
GNUNET_FS_GTK_unindex_handle_stop_ (info->value.unindex.cctx);
return NULL;
case GNUNET_FS_STATUS_UNINDEX_PROGRESS:
GNUNET_FS_GTK_unindex_handle_progress_ (info->value.unindex.cctx,
info->value.unindex.completed);
return info->value.unindex.cctx;
case GNUNET_FS_STATUS_UNINDEX_ERROR:
GNUNET_FS_GTK_unindex_handle_error_ (info->value.unindex.cctx,
info->value.unindex.specifics.error.message);
return info->value.unindex.cctx;
case GNUNET_FS_STATUS_UNINDEX_COMPLETED:
GNUNET_FS_GTK_unindex_handle_completed_ (info->value.unindex.cctx);
return info->value.unindex.cctx;
case GNUNET_FS_STATUS_UNINDEX_STOPPED:
GNUNET_FS_GTK_unindex_handle_stop_ (info->value.unindex.cctx);
return NULL;
default:
GNUNET_break (0);
break;

*/
    }
    return NULL;

}

void FileSharing::search(QString term, int anonLevel)
{
    emit searchSignal(term, anonLevel);
}

void FileSharing::searchSlot(QString terms, int anonLevel)
{
    char *emsg = NULL;
    struct GNUNET_FS_Uri *uri;

    QByteArray byteArray = terms.toUtf8();
    const char* cString = byteArray.constData();



    uri = GNUNET_FS_uri_ksk_create (cString, &emsg);
    if (NULL == uri) {
        //GNUNET_log (GNUNET_ERROR_TYPE_ERROR, _("Invalid keyword string `%s': %s"),
        //           cString, emsg);
        GNUNET_free_non_null (emsg);
        return;
    }

    /* start search */
    //qWarning("FIX ME !! IMPLEMENT FS_SEARCH !");
    GNUNET_FS_search_start (fs,
                            uri, anonLevel,
                            GNUNET_FS_SEARCH_OPTION_NONE, NULL);
    GNUNET_FS_uri_destroy (uri);
}

void FileSharing::downloadFromSearch(SearchResult* searchResult)
{
    Q_ASSERT(searchResult);

    //TODO: Implement anonimity Level
    int anonLevel = 0;
    enum GNUNET_FS_DownloadOptions opt;
    GNUNET_FS_DownloadContext * dc;
    opt = GNUNET_FS_DOWNLOAD_OPTION_NONE;

    //TODO: Pass a download context


    dc= GNUNET_FS_download_start (fs,
                                  searchResult->getUri(),
                                  searchResult->getMeta() /* meta data */,
                                  searchResult->getFilename().toUtf8(), NULL /* tempname */ ,
                                  0 /* offset */ ,
                                  searchResult->getFilesize(),
                                  anonLevel, opt,
                                  NULL,
                                  NULL);

    //if(dc)
    //gWarn("DOWNLOAD Started !");
    //else
    //gWarn("error starting download");
}

//ServiceStatus* FileSharing::getStatus()
//{
//    return status;
//}

void FileSharing::ProcessEvents()
{
    QCoreApplication::processEvents();
}

