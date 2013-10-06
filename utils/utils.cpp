#include "utils.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QProcess>


#include "cangote.h"
#include "core/gnunet/gnunet_includes.h"

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

void Utils::openFolder(QString filePath)
{
#if defined(Q_WS_MAC)
    QStringList args;
    args << "-e";
    args << "tell application \"Finder\"";
    args << "-e";
    args << "activate";
    args << "-e";
    args << "select POSIX file \""+filePath+"\"";
    args << "-e";
    args << "end tell";
    QProcess::startDetached("osascript", args)

#elif defined(Q_OS_WIN)
    QStringList args;
    args << "/select," << QDir::toNativeSeparators(filePath);
    QProcess::startDetached("explorer", args);
#endif

 //TODO:: Implement linux suport for opening Folder
}

QString Utils::getFileName(QString path){
  QFileInfo fi(path);
   QString name = fi.fileName();
   return name;
}


/**
 * Obtain pixbuf from thumbnail data in meta data.
 *
 * @param meta input meta data
 * @return NULL on error, otherwise the embedded thumbnail
 */
QImage * Utils::getThumbnailFromMetaData (const GNUNET_CONTAINER_MetaData *meta)
{
    size_t ts;
    unsigned char *thumb;

    thumb = NULL;
    ts = GNUNET_CONTAINER_meta_data_get_thumbnail (meta, &thumb);
    if (0 == ts)
        return NULL;

    QImage* image = new QImage();
    if(!image->loadFromData(thumb,ts))
    {
        delete image;
        image = NULL;
    }

    GNUNET_free (thumb);


    return image;
}


