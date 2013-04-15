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

#define START_SERVICES false

#define USE_ARM false

GNUNetLauncher::GNUNetLauncher(QObject *parent) :
    QObject(parent)
{

    startServices();
}

GNUNetLauncher::~GNUNetLauncher()
{
    stopServices();
}

void GNUNetLauncher::stopServices()
{

    if(!START_SERVICES)
        return;

    if(USE_ARM)
    {
        QProcess* killArmProcess     = new QProcess(this);
        killArmProcess->setProcessEnvironment(env);
        killArmProcess->start("gnunet-arm.exe -e");
        killArmProcess->waitForFinished(5000);
    }
    else
    {
        //TODO: do not kill the services, gracefully stop
        m_hostListProcess->kill();
        m_topologyProcess->kill();
        m_atsProcess->kill();
        m_coreProcess->kill();
        m_dataStoreProcess->kill();
        m_dhtProcess->kill();
        m_fsProcess->kill();
        m_nseProcess->kill();
        m_meshProcess->kill();
        m_peerinfoProcess->kill();
        m_statsProcess->kill();
        m_transportProcess->kill();
        m_resolverProcess->kill();

        //Wait for finish
        m_hostListProcess->waitForFinished(3000);
        m_topologyProcess->waitForFinished(3000);
        m_atsProcess->waitForFinished(3000);
        m_coreProcess->waitForFinished(3000);
        m_dataStoreProcess->waitForFinished(3000);
        m_dhtProcess->waitForFinished(3000);
        m_fsProcess->waitForFinished(3000);
        m_nseProcess->waitForFinished(3000);
        m_meshProcess->waitForFinished(3000);
        m_peerinfoProcess->waitForFinished(3000);
        m_statsProcess->waitForFinished(3000);
        m_transportProcess->waitForFinished(3000);
        m_resolverProcess->waitForFinished(3000);
    }


}



void GNUNetLauncher::startServices()
{

    if(!START_SERVICES)
        return;

    setEnvironment();

    if(USE_ARM)
    {
        m_armProcess = new QProcess(this);
        startArm();
    }
    else
    {
        m_hostListProcess     = new QProcess(this);
        m_topologyProcess     = new QProcess(this);
        m_atsProcess          = new QProcess(this);
        m_coreProcess         = new QProcess(this);
        m_dataStoreProcess    = new QProcess(this);
        m_dhtProcess          = new QProcess(this);
        m_fsProcess           = new QProcess(this);
        m_nseProcess          = new QProcess(this);
        m_meshProcess         = new QProcess(this);
        m_peerinfoProcess     = new QProcess(this);
        m_statsProcess        = new QProcess(this);
        m_transportProcess    = new QProcess(this);
        m_resolverProcess     = new QProcess(this);



        startCore();
        startAts();
        startHostList();
        startTopology();
        startDht();
        startFs();
        startTransport();
        startNse();
        startMesh();
        startPeerinfo();
        startStats();
        startDatastore();
        startResolver();

        connectSignals();
    }




}

void GNUNetLauncher::errorHandler(QProcess::ProcessState state)
{
   qWarning() << (QString(state));
}

void GNUNetLauncher::connectSignals()
{

    connect(m_fsProcess,SIGNAL(stateChanged(QProcess::ProcessState)),this, SLOT(errorHandler(QProcess::ProcessState)));

}

void GNUNetLauncher::setEnvironment()
{
    env = QProcessEnvironment::systemEnvironment();
   // env.insert("TMPDIR", "C:\\MyApp\\temp"); // Add an environment variable
    env.insert("PATH", env.value("Path") + ";C:\\sbuild\\mingw\\bin" +";C:\\sbuild\\mingw\\lib\\gnunet\\libexec" + ";C:\\sbuild\\mingw\\lib\\gnunet");
}

bool GNUNetLauncher::startArm()
{
    m_armProcess->setProcessEnvironment(env);
    m_armProcess->start("gnunet-arm.exe -s");
}

bool GNUNetLauncher::startCore()
{
    m_coreProcess->setProcessEnvironment(env);
    m_coreProcess->setWorkingDirectory("C:\\sbuild\\mingw\\lib\\gnunet\\libexec");
    connect(m_coreProcess,SIGNAL(error(QProcess::ProcessError)),SLOT(CoreError(QProcess::ProcessError)));

    m_coreProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-core.exe");

}


void GNUNetLauncher::CoreError ( QProcess::ProcessError error )
{

    qWarning() << (QString(error));
}

bool GNUNetLauncher::startHostList()
{
    m_hostListProcess->setProcessEnvironment(env);
    m_hostListProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-daemon-hostlist.exe");
}

bool GNUNetLauncher::startTopology()
{
    m_topologyProcess->setProcessEnvironment(env);
    m_topologyProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-daemon-topology.exe");
}

bool GNUNetLauncher::startAts()
{
    m_atsProcess->setProcessEnvironment(env);
    m_atsProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-ats.exe");
}

bool GNUNetLauncher::startDht()
{
    m_dhtProcess->setProcessEnvironment(env);
    m_dhtProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-dht.exe");
}

bool GNUNetLauncher::startFs()
{
    m_fsProcess->setProcessEnvironment(env);
    m_fsProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-fs.exe");
}

bool GNUNetLauncher::startTransport()
{
    m_transportProcess->setProcessEnvironment(env);
    m_transportProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-transport.exe");
}

bool GNUNetLauncher::startNse()
{
    m_nseProcess->setProcessEnvironment(env);
    m_nseProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-nse.exe");
}

bool GNUNetLauncher::startMesh()
{
    m_meshProcess->setProcessEnvironment(env);
    m_meshProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-mesh.exe");
}

bool GNUNetLauncher::startPeerinfo()
{
    m_peerinfoProcess->setProcessEnvironment(env);
    m_peerinfoProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-peerinfo.exe");
}

bool GNUNetLauncher::startStats()
{
    m_statsProcess->setProcessEnvironment(env);
    m_statsProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-statistics.exe");
}


bool GNUNetLauncher::startDatastore()
{
    m_dataStoreProcess->setProcessEnvironment(env);
    m_dataStoreProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-datastore.exe");
}


bool GNUNetLauncher::startResolver()
{
    m_resolverProcess->setProcessEnvironment(env);
    m_resolverProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-resolver.exe");
}


