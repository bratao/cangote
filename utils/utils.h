#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = 0);

signals:

public slots:


public:
    Q_INVOKABLE QString friendlyUnit(quint32 val, bool is_speed);
    Q_INVOKABLE QString openFilePicker();
    Q_INVOKABLE QString openFolderPicker();
    Q_INVOKABLE void openFile(QString file);
};

#endif // UTILS_H