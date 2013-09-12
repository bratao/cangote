#ifndef PUBLISH_H
#define PUBLISH_H



#include <QObject>
#include <QStringList>
#include <QQueue>

#include "core/gnunet/gnunet_includes.h"
#include "core/gnunet/filesharing/publish/publishfile.h"

class PublishModel;
class Publish : public QObject
{
    Q_OBJECT

public:
    struct AddContext{
        Publish* publish;
        GNUNET_FS_DirScanner* m_ds;
        GNUNET_FS_BlockOptions bo;
        bool do_index;

    };

    typedef struct AddFile{
        AddContext* context;
        QString path;
    }AddFile;


private:
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
    Q_INVOKABLE void publishItems();
    void directoryScanCallback(AddContext* context, const char *filename, int is_directory,enum GNUNET_FS_DirScannerProgressUpdateReason reason);


private slots:
    void publishItemsSlot();
    void addFilesSlot(QString path, int anonlevel, int priority, int replication, GNUNET_TIME_Absolute expiration, bool do_index);

signals:
    void addFilesSignal(QString path, int anonlevel, int priority, int replication,GNUNET_TIME_Absolute expiration, bool do_index);
    void publishItemsSignal();

private:
    PublishModel* m_model;
    QQueue<AddFile*> m_queue;
    bool m_isProcessing;
    int m_total;
    int m_done;

    void processResults(AddContext *context, GNUNET_FS_ShareTreeItem *toplevel, PublishFile *parent);
    PublishFile *processFile(AddContext *context, GNUNET_FS_ShareTreeItem *item, PublishFile *parent);
    void addFiles(QString path, int anonlevel, int priority, int replication, GNUNET_TIME_Absolute expiration, bool do_index)
    {
        emit addFilesSignal(path,anonlevel,priority,replication,expiration,do_index);
    }


    void processQueue();
};

#endif // PUBLISH_H
