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

#include "networkpeerdelegate.h"
#include <QApplication>
#include "models/gnunet_peers.h"
#include "utils/misc.h"

 NetworkPeerDelegate::NetworkPeerDelegate(QObject *parent=0) :
     QStyledItemDelegate(parent)
 {

 }

 NetworkPeerDelegate::~NetworkPeerDelegate()
 {

 }

 void  NetworkPeerDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {



     //Save our painter ( Recomendaded by Qt intructions)
      painter->save();


      QStyleOptionViewItemV4 opt = option;
      initStyleOption(&opt, index);







      switch(index.column()) {
      case GNUNetPeersModel::INCOMING_BANDWIDTH:
      case GNUNetPeersModel::OUTGOING_BANDWIDTH:
          {
              //We going to draw only the text formated. So Empty the text, draw the widget, and
              //Draw out formated text over the painted widet.
             misc::drawWidgetBackground(&opt,painter);

              //Draw the text
              float band = index.data().toFloat();
              QString str;
              if(band < 0.1)
                  str = "";
              else
                  str = misc::bytesToString(band)+"/s";
              painter->drawText(opt.rect,str);
          }
          break;

      case GNUNetPeersModel::INCOMING_TRAFFIC:
      case GNUNetPeersModel::OUTGOING_TRAFFIC:
      {
          float data;
          data = index.data().toFloat();
          QString str;
          if(data < 0.1)
              str = "";
          else
              str = misc::bytesToString(data);

          misc::drawWidgetBackground(&opt,painter);

          painter->drawText(opt.rect,str);
      }
          break;
        default:
          QStyledItemDelegate::paint(painter, option, index);
      }

      //Restore the painter
      painter->restore();
    }


 QWidget*  NetworkPeerDelegate::createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const {
   // No editor here
   return 0;
 }

