/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Components project.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets/QApplication>
#include <QtQml>
#include <QtQuick/QQuickView>
#include <QSystemTrayIcon>
#include <iostream>
#include "cangote.h"


void createTray();
void logProcessor(QtMsgType type, const QMessageLogContext &context, const QString &msg);





int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    qWarning("Starting Cangote p2p");
    Cangote cangote;


    QQmlApplicationEngine engine(QUrl::fromLocalFile("qml/main.qml"));

    cangote.registerImageProvider(&engine);


    //Install log processor
    //qInstallMessageHandler(logProcessor);

    QObject *topLevel = engine.rootObjects().value(0);
    theWindow = qobject_cast<QQuickWindow *>(topLevel);
    if ( !theWindow ) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }
    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));

    //Create the tray icon
    createTray();


    theWindow->setTitle("Cangote P2P 0.00");
    theWindow->setIcon(QIcon(":/asserts/CangoteHead.ico"));
    theWindow->show();
    return app.exec();

}

void createTray()
{
    QSystemTrayIcon*  tray = new QSystemTrayIcon(QIcon(":/asserts/CangoteHead.ico")); //Same as above
    tray->setVisible(true);

}

void logProcessor(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);
    QFile file(QDate::currentDate().toString("cangote_dd_MM_yyyy.log"));


    Q_ASSERT(file.open(QIODevice::Append | QIODevice::Text));

    QTextStream out(&file);
    out << QTime::currentTime().toString("hh:mm:ss.zzz ");

    switch (type)
    {
        case QtDebugMsg:	out << "[Debug] "; break;
        case QtWarningMsg:  out << "[Warning] "; break;
        case QtCriticalMsg: out << "[Critical] "; break;
        case QtFatalMsg:    out << "[Fatal] "; break;
    }

    out << msg << '\n';

    out.flush();
}





