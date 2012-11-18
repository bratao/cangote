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

#ifndef SEARCH_H
#define SEARCH_H

#include <QObject>
#include <stdint.h>





struct GNUNET_FS_SearchContext;
class GNUnetFsSearchResultsModel;
struct SearchResult;
class Search : public QObject
{
  Q_OBJECT
public:
  explicit Search(GNUNET_FS_SearchContext *sc,QString query_txt, QObject *parent = 0);
  SearchResult* AddResult(SearchResult *parent, const struct GNUNET_FS_Uri *uri,
                         const struct GNUNET_CONTAINER_MetaData *meta,
                         struct GNUNET_FS_SearchResult *result,
                         uint32_t applicability_rank);
  GNUnetFsSearchResultsModel* getModel() { return model;}
  SearchResult *UpdateResult(SearchResult *sr, const GNUNET_CONTAINER_MetaData *meta, int applicability_rank, int availability_rank, int availability_certainty);
  void Stop();

  void Connect();
  void Close();
  QString getTerm();
signals:
  
  void DeadSignal();
public slots:
  void AskedToDieSlot();

private:



 GNUnetFsSearchResultsModel* model;


  /**
   * Set in case this is an inner search, otherwise NULL.
   */
  Search *parent;

  /**
   * Handle for this search with FS library.
   */
  struct GNUNET_FS_SearchContext *sc;

  /**
   * Text of the search query.
   */
  QString query_txt;


  /**
   * Number of results we got for this search.
   */
  unsigned int num_results;
  
};

#endif // SEARCH_H
