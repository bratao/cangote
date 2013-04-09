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

#include "search.h"
//#include "core/cangote.h"
#include "core/gnunet/gnunet_includes.h"
#include <extractor.h>
#include "gnunet/gnunet_container_lib.h"

#include "models/SearchResultModel.h"
#include "searchresult.h"
#include "core/cangotecore.h"

Search::Search(GNUNET_FS_SearchContext *sc,QString query_txt, QObject *parent) :
  QObject(parent)
{
  m_model = NULL;
  this->sc = sc;
  this->query_txt = query_txt;


}




void Search::AskedToDieSlot()
{
  Stop();
  //gDebug("Search:"+query_txt + "asked to die" );
}

SearchResult* Search::UpdateResult(SearchResult *sr,
                                   const struct GNUNET_CONTAINER_MetaData *meta,
                                   int applicability_rank,
                           int availability_rank,
                                   int availability_certainty)
{

    if(m_model == NULL)
    {
        qWarning("Updating a result without a model !");
        return NULL;
    }


    sr->setMetadata((GNUNET_CONTAINER_MetaData *)meta,false);
    sr->setApplicabilityRank(applicability_rank,false);
    sr->setAvailabilityRank(availability_rank,false);
    sr->setAvailabilityCertainty(availability_certainty,false);
    sr->modified();


}


SearchResult* Search::AddResult(SearchResult *parent, const struct GNUNET_FS_Uri *uri,
                       const struct GNUNET_CONTAINER_MetaData *meta,
                       struct GNUNET_FS_SearchResult *result,
                       uint32_t applicability_rank)
{


  size_t ts;
  unsigned char *thumb;
  int fsize;
  QString mime;
  QString strUri;

  thumb = NULL;


  if(m_model == NULL)
  {
      qWarning("Adding a result without a model !");
      return NULL;
  }

  if (NULL == uri)
    {
      /* opened directory file */
      fsize = 0;
      strUri = "no URI";
    }
    else
    {
      if ( (GNUNET_FS_uri_test_loc (uri)) ||
           (GNUNET_FS_uri_test_chk (uri)) )
      {
        fsize = GNUNET_FS_uri_chk_get_file_size (uri);

        char* tmpMime = GNUNET_CONTAINER_meta_data_get_first_by_types (meta,
                                                                       EXTRACTOR_METATYPE_MIMETYPE,
                                                                       EXTRACTOR_METATYPE_FORMAT,
                                                                       -1);

        mime.fromLocal8Bit(tmpMime);
      }
      else
      {
        /* FIXME-FEATURE-MAYBE: create mime type for namespaces? */
        /* FIXME-BUG-MAYBE: can we encounter ksk URIs here too? */
        fsize = 0;
        mime = "GNUnet namespace";

      }
      char* tempuri = GNUNET_FS_uri_to_string (uri);
      strUri = strUri.fromLatin1(tempuri);
    }

    ts = GNUNET_CONTAINER_meta_data_get_thumbnail (meta, &thumb);




    char* desc =  GNUNET_CONTAINER_meta_data_get_first_by_types (meta,
                                                       EXTRACTOR_METATYPE_PACKAGE_NAME,
                                                       EXTRACTOR_METATYPE_TITLE,
                                                       EXTRACTOR_METATYPE_BOOK_TITLE,
                                                       EXTRACTOR_METATYPE_GNUNET_ORIGINAL_FILENAME,
                                                       EXTRACTOR_METATYPE_FILENAME,
                                                       EXTRACTOR_METATYPE_DESCRIPTION,
                                                       EXTRACTOR_METATYPE_SUMMARY,
                                                       EXTRACTOR_METATYPE_ALBUM,
                                                       EXTRACTOR_METATYPE_COMMENT,
                                                       EXTRACTOR_METATYPE_SUBJECT,
                                                       EXTRACTOR_METATYPE_KEYWORDS,
                                                       -1);



    QString filenameStr;


    filenameStr = filenameStr.fromUtf8 ( desc );


    SearchResult* newresult = m_model->addResult();



    newresult->setApplicabilityRank(applicability_rank,false);
    newresult->setFilename(filenameStr,false);
    newresult->setFilesize(fsize,false);
    //TODO:: We should respect const
    newresult->setMetadata((GNUNET_CONTAINER_MetaData *)meta, false);
    //newresult->setParent(NULL, false);



    newresult->setPreview(thumb,false);
    //TODO:: We should respect const
    newresult->setUri((GNUNET_FS_Uri *)uri,false);
    newresult->setResult(result,false);
    newresult->modified();


    return newresult;



}





void Search::Stop()
{

    GNUNET_FS_search_stop (sc);

}

void Search::Close()
{

  delete m_model;

}

QString Search::getTerm()
{
    return query_txt;
}
