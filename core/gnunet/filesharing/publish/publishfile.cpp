#include "publishfile.h"
#include "core/gnunet/gnunet_includes.h"

#include <QImage>
#include <QDebug>

#include "core/cangotecore.h"
#include "cangote.h"
#include "utils/utils.h"
#include "models/MetadataModel.h"
#include "models/KeywordModel.h"
///////// STATIC FUNCTIONS END/////////////


/**
 * Static Function called to extract the information from FI to populate the clas.
 */
static int
file_information_import_callback (void *cls,
                                  struct GNUNET_FS_FileInformation *fi,
                                  uint64_t length,
                                  struct GNUNET_CONTAINER_MetaData *meta,
                                  struct GNUNET_FS_Uri **uri,
                                  struct GNUNET_FS_BlockOptions *bo, int *do_index,
                                  void **client_info)
{
    PublishFile* publish = (PublishFile*)cls;

    publish->fileInformationImport(fi,length,meta,uri,bo,do_index,client_info);

}

static int
addMetadataCallBack (void *cls, const char *plugin_name,
                     enum EXTRACTOR_MetaType type,
                     enum EXTRACTOR_MetaFormat format,
                     const char *data_mime_type,
                     const char *data, size_t data_len)
{
    PublishFile* publish = (PublishFile*)cls;

    publish->addMetadata(plugin_name,type,format,data_mime_type,data,data_len);

    return 0; // Zero to continue
}

static int
addKeywordCallback (void *cls, const char *keyword, int is_mandatory)
{
    Q_UNUSED(is_mandatory);
    PublishFile* publish = (PublishFile*)cls;

    publish->addKeyword(QString(keyword));

    return GNUNET_OK;
}

///////// STATIC FUNCTIONS END/////////////





PublishFile::PublishFile(QString filename, GNUNET_FS_FileInformation *fi, PublishFile* parent_file, QObject *parent) :
    QObject(parent)
{

    m_metadataModel = new MetaModel();
    m_keywordModel = new KeywordModel();

    //Those objects need to live on the main thread.Because QML cannot connect to forgein threads.
    m_metadataModel->moveToThread(theApp->thread());
    m_keywordModel->moveToThread(theApp->thread());


    m_thumbnail = NULL;

    m_fi = fi;
    m_parent = parent_file;
    setFileName(filename);
    setHaveThumbnail(false);

    inpectInfo();
}


\
/**
 * @brief Inspect the information present in the GNUNET_FS_FileInformation and fill the class members
 */
void PublishFile::inpectInfo()
{
    /* import meta data and options */
    GNUNET_FS_file_information_inspect (m_fi, &file_information_import_callback, this);


}


int PublishFile::fileInformationImport ( struct GNUNET_FS_FileInformation *fi,
                                         uint64_t length,
                                         struct GNUNET_CONTAINER_MetaData *meta,
                                         struct GNUNET_FS_Uri **uri,
                                         struct GNUNET_FS_BlockOptions *bo, int *do_index,
                                         void **client_info)
{
    Q_UNUSED(client_info);
    Q_UNUSED(fi);

    setExpiration(bo->expiration_time.abs_value_us);
    setAnonLevel(bo->anonymity_level);
    setPriority(bo->content_priority);
    setReplication(bo->replication_level);
    setIndexed(*do_index);
    setFileSize(length);
    setDirectory(GNUNET_FS_file_information_is_directory (m_fi));

    /* import keywords */
    if (NULL != *uri)
        GNUNET_FS_uri_ksk_get_keywords (*uri, &addKeywordCallback, this);

    /* import meta data */
    if (NULL != meta)
    {
        GNUNET_CONTAINER_meta_data_iterate (meta,
                                            &addMetadataCallBack,
                                            this);
        m_thumbnail = theUtils->getThumbnailFromMetaData( meta);
        if (m_thumbnail == NULL)
        {
            setHaveThumbnail(false);
        }
        else{
            setHaveThumbnail(true);
        }

    }


    return GNUNET_SYSERR;         /* only visit top-level item */
}

/**
 * Add meta data to list store.
 *
 * @param plugin_name name of the plugin that produced this value;
 *        special values can be used (i.e. '<zlib>' for zlib being
 *        used in the main libextractor library and yielding
 *        meta data).
 * @param type libextractor-type describing the meta data
 * @param format basic format information about data
 * @param data_mime_type mime-type of data (not of the original file);
 *        can be NULL (if mime-type is not known)
 * @param data actual meta-data found
 * @param data_len number of bytes in data
 * @return 0 to continue (always)
 */
int
PublishFile::addMetadata (const char *plugin_name,
                          EXTRACTOR_MetaType type,
                          EXTRACTOR_MetaFormat format,
                          const char *data_mime_type,
                          const char *data, size_t data_len)
{

    QString name = QString(EXTRACTOR_metatype_to_string (type));
    QString value = QString(data);
    m_metadataModel->add(name,value);
}


/**
 * Add each of the keywords to the keyword list store.
 *
 * @param keyword the keyword
 * @param is_mandatory is the keyword mandatory (in a search)
 */
void
PublishFile::addKeyword (QString keyword)
{

    m_keywordModel->add(keyword);
}


