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

#ifndef GNUNETLAUNCHER_H
#define GNUNETLAUNCHER_H

#include <QObject>
#include <QProcess>

class GNUNetLauncher : public QObject
{
    Q_OBJECT
public:
    explicit GNUNetLauncher(QObject *parent = 0);
    
    void startServices();
    void setEnvironment();
    bool startHostList();
    bool startCore();
    bool startTopology();
    bool startAts();
    void stopServices();
    bool startArm();

    bool startDht();
    bool startFs();
    bool startTransport();
    bool startNse();
    bool startMesh();
    bool startPeerinfo();
    bool startStats();
    bool startDatastore();
    bool startResolver();
signals:
    
public slots:
    void CoreError(QProcess::ProcessError error);
private:
    QProcessEnvironment env;

    QProcess *armProcess;
    QProcess *hostListProcess;
    QProcess *topologyProcess;
    QProcess *atsProcess;
    QProcess *coreProcess;
    QProcess *dataStoreProcess;
    QProcess *dhtProcess;
    QProcess *fsProcess;
    QProcess *nseProcess;
    QProcess *peerinfoProcess;
    QProcess *statsProcess;
    QProcess *transportProcess;
    QProcess *meshProcess;
    QProcess *resolverProcess;
    
};

#endif // GNUNETLAUNCHER_H
