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

#ifndef CANGOTE_H
#define CANGOTE_H

#include <QObject>
#include <QThread>
#include "utils/log.h"


/** Pointer to this RetroShare application instance. */

#define gDebug(fmt)   (theApp->log(Log::Debug, (fmt)))
#define gInfo(fmt)    (theApp->log(Log::Info, (fmt)))
#define gNotice(fmt)  (theApp->log(Log::Notice, (fmt)))
#define gWarn(fmt)    (theApp->log(Log::Warn, (fmt)))
#define gError(fmt)   (theApp->log(Log::Error, (fmt)))




class CangoteDlg;
class GNUNet;
class Cangote : public QObject
{
    Q_OBJECT
public:
    explicit Cangote(QObject *parent = 0);
            ~Cangote();
public:


    
signals:



public:
        static Log _log;
        /** Writes <b>msg</b> with severity <b>level</b> to Cangote's log. */
        static Log::LogMessage log(Log::LogLevel level, QString msg);
        void createGNUNet();
        GNUNet* gnunet;
        void Search(QString term);
        void launchGNUNet();




private:
        void Connect();
        CangoteDlg* cangoteDlg;
        class GNUNetLauncher* launcher;

public slots:
         void GNUNetStatusChangedSlot(int signal);

signals:

    void searchSignal(QString term, int anonLevel);

private:
    QThread *gnunetThread;



    static void        qt_msg_handler(QtMsgType type, const char *s);
};

extern Cangote* theApp;

#endif // CANGOTE_H
