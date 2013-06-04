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

#include "gnunetlauncher.h"
#include <QDebug>
//#include "core/cangote.h"

GNUNetLauncher::GNUNetLauncher(QObject *parent) :
    QObject(parent)
{
    m_armProcess = NULL;

    connect(this,&GNUNetLauncher::relaunchServicesSignal,this,&GNUNetLauncher::relaunchServicesSlot);
    connect(this,&GNUNetLauncher::stopSignal,this,&GNUNetLauncher::stopSlot);

}

GNUNetLauncher::~GNUNetLauncher()
{
    stopSlot();
}


void GNUNetLauncher::start()
{

    setEnvironment();

    m_armProcess = new QProcess(this);
    startArm();

}

void GNUNetLauncher::stopSlot()
{


    QProcess* killArmProcess     = new QProcess(this);
    killArmProcess->setProcessEnvironment(env);
    killArmProcess->start("gnunet-arm.exe -e");
    killArmProcess->waitForFinished(1000);



}

bool GNUNetLauncher::startArm()
{
    QStringList arguments;
    arguments << "-s";

    m_armProcess->setProcessEnvironment(env);
    m_armProcess->start("gnunet-arm.exe", arguments);


}

void GNUNetLauncher::cleanOldProcesses()
{
    QProcess* killArmProcess     = new QProcess(this);
#ifdef Q_OS_WIN
    killArmProcess->setProcessEnvironment(env);
    killArmProcess->start("taskkill -f /IM gnunet-*");
#else
    QProcess* killArmProcess     = new QProcess(this);
    killArmProcess->setProcessEnvironment(env);
    killArmProcess->start("pkill -9 -f gnunet-*");
#endif

}


void GNUNetLauncher::relaunchServicesSlot()
{

    if(m_armProcess)
    {
        delete m_armProcess;
    }
    m_armProcess = new QProcess(this);
    cleanOldProcesses();
    startArm();
}

void
GNUNetLauncher::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qWarning() << (QString(exitStatus));
}

void GNUNetLauncher::errorHandler(QProcess::ProcessError error)
{
    qWarning() << (QString(error));
}


void GNUNetLauncher::stateChanged(QProcess::ProcessState state)
{
    qWarning() << (QString(state));
}

void GNUNetLauncher::connectSignals()
{


}

void GNUNetLauncher::setEnvironment()
{
    env = QProcessEnvironment::systemEnvironment();
    env.insert("PATH", env.value("Path") + ";C:\\sbuild\\mingw\\bin" +
               ";C:\\sbuild\\mingw\\lib\\gnunet\\libexec" +
               ";C:\\sbuild\\mingw\\lib\\gnunet");
}



void GNUNetLauncher::CoreError ( QProcess::ProcessError error )
{

    qWarning() << (QString(error));
}


