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

#ifndef KEYWORDMODEL_H
#define KEYWORDMODEL_H

#include <QAbstractListModel>

class KeywordModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit KeywordModel(QObject *parent = 0);

    enum KeywordRoles { NAME };

    int getCount();
    void add(QString name);

signals:
    void addSignal(QString name);

private slots:
    void addSlot(QString name);
private:
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    QList<QString> m_data;
    
};

#endif // KEYWORDMODEL_H
