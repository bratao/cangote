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

#include "sharedfiles.h"
#include "core/cangote.h"
#include "core/gnunet/gnunet_includes.h"
#include "models/sharedfilesmodel.h"

SharedFiles::SharedFiles(QObject *parent) :
    QObject(parent)
{
    m_fs = NULL;
    m_model = new SharedFilesModel(this);
}



/**
 * Print indexed filenames to stdout.
 *
 * @param cls closure
 * @param filename the name of the file
 * @param file_id hash of the contents of the indexed file
 * @return GNUNET_OK to continue iteration
 */
static int
print_indexed (void *cls, const char *filename, const struct GNUNET_HashCode * file_id)
{
    if(filename == NULL)
        return GNUNET_OK;
    gDebug(QString("Sharing: %1").arg(filename));
  return GNUNET_OK;
}



void SharedFiles::init(GNUNET_FS_Handle * fs)
{
    m_fs = fs;

    if (NULL == GNUNET_FS_get_indexed_files (m_fs, &print_indexed, NULL))
    {
      m_fs = NULL;
      return;
    }
}
