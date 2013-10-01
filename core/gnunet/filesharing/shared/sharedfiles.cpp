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

#include <QDebug>
#include "sharedfiles.h"
#include "core/cangotecore.h"
#include "models/models.h"
#include "core/gnunet/gnunet_includes.h"
#include "models/SharedFilesModel.h"

SharedFiles::SharedFiles(QObject *parent) :
  QObject(parent)
{
  m_fs = NULL;
  m_model = theApp->models()->sharedModel();
}

void * SharedFiles::eventHandler (void *cls,
                                  const struct GNUNET_FS_ProgressInfo *info)
{

  void *ret;

  //Disable -Wswitch error as we handle the other cases in filesharing class.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch (info->status)
    {

    case GNUNET_FS_STATUS_PUBLISH_START:
      {

        return setup_publish (info->value.publish.pc, info->value.publish.filename,
                              info->value.publish.size, (SharedFile*)info->value.publish.pctx);
      }
    case GNUNET_FS_STATUS_PUBLISH_RESUME:
      {
        ret =
            setup_publish (info->value.publish.pc, info->value.publish.filename,
                           info->value.publish.size, (SharedFile*)info->value.publish.pctx);
        if (NULL == ret)
          return ret;
        if (NULL != info->value.publish.specifics.resume.message)
          {
            handle_publish_error ((SharedFile*)ret,
                                  info->value.publish.specifics.resume.message);
          }
        else if (NULL != info->value.publish.specifics.resume.chk_uri)
          {
            handle_publish_completed ((SharedFile*)ret,info->value.publish.pc,
                                      info->value.publish.specifics.resume.chk_uri);
          }
        return ret;
      }
    case GNUNET_FS_STATUS_PUBLISH_SUSPEND:
      {
        handle_publish_stop ((SharedFile*)info->value.publish.cctx);
        return NULL;
      }
    case GNUNET_FS_STATUS_PUBLISH_PROGRESS:
      {
        mark_publish_progress ((SharedFile*)info->value.publish.cctx,
                               info->value.publish.size,
                               info->value.publish.completed);
        return info->value.publish.cctx;
      }
    case GNUNET_FS_STATUS_PUBLISH_ERROR:
      {
        handle_publish_error ((SharedFile*)info->value.publish.cctx,
                              info->value.publish.specifics.error.message);
        return info->value.publish.cctx;
      }
    case GNUNET_FS_STATUS_PUBLISH_COMPLETED:
      {
        handle_publish_completed ((SharedFile*)info->value.publish.cctx, info->value.publish.pc,
                                  info->value.publish.specifics.completed.chk_uri);
        return info->value.publish.cctx;
      }
    case GNUNET_FS_STATUS_PUBLISH_STOPPED:
      {
        handle_publish_stop ((SharedFile*)info->value.publish.cctx);
        return NULL;
      }
    }
  //Enable -Wswitch again
#pragma GCC diagnostic pop
}


static int
indexedFilesCallback (void *cls, const char *filename, const struct GNUNET_HashCode * file_id)
{

  SharedFiles* sharedFiles = (SharedFiles*)cls;

  if(filename == NULL)
    return GNUNET_OK;


  sharedFiles->addIndexedFile(filename,file_id);

  return GNUNET_OK;
}

void SharedFiles::addIndexedFile(const char *filename, const struct GNUNET_HashCode * file_id)
{

  const char * hash = GNUNET_h2s_full(file_id);
  QString strHash(hash);
  SharedFile* file;

  qWarning() << (QString("Sharing: %1 with Hash: %2").arg(filename).arg(strHash));


  QString qFilename = QString(filename);

  file = m_model->addFile(qFilename,strHash);
  file->setStatus(SharedFile::Indexed);
}


/**
 * The user started a publishing operation.  Add it to the publishing
 * tab.  If needed, create the publishing tab.
 *
 * @param pc the FS-API's publishing context for the operation
 * @param fn the name of the file (or directory) that is being published
 * @param fsize size of the file
 * @param parent parent of this publishing operation (for recursive operations), NULL for top-level operations
 * @return the publishing entry that will represent this operation
 */
SharedFile *
SharedFiles::setup_publish (struct GNUNET_FS_PublishContext *pc, const char *filename,
                            uint64_t fsize, SharedFile *parent)
{

  qWarning() << (QString("Publishing: %1 with Hash: %2").arg(filename).arg(fsize));

  //TODO: Support recursive download ( #13)
  Q_UNUSED(parent);
  Q_UNUSED(pc);

  QString qFilename =  QString(filename);

  SharedFile* file = m_model->addFile(qFilename,fsize);

  file->setStatus(SharedFile::Publishing);
  return file;

}


/**
 * We received a publish error message from the FS library.
 * Present it to the user in an appropriate form.
 *
 * @param pe publishing operation affected by the error
 * @param emsg the error message
 */
void
SharedFiles::handle_publish_error (SharedFile *pe,
                                   const char *emsg)
{

  pe->setStatus(SharedFile::Error);
}

/**
 * FS-API notified us that we're done with some publish operation.
 * Update the view accordingly.
 *
 * @param pe publish operation that has finished
 * @param uri resulting URI
 */
void
SharedFiles::handle_publish_completed (SharedFile *pe,struct GNUNET_FS_PublishContext *pc,
                                       const struct GNUNET_FS_Uri *uri)
{
  pe->setStatus(SharedFile::Published);

  //TODO: Set URI
}

/**
 * A publishing operation was stopped (in FS API).  Free an entry in
 * the publish tab and its associated state.
 *
 * @param pe publishing operation that was stopped
 */
void
SharedFiles::handle_publish_stop (SharedFile *pe)
{
  pe->setStatus(SharedFile::Unknown);

  //TODO:: Implement STOP support
}

/**
 * We got an event that some publishing operation is progressing.
 * Update the tree model accordingly.
 *
 * @param pe publish entry that is progressing
 * @param size overall size of the file or directory
 * @param completed number of bytes we have completed
 */
void
SharedFiles::mark_publish_progress (SharedFile *pe, uint64_t size,
                                    uint64_t completed)
{
 pe->setProgress(((size > 0) ? (100 * completed / size) : 100));

}


void SharedFiles::init(GNUNET_FS_Handle * fs)
{
  m_fs = fs;

  if (NULL == GNUNET_FS_get_indexed_files (m_fs,
                                           &indexedFilesCallback, this))
    {
      m_fs = NULL;
      return;
    }
}
