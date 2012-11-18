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

#ifndef TRANSFERLISTWIDGET_H
#define TRANSFERLISTWIDGET_H

#include <QTreeView>



class TransferListDelegate;
class DownloadModel;

QT_FORWARD_DECLARE_CLASS(QSortFilterProxyModel)
QT_FORWARD_DECLARE_CLASS(QStandardItemModel)

enum TorrentFilter {FILTER_ALL, FILTER_DOWNLOADING, FILTER_COMPLETED, FILTER_PAUSED, FILTER_ACTIVE, FILTER_INACTIVE};

class TransferListWidget: public QTreeView {
  Q_OBJECT

public:
  TransferListWidget(QWidget *parent);
  ~TransferListWidget();
  DownloadModel* getSourceModel() const;

  void setModel(DownloadModel *model);
public slots:
  void setSelectionLabel(QString label);
  void setSelectedTransferLocation();
  void startSelectedTransfer();
  void startVisibleTransfer();
  void pauseSelectedTransfer();
  void pauseVisibleTransfer();
  void deleteSelectedTransfer();
  void deleteVisibleTransfer();
  void increasePrioSelectedTransfer();
  void decreasePrioSelectedTransfer();
  void topPrioSelectedTransfer();
  void bottomPrioSelectedTransfer();
  void copySelectedMagnetURIs() const;
  void openSelectedTransferFolder() const;

  void previewSelectedTransfer();

  void displayDLHoSMenu(const QPoint&);
  void applyNameFilter(const QString& name);
  void applyStatusFilter(int f);
  void applyLabelFilter(QString label);
  void previewFile(QString filePath);
  void removeLabelFromRows(QString label);
  void renameSelectedTorrent();

protected:
  QModelIndex mapToSource(const QModelIndex &index) const;
  QModelIndex mapFromSource(const QModelIndex &index) const;
  QStringList getCustomLabels() const;
  void saveSettings();
  bool loadSettings();
  QModelIndexList getSelectedTransfers() const;

protected slots:
  void torrentDoubleClicked(const QModelIndex& index);
  void displayListMenu(const QPoint&);
  void currentChanged(const QModelIndex& current, const QModelIndex&);
  void toggleSelectedTransferSequentialDownload() const;
  void toggleSelectedFirstLastPiecePrio() const;
  void askNewLabelForSelection();

signals:
  //void currentTorrentChanged(const QTorrentHandle &h);

private:
  TransferListDelegate *listDelegate;
  DownloadModel *listModel;
  QSortFilterProxyModel *nameFilterModel;
  QSortFilterProxyModel *statusFilterModel;
  QSortFilterProxyModel *labelFilterModel;
};

#endif // TRANSFERLISTWIDGET_H
