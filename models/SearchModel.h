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

#ifndef GNUNETFSSEARCHMODEL_H
#define GNUNETFSSEARCHMODEL_H

#include <QAbstractListModel>


class Search;
class SearchModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SearchModel(QObject *parent = 0);

    enum SearchRoles { TERM, NUM_RESULTS, SEARCH, NB_SEARCH_TABS };

    

    Q_INVOKABLE Search *getSearch(int index);
    Q_INVOKABLE void closeSearch(int index);
    int getCount();

    Search* addNewSearch(void *sc, QString term);



signals:
    Search* addNewSearchSignal(Search *search);
    void closeSearchSignal(int index);
public slots:

private slots:
    void addNewSearchSlot(Search *search);
    void closeSearchSlot(int index);
private:
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QList<Search*> m_data;
    
};

#endif // GNUNETFSSEARCHMODEL_H
