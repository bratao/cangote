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

#ifndef SEARCHWND_H
#define SEARCHWND_H

#include <QWidget>
 #include <QMap>


class QLineEdit;
class QPushButton;
class QTreeView;
class QTabWidget;
class GNUnetFsSearchResultsModel;
class QModelIndex;
class SearchResultTab;
class SearchDetailsPanel;
class GNUnetFsSearchModel;
class SearchWnd : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWnd(QWidget *parent = 0);
    void CreateNewSearchTab(QString name, GNUnetFsSearchResultsModel* model);


    int GetTabIndex(SearchResultTab *tab);

    void GNUNetConnected();

signals:
    
public slots:
    void OnSearch();

    void CloseTab(SearchResultTab *tab);
    void NewSearchSlot(QString term, GNUnetFsSearchResultsModel* model);
        void RequestedClose(int index);
        void SetTabName(SearchResultTab *tab, QString newname);

            void newSearchSlot(const QModelIndex &parent, int start, int end);
private:

    void Connect();

    QLineEdit *searchTermBox;
    QPushButton* searchBtn;
    QTreeView *searchResultList;
    QTabWidget *searchTab;
    SearchDetailsPanel* panel;

    GNUnetFsSearchModel* model;


};

#endif // SEARCHWND_H
