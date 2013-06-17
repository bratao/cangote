#include "publishfile.h"
#include "core/gnunet/gnunet_includes.h"

#include <QImage>

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

}

///////// STATIC FUNCTIONS END/////////////





PublishFile::PublishFile(GNUNET_FS_FileInformation *fi, QString filename, PublishFile* parent_file, QObject *parent) :
    QObject(parent)
{
    m_fi = fi;
    m_parent = parent_file;
    setFileName(filename);

    inpectInfo();
}


\
/**
 * @brief Inspect the information present in the GNUNET_FS_FileInformation and fill the class members
 */
void PublishFile::inpectInfo()
{
    /* import meta data and options */
    GNUNET_FS_file_information_inspect (fip, &file_information_import_callback, ctx);

    setDirectory(GNUNET_FS_file_information_is_directory (fip));
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

    setExpiration(bo->expiration_time);
    setAnonLevel(bo->anonymity_level);
    setPriority(bo->content_priority);
    setReplication(bo->replication_level);
    setIndexed(*do_index);
    setSize(length);

    /* import keywords */
    if (NULL != *uri)
        GNUNET_FS_uri_ksk_get_keywords (*uri, &add_keyword, ctx->keywords_liststore);

    /* import meta data */
    if (NULL != meta)
    {
        GNUNET_CONTAINER_meta_data_iterate (meta,
                                            &GNUNET_FS_GTK_add_meta_data_to_list_store,
                                            ctx->meta_liststore);
        pixbuf = GNUNET_FS_GTK_get_thumbnail_from_meta_data (meta);
        if (pixbuf != NULL)
        {
            qWarning()<< "Create the thumbnail support";
        }
    }


    return GNUNET_SYSERR;         /* only visit top-level item */
}

/**
 * Add meta data to list store.
 *
 * @param cls closure (the GtkListStore)
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
                                           enum EXTRACTOR_MetaType type,
                                           enum EXTRACTOR_MetaFormat format,
                                           const char *data_mime_type,
                                           const char *data, size_t data_len)
{

    type
    format
    EXTRACTOR_metatype_to_string (type)
            data, data_len

    return 0; // Zero to continue
}

/**
 * Obtain pixbuf from thumbnail data in meta data.
 *
 * @param meta input meta data
 * @return NULL on error, otherwise the embedded thumbnail
 */
QImage *
PublishFile::getThumbnail (const GNUNET_CONTAINER_MetaData *meta)
{
    size_t ts;
    unsigned char *thumb;

    thumb = NULL;
    ts = GNUNET_CONTAINER_meta_data_get_thumbnail (meta, &thumb);
    if (0 == ts)
        return NULL;

    QImage* image = new QImage();
    image->loadFromData(thumb,ts);

    GNUNET_free (thumb);
    return image;
}
