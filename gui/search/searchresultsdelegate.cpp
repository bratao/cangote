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

#include "searchresultsdelegate.h"
#include <QApplication>
#include "models/gnunet_fs_search_results.h"
#include "utils/misc.h"

 SearchResultDelegate::SearchResultDelegate(QObject *parent=0) :
     QStyledItemDelegate(parent)
 {

 }

 SearchResultDelegate::~SearchResultDelegate()
 {

 }

 void  SearchResultDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {



     //Save our painter ( Recomendaded by Qt intructions)
      painter->save();


      QStyleOptionViewItemV4 opt = option;
      initStyleOption(&opt, index);







      switch(index.column()) {
      case GNUnetFsSearchResultsModel::FILESIZE:
          {
              //We going to draw only the text formated. So Empty the text, draw the widget, and
              //Draw out formated text over the painted widet.
             misc::drawWidgetBackground(&opt,painter);

              //Draw the text
              float size = index.data().toFloat();
              QString str;
              str = misc::bytesToString(size);
              painter->drawText(opt.rect,str);
          }
          break;

        default:
          QStyledItemDelegate::paint(painter, option, index);
      }

      //Restore the painter
      painter->restore();
    }



 QWidget*  SearchResultDelegate::createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const {
   // No editor here
   return 0;
 }

