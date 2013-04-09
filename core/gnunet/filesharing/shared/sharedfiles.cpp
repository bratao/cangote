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
#include "models/sharedfilesmodel.h"

SharedFiles::SharedFiles(QObject *parent) :
    QObject(parent)
{
    m_fs = NULL;
    m_model = theApp->models()->sharedModel();
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
