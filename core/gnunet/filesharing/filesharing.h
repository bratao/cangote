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

#ifndef FILESHARING_H
#define FILESHARING_H
#include <QObject>

#include "core/gnunet/gnunet_includes.h"
#include "service.h"

class Search;
class SearchResult;
class SearchModel;
class Downloads;
class Downloads;
class SharedFiles;
class SearchManager;
class FileSharing : public ServiceObject
{
    Q_OBJECT

    Q_PROPERTY(Downloads * downloads READ downloads CONSTANT)
    Q_PROPERTY(SharedFiles * sharedFiles READ sharedFiles CONSTANT)
    Q_PROPERTY(GNUNET_FS_Handle * fsHandle READ fsHandle CONSTANT)


public:
    explicit FileSharing( QObject *parent = 0);



    Downloads* downloads() const
    { return m_downloads; }

    SharedFiles* sharedFiles() const
    { return m_sharedFiles; }

    GNUNET_FS_Handle* fsHandle() const
    { return m_fs; }


    static void *
    GNUNET_fs_event_handler_callback (void *cls,
                                      const struct GNUNET_FS_ProgressInfo *info);


    void start(GNUNET_CONFIGURATION_Handle *config);
    Q_INVOKABLE void search(QString term, int searchType, int anonLevel);
    void ProcessEvents();
signals:
    void searchSignal(QString term,int searchType, int anonLevel);

private:







private:
    ////////////FILESHARING/////////////////////////
    void *
    eventHandler (void *cls,
                  const struct GNUNET_FS_ProgressInfo *info);


    /**
     * Handle for file-sharing operations.
     */
    struct GNUNET_FS_Handle *m_fs;

    struct GNUNET_CONFIGURATION_Handle *m_config;


    Downloads *m_downloads;
    SharedFiles *m_sharedFiles;
    SearchManager *m_search;


};

#endif // FILESHARING_H
