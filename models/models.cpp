/**************************************************************************
** This file is part of Cangote
** (C)2/24/2013 2013 Bruno Cabral (and other contributing authors)
**
** Cangote is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published
** by the Free Software Foundation; either version 3, or (at your
** option) any later version.
**
** Cangote is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Cangote; see the file COPYING.  If not, write to the
** Free Software Foundation, Inc., 59 Temple Place - Suite 330,
** Boston, MA 02111-1307, USA.
**************************************************************************/

#include "models.h"
#include "models/SearchModel.h"
#include "models/NetworkPeersModel.h"
#include "models/DownloadsModel.h"
#include "models/SharedFilesModel.h"

Models::Models(QObject *parent) :
    QObject(parent)
{
    m_search = new SearchModel(this);
    m_network = new NetworkPeersModel(this);
    m_downloads = new DownloadsModel(this);
    m_shared = new SharedFilesModel(this);
}

Models::~Models()
{

    delete m_search;
    m_search = NULL;
    //emit searchModelChanged(m_search);


    delete m_network;
    m_network = NULL;
    //emit networkModelChanged(m_network);

    delete m_downloads;
    m_downloads = NULL;
   // emit downloadsModelChanged(m_downloads);

    delete m_shared;
    m_shared = NULL;
   // emit sharedModelChanged(m_shared);
}
