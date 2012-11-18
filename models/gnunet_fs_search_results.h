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

#ifndef GNUNETFSSEARCHRESULTSMODEL_H
#define GNUNETFSSEARCHRESULTSMODEL_H

#include <QAbstractTableModel>





class SearchResult;
struct GNUNET_CONTAINER_MetaData;
class GNUnetFsSearchResultsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum SearchColumn { FILENAME, FILESIZE ,AVAILIABILITY, APPLICABILITYTRANK, NB_SEARCH_COLUMNS };


public:
    explicit GNUnetFsSearchResultsModel(QObject *parent = 0);
  void RequestToDie();

  void Die();
  int getSize();
  SearchResult* createResult();

  SearchResult *getResult(int index);
signals:

  void AskedToDieSignal();
  void DeadSignal();

public slots:
  void resultModifiedSlot(int indexRow);
  void removeResultSlot(QObject *result);
private:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

   // void onDataChanged();


private:
        QList<SearchResult*> m_data;
    
};

#endif // GNUNETFSSEARCHRESULTSMODEL_H
