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


#include "cangote.h"
#include "filesharing.h"
#include "preferences/preferences.h"

#include "core/cangotecore.h"
#include "core/gnunet/gnunet.h"

#include "models/models.h"
#include "models/DownloadsModel.h"


#include "search/searchmanager.h"

#include "transfer/downloaditem.h"
#include "transfer/downloads.h"

#include "shared/sharedfiles.h"

/**
 * @brief This class will instantiate and handle File sharing messages
 *
 */



/**
 * @brief Our constructor
 */
FileSharing::FileSharing(QObject *parent) :
  ServiceObject(parent)
{
  m_downloads = new Downloads(this);
  m_sharedFiles = new SharedFiles(this);
  m_search = new SearchManager(this);

  // Cross thread signal
  connect (this, &FileSharing::searchSignal, m_search,
           &SearchManager::searchSlot,Qt::QueuedConnection);

}





/**********************************************
 ********** EVENT HANDLER
 **********************************************/
void * FileSharing::eventHandler (void *cls,
                                  const struct GNUNET_FS_ProgressInfo *info)
{
  void *ret;

  switch (info->status)
    {


    //Publish
    case GNUNET_FS_STATUS_PUBLISH_START:
    case GNUNET_FS_STATUS_PUBLISH_RESUME:
    case GNUNET_FS_STATUS_PUBLISH_SUSPEND:
    case GNUNET_FS_STATUS_PUBLISH_PROGRESS:
    case GNUNET_FS_STATUS_PUBLISH_ERROR:
    case GNUNET_FS_STATUS_PUBLISH_COMPLETED:
    case GNUNET_FS_STATUS_PUBLISH_STOPPED:
      return m_sharedFiles->eventHandler(cls,info);
      break;



      //Downloads
    case GNUNET_FS_STATUS_DOWNLOAD_START:
    case GNUNET_FS_STATUS_DOWNLOAD_RESUME:
    case GNUNET_FS_STATUS_DOWNLOAD_SUSPEND:
    case GNUNET_FS_STATUS_DOWNLOAD_PROGRESS:
    case GNUNET_FS_STATUS_DOWNLOAD_ERROR:
    case GNUNET_FS_STATUS_DOWNLOAD_COMPLETED:
    case GNUNET_FS_STATUS_DOWNLOAD_STOPPED:
    case GNUNET_FS_STATUS_DOWNLOAD_ACTIVE:
    case GNUNET_FS_STATUS_DOWNLOAD_INACTIVE:
    case GNUNET_FS_STATUS_DOWNLOAD_LOST_PARENT:
      return m_downloads->eventHandler(cls,info);
      break;



      //
      //  Search
      //
    case GNUNET_FS_STATUS_SEARCH_START:
    case GNUNET_FS_STATUS_SEARCH_RESUME:
    case GNUNET_FS_STATUS_SEARCH_RESUME_RESULT:
    case GNUNET_FS_STATUS_SEARCH_SUSPEND:
    case GNUNET_FS_STATUS_SEARCH_RESULT:
    case GNUNET_FS_STATUS_SEARCH_RESULT_NAMESPACE:
    case GNUNET_FS_STATUS_SEARCH_UPDATE:
    case GNUNET_FS_STATUS_SEARCH_ERROR:
    case GNUNET_FS_STATUS_SEARCH_PAUSED:
    case GNUNET_FS_STATUS_SEARCH_CONTINUED:
    case GNUNET_FS_STATUS_SEARCH_RESULT_STOPPED:
    case GNUNET_FS_STATUS_SEARCH_RESULT_SUSPEND:
    case GNUNET_FS_STATUS_SEARCH_STOPPED:
      return m_search->eventHandler(cls,info);
      break;


    case GNUNET_FS_STATUS_UNINDEX_START:
    case GNUNET_FS_STATUS_UNINDEX_RESUME:
    case GNUNET_FS_STATUS_UNINDEX_SUSPEND:
    case GNUNET_FS_STATUS_UNINDEX_PROGRESS:
    case GNUNET_FS_STATUS_UNINDEX_ERROR:
    case GNUNET_FS_STATUS_UNINDEX_COMPLETED:
    case GNUNET_FS_STATUS_UNINDEX_STOPPED:
      return m_sharedFiles->eventHandler(cls,info);
      break;




    default:
      qWarning() << "Unknown Message in GNUnet Loop";

    }
  return NULL;

}




/**
 * @brief FileSharing::start
 * @param config
 */
void FileSharing::start(struct GNUNET_CONFIGURATION_Handle *config)
{


  this->m_config = config;

  unsigned int dl_parallel = 128;
  unsigned int req_parallel = 100000;


  //initialize file-sharing

  m_fs = GNUNET_FS_start (config, "Cangote",
                          GNUNET_fs_event_handler_callback, NULL,
                          (GNUNET_FS_Flags)(GNUNET_FS_FLAGS_PERSISTENCE | GNUNET_FS_FLAGS_DO_PROBES),
                          GNUNET_FS_OPTIONS_DOWNLOAD_PARALLELISM,
                          (unsigned int) dl_parallel,
                          GNUNET_FS_OPTIONS_REQUEST_PARALLELISM,
                          (unsigned int) req_parallel,
                          GNUNET_FS_OPTIONS_END);

  if (m_fs == NULL)
    {
      qWarning("Fs failed");
    }
  else
    {
      m_sharedFiles->init(m_fs);
      m_search->setFs(m_fs);
    }
}

/**
 * @brief FileSharing::GNUNET_fs_event_handler_callback
 * @param cls
 * @param info
 * @return
 */
void *
FileSharing::GNUNET_fs_event_handler_callback (void *cls,
                                               const struct GNUNET_FS_ProgressInfo *info)
{
  return theApp->gnunet()->filesharing()->eventHandler(cls,info);
}





/**
 * @brief FileSharing::search
 * @param term
 * @param anonLevel
 */
void FileSharing::search(QString term, int anonLevel)
{
  emit searchSignal(term, anonLevel);
}



/**
 * @brief FileSharing::ProcessEvents
 */
void FileSharing::ProcessEvents()
{
  QCoreApplication::processEvents();
}

