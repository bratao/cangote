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

#include "searchdetailspanel.h"
#include <QTreeView>
#include <QHBoxLayout>
#include "core/gnunet/gnunet_includes.h"
#include "models/gnunet_fs_search_results_metadata.h"



SearchDetailsPanel::SearchDetailsPanel(QWidget *parent) :
  QWidget(parent)
{
  Init();
  model = NULL;
}




void SearchDetailsPanel::Init()
{

  collumView = new QTreeView(this);

  collumView->setAlternatingRowColors(true);
  collumView->setItemsExpandable(false);
  collumView->setRootIsDecorated(false);

  QHBoxLayout *serverLayout = new QHBoxLayout;
  serverLayout->addWidget(collumView);
  setLayout(serverLayout);


}

int
GNUNET_FS_GTK_add_meta_data_to_list_store (void *cls, const char *plugin_name,
                                           enum EXTRACTOR_MetaType type,
                                           enum EXTRACTOR_MetaFormat format,
                                           const char *data_mime_type,
                                           const char *data, size_t data_len)
{
  SearchDetailsPanel* addr = (SearchDetailsPanel*)cls;

  addr->addMetadata(plugin_name,type,format,data_mime_type,data,data_len);
  //Return 0 to continue
  return 0;
}

void SearchDetailsPanel::addMetadata(const char *plugin_name,
                                     enum EXTRACTOR_MetaType type,
                                     enum EXTRACTOR_MetaFormat format,
                                     const char *data_mime_type,
                                     const char *data, size_t data_len)
{
  if(model ==NULL)
    return;

   const char * strMetaDatatype = EXTRACTOR_metatype_to_string(type);

   QString typeStr(strMetaDatatype);

  QString value;
  value = value.fromUtf8(data,data_len);

  Metadata* newMetadata = new Metadata;
  newMetadata->name = typeStr;
  newMetadata->value = value;


      model->addMetadata(newMetadata);

}

void SearchDetailsPanel::SetMetadata(const GNUNET_CONTAINER_MetaData *meta)
{

  if(model)
    delete model;

  model = new GNUnetFsSearchResultsMetadataModel();

  if (NULL == meta)
      return;


  GNUNET_CONTAINER_meta_data_iterate (meta,
                                          GNUNET_FS_GTK_add_meta_data_to_list_store,
                                          this);

  collumView->setModel(model);
}


