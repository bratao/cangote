#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QStringList>
class Utils : public QObject
{
    Q_OBJECT
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

};

#endif // UTILS_H
