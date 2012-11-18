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

#ifndef SEARCHDETAILSPANEL_H
#define SEARCHDETAILSPANEL_H

#include <QWidget>
#include "core/gnunet/gnunet_includes.h"


int GNUNET_FS_GTK_add_meta_data_to_list_store(void *cls, const char *plugin_name, EXTRACTOR_MetaType type, EXTRACTOR_MetaFormat format, const char *data_mime_type, const char *data, size_t data_len);
class GNUnetFsSearchResultsMetadataModel;
class QTreeView;
class SearchDetailsPanel : public QWidget
{
  Q_OBJECT
public:
  explicit SearchDetailsPanel(QWidget *parent = 0);
  
  void Init();
  void SetMetadata(const GNUNET_CONTAINER_MetaData *meta);

  void addMetadata(const char *plugin_name, EXTRACTOR_MetaType type, EXTRACTOR_MetaFormat format, const char *data_mime_type, const char *data, size_t data_len);
signals:
  
public slots:
  


private:
  GNUnetFsSearchResultsMetadataModel* model;
  QTreeView* collumView;

};

#endif // SEARCHDETAILSPANEL_H
