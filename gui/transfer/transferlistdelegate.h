/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2006  Christophe Dumez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef TRANSFERLISTDELEGATE_H
#define TRANSFERLISTDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QByteArray>
#include <QStyleOptionViewItem>
#include <QStyleOptionViewItemV2>
#include <QApplication>
#include <QPainter>
#include <QDateTime>
#include "utils/misc.h"
#include "core/gnunet/filesharing/transfer/downloaditem.h"

#ifdef Q_WS_WIN
  #include <QPlastiqueStyle>
#endif

// Defines for download list list columns

class TransferListDelegate: public QItemDelegate {
  Q_OBJECT

public:
  TransferListDelegate(QObject *parent) : QItemDelegate(parent) {}

  ~TransferListDelegate() {}

  void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QStyleOptionViewItemV2 opt = QItemDelegate::setOptions(index, option);
    painter->save();
    switch(index.column()) {
    case DownloadItem::TR_AMOUNT_DOWNLOADED:
    case DownloadItem::TR_AMOUNT_LEFT:
    case DownloadItem::TR_SIZE:{
        QItemDelegate::drawBackground(painter, opt, index);
        opt.displayAlignment = Qt::AlignRight;
        QItemDelegate::drawDisplay(painter, opt, option.rect, misc::friendlyUnit(index.data().toLongLong()));
        break;
      }
    case DownloadItem::TR_ETA:{
        QItemDelegate::drawBackground(painter, opt, index);
        QItemDelegate::drawDisplay(painter, opt, option.rect, misc::userFriendlyDuration(index.data().toLongLong()));
        break;
      }
    case DownloadItem::TR_STATUS: {
        const int state = index.data().toInt();
        QString display;
        switch(state) {
        case DownloadItem::STATE_DOWNLOADING:
          display = tr("Downloading");
          break;
        case DownloadItem::STATE_PAUSED:
          display = tr("Paused");
          break;
        case DownloadItem::STATE_QUEUED:
          display = tr("Queued", "i.e. torrent is queued");
          break;
        case DownloadItem::STATE_COMPLETE:
          display = tr("Complete", "Torrent is complete and in upload-only mode");
          break;
        default:
           display = "";
        }
        QItemDelegate::drawBackground(painter, opt, index);
        QItemDelegate::drawDisplay(painter, opt, opt.rect, display);
        break;
      }
    case DownloadItem::TR_DLSPEED:{
        QItemDelegate::drawBackground(painter, opt, index);
        const qulonglong speed = index.data().toULongLong();
        opt.displayAlignment = Qt::AlignRight;
        QItemDelegate::drawDisplay(painter, opt, opt.rect, misc::friendlyUnit(speed)+tr("/s", "/second (.i.e per second)"));
        break;
      }
    case DownloadItem::TR_TIME_ELAPSED: {
      QItemDelegate::drawBackground(painter, opt, index);
      QString txt = misc::userFriendlyDuration(index.data().toLongLong());
      qlonglong seeding_time = index.data(Qt::UserRole).toLongLong();
      if (seeding_time > 0)
        txt += " ("+tr("Seeded for %1", "e.g. Seeded for 3m10s").arg(misc::userFriendlyDuration(seeding_time))+")";
      QItemDelegate::drawDisplay(painter, opt, opt.rect, txt);
      break;
    }
    case DownloadItem::TR_ADD_DATE:
      QItemDelegate::drawBackground(painter, opt, index);
      QItemDelegate::drawDisplay(painter, opt, opt.rect, index.data().toDateTime().toLocalTime().toString(Qt::DefaultLocaleShortDate));
      break;
    case DownloadItem::TR_PROGRESS:{
        QStyleOptionProgressBarV2 newopt;
        qreal progress = index.data().toDouble()*100.;
        // We don't want to display 100% unless
        // the torrent is really complete
        if (progress > 99.94 && progress < 100.)
          progress = 99.9;
        newopt.rect = opt.rect;
        newopt.text = QString::number(progress, 'f', 1)+"%";
        newopt.progress = (int)progress;
        newopt.maximum = 100;
        newopt.minimum = 0;
        newopt.state |= QStyle::State_Enabled;
        newopt.textVisible = true;
#ifndef Q_WS_WIN
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &newopt, painter);
#else
        // XXX: To avoid having the progress text on the right of the bar
        QPlastiqueStyle st;
        st.drawControl(QStyle::CE_ProgressBar, &newopt, painter, 0);
#endif
        break;
      }
    default:
      QItemDelegate::paint(painter, option, index);
    }
    painter->restore();
  }

  QWidget* createEditor(QWidget*, const QStyleOptionViewItem &, const QModelIndex &) const {
    // No editor here
    return 0;
  }

};

#endif // TRANSFERLISTDELEGATE_H
