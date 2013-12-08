#include "searchmanager.h"
#include "cangote.h"


#include "core/cangotecore.h"
#include "core/gnunet/gnunet.h"
#include "preferences/preferences.h"
#include "models/models.h"
#include "models/SearchModel.h"
#include "searchresult.h"
#include "search.h"


SearchManager::SearchManager(QObject *parent) :
    QObject(parent)
{
    m_fs = NULL;
    m_searchModel= theApp->models()->searchModel();

}
void * SearchManager::eventHandler (void *cls,
                                    const struct GNUNET_FS_ProgressInfo *info)
{

    void *ret;

    //Disable -Wswitch error as we handle the other cases in filesharing class.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
    switch (info->status)
    {



    case GNUNET_FS_STATUS_SEARCH_START:
    {
        if (NULL != info->value.search.pctx)
            return setupInnerSearch (info->value.search.sc,
                                     (SearchResult*)info->value.search.pctx);
        return (void*)setupSearch (info->value.search.sc, info->value.search.query);
    }
    case GNUNET_FS_STATUS_SEARCH_RESUME:
    {
        ret = (void*)setupSearch (info->value.search.sc, info->value.search.query);
        if (info->value.search.specifics.resume.message)
            searchError ((SearchTab*)ret,
                         info->value.search.specifics.resume.message);
        return ret;
    }
    case GNUNET_FS_STATUS_SEARCH_RESUME_RESULT:
    {
        ret =
                processSearch ((Search*)info->value.search.cctx, (SearchResult*)info->value.search.pctx,
                               info->value.search.specifics.resume_result.uri,
                               info->value.search.specifics.resume_result.meta,
                               info->value.search.specifics.resume_result.
                               result,
                               info->value.search.specifics.resume_result.
                               applicability_rank);
        updateSearch ((SearchResult*)ret,
                      info->value.search.specifics.resume_result.
                      meta,
                      info->value.search.specifics.resume_result.
                      applicability_rank,
                      info->value.search.specifics.resume_result.
                      availability_rank,
                      info->value.search.specifics.resume_result.
                      availability_certainty);
        return ret;
    }
    case GNUNET_FS_STATUS_SEARCH_SUSPEND:
    {
        closeSearch ((Search*)info->value.search.cctx);
        return NULL;
    }
    case GNUNET_FS_STATUS_SEARCH_RESULT:
    {
        return processSearch ((Search*)info->value.search.cctx,
                              (SearchResult*)info->value.search.pctx,
                              info->value.search.specifics.result.uri,
                              info->value.search.specifics.result.meta,
                              info->value.search.specifics.result.result,
                              info->value.search.specifics.result.
                              applicability_rank);
    }
    case GNUNET_FS_STATUS_SEARCH_RESULT_NAMESPACE:
    {
        GNUNET_break (0);
        break;
    }
    case GNUNET_FS_STATUS_SEARCH_UPDATE:
    {
        updateSearch ((SearchResult*)info->value.search.specifics.update.cctx,
                      info->value.search.specifics.update.meta,
                      info->value.search.specifics.update.
                      applicability_rank,
                      info->value.search.specifics.update.
                      availability_rank,
                      info->value.search.specifics.update.
                      availability_certainty);
        return info->value.search.specifics.update.cctx;
    }
    case GNUNET_FS_STATUS_SEARCH_ERROR:
    {
        searchError ((SearchTab*)info->value.search.cctx,
                     info->value.search.specifics.error.message);
        return info->value.search.cctx;
    }
    case GNUNET_FS_STATUS_SEARCH_PAUSED:
        return info->value.search.cctx;
    case GNUNET_FS_STATUS_SEARCH_CONTINUED:
        return info->value.search.cctx;
    case GNUNET_FS_STATUS_SEARCH_RESULT_STOPPED:
        freeSearch ((SearchResult*)info->value.search.specifics.result_stopped.cctx);
        return NULL;
    case GNUNET_FS_STATUS_SEARCH_RESULT_SUSPEND:
        freeSearch ((SearchResult*)info->value.search.specifics.result_suspend.cctx);
        return NULL;
    case GNUNET_FS_STATUS_SEARCH_STOPPED:
        closeSearch ((Search*)info->value.search.cctx);
        return NULL;

    }
    //Enable -Wswitch again
#pragma GCC diagnostic pop
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
SearchResult *
SearchManager::setupInnerSearch (struct GNUNET_FS_SearchContext *sc,
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
SearchManager::setupSearch (struct GNUNET_FS_SearchContext *sc,
                            const struct GNUNET_FS_Uri *query)
{


    char * querytmp;


    //TODO: Handle this case. What query == NULL means ?
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


    Search* search = m_searchModel->addNewSearch(sc,queryStr);




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
SearchManager::searchError (struct SearchTab *tab,
                            const char *emsg)
{
    //TODO:: Implement search error handling.
    qWarning() << "Search Failed !!";
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
SearchResult *
SearchManager::processSearch (Search* search,
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

    connect(sr, &SearchResult::requestDownload, this, &SearchManager::downloadFromSearch);

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
SearchManager::updateSearch (SearchResult *sr,
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
SearchManager::closeSearch (struct Search *tab)
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
SearchManager::freeSearch (struct SearchResult *sr)
{

    if (NULL == sr)
        return;

    delete sr;

}


/**
 * @brief FileSharing::download
 * @param searchResult
 */
void SearchManager::downloadFromSearch(SearchResult* searchResult)
{
    Q_ASSERT(searchResult);
    Q_ASSERT(m_fs);

    //TODO: Implement anonimity Level
    int anonLevel = 0;
    enum GNUNET_FS_DownloadOptions opt;
    GNUNET_FS_DownloadContext * dc;
    opt = GNUNET_FS_DOWNLOAD_OPTION_NONE;

    //TODO: Store this download context
    dc = GNUNET_FS_download_start (m_fs,
                                   searchResult->getUri(),
                                   searchResult->getMeta() /* meta data */,
                                   (thePrefs->getDownloadDirectory() +"/" + QString(searchResult->getFileName())).toUtf8(), NULL /* tempname */ ,
                                   0 /* offset */ ,
                                   searchResult->getFilesize(),
                                   anonLevel, opt,
                                   NULL,
                                   NULL);

}

void SearchManager::setFs(GNUNET_FS_Handle * fs)
{
    m_fs = fs;
}


/**
 * @brief FileSharing::searchSlot
 * @param terms
 * @param anonLevel
 */
void SearchManager::searchSlot(QString terms,int searchType, int anonLevel)
{
    char *emsg = NULL;
    struct GNUNET_FS_Uri *uri;


    //Use AND if we specify search type
    if((searchType!=0)&& (terms.size() > 0) && (terms.at(0)!='+'))
    {
        terms.insert(0,"+");
    }
    terms+= getStringFromSearchType(searchType);

    //Convert string to C-String
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
    GNUNET_FS_search_start(m_fs,
                           uri, anonLevel,
                           GNUNET_FS_SEARCH_OPTION_NONE, NULL);
    GNUNET_FS_uri_destroy (uri);
}


QString SearchManager::getStringFromSearchType(int searchType)
{
    QString searchTypeStr;
    searchTypeStr = " +mimetype:";
    switch (searchType) {
    case 0:
        return"";
        break;
    case 1:
        return searchTypeStr + "audio";
        break;
    case 2:
        return searchTypeStr + "video";
        break;
    case 3:
        return searchTypeStr + "image";
        break;
    case 4:
        return searchTypeStr + "application";
        break;
    case 5:
        return searchTypeStr + "text";
        break;
    case 6:
        return searchTypeStr + "application";
        break;
    default:
        break;
    }

}

