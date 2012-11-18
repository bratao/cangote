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

#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QDesktopServices>
#include <QTimer>
#include <QClipboard>
#include <QInputDialog>
#include <QColor>
#include <QUrl>
#include <QMenu>
#include <QRegExp>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QHeaderView>

#include <vector>
#include <queue>
#include <QDebug>

#include "core/cangote.h"
#include "transferlistwidget.h"
#include "models/downloadmodel.h"
#include "transferlistdelegate.h"
#include "core/gnunet/gnunet.h"



TransferListWidget::TransferListWidget(QWidget *parent):
  QTreeView(parent) {

  // Load settings
  bool column_loaded = loadSettings();

  // Create and apply delegate
  listDelegate = new TransferListDelegate(this);
  setItemDelegate(listDelegate);


  // Visual settings
  setRootIsDecorated(false);
  setAllColumnsShowFocus(true);
  setSortingEnabled(true);
  setSelectionMode(QAbstractItemView::ExtendedSelection);
  setItemsExpandable(false);
  setAutoScroll(true);
  setDragDropMode(QAbstractItemView::DragOnly);
#if defined(Q_WS_MAC)
  setAttribute(Qt::WA_MacShowFocusRect, false);
#endif

  // Default hidden columns
  if (!column_loaded) {
    setColumnHidden(DownloadItem::TR_ADD_DATE, true);
    setColumnHidden(DownloadItem::TR_AMOUNT_DOWNLOADED, true);
    setColumnHidden(DownloadItem::TR_AMOUNT_LEFT, true);
    setColumnHidden(DownloadItem::TR_TIME_ELAPSED, true);
  }

  setContextMenuPolicy(Qt::CustomContextMenu);

  // Listen for list events
  connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(torrentDoubleClicked(QModelIndex)));
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(displayListMenu(const QPoint&)));
  header()->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(header(), SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(displayDLHoSMenu(const QPoint&)));
}

TransferListWidget::~TransferListWidget() {
  qDebug() << Q_FUNC_INFO << "ENTER";
  // Save settings
  saveSettings();
  // Clean up
  delete labelFilterModel;
  delete statusFilterModel;
  delete nameFilterModel;
  delete listModel;
  delete listDelegate;
  qDebug() << Q_FUNC_INFO << "EXIT";
}


void TransferListWidget::setModel(DownloadModel* model)
{
    // Create transfer list model
    listModel = model;

    // Set Sort/Filter proxy
    labelFilterModel = new QSortFilterProxyModel();
    labelFilterModel->setDynamicSortFilter(true);
    labelFilterModel->setSourceModel(listModel);
    labelFilterModel->setFilterKeyColumn(DownloadItem::TR_LABEL);
    labelFilterModel->setFilterRole(Qt::DisplayRole);

    statusFilterModel = new QSortFilterProxyModel();
    statusFilterModel->setDynamicSortFilter(true);
    statusFilterModel->setSourceModel(labelFilterModel);
    statusFilterModel->setFilterKeyColumn(DownloadItem::TR_STATUS);
    statusFilterModel->setFilterRole(Qt::DisplayRole);

    nameFilterModel = new QSortFilterProxyModel();
    nameFilterModel->setDynamicSortFilter(true);
    nameFilterModel->setSourceModel(statusFilterModel);
    nameFilterModel->setFilterKeyColumn(DownloadItem::TR_NAME);
    nameFilterModel->setFilterRole(Qt::DisplayRole);
    nameFilterModel->setSortCaseSensitivity(Qt::CaseInsensitive);

    QTreeView::setModel(nameFilterModel);

}



DownloadModel* TransferListWidget::getSourceModel() const {
  return listModel;
}

void TransferListWidget::previewFile(QString filePath) {
  QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}



inline QModelIndex TransferListWidget::mapToSource(const QModelIndex &index) const {
  Q_ASSERT(index.isValid());
  if (index.model() == nameFilterModel)
    return labelFilterModel->mapToSource(statusFilterModel->mapToSource(nameFilterModel->mapToSource(index)));
  if (index.model() == statusFilterModel)
    return labelFilterModel->mapToSource(statusFilterModel->mapToSource(index));
  return labelFilterModel->mapToSource(index);
}

inline QModelIndex TransferListWidget::mapFromSource(const QModelIndex &index) const {
  Q_ASSERT(index.isValid());
  Q_ASSERT(index.model() == labelFilterModel);
  return nameFilterModel->mapFromSource(statusFilterModel->mapFromSource(labelFilterModel->mapFromSource(index)));
}


QStringList TransferListWidget::getCustomLabels() const {
  QSettings settings(QString::fromUtf8("CangoteTeam"), QString::fromUtf8("Cangote"));
  return settings.value("TransferListFilters/customLabels", QStringList()).toStringList();
}

void TransferListWidget::torrentDoubleClicked(const QModelIndex& index) {
  const int row = mapToSource(index).row();
  //TODO: implement double click on transfer
  gWarn("Transfer Double clicked ! ");
}

QModelIndexList TransferListWidget::getSelectedTransfers() const {
  const QModelIndexList selectedIndexes = selectionModel()->selectedRows();
  return selectedIndexes;
}

void TransferListWidget::setSelectedTransferLocation() {
  const QModelIndexList selectedIndexes = getSelectedTransfers();
  //TODO: implement setSelectedTransferLocation
  gWarn("setSelectedTransferLocation");
}

void TransferListWidget::startSelectedTransfer() {
  QModelIndexList transfers = getSelectedTransfers();
  //TODO: implement Start Selected Transfers
  gWarn("Start selected transfers");
}

void TransferListWidget::startVisibleTransfer() {
    //TODO: implement startVisibleTransfer
    gWarn("startVisibleTransfer");
}

void TransferListWidget::pauseSelectedTransfer() {
  const QModelIndexList selectedIndexes = getSelectedTransfers();
  foreach (const QModelIndex &index, selectedIndexes) {
      //TODO:: Inplement pauseSelectedTransfer
       gWarn("pauseSelectedTransfer");
    //BTSession->pauseTorrent(hash);
  }
}

void TransferListWidget::pauseVisibleTransfer() {
    //TODO: implement pauseVisibleTransfer
    gWarn("pauseVisibleTransfer");
}

void TransferListWidget::deleteSelectedTransfer() {

  const QModelIndexList selectedIndexes = getSelectedTransfers();
  foreach (const QModelIndex &index, selectedIndexes) {
      //TODO:: Inplement deleteSelectedTransfer
       gWarn("deleteSelectedTransfer");
  }
}

void TransferListWidget::deleteVisibleTransfer() {
    //TODO: implement deleteVisibleTransfer
    gWarn("deleteVisibleTransfer");
}

void TransferListWidget::increasePrioSelectedTransfer() {
  qDebug() << Q_FUNC_INFO;
  const QModelIndexList selectedIndexes = getSelectedTransfers();
  foreach (const QModelIndex &index, selectedIndexes) {
      //TODO:: Implement increasePrioSelectedTransfer
       gWarn("increasePrioSelectedTransfer");
  }
}

void TransferListWidget::decreasePrioSelectedTransfer() {
  qDebug() << Q_FUNC_INFO;
  const QModelIndexList selectedIndexes = getSelectedTransfers();
  foreach (const QModelIndex &index, selectedIndexes) {
      //TODO:: Implement decreasePrioSelectedTransfer
       gWarn("decreasePrioSelectedTransfer");
  }
}

void TransferListWidget::topPrioSelectedTransfer() {
    qDebug() << Q_FUNC_INFO;
    const QModelIndexList selectedIndexes = getSelectedTransfers();
    foreach (const QModelIndex &index, selectedIndexes) {
        //TODO:: Implement topPrioSelectedTransfer
         gWarn("topPrioSelectedTransfer");
    }
}

void TransferListWidget::bottomPrioSelectedTransfer() {
    qDebug() << Q_FUNC_INFO;
    const QModelIndexList selectedIndexes = getSelectedTransfers();
    foreach (const QModelIndex &index, selectedIndexes) {
        //TODO:: Implement bottomPrioSelectedTransfer
         gWarn("bottomPrioSelectedTransfer");
    }
}

void TransferListWidget::copySelectedMagnetURIs() const {
  QStringList magnet_uris;
  qDebug() << Q_FUNC_INFO;
  const QModelIndexList selectedIndexes = getSelectedTransfers();
  foreach (const QModelIndex &index, selectedIndexes) {
      //TODO:: Implement copySelectedMagnetURIs
       gWarn("copySelectedMagnetURIs");
  }
  qApp->clipboard()->setText(magnet_uris.join("\n"));
}


void TransferListWidget::openSelectedTransferFolder() const {
    qDebug() << Q_FUNC_INFO;
    const QModelIndexList selectedIndexes = getSelectedTransfers();
    foreach (const QModelIndex &index, selectedIndexes) {
        //TODO:: Implement openSelectedTransferFolder
         gWarn("openSelectedTransferFolder");
    }
}

void TransferListWidget::previewSelectedTransfer() {
    qDebug() << Q_FUNC_INFO;
    const QModelIndexList selectedIndexes = getSelectedTransfers();
    foreach (const QModelIndex &index, selectedIndexes) {
        //TODO:: Implement previewSelectedTransfer
         gWarn("previewSelectedTransfer");
    }
}


// hide/show columns menu
void TransferListWidget::displayDLHoSMenu(const QPoint&) {
  QMenu hideshowColumn(this);
  hideshowColumn.setTitle(tr("Column visibility"));
  QList<QAction*> actions;
  for (int i=0; i < listModel->columnCount(); ++i) {
    QAction *myAct = hideshowColumn.addAction(listModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
    myAct->setCheckable(true);
    myAct->setChecked(!isColumnHidden(i));
    actions.append(myAct);
  }
  // Call menu
  QAction *act = hideshowColumn.exec(QCursor::pos());
  if (act) {
    int col = actions.indexOf(act);
    Q_ASSERT(col >= 0);
    qDebug("Toggling column %d visibility", col);
    setColumnHidden(col, !isColumnHidden(col));
    if (!isColumnHidden(col) && columnWidth(col) <= 5)
      setColumnWidth(col, 100);
  }
}


void TransferListWidget::toggleSelectedTransferSequentialDownload() const {
    qDebug() << Q_FUNC_INFO;
    const QModelIndexList selectedIndexes = getSelectedTransfers();
    foreach (const QModelIndex &index, selectedIndexes) {
        //TODO:: Implement toggleSelectedTransferSequentialDownload
         gWarn("toggleSelectedTransferSequentialDownload");
    }
}

void TransferListWidget::toggleSelectedFirstLastPiecePrio() const {
    qDebug() << Q_FUNC_INFO;
    const QModelIndexList selectedIndexes = getSelectedTransfers();
    foreach (const QModelIndex &index, selectedIndexes) {
        //TODO:: Implement toggleSelectedFirstLastPiecePrio
         gWarn("toggleSelectedFirstLastPiecePrio");
    }
}

void TransferListWidget::askNewLabelForSelection() {
  // Ask for label
  bool ok;
  bool invalid;
  do {
    invalid = false;
    const QString label = QInputDialog::getText(this, tr("New Label"), tr("Label:"), QLineEdit::Normal, "", &ok);
    if (ok && !label.isEmpty()) {
        //TODO:: Implement askNewLabelForSelection
         gWarn("askNewLabelForSelection");
    }
  }while(invalid);
}

void TransferListWidget::renameSelectedTorrent() {
  const QModelIndexList selectedIndexes = selectionModel()->selectedRows();
  if (selectedIndexes.size() != 1) return;
  if (!selectedIndexes.first().isValid()) return;
  //TODO:: Implement renameSelectedTorrent
   gWarn("renameSelectedTorrent");

}

void TransferListWidget::setSelectionLabel(QString label) {
    qDebug() << Q_FUNC_INFO;
    const QModelIndexList selectedIndexes = getSelectedTransfers();
    foreach (const QModelIndex &index, selectedIndexes) {
        //TODO:: Implement setSelectionLabel
         gWarn("setSelectionLabel");
    }
}

void TransferListWidget::removeLabelFromRows(QString label) {
  for (int i=0; i<listModel->rowCount(); ++i) {
    //if (listModel->data(listModel->index(i, DownloadItem::TR_LABEL)) == label) {
        //TODO:: Implement removeLabelFromRows
         gWarn("removeLabelFromRows");
    //}
  }
}

void TransferListWidget::displayListMenu(const QPoint&) {
  // Create actions
  QAction actionStart(QIcon("media-playback-start"), tr("Resume", "Resume/start the torrent"), 0);
  connect(&actionStart, SIGNAL(triggered()), this, SLOT(startSelectedTransfer()));
  QAction actionPause(QIcon("media-playback-pause"), tr("Pause", "Pause the torrent"), 0);
  connect(&actionPause, SIGNAL(triggered()), this, SLOT(pauseSelectedTransfer()));
  QAction actionDelete(QIcon("edit-delete"), tr("Delete", "Delete the torrent"), 0);
  connect(&actionDelete, SIGNAL(triggered()), this, SLOT(deleteSelectedTransfer()));
  QAction actionPreview_file(QIcon("view-preview"), tr("Preview file..."), 0);
  connect(&actionPreview_file, SIGNAL(triggered()), this, SLOT(previewSelectedTransfer()));

  QAction actionOpen_destination_folder(QIcon("inode-directory"), tr("Open destination folder"), 0);
  connect(&actionOpen_destination_folder, SIGNAL(triggered()), this, SLOT(openSelectedTransferFolder()));
  QAction actionIncreasePriority(QIcon("go-up"), tr("Move up", "i.e. move up in the queue"), 0);
  connect(&actionIncreasePriority, SIGNAL(triggered()), this, SLOT(increasePrioSelectedTransfer()));
  QAction actionDecreasePriority(QIcon("go-down"), tr("Move down", "i.e. Move down in the queue"), 0);
  connect(&actionDecreasePriority, SIGNAL(triggered()), this, SLOT(decreasePrioSelectedTransfer()));
  QAction actionTopPriority(QIcon("go-top"), tr("Move to top", "i.e. Move to top of the queue"), 0);
  connect(&actionTopPriority, SIGNAL(triggered()), this, SLOT(topPrioSelectedTransfer()));
  QAction actionBottomPriority(QIcon("go-bottom"), tr("Move to bottom", "i.e. Move to bottom of the queue"), 0);
  connect(&actionBottomPriority, SIGNAL(triggered()), this, SLOT(bottomPrioSelectedTransfer()));
  QAction actionSetTorrentPath(QIcon("inode-directory"), tr("Set location..."), 0);
  connect(&actionSetTorrentPath, SIGNAL(triggered()), this, SLOT(setSelectedTransferLocation()));
  QAction actionCopy_magnet_link(QIcon(":/Icons/magnet.png"), tr("Copy magnet link"), 0);
  connect(&actionCopy_magnet_link, SIGNAL(triggered()), this, SLOT(copySelectedMagnetURIs()));
  QAction actionRename(QIcon("edit-rename"), tr("Rename..."), 0);
  connect(&actionRename, SIGNAL(triggered()), this, SLOT(renameSelectedTorrent()));
  QAction actionSequential_download(tr("Download in sequential order"), 0);
  actionSequential_download.setCheckable(true);
  connect(&actionSequential_download, SIGNAL(triggered()), this, SLOT(toggleSelectedTransferSequentialDownload()));
  QAction actionFirstLastPiece_prio(tr("Download first and last piece first"), 0);
  actionFirstLastPiece_prio.setCheckable(true);
  connect(&actionFirstLastPiece_prio, SIGNAL(triggered()), this, SLOT(toggleSelectedFirstLastPiecePrio()));
  // End of actions
  QMenu listMenu(this);
  // Enable/disable pause/start action given the DL state
  QModelIndexList selectedIndexes = selectionModel()->selectedRows();
  bool has_pause = false, has_start = false, has_preview = false;
  bool all_same_super_seeding = true;
  bool super_seeding_mode = false;
  bool all_same_sequential_download_mode = true, all_same_prio_firstlast = true;
  bool sequential_download_mode = false, prioritize_first_last = false;
  bool one_has_metadata = false, one_not_seed = false;
  bool first = true;


  //TODO:: Set the configs
  /*
  QTorrentHandle h;
  qDebug("Displaying menu");
  foreach (const QModelIndex &index, selectedIndexes) {
    // Get the file name
    QString hash = getHashFromRow(mapToSource(index).row());
    // Get handle and pause the torrent
    h = BTSession->getTorrentHandle(hash);
    if (!h.is_valid()) continue;
    if (h.has_metadata())
      one_has_metadata = true;
    if (!h.is_seed()) {
      one_not_seed = true;
      if (h.has_metadata()) {
        if (first) {
          sequential_download_mode = h.is_sequential_download();
          prioritize_first_last = h.first_last_piece_first();
        } else {
          if (sequential_download_mode != h.is_sequential_download()) {
            all_same_sequential_download_mode = false;
          }
          if (prioritize_first_last != h.first_last_piece_first()) {
            all_same_prio_firstlast = false;
          }
        }
      }
    }
    else {
      if (!one_not_seed && all_same_super_seeding && h.has_metadata()) {
        if (first) {
          super_seeding_mode = h.super_seeding();
        } else {
          if (super_seeding_mode != h.super_seeding()) {
            all_same_super_seeding = false;
          }
        }
      }
    }
    if (h.is_paused()) {
      if (!has_start) {
        listMenu.addAction(&actionStart);
        has_start = true;
      }
    }else{
      if (!has_pause) {
        listMenu.addAction(&actionPause);
        has_pause = true;
      }
    }
    if (h.has_metadata() && BTSession->isFilePreviewPossible(hash) && !has_preview) {
      has_preview = true;
    }
    first = false;
    if (has_pause && has_start && has_preview && one_not_seed) break;
  }
  */
  listMenu.addSeparator();
  listMenu.addAction(&actionDelete);
  listMenu.addSeparator();
  listMenu.addAction(&actionSetTorrentPath);
  if (selectedIndexes.size() == 1)
    listMenu.addAction(&actionRename);
  // Label Menu
  QStringList customLabels = getCustomLabels();
  customLabels.sort();
  QList<QAction*> labelActions;
  QMenu *labelMenu = listMenu.addMenu(QIcon("view-categories"), tr("Label"));
  labelActions << labelMenu->addAction(QIcon("list-add"), tr("New...", "New label..."));
  labelActions << labelMenu->addAction(QIcon("edit-clear"), tr("Reset", "Reset label"));
  labelMenu->addSeparator();
  foreach (const QString &label, customLabels) {
    labelActions << labelMenu->addAction(QIcon("inode-directory"), label);
  }
  listMenu.addSeparator();
  bool added_preview_action = false;
  if (has_preview) {
    listMenu.addAction(&actionPreview_file);
    added_preview_action = true;
  }
  if (one_not_seed && one_has_metadata) {
    if (all_same_sequential_download_mode) {
      actionSequential_download.setChecked(sequential_download_mode);
      listMenu.addAction(&actionSequential_download);
      added_preview_action = true;
    }
    if (all_same_prio_firstlast) {
      actionFirstLastPiece_prio.setChecked(prioritize_first_last);
      listMenu.addAction(&actionFirstLastPiece_prio);
      added_preview_action = true;
    }
  }
  if (added_preview_action)
    listMenu.addSeparator();

  listMenu.addAction(&actionOpen_destination_folder);
    listMenu.addSeparator();
    QMenu *prioMenu = listMenu.addMenu(tr("Priority"));
    prioMenu->addAction(&actionTopPriority);
    prioMenu->addAction(&actionIncreasePriority);
    prioMenu->addAction(&actionDecreasePriority);
    prioMenu->addAction(&actionBottomPriority);
  listMenu.addSeparator();
  if (one_has_metadata)
    listMenu.addAction(&actionCopy_magnet_link);
  // Call menu
  QAction *act = 0;
  act = listMenu.exec(QCursor::pos());
  if (act) {
    // Parse label actions only (others have slots assigned)
    int i = labelActions.indexOf(act);
    if (i >= 0) {
      // Label action
      if (i == 0) {
        // New Label
        askNewLabelForSelection();
      } else {
        QString label = "";
        if (i > 1)
          label = customLabels.at(i-2);
        // Update Label
        setSelectionLabel(label);
      }
    }
  }
}

void TransferListWidget::currentChanged(const QModelIndex& current, const QModelIndex&) {
  qDebug("CURRENT CHANGED");
  if (current.isValid()) {
    const int row = mapToSource(current).row();
    //TODO:: Implement currentChanged
     gWarn("currentChanged");
    // Scroll Fix
    scrollTo(current);
  }
  //emit currentTorrentChanged(h);
}

void TransferListWidget::applyLabelFilter(QString label) {
  if (label == "all") {
    labelFilterModel->setFilterRegExp(QRegExp());
    return;
  }
  if (label == "none") {
    labelFilterModel->setFilterRegExp(QRegExp("^$"));
    return;
  }
  qDebug("Applying Label filter: %s", qPrintable(label));
  labelFilterModel->setFilterRegExp(QRegExp("^" + QRegExp::escape(label) + "$", Qt::CaseSensitive));
}

void TransferListWidget::applyNameFilter(const QString& name) {
  nameFilterModel->setFilterRegExp(QRegExp(QRegExp::escape(name), Qt::CaseInsensitive));
}

void TransferListWidget::applyStatusFilter(int f) {
  switch(f) {
  case FILTER_DOWNLOADING:
    statusFilterModel->setFilterRegExp(QRegExp(QString::number(DownloadItem::STATE_DOWNLOADING)+"|"+QString::number(DownloadItem::STATE_PAUSED)+"|"+
                                               QString::number(DownloadItem::STATE_QUEUED), Qt::CaseSensitive));
    break;
  case FILTER_COMPLETED:
    statusFilterModel->setFilterRegExp(QRegExp(QString::number(DownloadItem::STATE_COMPLETE), Qt::CaseSensitive));
    break;
  case FILTER_ACTIVE:
    statusFilterModel->setFilterRegExp(QRegExp(QString::number(DownloadItem::STATE_DOWNLOADING), Qt::CaseSensitive));
    break;
  case FILTER_INACTIVE:
    statusFilterModel->setFilterRegExp(QRegExp("[^"+QString::number(DownloadItem::STATE_DOWNLOADING)+"]", Qt::CaseSensitive));
    break;
  case FILTER_PAUSED:
    statusFilterModel->setFilterRegExp(QRegExp(QString::number(DownloadItem::STATE_PAUSED)));
    break;
  default:
    statusFilterModel->setFilterRegExp(QRegExp());
  }
  // Select first item if nothing is selected
  if (selectionModel()->selectedRows(0).empty() && nameFilterModel->rowCount() > 0) {
    qDebug("Nothing is selected, selecting first row: %s", qPrintable(nameFilterModel->index(0, DownloadItem::TR_NAME).data().toString()));
    selectionModel()->setCurrentIndex(nameFilterModel->index(0, DownloadItem::TR_NAME), QItemSelectionModel::SelectCurrent|QItemSelectionModel::Rows);
  }
}

void TransferListWidget::saveSettings()
{
    //TODO:: Set a global preferences
  QSettings settings("CangoteTeam", "Cangote");
  settings.setValue("TransferList/HeaderState", header()->saveState());
}

bool TransferListWidget::loadSettings()
{
  QSettings settings("CangoteTeam", "Cangote");
  bool ok = header()->restoreState(settings.value("TransferList/HeaderState").toByteArray());
  if (!ok) {
    header()->resizeSection(0, 200); // Default
  }
  return ok;
}

