#include "utils.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QComboBox>
#include <QGridLayout>
#include <QFormLayout>
#include <QLabel>
#include <QProcess>


#include "cangote.h"
#include "core/gnunet/gnunet_includes.h"

Utils::Utils(QObject *parent) :
  QObject(parent)
{
  initFileTable();
}


// return best userfriendly storage unit (B, KiB, MiB, GiB, TiB)
// use Binary prefix standards from IEC 60027-2
// see http://en.wikipedia.org/wiki/Kilobyte
// value must be given in bytes
QString Utils::friendlyUnit(quint32 val, bool is_speed) {

  qreal convertedVal = val;
  if (convertedVal < 0)
    return tr("Unknown", "Unknown (size)");
  int i = 0;
  while(convertedVal >= 1024. && i++<6)
    convertedVal /= 1024.;
  QString ret;
  if (i == 0)
    ret = QString::number((long)convertedVal) + " " + tr("B");
  else if (i == 1)
    ret = QString::number(convertedVal, 'f', 2) + " " + tr("KB");
  else if (i == 2)
    ret = QString::number(convertedVal, 'f', 2) + " " + tr("MB");
  else if (i == 3)
    ret = QString::number(convertedVal, 'f', 2) + " " + tr("GB");
  else if (i == 4)
    ret = QString::number(convertedVal, 'f', 2) + " " + tr("PB");

  if (is_speed)
    ret += tr("/s", "per second");
  return ret;
}


QStringList Utils::openFilePicker()
{
  return QFileDialog::getOpenFileNames(NULL,
                                       tr("Pick Files"), NULL, NULL);

}

QString Utils::openFolderPicker()
{
  return QFileDialog::getExistingDirectory(NULL,
                                           tr("Pick Folder"), NULL, QFileDialog::DontUseNativeDialog| QFileDialog::ShowDirsOnly);
}

void Utils::openFile(QString file)
{
  QString path;
  path = QString("file:///") + file;
  QDesktopServices::openUrl(QUrl(path));
}

void Utils::openFolder(QString filePath)
{
#if defined(Q_WS_MAC)
  QStringList args;
  args << "-e";
  args << "tell application \"Finder\"";
  args << "-e";
  args << "activate";
  args << "-e";
  args << "select POSIX file \""+filePath+"\"";
  args << "-e";
  args << "end tell";
  QProcess::startDetached("osascript", args)

    #elif defined(Q_OS_WIN)
  QStringList args;
  args << "/select," << QDir::toNativeSeparators(filePath);
  QProcess::startDetached("explorer", args);
#endif

  //TODO:: Implement linux suport for opening Folder
}

QString Utils::getFileName(QString path){
  QFileInfo fi(path);
  QString name = fi.fileName();
  return name;
}

QString Utils::getFileExtension(QString filename){
  QFileInfo fi(filename);
  QString name = fi.suffix();
  return name;
}

/**
 * Obtain pixbuf from thumbnail data in meta data.
 *
 * @param meta input meta data
 * @return NULL on error, otherwise the embedded thumbnail
 */
QImage * Utils::getThumbnailFromMetaData (const GNUNET_CONTAINER_MetaData *meta)
{
  size_t ts;
  unsigned char *thumb;

  thumb = NULL;
  ts = GNUNET_CONTAINER_meta_data_get_thumbnail (meta, &thumb);
  if (0 == ts)
    return NULL;

  QImage* image = new QImage();
  if(!image->loadFromData(thumb,ts))
    {
      delete image;
      image = NULL;
    }

  GNUNET_free (thumb);


  return image;
}



/**
  * @brief Utils::initFileTable
  * Stole from emule-project
  */
void Utils::initFileTable ()
{
  m_fileTypeTable["aac"] = FILE_FT_AUDIO;      // Advanced Audio Coding File
  m_fileTypeTable["ac3"] = FILE_FT_AUDIO;       // Audio Codec 3 File
  m_fileTypeTable["aif"] = FILE_FT_AUDIO;       // Audio Interchange File Format
  m_fileTypeTable["aifc"] = FILE_FT_AUDIO;      // Audio Interchange File Format
  m_fileTypeTable["aiff"] = FILE_FT_AUDIO;      // Audio Interchange File Format
  m_fileTypeTable["alac"] = FILE_FT_AUDIO;      // Apple Lossless Audio Codec File
  m_fileTypeTable["amr"] = FILE_FT_AUDIO;       // Adaptive Multi-Rate Codec File
  m_fileTypeTable["ape"] = FILE_FT_AUDIO;       // Monkey's Audio Lossless Audio File
  m_fileTypeTable["au"] = FILE_FT_AUDIO;        // Audio File (Sun, Unix)
  m_fileTypeTable["aud"] = FILE_FT_AUDIO;       // General Audio File
  m_fileTypeTable["audio"] = FILE_FT_AUDIO;     // General Audio File
  m_fileTypeTable["cda"] = FILE_FT_AUDIO;       // CD Audio Track
  m_fileTypeTable["dmf"] = FILE_FT_AUDIO;       // Delusion Digital Music File
  m_fileTypeTable["dsm"] = FILE_FT_AUDIO;       // Digital Sound Module
  m_fileTypeTable["dts"] = FILE_FT_AUDIO;       // DTS Encoded Audio File
  m_fileTypeTable["far"] = FILE_FT_AUDIO;       // Farandole Composer Module
  m_fileTypeTable["flac"] = FILE_FT_AUDIO;      // Free Lossless Audio Codec File
  m_fileTypeTable["it"] = FILE_FT_AUDIO;        // Impulse Tracker Module
  m_fileTypeTable["m1a"] = FILE_FT_AUDIO;       // MPEG-1 Audio File
  m_fileTypeTable["m2a"] = FILE_FT_AUDIO;       // MPEG-2 Audio File
  m_fileTypeTable["m4a"] = FILE_FT_AUDIO;       // MPEG-4 Audio File
  m_fileTypeTable["mdl"] = FILE_FT_AUDIO;       // DigiTrakker Module
  m_fileTypeTable["med"] = FILE_FT_AUDIO;       // Amiga MED Sound File
  m_fileTypeTable["mid"] = FILE_FT_AUDIO;       // MIDI File
  m_fileTypeTable["midi"] = FILE_FT_AUDIO;      // MIDI File
  m_fileTypeTable["mka"] = FILE_FT_AUDIO;       // Matroska Audio File
  m_fileTypeTable["mod"] = FILE_FT_AUDIO;       // Amiga Music Module File
  m_fileTypeTable["mp1"] = FILE_FT_AUDIO;       // MPEG-1 Audio File
  m_fileTypeTable["mp2"] = FILE_FT_AUDIO;       // MPEG-2 Audio File
  m_fileTypeTable["mp3"] = FILE_FT_AUDIO;       // MPEG-3 Audio File
  m_fileTypeTable["mpa"] = FILE_FT_AUDIO;       // MPEG Audio File
  m_fileTypeTable["mpc"] = FILE_FT_AUDIO;       // Musepack Compressed Audio File
  m_fileTypeTable["mtm"] = FILE_FT_AUDIO;       // MultiTracker Module
  m_fileTypeTable["ogg"] = FILE_FT_AUDIO;       // Ogg Vorbis Compressed Audio File
  m_fileTypeTable["opus"] = FILE_FT_AUDIO;      // Opus Audio File
  m_fileTypeTable["psm"] = FILE_FT_AUDIO;       // Protracker Studio Module
  m_fileTypeTable["ptm"] = FILE_FT_AUDIO;       // PolyTracker Module
  m_fileTypeTable["ra"] = FILE_FT_AUDIO;        // Real Audio File
  m_fileTypeTable["rmi"] = FILE_FT_AUDIO;       // MIDI File
  m_fileTypeTable["s3m"] = FILE_FT_AUDIO;       // Scream Tracker 3 Module
  m_fileTypeTable["shn"] = FILE_FT_AUDIO;       // Shorten Audio File
  m_fileTypeTable["snd"] = FILE_FT_AUDIO;       // Audio File (Sun, Unix)
  m_fileTypeTable["stm"] = FILE_FT_AUDIO;       // Scream Tracker 2 Module
  m_fileTypeTable["tak"] = FILE_FT_AUDIO;       // Tom's Audio-Kompressor File
  m_fileTypeTable["umx"] = FILE_FT_AUDIO;       // Unreal Music Package
  m_fileTypeTable["wav"] = FILE_FT_AUDIO;       // WAVE Audio File
  m_fileTypeTable["w64"] = FILE_FT_AUDIO;       // Sonic Foundry Video Editor Wave64 File
  m_fileTypeTable["wma"] = FILE_FT_AUDIO;       // Windows Media Audio File
  m_fileTypeTable["wv"] = FILE_FT_AUDIO;        // WavPack Audio File
  m_fileTypeTable["xm"] = FILE_FT_AUDIO;        // Fasttracker 2 Extended Module


  m_fileTypeTable["3g2"] = FILE_FT_VIDEO;       // 3GPP Multimedia File
  m_fileTypeTable["3gp"] = FILE_FT_VIDEO;       // 3GPP Multimedia File
  m_fileTypeTable["3gp2"] = FILE_FT_VIDEO;      // 3GPP Multimedia File
  m_fileTypeTable["3gpp"] = FILE_FT_VIDEO;      // 3GPP Multimedia File
  m_fileTypeTable["amv"] = FILE_FT_VIDEO;       // Anime Music Video File
  m_fileTypeTable["asf"] = FILE_FT_VIDEO;       // Advanced Systems Format File
  m_fileTypeTable["avi"] = FILE_FT_VIDEO;       // Audio Video Interleave File
  m_fileTypeTable["bik"] = FILE_FT_VIDEO;       // BINK Video File
  m_fileTypeTable["divx"] = FILE_FT_VIDEO;      // DivX-Encoded Movie File
  m_fileTypeTable["dvr-ms"]= FILE_FT_VIDEO;      // Microsoft Digital Video Recording
  m_fileTypeTable["flc"] = FILE_FT_VIDEO;       // FLIC Video File
  m_fileTypeTable["fli"] = FILE_FT_VIDEO;       // FLIC Video File
  m_fileTypeTable["flic"] = FILE_FT_VIDEO;      // FLIC Video File
  m_fileTypeTable["flv"] = FILE_FT_VIDEO;       // Flash Video File
  m_fileTypeTable["hdmov"] = FILE_FT_VIDEO;     // High-Definition QuickTime Movie
  m_fileTypeTable["ifo"] = FILE_FT_VIDEO;       // DVD-Video Disc Information File
  m_fileTypeTable["m1v"] = FILE_FT_VIDEO;       // MPEG-1 Video File
  m_fileTypeTable["m2t"] = FILE_FT_VIDEO;       // MPEG-2 Video Transport Stream
  m_fileTypeTable["m2ts"] = FILE_FT_VIDEO;      // MPEG-2 Video Transport Stream
  m_fileTypeTable["m2v"] = FILE_FT_VIDEO;       // MPEG-2 Video File
  m_fileTypeTable["m4b"] = FILE_FT_VIDEO;       // MPEG-4 Video File
  m_fileTypeTable["m4v"] = FILE_FT_VIDEO;       // MPEG-4 Video File
  m_fileTypeTable["mkv"] = FILE_FT_VIDEO;       // Matroska Video File
  m_fileTypeTable["mov"] = FILE_FT_VIDEO;       // QuickTime Movie File
  m_fileTypeTable["movie"] = FILE_FT_VIDEO;     // QuickTime Movie File
  m_fileTypeTable["mp1v"] = FILE_FT_VIDEO;      // MPEG-1 Video File
  m_fileTypeTable["mp2v"] = FILE_FT_VIDEO;      // MPEG-2 Video File
  m_fileTypeTable["mp4"] = FILE_FT_VIDEO;       // MPEG-4 Video File
  m_fileTypeTable["mpe"] = FILE_FT_VIDEO;       // MPEG Video File
  m_fileTypeTable["mpeg"] = FILE_FT_VIDEO;      // MPEG Video File
  m_fileTypeTable["mpg"] = FILE_FT_VIDEO;       // MPEG Video File
  m_fileTypeTable["mpv"] = FILE_FT_VIDEO;       // MPEG Video File
  m_fileTypeTable["mpv1"] = FILE_FT_VIDEO;      // MPEG-1 Video File
  m_fileTypeTable["mpv2"] = FILE_FT_VIDEO;      // MPEG-2 Video File
  m_fileTypeTable["ogm"] = FILE_FT_VIDEO;       // Ogg Media File
  m_fileTypeTable["ogv"] = FILE_FT_VIDEO;       // Ogg Video File
  m_fileTypeTable["pva"] = FILE_FT_VIDEO;       // MPEG Video File
  m_fileTypeTable["qt"] = FILE_FT_VIDEO;        // QuickTime Movie
  m_fileTypeTable["ram"] = FILE_FT_VIDEO;       // Real Audio Media
  m_fileTypeTable["ratdvd"] = FILE_FT_VIDEO;      // RatDVD Disk Image
  m_fileTypeTable["rm"] = FILE_FT_VIDEO;        // Real Media File
  m_fileTypeTable["rmm"] = FILE_FT_VIDEO;       // Real Media File
  m_fileTypeTable["rmvb"] = FILE_FT_VIDEO;      // Real Video Variable Bit Rate File
  m_fileTypeTable["rv"] = FILE_FT_VIDEO;        // Real Video File
  m_fileTypeTable["smil"] = FILE_FT_VIDEO;      // SMIL Presentation File
  m_fileTypeTable["smk"] = FILE_FT_VIDEO;       // Smacker Compressed Movie File
  m_fileTypeTable["swf"] = FILE_FT_VIDEO;       // Macromedia Flash Movie
  m_fileTypeTable["tp"] = FILE_FT_VIDEO;        // Video Transport Stream File
  m_fileTypeTable["ts"] = FILE_FT_VIDEO;        // Video Transport Stream File
  m_fileTypeTable["vid"] = FILE_FT_VIDEO;       // General Video File
  m_fileTypeTable["video"] = FILE_FT_VIDEO;     // General Video File
  m_fileTypeTable["vob"] = FILE_FT_VIDEO;       // DVD Video Object File
  m_fileTypeTable["vp6"] = FILE_FT_VIDEO;       // TrueMotion VP6 Video File
  m_fileTypeTable["wm"] = FILE_FT_VIDEO;        // Windows Media Video File
  m_fileTypeTable["wmv"] = FILE_FT_VIDEO;       // Windows Media Video File
  m_fileTypeTable["xvid"] = FILE_FT_VIDEO;      // Xvid-Encoded Video File


  m_fileTypeTable["bmp"] = FILE_FT_IMAGE;       // Bitmap Image File
  m_fileTypeTable["emf"] = FILE_FT_IMAGE;       // Enhanced Windows Metafile
  m_fileTypeTable["gif"] = FILE_FT_IMAGE;       // Graphical Interchange Format File
  m_fileTypeTable["ico"] = FILE_FT_IMAGE;       // Icon File
  m_fileTypeTable["jfif"] = FILE_FT_IMAGE;      // JPEG File Interchange Format
  m_fileTypeTable["jpe"] = FILE_FT_IMAGE;       // JPEG Image File
  m_fileTypeTable["jpeg"] = FILE_FT_IMAGE;      // JPEG Image File
  m_fileTypeTable["jpg"] = FILE_FT_IMAGE;       // JPEG Image File
  m_fileTypeTable["pct"] = FILE_FT_IMAGE;       // PICT Picture File
  m_fileTypeTable["pcx"] = FILE_FT_IMAGE;       // Paintbrush Bitmap Image File
  m_fileTypeTable["pic"] = FILE_FT_IMAGE;       // PICT Picture File
  m_fileTypeTable["pict"] = FILE_FT_IMAGE;      // PICT Picture File
  m_fileTypeTable["png"] = FILE_FT_IMAGE;       // Portable Network Graphic
  m_fileTypeTable["psd"] = FILE_FT_IMAGE;       // Photoshop Document
  m_fileTypeTable["psp"] = FILE_FT_IMAGE;       // Paint Shop Pro Image File
  m_fileTypeTable["pspimage"] = FILE_FT_IMAGE;  // Paint Shop Pro Image File
  m_fileTypeTable["tga"] = FILE_FT_IMAGE;       // Targa Graphic
  m_fileTypeTable["tif"] = FILE_FT_IMAGE;       // Tagged Image File
  m_fileTypeTable["tiff"] = FILE_FT_IMAGE;      // Tagged Image File
  m_fileTypeTable["wmf"] = FILE_FT_IMAGE;       // Windows Metafile
  m_fileTypeTable["wmp"] = FILE_FT_IMAGE;       // Windows Media Photo File
  m_fileTypeTable["xbm"] = FILE_FT_IMAGE;       // X Bitmap File
  m_fileTypeTable["xif"] = FILE_FT_IMAGE;       // ScanSoft Pagis Extended Image Format File
  m_fileTypeTable["xpm"] = FILE_FT_IMAGE;       // X Pixmap File


  m_fileTypeTable["7z"] = FILE_FT_ARCHIVE;      // 7-Zip Compressed File
  m_fileTypeTable["ace"] = FILE_FT_ARCHIVE;     // WinAce Compressed File
  m_fileTypeTable["alz"] = FILE_FT_ARCHIVE;     // ALZip Archive
  m_fileTypeTable["arc"] = FILE_FT_ARCHIVE;     // Compressed File Archive
  m_fileTypeTable["arj"] = FILE_FT_ARCHIVE;     // ARJ Compressed File Archive
  m_fileTypeTable["bz2"] = FILE_FT_ARCHIVE;     // Bzip Compressed File
  m_fileTypeTable["cab"] = FILE_FT_ARCHIVE;     // Cabinet File
  m_fileTypeTable["cbr"] = FILE_FT_ARCHIVE;     // Comic Book RAR Archive
  m_fileTypeTable["cbz"] = FILE_FT_ARCHIVE;     // Comic Book ZIP Archive
  m_fileTypeTable["gz"] = FILE_FT_ARCHIVE;      // Gnu Zipped File
  m_fileTypeTable["hqx"] = FILE_FT_ARCHIVE;     // BinHex 4.0 Encoded File
  m_fileTypeTable["jar"] = FILE_FT_ARCHIVE;     // Java Archive File
  m_fileTypeTable["lha"] = FILE_FT_ARCHIVE;     // LHARC Compressed Archive
  m_fileTypeTable["lzh"] = FILE_FT_ARCHIVE;     // LZH Compressed File
  m_fileTypeTable["msi"] = FILE_FT_ARCHIVE;     // Microsoft Installer File
  m_fileTypeTable["pak"] = FILE_FT_ARCHIVE;     // PAK (Packed) File
  m_fileTypeTable["par"] = FILE_FT_ARCHIVE;     // Parchive Index File
  m_fileTypeTable["par2"] = FILE_FT_ARCHIVE;    // Parchive 2 Index File
  m_fileTypeTable["rar"] = FILE_FT_ARCHIVE;     // WinRAR Compressed Archive
  m_fileTypeTable["sit"] = FILE_FT_ARCHIVE;     // Stuffit Archive
  m_fileTypeTable["sitx"] = FILE_FT_ARCHIVE;    // Stuffit X Archive
  m_fileTypeTable["sqx"] = FILE_FT_ARCHIVE;     // Squeez Archive
  m_fileTypeTable["tar"] = FILE_FT_ARCHIVE;     // Consolidated Unix File Archive
  m_fileTypeTable["tbz2"] = FILE_FT_ARCHIVE;    // Tar BZip 2 Compressed File
  m_fileTypeTable["tgz"] = FILE_FT_ARCHIVE;     // Gzipped Tar File
  m_fileTypeTable["uha"] = FILE_FT_ARCHIVE;     // uharc compression
  m_fileTypeTable["xpi"] = FILE_FT_ARCHIVE;     // Mozilla Installer Package
  m_fileTypeTable["z"] = FILE_FT_ARCHIVE;       // Unix Compressed File
  m_fileTypeTable["zip"] = FILE_FT_ARCHIVE;     // Zipped File
  m_fileTypeTable["zipx"] = FILE_FT_ARCHIVE;    // WinZip Archive File


  m_fileTypeTable["apk"] = FILE_FT_PROGRAM;     // Android package
  m_fileTypeTable["app"] = FILE_FT_PROGRAM;     // Mac OS X Application File
  m_fileTypeTable["bat"] = FILE_FT_PROGRAM;     // Batch File
  m_fileTypeTable["cmd"] = FILE_FT_PROGRAM;     // Command File
  m_fileTypeTable["com"] = FILE_FT_PROGRAM;     // COM File
  m_fileTypeTable["exe"] = FILE_FT_PROGRAM;     // Executable File
  m_fileTypeTable["hta"] = FILE_FT_PROGRAM;     // HTML Application
  m_fileTypeTable["js"] = FILE_FT_PROGRAM;      // Java Script
  m_fileTypeTable["jse"] = FILE_FT_PROGRAM;     // Encoded Java Script
  m_fileTypeTable["msc"] = FILE_FT_PROGRAM;     // Microsoft Common Console File
  m_fileTypeTable["vbe"] = FILE_FT_PROGRAM;     // Encoded Visual Basic Script File
  m_fileTypeTable["vbs"] = FILE_FT_PROGRAM;     // Visual Basic Script File
  m_fileTypeTable["wsf"] = FILE_FT_PROGRAM;     // Windows Script File
  m_fileTypeTable["wsh"] = FILE_FT_PROGRAM;     // Windows Scripting Host File


  m_fileTypeTable["bin"] = FILE_FT_CDIMAGE;     // CD Image
  m_fileTypeTable["bwa"] = FILE_FT_CDIMAGE;     // BlindWrite Disk Information File
  m_fileTypeTable["bwi"] = FILE_FT_CDIMAGE;     // BlindWrite CD/DVD Disc Image
  m_fileTypeTable["bws"] = FILE_FT_CDIMAGE;     // BlindWrite Sub Code File
  m_fileTypeTable["bwt"] = FILE_FT_CDIMAGE;     // BlindWrite 4 Disk Image
  m_fileTypeTable["ccd"] = FILE_FT_CDIMAGE;     // CloneCD Disk Image
  m_fileTypeTable["cue"] = FILE_FT_CDIMAGE;     // Cue Sheet File
  m_fileTypeTable["dmg"] = FILE_FT_CDIMAGE;     // Mac OS X Disk Image
  m_fileTypeTable["img"] = FILE_FT_CDIMAGE;     // Disk Image Data File
  m_fileTypeTable["iso"] = FILE_FT_CDIMAGE;     // Disc Image File
  m_fileTypeTable["mdf"] = FILE_FT_CDIMAGE;     // Media Disc Image File
  m_fileTypeTable["mds"] = FILE_FT_CDIMAGE;     // Media Descriptor File
  m_fileTypeTable["nrg"] = FILE_FT_CDIMAGE;     // Nero CD/DVD Image File
  m_fileTypeTable["sub"] = FILE_FT_CDIMAGE;     // Subtitle File
  m_fileTypeTable["toast"] = FILE_FT_CDIMAGE;   // Toast Disc Image


  m_fileTypeTable["chm"] = FILE_FT_DOCUMENT;    // Compiled HTML Help File
  m_fileTypeTable["css"] = FILE_FT_DOCUMENT;    // Cascading Style Sheet
  m_fileTypeTable["diz"] = FILE_FT_DOCUMENT;    // Description in Zip File
  m_fileTypeTable["doc"] = FILE_FT_DOCUMENT;    // Document File
  m_fileTypeTable["docx"] = FILE_FT_DOCUMENT;   // Document File
  m_fileTypeTable["dot"] = FILE_FT_DOCUMENT;    // Document Template File
  m_fileTypeTable["dotx"] = FILE_FT_DOCUMENT;   // Document Template File
  m_fileTypeTable["hlp"] = FILE_FT_DOCUMENT;    // Help File
  m_fileTypeTable["htm"] = FILE_FT_DOCUMENT;    // HTML File
  m_fileTypeTable["html"] = FILE_FT_DOCUMENT;   // HTML File
  m_fileTypeTable["nfo"] = FILE_FT_DOCUMENT;    // Warez Information File
  m_fileTypeTable["odb"] = FILE_FT_DOCUMENT;    // Open Document File
  m_fileTypeTable["odf"] = FILE_FT_DOCUMENT;    // Open Document File
  m_fileTypeTable["odp"] = FILE_FT_DOCUMENT;    // Open Document File
  m_fileTypeTable["ods"] = FILE_FT_DOCUMENT;    // Open Document File
  m_fileTypeTable["odt"] = FILE_FT_DOCUMENT;    // Open Document File
  m_fileTypeTable["pdf"] = FILE_FT_DOCUMENT;    // Portable Document Format File
  m_fileTypeTable["pmd"] = FILE_FT_DOCUMENT;    // PageMaker Publication
  m_fileTypeTable["pmv"] = FILE_FT_DOCUMENT;    // PlanMaker Spreadsheet
  m_fileTypeTable["pps"] = FILE_FT_DOCUMENT;    // PowerPoint Slide Show
  m_fileTypeTable["ppt"] = FILE_FT_DOCUMENT;    // PowerPoint Presentation
  m_fileTypeTable["pptx"] = FILE_FT_DOCUMENT;   // PowerPoint Presentation
  m_fileTypeTable["ps"] = FILE_FT_DOCUMENT;     // PostScript File
  m_fileTypeTable["qpw"] = FILE_FT_DOCUMENT;    // Quattro Pro Spreadsheet
  m_fileTypeTable["rtf"] = FILE_FT_DOCUMENT;    // Rich Text Format File
  m_fileTypeTable["text"] = FILE_FT_DOCUMENT;   // General Text File
  m_fileTypeTable["tmd"] = FILE_FT_DOCUMENT;    // TextMaker Document
  m_fileTypeTable["txt"] = FILE_FT_DOCUMENT;    // Text File
  m_fileTypeTable["wpd"] = FILE_FT_DOCUMENT;    // WordPerfect Document
  m_fileTypeTable["wri"] = FILE_FT_DOCUMENT;    // Windows Write Document
  m_fileTypeTable["xls"] = FILE_FT_DOCUMENT;    // Microsoft Excel Spreadsheet
  m_fileTypeTable["xlsx"] = FILE_FT_DOCUMENT;   // Microsoft Excel Spreadsheet
  m_fileTypeTable["xlt"] = FILE_FT_DOCUMENT;    // Microsoft Excel Template File
  m_fileTypeTable["xltx"] = FILE_FT_DOCUMENT;   // Microsoft Excel Template File
  m_fileTypeTable["xml"] = FILE_FT_DOCUMENT;    // XML File

}

QImage Utils::getFileTypeImage(QString extension,int h, int w)
{
  FileType fileType = FILE_FT_UNKNOWN;
  QImage image;

  if(m_fileTypeTable.contains(extension))
    {
      fileType = m_fileTypeTable[extension];
    }

  switch (fileType) {
    case FILE_FT_AUDIO:
      image = QImage(":/qml/filetypes/FileTypeAudio.png");
      break;
    case FILE_FT_VIDEO:
      image = QImage(":/qml/filetypes/FileTypeVideo.png");
      break;
    case FILE_FT_IMAGE:
      image = QImage(":/qml/filetypes/FileTypePicture.png");
      break;
    case FILE_FT_PROGRAM:
      image = QImage(":/qml/filetypes/FileTypeProgram.png");
      break;
    case FILE_FT_DOCUMENT:
      image = QImage(":/qml/filetypes/FileTypeDocument.png");
      break;
    case FILE_FT_ARCHIVE:
      image = QImage(":/qml/filetypes/FileTypeArchive.png");
      break;
    case FILE_FT_CDIMAGE:
      image = QImage(":/qml/filetypes/FileTypeCDImage.png");
      break;

    default:
      image = QImage(":/qml/filetypes/FileTypeAny.png");
      break;
    }

  return image;

}

