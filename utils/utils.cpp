#include "utils.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>


#include "cangote.h"

Utils::Utils(QObject *parent) :
    QObject(parent)
{
}


// return best userfriendly storage unit (B, KiB, MiB, GiB, TiB)
// use Binary prefix standards from IEC 60027-2
// see http://en.wikipedia.org/wiki/Kilobyte
// value must be given in bytes
QString Utils::friendlyUnit(quint32 val, bool is_speed) {

  qreal convertedVal = val;
  if (convertedVal < 0)
    return tr("Unknown", "Unknown (size)");
  int i = 0;
  while(convertedVal >= 1024. && i++<6)
    convertedVal /= 1024.;
  QString ret;
  if (i == 0)
      ret = QString::number((long)convertedVal) + " " + tr("B");
  else if (i == 1)
      ret = QString::number(convertedVal, 'f', 2) + " " + tr("KB");
  else if (i == 2)
      ret = QString::number(convertedVal, 'f', 2) + " " + tr("MB");
  else if (i == 3)
      ret = QString::number(convertedVal, 'f', 2) + " " + tr("GB");
  else if (i == 4)
      ret = QString::number(convertedVal, 'f', 2) + " " + tr("PB");

  if (is_speed)
    ret += tr("/s", "per second");
  return ret;
}


QStringList Utils::openFilePicker()
{
    /*return QFileDialog::getOpenFileNames(NULL,
        tr("Pick Files"), NULL, NULL);*/
    QStringList fileNames;


    QFileDialog dialog;

    //Add button
      QFormLayout *columnLayout1 = new QFormLayout;
      QFormLayout *columnLayout2 = new QFormLayout;
      QHBoxLayout * rowLayout = new QHBoxLayout;

    QLabel* expirationLabel = new QLabel(tr("Expiration:"),&dialog);
    QComboBox* expirationCombo = new QComboBox(&dialog);
    expirationCombo->addItem("Expire in 6 months");
    expirationCombo->addItem("Expire in 1 year");
    expirationCombo->addItem("Expire in 2 years");
    expirationCombo->addItem("Expire in 5 years");
    expirationCombo->addItem("Expire in 10 years");

    QLabel* replicationLabel = new QLabel(tr("Replication:"),&dialog);
    QComboBox* replicationCombo = new QComboBox(&dialog);
    replicationCombo->addItem("No replication");
    replicationCombo->addItem("Replicate at least 1 time");
    replicationCombo->addItem("Replicate at least 2 times");
    replicationCombo->addItem("Replicate at least 5 times");

    QLabel* priorityLabel = new QLabel(tr("Priority:"),&dialog);
    QComboBox* priorityCombo = new QComboBox(&dialog);
    priorityCombo->addItem("Low");
    priorityCombo->addItem("Normal");
    priorityCombo->addItem("High");
    priorityCombo->addItem("Highest");


    QLabel* anonLabel = new QLabel(tr("Anonymity:"),&dialog);
    QComboBox* anonCombo = new QComboBox(&dialog);
    anonCombo->addItem("0 - Low");
    anonCombo->addItem("1 - High");
    anonCombo->addItem("2 - Very high");
    anonCombo->addItem("5 - Ultra high");
    anonCombo->addItem("10 - Paranoid");



    columnLayout1->addRow(expirationLabel,expirationCombo);
    columnLayout1->addRow(replicationLabel,replicationCombo);
    columnLayout2->addRow(priorityLabel,priorityCombo);
    columnLayout2->addRow(anonLabel,anonCombo);

    rowLayout->addLayout(columnLayout1);
    rowLayout->addLayout(columnLayout2);
   // configLayout->addRow(combo);




    QGridLayout *layout = (QGridLayout*)dialog.layout();
    layout->addLayout(rowLayout,4,0,1,-1);

    //Set mode
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    return fileNames;

}

QString Utils::openFolderPicker()
{
    return QFileDialog::getExistingDirectory(NULL,
        tr("Pick Folder"), NULL, QFileDialog::DontUseNativeDialog| QFileDialog::ShowDirsOnly);
}

void Utils::openFile(QString file)
{
    QString path;
    path = QString("file:///") + file;
    QDesktopServices::openUrl(QUrl(path));
}

