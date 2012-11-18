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

#ifndef FILESHARING_H
#define FILESHARING_H
#include <QObject>

#include "core/gnunet/gnunet_includes.h"


class Search;




class GNUnetFsSearchResultsModel;
class SearchResult;
class ServiceStatus;
class GNUnetFsSearchModel;
class DownloadModel;
class Downloads;
class SharedFiles;
class FileSharing : public QObject
{
  Q_OBJECT
public:
    explicit FileSharing( QObject *parent = 0);


    ////////////FILESHARING/////////////////////////
    void *
    GNUNET_fs_event_handler (void *cls,
                                 const struct GNUNET_FS_ProgressInfo *info);

        ////////SEARCH//////////
    SearchResult *setup_inner_search(struct GNUNET_FS_SearchContext *sc,
                        SearchResult *parent);
    Search *
    setup_search_tab (struct GNUNET_FS_SearchContext *sc,
              const struct GNUNET_FS_Uri *query);
    SearchResult *
    process_search_result (Search *search,
                   SearchResult *parent,
                           const struct GNUNET_FS_Uri *uri,
                           const struct GNUNET_CONTAINER_MetaData *meta,
                           struct GNUNET_FS_SearchResult *result,
                           uint32_t applicability_rank);
    void
    update_search_result (SearchResult *sr,
                          const struct GNUNET_CONTAINER_MetaData *meta,
                          int applicability_rank,
                  int availability_rank,
                          int availability_certainty);
    void
    close_search_tab (Search *tab);
    void
    free_search_result (SearchResult *sr);

    void
    handle_search_error (struct SearchTab *tab,
                 const char *emsg);
    static void *
    GNUNET_fs_event_handler_callback (void *cls,
                                 const struct GNUNET_FS_ProgressInfo *info);


    void start(GNUNET_CONFIGURATION_Handle *config);
    void downloadFromSearch(Search *search);
    ServiceStatus *getStatus();

    GNUnetFsSearchModel* searchModel;
    Downloads* downloads;

    SharedFiles* m_sharedFiles;

public slots:
    void downloadFromSearch(SearchResult *searchResult);
        void DoSearch(QString terms, int anonLevel);
private:
    /**
     * Handle for file-sharing operations.
     */
        static struct GNUNET_FS_Handle *fs;

        struct GNUNET_CONFIGURATION_Handle *config;

        ServiceStatus* status;


};

#endif // FILESHARING_H
