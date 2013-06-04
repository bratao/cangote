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
#include "models/models.h"
#include "models/PublishModel.h"
#include "core/gnunet/filesharing/filesharing.h"




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
    Publish* publish = (Publish*)cls;
    publish->directoryScanCallback(filename,is_directory,reason);



}

Publish::Publish(QObject *parent) :
    QObject(parent)
{
    m_model = theApp->models()->publishModel();
    m_total = 0;
    m_done=0;


}

void Publish::filePicker()
{
    emit filePickerSignal();
}


void Publish::filePickerSlot()
{
    QStringList fileNames;


    QFileDialog dialog;

    //Add button
    QFormLayout *columnLayout1 = new QFormLayout;
    QFormLayout *columnLayout2 = new QFormLayout;
    QHBoxLayout * rowLayout = new QHBoxLayout;

    QLabel* expirationLabel = new QLabel(tr("Expiration:"),&dialog);
    QComboBox* expirationCombo = new QComboBox(&dialog);
    expirationCombo->addItem("Expire in 6 months");
    expirationCombo->addItem("Expire in 1 year");
    expirationCombo->addItem("Expire in 2 years");
    expirationCombo->addItem("Expire in 5 years");
    expirationCombo->addItem("Expire in 10 years");

    QLabel* replicationLabel = new QLabel(tr("Replication:"),&dialog);
    QComboBox* replicationCombo = new QComboBox(&dialog);
    replicationCombo->addItem("No replication");
    replicationCombo->addItem("Replicate at least 1 time");
    replicationCombo->addItem("Replicate at least 2 times");
    replicationCombo->addItem("Replicate at least 5 times");

    QLabel* priorityLabel = new QLabel(tr("Priority:"),&dialog);
    QComboBox* priorityCombo = new QComboBox(&dialog);
    priorityCombo->addItem("Low");
    priorityCombo->addItem("Normal");
    priorityCombo->addItem("High");
    priorityCombo->addItem("Highest");


    QLabel* anonLabel = new QLabel(tr("Anonymity:"),&dialog);
    QComboBox* anonCombo = new QComboBox(&dialog);
    anonCombo->addItem("0 - Low");
    anonCombo->addItem("1 - High");
    anonCombo->addItem("2 - Very high");
    anonCombo->addItem("5 - Ultra high");
    anonCombo->addItem("10 - Paranoid");


    QCheckBox* doIndex = new QCheckBox(tr("Index only"),&dialog);

    columnLayout1->addRow(expirationLabel,expirationCombo);
    columnLayout1->addRow(replicationLabel,replicationCombo);
    columnLayout2->addRow(priorityLabel,priorityCombo);
    columnLayout2->addRow(anonLabel,anonCombo);
    columnLayout2->addRow(anonLabel,doIndex);

    rowLayout->addLayout(columnLayout1);
    rowLayout->addLayout(columnLayout2);


    QGridLayout *layout = (QGridLayout*)dialog.layout();
    layout->addLayout(rowLayout,4,0,1,-1);

    //Set mode
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);

    if (dialog.exec())
        fileNames = dialog.selectedFiles();



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

        addFiles(fileName, anonlevel,priority,replication,expiration);
    }
    //return fileNames;

}


void Publish::addFiles(QString path, int anonlevel, int priority, int replication, GNUNET_TIME_Absolute expiration)
{
    char *filename;
    GNUNET_FS_BlockOptions bo;
    int do_index;

    bo.anonymity_level = anonlevel;
    bo.content_priority = priority;
    bo.expiration_time = expiration;
    bo.replication_level = replication;

    //TODO, CREATE an progress window

    /* actually start the scan */
    m_ds = GNUNET_FS_directory_scan_start (path.toLatin1().constData(),
                                           GNUNET_NO, NULL,
                                           &directoryScanStaticCallback, this);




}

void Publish::directoryScanCallback(const char *filename, int is_directory,
                                    enum GNUNET_FS_DirScannerProgressUpdateReason reason)
{

    //struct AddDirClientContext *adcc = cls;
    static struct GNUNET_TIME_Absolute last_pulse;
    char *s;
    double fraction;

    switch (reason)
    {
    case GNUNET_FS_DIRSCANNER_FILE_START:
    {
        GNUNET_assert (NULL != filename);
        if (GNUNET_TIME_absolute_get_duration (last_pulse).rel_value > 100)
        {

            last_pulse = GNUNET_TIME_absolute_get ();
        }

        if (is_directory == GNUNET_YES)
        {
            qWarning() << QString("Scanning directory '%1'.").arg(filename);
        }
        else
            m_total++;
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
        qWarning() << QString("%1/%2 (%3 %)").arg(m_done).arg(m_total).arg(100.0 * fraction);
        break;
    }
    case GNUNET_FS_DIRSCANNER_EXTRACT_FINISHED:
    {
        GNUNET_assert (NULL != filename);

        qWarning() << QString("Processed file '%1'").arg(filename);
        m_done++;
        GNUNET_assert (m_done <= m_total);
        fraction = (m_total == 0) ? 1.0 : (1.0 * m_done) / m_total;
        qWarning() << QString("%1/%2 (%3 %)").arg(m_done).arg(m_total).arg(100.0 * fraction);

        break;
    }
    case GNUNET_FS_DIRSCANNER_INTERNAL_ERROR:
    {
        qWarning() << QString("Operation failed");

        GNUNET_FS_directory_scan_abort (m_ds);
        break;
    }
    case GNUNET_FS_DIRSCANNER_FINISHED:
    {
        struct GNUNET_FS_ShareTreeItem *directory_scan_result;

        qWarning() << QString("Scanner has finished.");
        directory_scan_result = GNUNET_FS_directory_scan_get_result (m_ds);
        m_ds = NULL;
        GNUNET_FS_share_tree_trim (directory_scan_result);
        //add_share_items_to_treestore (adcc,
        //                              directory_scan_result,
        //                              NULL);
        GNUNET_FS_share_tree_free (directory_scan_result);
        //destroy_progress_dialog (adcc);
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
Publish::processResults (struct GNUNET_FS_ShareTreeItem *toplevel,
                         void *parent_iter)
{


    struct GNUNET_FS_ShareTreeItem *item;

    for (item = toplevel; NULL != item; item = item->next)
    {
        processFile(item, parent_iter);
        if (item->is_directory == GNUNET_YES){
            qWarning() << "TODO: implement folder support !";
            //TODO:: FOlder
            //processResults (item->children_head);
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

void
Publish::processFile (struct GNUNET_FS_ShareTreeItem *item,
                      void *parent)
{


    //m_model->addFile(file);





    char *file_size_fancy;
    struct GNUNET_FS_FileInformation *fi;

    uint64_t fsize;



    if ((item->is_directory != GNUNET_YES) && (GNUNET_OK !=
                                               GNUNET_DISK_file_size (item->filename, &fsize, GNUNET_YES, GNUNET_YES)))
        return;


    if (item->is_directory == GNUNET_YES)
    {
        // update meta data mime type (force to be GNUnet-directory)
        if (NULL != item->meta)
            GNUNET_CONTAINER_meta_data_delete (item->meta,
                                               EXTRACTOR_METATYPE_MIMETYPE, NULL, 0);
        else
            item->meta = GNUNET_CONTAINER_meta_data_create ();
        GNUNET_FS_meta_data_make_directory (item->meta);

        /*fi = GNUNET_FS_file_information_create_empty_directory (theApp->gnunet()->filesharing()->fsHandle(),
                                                                NULL,
                                                                item->ksk_uri,
                                                                item->meta,
                                                                &adcc->directory_scan_bo,
                                                                item->filename);*/
        file_size_fancy = GNUNET_strdup ("-");
    }
    else
    {
        /*fi = GNUNET_FS_file_information_create_from_file (theApp->gnunet()->filesharing()->fsHandle(),
                                                          NULL,
                                                          item->filename,
                                                          item->ksk_uri,
                                                          item->meta,
                                                          adcc->directory_scan_do_index,
                                                          &adcc->directory_scan_bo);*/
        file_size_fancy = GNUNET_STRINGS_byte_size_fancy (fsize);
    }
    //file_size_fancy
    //adcc->directory_scan_do_index
    //item->short_filename
    //adcc->directory_scan_bo.anonymity_level
    //adcc->directory_scan_bo.content_priority
    //adcc->directory_scan_bo.expiration_time.abs_value
    //adcc->directory_scan_bo.replication_level

    GNUNET_free (file_size_fancy);
}



