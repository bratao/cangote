#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QHash>
#include <QStringList>




class Utils : public QObject
{
    Q_OBJECT



  enum FileType
  {
          FILE_FT_UNKNOWN		= 0,
          FILE_FT_AUDIO			= 1,
          FILE_FT_VIDEO			= 2,
          FILE_FT_IMAGE			= 3,
          FILE_FT_PROGRAM			= 4,
          FILE_FT_DOCUMENT		= 5,
          FILE_FT_ARCHIVE			= 6,
          FILE_FT_CDIMAGE			= 7
  };

public:
    explicit Utils(QObject *parent = 0);

signals:

public slots:


public:
    Q_INVOKABLE QString friendlyUnit(quint32 val, bool is_speed);
    Q_INVOKABLE QStringList openFilePicker();
    Q_INVOKABLE QString openFolderPicker();
  Q_INVOKABLE void openFile(QString file);
  Q_INVOKABLE QString getFileName(QString path);
  Q_INVOKABLE void openFolder(QString filePath);
  QImage *   getThumbnailFromMetaData (const struct GNUNET_CONTAINER_MetaData *meta);


  void initFileTable();
  QImage getFileTypeImage(QString extension, int h, int w);
  Q_INVOKABLE QString getFileExtension(QString filename);
private:
    QHash<QString, FileType>m_fileTypeTable;

};

#endif // UTILS_H
