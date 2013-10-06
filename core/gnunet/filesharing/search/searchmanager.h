#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>

class SearchResult;
class Search;
class SearchModel;
class SearchManager : public QObject
{
  Q_OBJECT
public:
  explicit SearchManager(QObject *parent = 0);

  void *eventHandler(void *cls, const struct GNUNET_FS_ProgressInfo *info);
  void setFs(struct GNUNET_FS_Handle *fs);
signals:

public slots:

  void downloadFromSearch(SearchResult *searchResult);
  void searchSlot(QString terms, int anonLevel);


private:
  ////////SEARCH//////////
  SearchResult *setupInnerSearch(struct GNUNET_FS_SearchContext *sc,
                                 SearchResult *parent);

  Search*
  setupSearch (struct GNUNET_FS_SearchContext *sc,
               const struct GNUNET_FS_Uri *query);

  SearchResult *
  processSearch (Search *search,
                 SearchResult *parent,
                 const struct GNUNET_FS_Uri *uri,
                 const struct GNUNET_CONTAINER_MetaData *meta,
                 struct GNUNET_FS_SearchResult *result,
                 uint32_t applicability_rank);
  void
  updateSearch (SearchResult *sr,
                const struct GNUNET_CONTAINER_MetaData *meta,
                int applicability_rank,
                int availability_rank,
                int availability_certainty);
  void
  closeSearch (Search *tab);

  void
  freeSearch (SearchResult *sr);

  void
  searchError (struct SearchTab *tab,
               const char *emsg);



private:



  struct GNUNET_FS_Handle *m_fs;
      SearchModel *m_searchModel;

};

#endif // SEARCHMANAGER_H
