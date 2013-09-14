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
                              info->value.publish.size, (PublishEntry*)info->value.publish.pctx);
      }
    case GNUNET_FS_STATUS_PUBLISH_RESUME:
      {
        ret =
            setup_publish (info->value.publish.pc, info->value.publish.filename,
                           info->value.publish.size, (PublishEntry*)info->value.publish.pctx);
        if (NULL == ret)
          return ret;
        if (NULL != info->value.publish.specifics.resume.message)
          {
            handle_publish_error ((PublishEntry*)ret,
                                  info->value.publish.specifics.resume.message);
          }
        else if (NULL != info->value.publish.specifics.resume.chk_uri)
          {
            handle_publish_completed ((PublishEntry*)ret,
                                      info->value.publish.specifics.resume.chk_uri);
          }
        return ret;
      }
    case GNUNET_FS_STATUS_PUBLISH_SUSPEND:
      {
        handle_publish_stop ((PublishEntry*)info->value.publish.cctx);
        return NULL;
      }
    case GNUNET_FS_STATUS_PUBLISH_PROGRESS:
      {
        mark_publish_progress ((PublishEntry*)info->value.publish.cctx,
                               info->value.publish.size,
                               info->value.publish.completed);
        return info->value.publish.cctx;
      }
    case GNUNET_FS_STATUS_PUBLISH_ERROR:
      {
        handle_publish_error ((PublishEntry*)info->value.publish.cctx,
                              info->value.publish.specifics.error.message);
        return info->value.publish.cctx;
      }
    case GNUNET_FS_STATUS_PUBLISH_COMPLETED:
      {
        handle_publish_completed ((PublishEntry*)info->value.publish.cctx,
                                  info->value.publish.specifics.completed.chk_uri);
        return info->value.publish.cctx;
      }
    case GNUNET_FS_STATUS_PUBLISH_STOPPED:
      {
        handle_publish_stop ((PublishEntry*)info->value.publish.cctx);
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

  sharedFiles->addNewFiles(filename,file_id);

  return GNUNET_OK;
}

void SharedFiles::addNewFiles(const char *filename, const struct GNUNET_HashCode * file_id)
{

  const char * hash = GNUNET_h2s_full(file_id);
  QString strHash(hash);
  qWarning() << (QString("Sharing: %1 with Hash: %2").arg(filename).arg(strHash));

  m_model->addFile(QString(filename),strHash);
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
                            uint64_t fsize, struct PublishEntry *parent)
{

  qWarning() << (QString("Pulbishing: %1 with Hash: %2").arg(filename).arg(fsize));

  //TODO: Support recursive download ( #13)
  Q_UNUSED(parent);
  Q_UNUSED(pc);

  return m_model->addFile(QString(filename),fsize);

}


/**
 * We received a publish error message from the FS library.
 * Present it to the user in an appropriate form.
 *
 * @param pe publishing operation affected by the error
 * @param emsg the error message
 */
void
SharedFiles::handle_publish_error (struct PublishEntry *pe,
                                   const char *emsg)
{
  /*
  GtkTreeIter iter;
  GtkTreePath *path;

  path = gtk_tree_row_reference_get_path (pe->rr);
  if (! gtk_tree_model_get_iter (GTK_TREE_MODEL (pe->tab->ts), &iter, path))
  {
    GNUNET_break (0);
    gtk_tree_path_free (path);
    return;
  }
  gtk_tree_path_free (path);
  if (NULL == animation_error)
    animation_error = load_animation ("error");
  gtk_tree_store_set (pe->tab->ts, &iter,
                      PUBLISH_TAB_MC_RESULT_STRING, emsg,
                      PUBLISH_TAB_MC_PROGRESS, 100,
                      PUBLISH_TAB_MC_STATUS_ICON,
                      SEARCH_TAB_MC_STATUS_ICON,
                      GNUNET_GTK_animation_context_get_pixbuf (animation_error),
                      -1);
  change_publish_color (pe, "red");*/
}

/**
 * FS-API notified us that we're done with some publish operation.
 * Update the view accordingly.
 *
 * @param pe publish operation that has finished
 * @param uri resulting URI
 */
void
SharedFiles::handle_publish_completed (struct PublishEntry *pe,
                                       const struct GNUNET_FS_Uri *uri)
{
  /*
  GtkTreeIter iter;
  GtkTreePath *path;
  char *uris;

  path = gtk_tree_row_reference_get_path (pe->rr);
  if (! gtk_tree_model_get_iter (GTK_TREE_MODEL (pe->tab->ts), &iter, path))
  {
    GNUNET_break (0);
    gtk_tree_path_free (path);
    return;
  }
  gtk_tree_path_free (path);
  pe->uri = GNUNET_FS_uri_dup (uri);
  uris = GNUNET_FS_uri_to_string (uri);
  gtk_tree_store_set (pe->tab->ts, &iter,
                      PUBLISH_TAB_MC_RESULT_STRING, uris,
                      PUBLISH_TAB_MC_PROGRESS, 100,
                      PUBLISH_TAB_MC_STATUS_ICON,
                      GNUNET_GTK_animation_context_get_pixbuf (animation_published),
                      -1);
  GNUNET_free (uris);
  change_publish_color (pe, "green");
  */
}

/**
 * A publishing operation was stopped (in FS API).  Free an entry in
 * the publish tab and its associated state.
 *
 * @param pe publishing operation that was stopped
 */
void
SharedFiles::handle_publish_stop (struct PublishEntry *pe)
{
 /* GtkTreeIter iter;
  GtkTreePath *path;

  path = gtk_tree_row_reference_get_path (pe->rr);
  //This is a child of a directory, and we've had that directory
     free'd already
  if (! gtk_tree_model_get_iter (GTK_TREE_MODEL (pe->tab->ts), &iter, path))
    {
      GNUNET_break (0);
      return;
    }
  (void) gtk_tree_store_remove (pe->tab->ts, &iter);
  gtk_tree_path_free (path);
  gtk_tree_row_reference_free (pe->rr);
  if (pe->uri != NULL)
    {
      GNUNET_FS_uri_destroy (pe->uri);
      pe->uri = NULL;
    }
  if (! gtk_tree_model_iter_children (GTK_TREE_MODEL (pe->tab->ts), &iter, NULL))
    delete_publish_tab ();
  GNUNET_free (pe);*/
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
SharedFiles::mark_publish_progress (struct PublishEntry *pe, uint64_t size,
                                    uint64_t completed)
{
/*  GtkTreeIter iter;
  GtkTreePath *path;

  path = gtk_tree_row_reference_get_path (pe->rr);
  if (! gtk_tree_model_get_iter (GTK_TREE_MODEL (pe->tab->ts), &iter, path))
    {
      GNUNET_break (0);
      gtk_tree_path_free (path);
      return;
    }
  gtk_tree_path_free (path);
  gtk_tree_store_set (pe->tab->ts, &iter,
                      PUBLISH_TAB_MC_PROGRESS,
                      (guint) ((size > 0) ? (100 * completed / size) : 100),
                      -1);*/
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
