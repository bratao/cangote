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

#include "SearchModel.h"
#include "core/gnunet/filesharing/search/search.h"
#include "models/SearchResultModel.h"
#include "cangote.h"
#include "core/cangotecore.h"
#include "models/models.h"
#include "utils/utils.h"

#include "core/gnunet/filesharing/search/searchresult.h"



/***
 * Thumbnail Provider for QML
 **/


QImage SearchResultThumbnailImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{

  int width = requestedSize.width() > 0 ? requestedSize.width() : 200;
  int height = requestedSize.height() > 0 ? requestedSize.height() :100;

  if (size)
    *size = QSize(width, height);


  //Default image
  QImage image(width,
               height,QImage::Format_ARGB32);

  image.fill(qRgba(0, 0, 0, 0));


  QStringList list;

  list = id.split("/");


  int searchId = list[0].toInt();
  int searchResultId = list[1].toInt();


  //Load from file
  SearchResultsModel* searchResultModel = theApp->models()->searchModel()->getSearch(searchId)->model();

  SearchResult* searchResult = searchResultModel->getResult(searchResultId);

  Q_ASSERT(searchResult);

  QString type = theUtils->getFileExtension(searchResult->getFileName());


  if((list.size() == 3 )&& (list[2].compare("thumbnail") == 0)){

      return theUtils->getFileTypeImage(type,width,height);

    }
  else
    {

      if (searchResult->thumbnail())
        {

          //If we ask for an specified size, do it. Scale to height otherwise.
          if((requestedSize.width() > 0 )&&(requestedSize.height() > 0)){
              image = searchResult->thumbnail()->scaled(requestedSize.width() > 0 ? requestedSize.width() : width,
                                                        requestedSize.height() > 0 ? requestedSize.height() : height);
            }
          else
            {
              image = searchResult->thumbnail()->scaledToHeight(height,Qt::SmoothTransformation);
            }

        }
      else
        {
            return QImage(":/qml/filetypes/text-plain.png");
        }

      return image;
    }

}

//Thumbnail end






SearchModel::SearchModel(QObject *parent) :
  QAbstractListModel(parent)
{

  m_thumbnailProvider = new SearchResultThumbnailImageProvider();

  // connect signal-slots for decoupling
  connect (this, &SearchModel::addNewSearchSignal, this,
           &SearchModel::addNewSearchSlot,Qt::BlockingQueuedConnection);

  connect (this, &SearchModel::closeSearchSignal, this,
           &SearchModel::closeSearchSlot,Qt::QueuedConnection);

}
int SearchModel::rowCount(const QModelIndex& parent) const
{
  return m_data.size();
}

QVariant SearchModel::data(const QModelIndex& index, int role) const
{

  Search* search = m_data[index.row()];


  switch(role)
    {

    case TERM:
      return search->getTerm();
      break;
    case NUM_RESULTS:
      return search->numResults();
      break;

    default:
      return QVariant::Invalid;
    }


  return QVariant::Invalid;
}


QHash<int, QByteArray> SearchModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[TERM]                   = "term";
  roles[NUM_RESULTS]            = "numResults";


  return roles;
}


Search*  SearchModel::addNewSearch(void *sc,QString term )
{

  Search* search = new Search((GNUNET_FS_SearchContext*)sc,term );
  emit addNewSearchSignal(search);
  return search;
}

void  SearchModel::addNewSearchSlot(Search* search)
{



  int count = m_data.count();

  beginInsertRows(QModelIndex(), count, count);


  SearchResultsModel* resultModel = new SearchResultsModel(this);
  search->setModel(resultModel);
  search->setId(count);


  m_data.append(search);
  connect(search, &Search::resultsChanged, this, &SearchModel::modifiedSlot);


  endInsertRows();

  resultModel->setIndex(new QPersistentModelIndex (index(count, 0)));




}

void SearchModel::closeSearch(int index )
{

  emit closeSearchSignal(index);

}

void  SearchModel::closeSearchSlot(int index)
{

  beginRemoveRows(QModelIndex(), index, index);

  Search* search = getSearch(index);
  search->stop();

  //Model was allocated here because QML can't work with cross-tread models.
  if(search->model())
    delete search->model();

  m_data.removeAt(index);

  endRemoveRows();


}

void SearchModel::modifiedSlot(int indexRow)
{
  emit dataChanged(index(indexRow,0), index(indexRow,0));


}


Search* SearchModel::getSearch(int index)
{
  if ((index < 0) || (index >= m_data.count()))
    return NULL;


  return m_data.at(index);

}

int SearchModel::getCount()
{
  return m_data.count();
}
