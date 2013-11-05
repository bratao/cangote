#include "publish.h"
#include "cangote.h"


#include <QString>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>


#include "core/cangotecore.h"
#include "core/status.h"
#include "models/models.h"
#include "models/PublishModel.h"

#include "core/gnunet/filesharing/filesharing.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/filesharing/publish/publishfile.h"







/**
 * Progress callback called from the directory scanner with
 * information about our progress scanning the hierarchy.
 *
 * @param cls  progress dialog context of our window
 * @param filename filename this update is about, can be NULL
 * @param is_directory is this file a directory, SYSERR if not applicable
 * @param reason kind of progress that was made
 */
static void
directoryScanStaticCallback (void *cls,
                             const char *filename, int is_directory,
                             enum GNUNET_FS_DirScannerProgressUpdateReason reason)
{
    Publish* publish = ((Publish::AddContext*)cls)->publish;
    publish->directoryScanCallback((Publish::AddContext*)cls,filename,is_directory,reason);



}

Publish::Publish(QObject *parent) :
    QObject(parent)
{
    m_model = theApp->models()->publishModel();
    m_isProcessing = false;

    qRegisterMetaType<GNUNET_TIME_Absolute>("GNUNET_TIME_Absolute");

    //Connect cross-thread signals
    connect(this,&Publish::addFilesSignal,this,&Publish::addFilesSlot);
    connect(this,&Publish::publishItemsSignal,this,&Publish::publishItemsSlot);

    m_done =0;
    m_total = 0;

}

/*
 * This function must be executed from the GUI thread.
 */
void Publish::filePicker()
{
    QStringList fileNames;



    QDialog* dialog = new QDialog();

    QFileDialog* filePicker = new QFileDialog;

    //Add button
    QFormLayout *columnLayout1 = new QFormLayout;
    QFormLayout *columnLayout2 = new QFormLayout;
    QHBoxLayout * rowLayout = new QHBoxLayout;
    QVBoxLayout * columnLayout = new QVBoxLayout;

    QLabel* expirationLabel = new QLabel(tr("Expiration:"),filePicker);
    QComboBox* expirationCombo = new QComboBox(filePicker);
    expirationCombo->addItem("Expire in 6 months");
    expirationCombo->addItem("Expire in 1 year");
    expirationCombo->addItem("Expire in 2 years");
    expirationCombo->addItem("Expire in 5 years");
    expirationCombo->addItem("Expire in 10 years");
    expirationCombo->setCurrentIndex(1);

    QLabel* replicationLabel = new QLabel(tr("Replication:"),filePicker);
    QComboBox* replicationCombo = new QComboBox(filePicker);
    replicationCombo->addItem("No replication");
    replicationCombo->addItem("Replicate at least 1 time");
    replicationCombo->addItem("Replicate at least 2 times");
    replicationCombo->addItem("Replicate at least 5 times");
    replicationCombo->setCurrentIndex(1);


    QLabel* priorityLabel = new QLabel(tr("Priority:"),filePicker);
    QComboBox* priorityCombo = new QComboBox(filePicker);
    priorityCombo->addItem("Low");
    priorityCombo->addItem("Normal");
    priorityCombo->addItem("High");
    priorityCombo->addItem("Highest");
    priorityCombo->setCurrentIndex(1);


    QLabel* anonLabel = new QLabel(tr("Anonymity:"),filePicker);
    QComboBox* anonCombo = new QComboBox(filePicker);
    anonCombo->addItem("0 - Low");
    anonCombo->addItem("1 - High");
    anonCombo->addItem("2 - Very high");
    anonCombo->addItem("5 - Ultra high");
    anonCombo->addItem("10 - Paranoid");
    anonCombo->setCurrentIndex(0);

    QLabel* indexLabel = new QLabel(tr("Index:"),filePicker);
    QCheckBox* doIndex = new QCheckBox(tr("Index only"),filePicker);
    doIndex->setChecked(true);

    columnLayout1->addRow(expirationLabel,expirationCombo);
    columnLayout1->addRow(replicationLabel,replicationCombo);
    columnLayout2->addRow(priorityLabel,priorityCombo);
    columnLayout2->addRow(anonLabel,anonCombo);
    columnLayout2->addRow(indexLabel,doIndex);


    rowLayout->addLayout(columnLayout1);
    rowLayout->addLayout(columnLayout2);

    columnLayout->addWidget(filePicker);
    columnLayout->addLayout(rowLayout);


    //QGridLayout *layout = (QGridLayout*)dialog.layout();
    //layout->addLayout(rowLayout,4,0,1,-1);

    dialog->setLayout(columnLayout);

    //Set mode
    filePicker->setFileMode(QFileDialog::ExistingFiles);
    filePicker->setViewMode(QFileDialog::Detail);
    filePicker->setOption(QFileDialog::DontUseNativeDialog, true);

    /*if (filePicker->exec())
        fileNames = filePicker->selectedFiles();
    */


    QObject::connect(filePicker,&QFileDialog::accepted,dialog,&QDialog::accept );
    QObject::connect(filePicker,&QFileDialog::rejected,dialog,&QDialog::reject );


    if (dialog->exec())
      fileNames = filePicker->selectedFiles();


    //Get the values
    int anonlevel;
    int priority;
    int replication;
    GNUNET_TIME_Absolute expiration;

    //Expiration
    switch(expirationCombo->currentIndex())
    {
    case SIXMONTHS_EXPIRATION:
        expiration =  GNUNET_TIME_relative_to_absolute (GNUNET_TIME_relative_multiply(GNUNET_TIME_UNIT_MONTHS,6));
        break;
    case ONEYEAR_EXPIRATION:
        expiration = GNUNET_TIME_relative_to_absolute (GNUNET_TIME_relative_multiply(GNUNET_TIME_UNIT_YEARS,1));
        break;
    case TWOYEARS_EXPIRATION:
        expiration = GNUNET_TIME_relative_to_absolute (GNUNET_TIME_relative_multiply(GNUNET_TIME_UNIT_YEARS,2));
        break;
    case FIVEYEARS_EXPIRATION:
        expiration = GNUNET_TIME_relative_to_absolute (GNUNET_TIME_relative_multiply(GNUNET_TIME_UNIT_YEARS,5));
        break;
    case TENYEARS_EXPIRATION:
        expiration = GNUNET_TIME_relative_to_absolute (GNUNET_TIME_relative_multiply(GNUNET_TIME_UNIT_YEARS,10));
        break;
    default:
        expiration = GNUNET_TIME_relative_to_absolute (GNUNET_TIME_relative_multiply(GNUNET_TIME_UNIT_YEARS,1));
        break;
    }

    //Replication
    switch(replicationCombo->currentIndex())
    {
    case NO_REPLICATION:
        replication = 0;
        break;
    case ONE_REPLICATION:
        replication = 1;
        break;
    case TWO_REPLICATION:
        replication = 2;
        break;
    case FIVE_REPLICATION:
        replication = 5;
        break;
    default:
        replication = 1;
        break;
    }

    //Priority
    switch(priorityCombo->currentIndex())
    {
    case LOW_PRIORITY:
        priority = 0;
        break;
    case NORMAL_PRIORITY:
        priority = 1;
        break;
    case HIGH_PRIORITY:
        priority = 2;
        break;
    case HIGHEST_PRIORITY:
        priority = 5;
        break;

    default:
        priority = 1;
        break;
    }

    //Anonimity
    switch(anonCombo->currentIndex())
    {
    case LOW_ANONIMITY:
        anonlevel = 0;
        break;
    case MEDIUM_ANONIMITY:
        anonlevel = 1;
        break;
    case HIGH_ANONIMITY:
        anonlevel = 2;
        break;
    case ULTRAHIGH_ANONIMITY:
        anonlevel = 5;
        break;
    case PARANOID_ANONIMITY:
        anonlevel = 10;
        break;
    default:
        anonlevel = 1;
        break;
    }

    for(QString fileName : fileNames)
    {

        addFiles(fileName, anonlevel,priority,replication,expiration, doIndex->isChecked());
    }
    //return fileNames;

}




/**
 * The user pushed the 'execute' button.  Start the publishing
 * operation.
 *
 */
void
Publish::publishItems()
{
    emit publishItemsSignal();
}


/**
 * Publish Slot
 *
 *
 */
void
Publish::publishItemsSlot ()
{

  const char *namespace_id,*namespace_uid;
  struct GNUNET_IDENTITY_Ego *ns;
  struct GNUNET_FS_FileInformation *fi;

  bool do_global;
  bool do_updateable;
  bool do_own;
  bool disable_ads_insertion;


  //TODO:: Implement namespace
  do_global = true;
  do_updateable = false;
  do_own = false;

  //TODO:: add disable automatic namespace insertion
  disable_ads_insertion =  false;

  ns = NULL;
  namespace_id = NULL;
  namespace_uid = NULL;





  for(int i =0 ; i < m_model->getCount();i++)
  {
      PublishFile* file =  m_model->getPublishedFile(i);

      fi = file->getFileInformation();
      //if (do_global && do_own && !disable_ads_insertion)
      //  GNUNET_FS_file_information_inspect (fi, insert_advertisement, ctx);
      GNUNET_FS_publish_start (theApp->gnunet()->filesharing()->fsHandle(),
                   fi,
                   (NULL == ns)
                   ? NULL
                   : GNUNET_IDENTITY_ego_get_private_key (ns),
                   namespace_id, namespace_uid,
                   GNUNET_FS_PUBLISH_OPTION_NONE);


  }


  m_model->clean();


  //GNUNET_break (GNUNET_YES == close_master_publish_dialog (ctx));
}




/*
 * This function must be executed from the GNUNET thread.
 */

void Publish::addFilesSlot(QString path, int anonlevel, int priority, int replication, GNUNET_TIME_Absolute expiration, bool do_index)
{

    AddContext* ctx = new AddContext;

    ctx->bo.anonymity_level = anonlevel;
    ctx->bo.content_priority = priority;
    ctx->bo.expiration_time = expiration;
    ctx->bo.replication_level = replication;

    ctx->do_index = do_index;

    //TODO, CREATE an progress window

    /* actually start the scan */


    ctx->publish = this;


    AddFile* file = new AddFile;
    file->context = ctx;
    file->path = path;
    m_queue.enqueue(file);
    m_total++;

    processQueue();




}

/**
 * @brief This function will process another file in the queue if we are not processing any.
 */
void Publish::processQueue(){


    if(m_isProcessing)
        return; //We already processing, return.

    if(m_queue.isEmpty())
    {
        m_done = 0;
        m_total = 0;
        theApp->status()->setPublishing(false);
        return;
    }

    theApp->status()->setPublishing(true);
    m_isProcessing = true;


    AddFile* file = m_queue.dequeue();
    qWarning() << QString("process queue send '%1'.").arg(file->path);
    file->context->m_ds = GNUNET_FS_directory_scan_start (file->path.toUtf8().constData(),
                                                         GNUNET_NO, NULL,
                                                         &directoryScanStaticCallback, file->context);
}


void Publish::directoryScanCallback(AddContext* context, const char *filename, int is_directory,
                                    enum GNUNET_FS_DirScannerProgressUpdateReason reason)
{

    static struct GNUNET_TIME_Absolute last_pulse;
    double fraction;

    switch (reason)
    {
    case GNUNET_FS_DIRSCANNER_FILE_START:
    {
        GNUNET_assert (NULL != filename);

        if (GNUNET_TIME_absolute_get_duration (last_pulse).rel_value_us > 100000LL)
        {

            last_pulse = GNUNET_TIME_absolute_get ();
        }

        if (is_directory == GNUNET_YES)
        {
            qWarning() << QString("Scanning directory '%1'.").arg(filename);
        }
        break;
    }

    case GNUNET_FS_DIRSCANNER_FILE_IGNORED:
    {
        GNUNET_assert (NULL != filename);
        qWarning() << QString("Failed to scan '%1' (access error). Skipping.").arg(filename);
        break;
    }
    case GNUNET_FS_DIRSCANNER_ALL_COUNTED:
    {
        fraction = (m_total == 0) ? 1.0 : (1.0 * m_done) / m_total;
        theApp->status()->setPublishingPercentage(100.0 * fraction);
        break;
    }
    case GNUNET_FS_DIRSCANNER_EXTRACT_FINISHED:
    {
        GNUNET_assert (NULL != filename);

        qWarning() << QString("Processed file '%1'").arg(filename);
        fraction = (m_total == 0) ? 1.0 : (1.0 * m_done) / m_total;
        theApp->status()->setPublishingPercentage(100.0 * fraction);
        break;
    }
    case GNUNET_FS_DIRSCANNER_INTERNAL_ERROR:
    {
        qWarning() << QString("Operation failed");
        //GNUNET_FS_directory_scan_abort (context->m_ds);
        m_isProcessing = false;
        processQueue();

        break;
    }
    case GNUNET_FS_DIRSCANNER_FINISHED:
    {
        struct GNUNET_FS_ShareTreeItem *directory_scan_result;
        qWarning() << QString("Scanner has finished.");
        directory_scan_result = GNUNET_FS_directory_scan_get_result (context->m_ds);
        context->m_ds = NULL;
        GNUNET_FS_share_tree_trim (directory_scan_result);
        processResults(context,directory_scan_result,NULL);
        GNUNET_FS_share_tree_free (directory_scan_result);

        m_isProcessing = false;
        m_done++;
        processQueue();


        delete context;

    }
        break;
    default:
        GNUNET_break (0);
        break;
    }
}
/**
 * Recursively traverse the share tree and add it to the tree store
 *
 * @param adcc  progress dialog context of our window
 * @param toplevel root of the tree to add
 * @param parent_iter parent of the current entry to add
 */
void
Publish::processResults (AddContext* context, struct GNUNET_FS_ShareTreeItem *toplevel,
                         PublishFile * parent)
{


    struct GNUNET_FS_ShareTreeItem *item;

    for (item = toplevel; NULL != item; item = item->next)
    {
        PublishFile * file = processFile(context, item, parent);
        if (item->is_directory == GNUNET_YES){
            qWarning() << "TODO: implement folder support !";
            processResults (context,item->children_head,file);
        }
    }

}




/**
 * Convert a single item from the scan to an entry in the tree view.
 *
 * @param adcc progress dialog context of our window
 * @param ts tree store to add an item to
 * @param item scanned item to add
 * @param parent of the item, can be NULL (for root)
 * @param sibling predecessor of the item, can be NULL (for first)
 * @param item_iter entry to set to the added item (OUT)
 */

PublishFile*
Publish::processFile (AddContext* context, struct GNUNET_FS_ShareTreeItem *item,
                      PublishFile* parent)
{
    struct GNUNET_FS_FileInformation *fi;

    uint64_t fsize;

    if ((item->is_directory != GNUNET_YES) && (GNUNET_OK !=
                                               GNUNET_DISK_file_size (item->filename, &fsize, GNUNET_YES, GNUNET_YES)))
        return NULL;


    if (item->is_directory == GNUNET_YES)
    {
        // update meta data mime type (force to be GNUnet-directory)
        if (NULL != item->meta)
            GNUNET_CONTAINER_meta_data_delete (item->meta,
                                               EXTRACTOR_METATYPE_MIMETYPE, NULL, 0);
        else
            item->meta = GNUNET_CONTAINER_meta_data_create ();
        GNUNET_FS_meta_data_make_directory (item->meta);

        fi = GNUNET_FS_file_information_create_empty_directory (theApp->gnunet()->filesharing()->fsHandle(),
                                                                NULL,
                                                                item->ksk_uri,
                                                                item->meta,
                                                                &context->bo,
                                                                item->filename);
    }
    else
    {
        fi = GNUNET_FS_file_information_create_from_file (theApp->gnunet()->filesharing()->fsHandle(),
                                                          NULL,
                                                          item->filename,
                                                          item->ksk_uri,
                                                          item->meta,
                                                          context->do_index,
                                                          &context->bo);
    }


    return m_model->add(item->filename,fi,parent);

}



