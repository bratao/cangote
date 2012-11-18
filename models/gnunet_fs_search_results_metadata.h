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

#ifndef GNUNETFSSEARCHRESULTSMETADATAMODEL_H
#define GNUNETFSSEARCHRESULTSMETADATAMODEL_H

#include <QAbstractTableModel>





struct Metadata
{
 QString name;
 QString value;


};




class GNUnetFsSearchResultsMetadataModel : public QAbstractTableModel
{
    Q_OBJECT


public:
    explicit GNUnetFsSearchResultsMetadataModel(QObject *parent = 0);

  bool SetMetadata(Metadata *result);
  bool addMetadata(Metadata *result);
signals:

public slots:

private:
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

   // void onDataChanged();


private:
        QList<Metadata*> m_data;

};

#endif // GNUNETFSSEARCHRESULTSMODEL_H
