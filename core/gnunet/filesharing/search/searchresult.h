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

  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QString fileName READ getFileName WRITE setFileName NOTIFY fileNameChanged)
  Q_PROPERTY(QImage* thumbnail READ thumbnail CONSTANT)


public:


  /**
     * @brief name , Fancy name to present
     * @return
     */
  QString name() const
  { return m_name; }
  void setName(QString name)
  {
    m_name = name;
    emit nameChanged(name);
  }

  /**
     * @brief fileName , the filename as it should be downloaded on disk
     * @return
     */
  Q_INVOKABLE QString getFileName() const
  { return m_filename; }
  void setFileName(QString filename)
  {
    m_filename = filename;
    emit fileNameChanged(filename);
  }

  QImage* thumbnail() const
  { return m_thumbnail; }



signals:
  void nameChanged(QString);
  void fileNameChanged(QString);


public:
  explicit SearchResult(QObject *m_parent = 0);


  Search *getOwner();
  void setMetadata(GNUNET_CONTAINER_MetaData *m_meta, bool notifyModified =true);
  void setAvailabilityRank(int m_availabilityRank, bool notifyModified =true);
  void setApplicabilityRank(int m_applicabilityRank, bool notifyModified =true);
  void setAvailabilityCertainty(int m_availabilityCertainty, bool notifyModified =true);
  void modified();
  int getPercentAvail();
  void setFilesize(unsigned int m_fileSize, bool notifyModified =true);
  void setOwner(Search *m_owner, bool notifyModified =true);
  void setParent(SearchResult *m_parent, bool notifyModified =true);

  void setUri(GNUNET_FS_Uri *m_uri, bool notifyModified =true);
  void setResult(GNUNET_FS_SearchResult *m_result, bool notifyModified =true);
  QPersistentModelIndex *getIndex();
  void setIndex(QPersistentModelIndex *m_index, bool notifyModified =true);
  unsigned int getFilesize();
  int getApplicabilityRank();
  GNUNET_CONTAINER_MetaData *getMeta();
  Q_INVOKABLE void download();
  const GNUNET_FS_Uri *getUri();
private:

  QString m_filename;
  QString m_name;
  QString m_hash;

  struct GNUNET_FS_SearchResult *m_result;
  const struct GNUNET_FS_Uri* m_uri;
  struct GNUNET_CONTAINER_MetaData *m_meta;

  QPersistentModelIndex* m_index;
  QImage * m_thumbnail;
  Search* m_owner;
  SearchResult *m_parent;

  unsigned int m_applicabilityRank;
  int m_availabilityRank;
  int m_availabilityCertainty;
  unsigned int m_fileSize;


  void checkDownloaded();
signals:
  void modifiedSignal(int m_index);
  void requestDownload(SearchResult* m_result);

public slots:

};

#endif // SEARCHRESULT_H
