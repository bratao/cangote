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
class SearchResultsModel;
struct SearchResult;
class Search : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SearchResultsModel * model READ model WRITE setModel NOTIFY modelChanged)
public:
    explicit Search(GNUNET_FS_SearchContext *m_sc,QString m_query, QObject *m_parent = 0);


    //Properties definition
    SearchResultsModel* model() const
    { return m_model; }

    void setModel(SearchResultsModel* model)
    {
        m_model = model;
        emit modelChanged(model);
    }


    SearchResult* AddResult(SearchResult *m_parent, const struct GNUNET_FS_Uri *uri,
                            const struct GNUNET_CONTAINER_MetaData *meta,
                            struct GNUNET_FS_SearchResult *result,uint32_t applicability_rank);

    SearchResult* UpdateResult(SearchResult *sr, const GNUNET_CONTAINER_MetaData *meta, int applicability_rank,
                               int availability_rank, int availability_certainty);

    //Stop the search
    void stop();

    //Ask the search to close
    void close();


    QString getTerm();
signals:
    void modelChanged(SearchResultsModel*);
    void stopped();
    void closed();
private slots:
    void stopSlot();
    void closeSlot();

private:

    //Our model
    SearchResultsModel* m_model;

    //Parent search
    //Set in case this is an inner search, otherwise NULL.
    Search *m_parent;

    //Handle for this search with FS library.
    struct GNUNET_FS_SearchContext *m_sc;

    //Search query.
    QString m_query;


    //Number of results we got for this search.
    unsigned int m_numResults;

};

#endif // SEARCH_H
