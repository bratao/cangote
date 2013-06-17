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
    return QFileDialog::getOpenFileNames(NULL,
        tr("Pick Files"), NULL, NULL);

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

