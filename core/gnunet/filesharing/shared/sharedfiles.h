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

#ifndef SHAREDFILES_H
#define SHAREDFILES_H

#include <QObject>

class SharedFilesModel;
class SharedFiles : public QObject
{
    Q_OBJECT
public:
    explicit SharedFiles(QObject *parent = 0);
    
    void init();
    void init(struct GNUNET_FS_Handle *fs);
    void addNewFiles(const char *filename, const struct GNUNET_HashCode *file_id);
signals:
    
public slots:

private:
    struct GNUNET_FS_Handle * m_fs;
    SharedFilesModel* m_model;
    
};

#endif // SHAREDFILES_H
