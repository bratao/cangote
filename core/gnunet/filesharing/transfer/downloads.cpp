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

#include "downloads.h"
//#include "core/cangote.h"
#include "downloaditem.h"
#include "core/gnunet/gnunet_includes.h"
#include "models/DownloadsModel.h"
#include "core/cangotecore.h"
#include "models/models.h"


Downloads::Downloads(QObject *parent) :
  QObject(parent)
{
  m_model = theApp->models()->downloadsModel();
}





void * Downloads::eventHandler (void *cls,
                                const struct GNUNET_FS_ProgressInfo *info)
{
  void *ret;

  //Disable -Wswitch error as we handle the other cases in filesharing class.
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wswitch"
  switch (info->status)
    {
    case GNUNET_FS_STATUS_DOWNLOAD_START:
      {
        return setup_download ((DownloadItem *)info->value.download.cctx,
                               (DownloadItem *)info->value.download.pctx, info->value.download.dc,
                               info->value.download.uri,
                               info->value.download.filename,
                               info->value.download.specifics.start.meta,
                               info->value.download.size,
                               info->value.download.completed);
      }
    case GNUNET_FS_STATUS_DOWNLOAD_RESUME:
      {
        ret = setup_download ((DownloadItem *)info->value.download.cctx, (DownloadItem *)info->value.download.pctx, info->value.download.dc,
                              info->value.download.uri, info->value.download.filename,
                              info->value.download.specifics.resume.meta,
                              info->value.download.size,
                              info->value.download.completed);

        if (NULL != info->value.download.specifics.resume.message)
          mark_download_error ((DownloadItem*)ret,
                               info->value.download.specifics.resume.message);

        return ret;
      }
      break;
    case GNUNET_FS_STATUS_DOWNLOAD_SUSPEND:
      {
        pause_download ((DownloadItem*)info->value.download.cctx);
        return NULL;
      }
    case GNUNET_FS_STATUS_DOWNLOAD_PROGRESS:
      {
        mark_download_progress ((DownloadItem*)info->value.download.cctx,
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
      }
    case GNUNET_FS_STATUS_DOWNLOAD_ERROR:
      {
        mark_download_error ((DownloadItem*)info->value.download.cctx,
                             info->value.download.specifics.error.message);
        return info->value.download.cctx;
      }
    case GNUNET_FS_STATUS_DOWNLOAD_COMPLETED:
      {
        mark_download_completed ((DownloadItem*)info->value.download.cctx,
                                 info->value.download.size);
        return info->value.download.cctx;
      }
    case GNUNET_FS_STATUS_DOWNLOAD_STOPPED:
      {
        stop_download ((DownloadItem*)info->value.download.cctx);
        return NULL;

      }

    case GNUNET_FS_STATUS_DOWNLOAD_ACTIVE:
      {
        setDownloadActive((DownloadItem*)info->value.download.cctx);
        return info->value.download.cctx;
      }
    case GNUNET_FS_STATUS_DOWNLOAD_INACTIVE:
      {
        setDownloadInactive((DownloadItem*)info->value.download.cctx);
        return info->value.download.cctx;
      }


    case GNUNET_FS_STATUS_DOWNLOAD_LOST_PARENT:
      {
        //TODO: Implement LOST PARENT (Directory/ recursive downloads)
        //  download_lost_parent (info->value.download.cctx);
        return info->value.download.cctx;
      }
    }
  //Enable -Wswitch again
  #pragma GCC diagnostic pop
}






  /**
 * Setup a new download entry.
 *
 * @param de existing download entry for the download, or NULL (in which case we create a fresh one)
 * @param pde parent download entry, or NULL
 * @param dc download context (for stopping)
 * @param uri the URI, must not be NULL
 * @param filename filename on disk
 * @param meta metadata
 * @param size total size
 * @param completed current progressc
 * @return download entry struct for the download (equal to 'de' if 'de' was not NULL)
 */
  DownloadItem *
      Downloads::setup_download (DownloadItem *de, DownloadItem *pde, struct GNUNET_FS_DownloadContext *dc,
                                 const struct GNUNET_FS_Uri *uri, const char *filename,
                                 const struct GNUNET_CONTAINER_MetaData *meta, qint64 size,
                                 qint64 completed)
  {

    qDebug("Setuping a download");

    GNUNET_assert (NULL != uri);
    if (NULL == de)
      {
        //No existing download entry to build on, create a fresh one
        QString qFilename;
        qFilename = qFilename.fromUtf8(filename);
        de = m_model->addDownload(pde,dc,uri,qFilename,meta,size,completed);
      }
    else
      {
        //Test if equal
        QString strUri;
        char* tempuri = GNUNET_FS_uri_to_string (uri);
        strUri = strUri.fromUtf8(tempuri);
        Q_ASSERT(de->getUri() ==strUri);

      }


    de->setContext(dc);
    de->setParent(pde);






    return de;
  }

  /**
 * A download operation was stopped.
 * @param de the download that was stopped
 */
  void
      Downloads::stop_download (DownloadItem *de)
  {
    de->setStopped();
  }


  /**
 * A download operation was paused.
 *
 * @param de the download that was paused
 */
  void
      Downloads::pause_download (DownloadItem *de)
  {
    de->setPaused();
  }


  /**
 * We got an event that some download is progressing.  Update the tree
 * model accordingly.  If the download is a directory, try to display
 * the contents.
 *
 * @param de download entry that is progressing
 * @param filename name of the downloaded file on disk (possibly a temporary file)
 * @param size overall size of the download
 * @param completed number of bytes we have completed
 * @param block_data current block we've downloaded
 * @param offset offset of block_data in the overall file
 * @param block_size number of bytes in block_data
 * @param depth depth of the block in the ECRS tree
 */
  void
      Downloads::mark_download_progress (DownloadItem *de,
                                         const char *filename,
                                         qint64 size,
                                         qint64 completed, const void *block_data,
                                         qint64 offset, qint64 block_size,
                                         unsigned int depth)
  {

    //gDebug(QString("Marking download progress for DE=%1, %2/%3, %4@%5 depth=%6\n").arg(de).arg(completed)
    //      .arg(size).arg(block_size).arg(offset).arg(depth));



    if(de == NULL)
      return;

    de->setCompleted(completed);
    de->setSize(size);

    if (completed < size)
      {
        ;
        //TODO: Implement directory support(mark_download_progress)
      }
    else
      {
        de->setCompleted();
        //TODO: Implement directory support

      }
  }


  /**
 * FS-API encountered an error downloading a file.  Update the
 * view accordingly.
 *
 * @param de download that had an error
 * @param emsg error message to display
 */
  void
      Downloads::mark_download_error (DownloadItem *de,
                                      const char *emsg)
  {
    Q_ASSERT(de);
    qWarning() << QString("Download Error : %1").arg(emsg);

    de->setError();
  }

  /**
 * FS-API notified us that we're done with a download.  Update the
 * view accordingly.
 *
 * @param de download that has finished
 * @param size overall size of the file
 */
  void
      Downloads::mark_download_completed (DownloadItem *de, qint64 size)
  {
    Q_ASSERT(de);
    //gInfo("Download completed !");

    de->setComplete();
  }

  void
      Downloads::setDownloadActive(DownloadItem *de)
  {
    Q_ASSERT(de);
    //gInfo("Setting a download as active !");

    de->setDownloading();
  }

  void
      Downloads::setDownloadInactive(DownloadItem *de)
  {

    Q_ASSERT(de);

    //gInfo("Setting a download as Inactive !");

    de->setPaused();

  }




