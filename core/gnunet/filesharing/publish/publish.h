#ifndef PUBLISH_H
#define PUBLISH_H



#include <QObject>
#include <QStringList>

#include "core/gnunet/gnunet_includes.h"

class PublishModel;
class Publish : public QObject
{
    Q_OBJECT






    enum Expiration{
        SIXMONTHS_EXPIRATION,
        ONEYEAR_EXPIRATION,
        TWOYEARS_EXPIRATION,
        FIVEYEARS_EXPIRATION,
        TENYEARS_EXPIRATION

    };

    enum Replication{
        NO_REPLICATION,
        ONE_REPLICATION,
        TWO_REPLICATION,
        FIVE_REPLICATION
    };

    enum Priority{
        LOW_PRIORITY,
        NORMAL_PRIORITY,
        HIGH_PRIORITY,
        HIGHEST_PRIORITY
    };

    enum AnonLevel{
        LOW_ANONIMITY,
        MEDIUM_ANONIMITY,
        HIGH_ANONIMITY,
        ULTRAHIGH_ANONIMITY,
        PARANOID_ANONIMITY

    };

public:
    explicit Publish(QObject *parent = 0);
    
    Q_INVOKABLE void filePicker();
signals:
    void filePickerSignal();
public slots:


public:
    void directoryScanCallback(const char *filename, int is_directory,enum GNUNET_FS_DirScannerProgressUpdateReason reason);

private slots:
    void filePickerSlot();
private:
    PublishModel* m_model;
    


    int m_total;
    int m_done;
    GNUNET_FS_DirScanner * m_ds;
    void processResults(GNUNET_FS_ShareTreeItem *toplevel, void *parent_iter);
    void processFile(GNUNET_FS_ShareTreeItem *item, void *parent);
    void addFiles(QString path, int anonlevel, int priority, int replication, GNUNET_TIME_Absolute expiration);
};

#endif // PUBLISH_H
