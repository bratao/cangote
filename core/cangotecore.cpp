#include <QDebug>
#include "cangotecore.h"
#include "cangote.h"
#include "preferences/preferences.h"
#include "gnunet/gnunet.h"
#include "models/models.h"
#include "status.h"
#include "core/gnunet/launcher/gnunetlauncher.h"
#include "gnunet/network/NetworkManager.h"
#include "utils/update_checker.h"

#include <QTimer>
#include <QQuickWindow>
#include <QMenu>
#include <QApplication>
#include <QDesktopWidget>
#include <QCheckBox>
#include <QDialogButtonBox>

#include <QVBoxLayout>
#include <QLabel>
#include <qdialog.h>

#include <qpainter.h>
/* Static member variables */
CangoteCore* theApp;



CangoteCore::CangoteCore(QObject *parent) :
  QObject(parent)
{
  theApp = this;
  m_connected = false;
  m_launcher = new GNUNetLauncher();
  m_models = new Models(this);

  m_update = new UpdateChecker(this);
  m_update->checkForUpdate();

  //Launcher services
  startLauncher();


  //Timer to try to connect to arm
  m_armConnectTimer = new QTimer(this);
  m_armConnectTimer->setSingleShot(true);
  connect(m_armConnectTimer, &QTimer::timeout, this, &CangoteCore::armTimeOut);


  //The processing timer
  m_timer = new QTimer(this);
  connect(m_timer, &QTimer::timeout, this, &CangoteCore::process);
  m_timer->start(1000);

  //Finally start gnunet
  startGNUNet();

  //Start the Status. It need to load after all
  m_status = new Status(this);

}



CangoteCore::~CangoteCore()
{
  m_launcher->stop();
  m_models = NULL;
}

void CangoteCore::process()
{
  //TODO: Timer !

}

void CangoteCore::armTimeOut()
{

  qWarning() << "Connection lost, trying again in:" << m_armConnectTimer->interval() << "ms \n";

  if(m_connected == false)
    m_launcher->relaunchServices();

  //Exponential backoff
  m_armConnectTimer->start(m_armConnectTimer->interval()*2);


}

void CangoteCore::setupTray()
{
  // create the menu
  m_trayMenu = new QMenu( QCoreApplication::instance()->applicationName() );
  // add a horizontal line to the menu

  m_trayMenu->addSeparator();
  m_trayCloseAction = m_trayMenu->addAction("Close");
  connect(m_trayCloseAction, &QAction::triggered, this, &CangoteCore::close);



  m_tray = new QSystemTrayIcon(QIcon(":/asserts/CangoteHead.ico"),theWindow); //Same as above
  m_tray->setContextMenu(m_trayMenu);
  m_tray->setVisible(true);

  QObject::connect(m_tray, &QSystemTrayIcon::activated,this, &CangoteCore::trayActivated );

}


void CangoteCore::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
  if(reason == QSystemTrayIcon::DoubleClick){
      if(!theWindow->isVisible()){

          theWindow->show();

        }else{
          onClose();
        }
    }
}

void CangoteCore::startLauncher()
{
  //New thread where the will be run on.
  m_launcherThread = new QThread();

  m_launcher->moveToThread(m_launcherThread);

  // Call the start function after our thread is ready to run
  connect(m_launcherThread,
          &QThread::started,
          m_launcher,
          &GNUNetLauncher::start);

  m_launcherThread->start();


}

void CangoteCore::startGNUNet()
{
  //Create the Gnunet object
  m_gnunet = new GNUNet();

  //New thread where the Gnunet will be run on.
  m_gnunetThread = new QThread();

  m_gnunet->moveToThread(m_gnunetThread);

  // Call the start function after our thread is ready to run
  connect(m_gnunetThread,
          &QThread::started,
          m_gnunet,
          &GNUNet::start);

  m_gnunetThread->start();

  connect(m_gnunet, &GNUNet::connectedChanged, this, &CangoteCore::setConnected, Qt::QueuedConnection);

}



void CangoteCore::setConnected(bool connected)
{
  m_connected = connected;
  if((connected == false) && !m_armConnectTimer->isActive())
    {
      qWarning() << "Starting Gnunet again;";
      m_armConnectTimer->start(4000);
    }
  else if (m_armConnectTimer->isActive())
    {
      m_armConnectTimer->stop();
    }
  emit connectedChanged(m_connected);
}

/**
 * @brief CangoteCore::onClose
 * Recivied close signal
 */
void CangoteCore::onClose()
{
  showTrayInfo();
  theWindow->hide();

}

/**
 * @brief CangoteCore::close
 * Actually close
 */
void CangoteCore::close(){
  QApplication::quit();
}

/**
 * Show that we going to the tray.
 * Tray screenshot code borred from kommute.
 */

void CangoteCore::showTrayInfo(){

  if(!thePrefs->value("dialogs/ShowGoToTrayDialog",true).toBool())
      return;


  // Compute size and position of the pixmap to be grabbed:
  QRect g = m_tray->geometry();
  int desktopWidth  = qApp->desktop()->width();
  int desktopHeight = qApp->desktop()->height();
  int tw = g.width();
  int th = g.height();
  int w = desktopWidth / 4;
  int h = desktopHeight / 9;
  int x = g.x() + tw/2 - w/2;               // Center the rectange in the systray icon
  int y = g.y() + th/2 - h/2;
  if ( x < 0 )                 x = 0;       // Move the rectangle to stay in the desktop limits
  if ( y < 0 )                 y = 0;
  if ( x + w > desktopWidth )  x = desktopWidth - w;
  if ( y + h > desktopHeight ) y = desktopHeight - h;

  // Grab the desktop and draw a circle arround the icon:
  QPixmap shot = QPixmap::grabWindow( QApplication::desktop()->winId(),  x,  y,  w,  h );
  QPainter painter( &shot );
  const int MARGINS = 6;
  const int WIDTH   = 3;
  int ax = g.x() - x - MARGINS -1;
  int ay = g.y() - y - MARGINS -1;
  painter.setPen(  QPen( Qt::red,  WIDTH ) );
  painter.drawArc( ax,  ay,  tw + 2*MARGINS,  th + 2*MARGINS,  0,  16*360 );
  painter.end();


  QDialog* dockDialog = new QDialog();
  dockDialog->setWindowTitle(tr("Docking in System Tray"));


  //Add button

  QVBoxLayout * columnLayout = new QVBoxLayout;


  QLabel* image = new QLabel("",dockDialog);
  image->setPixmap(shot);

  QLabel* text = new QLabel("",dockDialog);
  text->setText(tr( "<p>Closing the main window will keep Cangote running in the system tray.</p> "
                    "<p>This is very important to the network.</p> "
                    "<p>You can disable this behavior in <b>Preferences->General->Close go to tray</b> .</p> "
                "<p>Use <b>Quit</b> from the <b>MainWindow</b> menu to quit the application.</p>"));


  QHBoxLayout * lineLayout = new QHBoxLayout;
  QCheckBox* doNotShowAgainCheckBox =  new QCheckBox(tr("Do not show this again"),dockDialog);
  QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
  connect(buttonBox, SIGNAL(accepted()), dockDialog, SLOT(accept()));

  lineLayout->addWidget(doNotShowAgainCheckBox);
  lineLayout->addWidget(buttonBox);

  columnLayout->addWidget(image);
  columnLayout->addWidget(text);
  columnLayout->addWidget(doNotShowAgainCheckBox);
  columnLayout->addLayout(lineLayout);


  thePrefs->setValue("dialogs/ShowGoToTrayDialog",!doNotShowAgainCheckBox->isChecked());

  dockDialog->setLayout(columnLayout);
  dockDialog->exec();



}

