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
#include "core/cangote.h"
#include "downloaditem.h"
#include "core/gnunet/gnunet_includes.h"
#include "models/downloadmodel.h"


Downloads::Downloads(QObject *parent) :
    QObject(parent)
{
    model = new DownloadModel(this);
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
                const struct GNUNET_CONTAINER_MetaData *meta, uint64_t size,
                uint64_t completed)
{

  gWarn("Setuping a download");

  GNUNET_assert (NULL != uri);
  if (NULL == de)
  {
    //No existing download entry to build on, create a fresh one
      QString qFilename;
      qFilename = qFilename.fromUtf8(filename);
      de = model->addDownload(pde,dc,uri,qFilename,meta,size,completed);
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
            uint64_t size,
                        uint64_t completed, const void *block_data,
                        uint64_t offset, uint64_t block_size,
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
    gWarn(QString(emsg));

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
Downloads::mark_download_completed (DownloadItem *de, uint64_t size)
{
    Q_ASSERT(de);
    gInfo("Download completed !");

    de->setComplete();
}

void
Downloads::setDownloadActive(DownloadItem *de)
{
    Q_ASSERT(de);
    gInfo("Setting a download as active !");

    de->setDownloading();
}

void
Downloads::setDownloadInactive(DownloadItem *de)
{

    Q_ASSERT(de);

    gInfo("Setting a download as Inactive !");

    de->setPaused();

}




