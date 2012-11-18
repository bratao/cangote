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

#include "core/cangote.h"

#define START_SERVICES true

#define USE_ARM true

GNUNetLauncher::GNUNetLauncher(QObject *parent) :
    QObject(parent)
{

    startServices();
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
        hostListProcess->kill();
        topologyProcess->kill();
        atsProcess->kill();
        coreProcess->kill();
        dataStoreProcess->kill();
        dhtProcess->kill();
        fsProcess->kill();
        nseProcess->kill();
        meshProcess->kill();
        peerinfoProcess->kill();
        statsProcess->kill();
        transportProcess->kill();
        resolverProcess->kill();

        //Wait for finish
        hostListProcess->waitForFinished(3000);
        topologyProcess->waitForFinished(3000);
        atsProcess->waitForFinished(3000);
        coreProcess->waitForFinished(3000);
        dataStoreProcess->waitForFinished(3000);
        dhtProcess->waitForFinished(3000);
        fsProcess->waitForFinished(3000);
        nseProcess->waitForFinished(3000);
        meshProcess->waitForFinished(3000);
        peerinfoProcess->waitForFinished(3000);
        statsProcess->waitForFinished(3000);
        transportProcess->waitForFinished(3000);
        resolverProcess->waitForFinished(3000);
    }


}



void GNUNetLauncher::startServices()
{

    if(!START_SERVICES)
        return;

    setEnvironment();

    if(USE_ARM)
    {
        armProcess = new QProcess(this);
        startArm();
    }
    else
    {
        hostListProcess     = new QProcess(this);
        topologyProcess     = new QProcess(this);
        atsProcess          = new QProcess(this);
        coreProcess         = new QProcess(this);
        dataStoreProcess    = new QProcess(this);
        dhtProcess          = new QProcess(this);
        fsProcess           = new QProcess(this);
        nseProcess          = new QProcess(this);
        meshProcess         = new QProcess(this);
        peerinfoProcess     = new QProcess(this);
        statsProcess        = new QProcess(this);
        transportProcess    = new QProcess(this);
        resolverProcess     = new QProcess(this);



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
    }




}

void GNUNetLauncher::setEnvironment()
{
    env = QProcessEnvironment::systemEnvironment();
   // env.insert("TMPDIR", "C:\\MyApp\\temp"); // Add an environment variable
    env.insert("PATH", env.value("Path") + ";C:\\sbuild\\mingw\\bin" +";C:\\sbuild\\mingw\\lib\\gnunet\\libexec" + ";C:\\sbuild\\mingw\\lib\\gnunet");
}

bool GNUNetLauncher::startArm()
{
    armProcess->setProcessEnvironment(env);
    armProcess->start("gnunet-arm.exe -s");
}

bool GNUNetLauncher::startCore()
{
    coreProcess->setProcessEnvironment(env);
    coreProcess->setWorkingDirectory("C:\\sbuild\\mingw\\lib\\gnunet\\libexec");
    connect(coreProcess,SIGNAL(error(QProcess::ProcessError)),SLOT(CoreError(QProcess::ProcessError)));

    coreProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-core.exe");

}


void GNUNetLauncher::CoreError ( QProcess::ProcessError error )
{

    gWarn(QString(error));
}

bool GNUNetLauncher::startHostList()
{
    hostListProcess->setProcessEnvironment(env);
    hostListProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-daemon-hostlist.exe");
}

bool GNUNetLauncher::startTopology()
{
    topologyProcess->setProcessEnvironment(env);
    topologyProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-daemon-topology.exe");
}

bool GNUNetLauncher::startAts()
{
    atsProcess->setProcessEnvironment(env);
    atsProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-ats.exe");
}

bool GNUNetLauncher::startDht()
{
    dhtProcess->setProcessEnvironment(env);
    dhtProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-dht.exe");
}

bool GNUNetLauncher::startFs()
{
    fsProcess->setProcessEnvironment(env);
    fsProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-fs.exe");
}

bool GNUNetLauncher::startTransport()
{
    transportProcess->setProcessEnvironment(env);
    transportProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-transport.exe");
}

bool GNUNetLauncher::startNse()
{
    nseProcess->setProcessEnvironment(env);
    nseProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-nse.exe");
}

bool GNUNetLauncher::startMesh()
{
    meshProcess->setProcessEnvironment(env);
    meshProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-mesh.exe");
}

bool GNUNetLauncher::startPeerinfo()
{
    peerinfoProcess->setProcessEnvironment(env);
    peerinfoProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-peerinfo.exe");
}

bool GNUNetLauncher::startStats()
{
    statsProcess->setProcessEnvironment(env);
    statsProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-statistics.exe");
}


bool GNUNetLauncher::startDatastore()
{
    dataStoreProcess->setProcessEnvironment(env);
    dataStoreProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-datastore.exe");
}


bool GNUNetLauncher::startResolver()
{
    resolverProcess->setProcessEnvironment(env);
    resolverProcess->start("C:\\sbuild\\mingw\\lib\\gnunet\\libexec\\gnunet-service-resolver.exe");
}


