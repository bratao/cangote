/*
     This file is part of Cangote
     (C) 2012 Bruno Cabral (and other contributing authors)

     Cangote is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 3, or (at your
     option) any later version.

     Cangote is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with Cangote; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.
*/

#include "cangote.h"
#include "gui/cangoteDlg.h"
#include "core/gnunet/gnunet.h"
#include "core/gnunet/filesharing/filesharing.h"
#include <QApplication>
#include "core/gnunet/launcher/gnunetlauncher.h"
#include "core/servicestatus.h"



/* Static member variables */
Log Cangote::_log;
Cangote* theApp;

Cangote::Cangote(QObject *parent) :
    QObject(parent)
{
    theApp =this;


    //setup log

    _log.open("log.txt");
    _log.setLogLevel(Log::Debug);



    qInstallMsgHandler(qt_msg_handler);



    gInfo("Starting Main Dialog");
    cangoteDlg = new CangoteDlg();

    cangoteDlg->show();
    cangoteDlg->Connect();
    gInfo("Main Dialog started");


    gInfo("Launching GNUNet");
    launchGNUNet();

    gInfo("Starting GNUNet Manager");
    createGNUNet();





}

Cangote::~Cangote()
{
    if(launcher)
        launcher->stopServices();
}


void Cangote::GNUNetStatusChangedSlot(int signal)
{
    gInfo("GNUnet service is Connected");
    cangoteDlg->GNUNetConnected();
    gInfo("Connecting signals");
    Connect();
}


void Cangote::launchGNUNet()
{
    launcher = new GNUNetLauncher(this);


}


void Cangote::createGNUNet()
{
    //GNUNet object
    gnunet = new GNUNet();

    //New thread where the Gnunet will be run on.
    gnunetThread = new QThread();


    gnunet->moveToThread(gnunetThread);

    // Call the start function after our thread is ready to run
    gnunet->connect(gnunetThread,
                    SIGNAL(started()),
                    SLOT(Start()));

    gnunetThread->start();

    connect(gnunet->getStatus(),SIGNAL(stateChangedSignal(int)),SLOT(GNUNetStatusChangedSlot(int)));
}





void Cangote::Connect()
{

    connect(this,SIGNAL(searchSignal(QString,int)),gnunet->filesharing,SLOT(DoSearch(QString,int)));
}


/** Catches debugging messages from Qt and sends them to RetroShare's logs. If Qt
 * emits a QtFatalMsg, we will write the message to the log and then abort().
 */
void
Cangote::qt_msg_handler(QtMsgType type, const char *s)
{
  QString msg(s);
  switch (type) {
    case QtDebugMsg:
      gDebug(QString("QtDebugMsg: %1").arg(msg));
      break;
    case QtWarningMsg:
      gNotice(QString("QtWarningMsg: %1").arg(msg));
      break;
    case QtCriticalMsg:
      gWarn(QString("QtCriticalMsg: %1").arg(msg));
      break;
    case QtFatalMsg:
      gError(QString("QtFatalMsg: %1").arg(msg));
      break;
  }
  if (type == QtFatalMsg) {
    gError("Fatal Qt error. Aborting.");
    abort();
  }
}


//Write log
Log::LogMessage
Cangote::log(Log::LogLevel level, QString msg)
{
  return _log.log(level, msg);
}

void Cangote::Search(QString term)
{

    emit searchSignal(term, 1);
}


