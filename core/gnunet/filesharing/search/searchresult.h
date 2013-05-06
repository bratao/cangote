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

#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QObject>
#include <QPersistentModelIndex>
#include "core/gnunet/gnunet_includes.h"

class Search;
class SearchResult : public QObject
{
    Q_OBJECT
public:
    explicit SearchResult(QObject *m_parent = 0);


    Search *getOwner();
    void setMetadata(GNUNET_CONTAINER_MetaData *m_meta, bool notifyModified =true);
    void setAvailabilityRank(int availability_rank, bool notifyModified =true);
    void setApplicabilityRank(int m_applicabilityRank, bool notifyModified =true);
    void setAvailabilityCertainty(int availability_certainty, bool notifyModified =true);
    void modified();
    int getPercentAvail();
    void setFilename(QString m_filename, bool notifyModified =true);
    void setFilesize(unsigned int m_fileSize, bool notifyModified =true);
    void setOwner(Search *m_owner, bool notifyModified =true);
    void setParent(SearchResult *m_parent, bool notifyModified =true);
    void setPreview(void *m_preview, bool notifyModified =true);
    void setUri(GNUNET_FS_Uri *m_uri, bool notifyModified =true);
    void setResult(GNUNET_FS_SearchResult *m_result, bool notifyModified =true);
    QPersistentModelIndex *getIndex();
    void setIndex(QPersistentModelIndex *m_index, bool notifyModified =true);
    QString getFilename();
    unsigned int getFilesize();
    int getApplicabilityRank();
    GNUNET_CONTAINER_MetaData *getMeta();
    Q_INVOKABLE void download();
    const GNUNET_FS_Uri *getUri();
private:

    QString m_filename;
    void* m_preview;
    unsigned int m_fileSize;
    QPersistentModelIndex* m_index;
    class Search* m_owner;
    struct GNUNET_FS_SearchResult *m_result;
    SearchResult *m_parent;
    const struct GNUNET_FS_Uri* m_uri;
    struct GNUNET_CONTAINER_MetaData *m_meta;
    unsigned int m_applicabilityRank;
    int availability_rank;
    int availability_certainty;

signals:
        void modifiedSignal(int m_index);
        void requestDownload(SearchResult* m_result);

public slots:

};

#endif // SEARCHRESULT_H
