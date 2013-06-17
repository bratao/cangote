#ifndef PUBLISHFILE_H
#define PUBLISHFILE_H

#include <QObject>

class PublishFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(int fileSize READ fileSize WRITE setFileSize NOTIFY fileSizeChanged)
    Q_PROPERTY(bool indexed READ indexed WRITE setIndexed NOTIFY indexedChanged)
    Q_PROPERTY(bool directory READ directory WRITE setDirectory)
    Q_PROPERTY(int anonLevel READ anonLevel WRITE setAnonLevel NOTIFY anonLevelChanged)
    Q_PROPERTY(int priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PROPERTY(unsigned int expiration READ expiration WRITE setExpiration NOTIFY expirationChanged)
    Q_PROPERTY(int replication READ replication WRITE setReplication NOTIFY replicationChanged)



public:
    QString fileName() const
    { return m_filename; }

    void setFileName(QString name)
    {
        m_filename = name;
        emit fileNameChanged(name);
    }

    int fileSize() const
    { return m_filesize; }

    void setFileName(int size)
    {
        m_filename = size;
        emit fileSizeChanged(size);
    }

    bool indexed() const
    { return m_indexed; }

    void setIndexed(bool indexed)
    {
        m_indexed = indexed;
        emit indexedChanged(indexed);
    }

    bool directory() const
    { return m_directory; }

    void setDirectory(bool directory)
    {
        m_directory = directory;
    }


    int anonLevel() const
    { return m_anonLevel; }

    void setAnonLevel(int anon)
    {
        m_anonLevel = anon;
        emit anonLevelChanged(anon);
    }

    int priority() const
    { return m_priority; }

    void setPriority(int priority)
    {
        m_priority = priority;
        emit priorityChanged(priority);
    }

    unsigned int expiration() const
    { return m_expiration; }

    void setExpiration(unsigned int expiration)
    {
        m_expiration = expiration;
        emit expirationChanged(expiration);
    }

    int replication() const
    { return m_replication; }

    void setReplication(int replication)
    {
        m_replication = replication;
        emit replicationChanged(replication);
    }




public:
    explicit PublishFile(GNUNET_FS_FileInformation *fi, QString filename, PublishFile* parent_file, QObject *parent = 0);
    
    QString getFilename();
    int fileInformationImport(GNUNET_FS_FileInformation *fi, uint64_t length, GNUNET_CONTAINER_MetaData *meta, GNUNET_FS_Uri **uri, GNUNET_FS_BlockOptions *bo, int *do_index, void **client_info);
signals:

    void fileNameChanged(QString filename);
    void fileSizeChanged(int size);
    void indexedChanged(bool indexed);
    void anonLevelChanged(int anonLevel);
    void priorityChanged(int priority);
    void expirationChanged(unsigned int expiration);
    void replicationChanged(int replication);


    
public slots:

private:
    struct GNUNET_FS_FileInformation *m_fi;
    PublishFile* m_parent;
    QString m_filename;
    int m_filesize;
    bool m_indexed;
    bool m_directory;
    int m_anonLevel;
    int m_priority;
    unsigned int m_expiration;
    int m_replication;
    QImage *getThumbnail(const struct GNUNET_CONTAINER_MetaData *meta);
};

#endif // PUBLISHFILE_H
