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
    ~GNUNetLauncher();
    
    
    void startServices();
    void stopServices();
    void setEnvironment();
    bool startResolver();
    void connectSignals();
    
signals:
    
public slots:
    void CoreError(QProcess::ProcessError error);
        void errorHandler(QProcess::ProcessState state);
private:
    QProcessEnvironment env;
    QString m_path;

    QProcess *m_armProcess;
    QProcess *m_hostListProcess;
    QProcess *m_topologyProcess;
    QProcess *m_atsProcess;
    QProcess *m_coreProcess;
    QProcess *m_dataStoreProcess;
    QProcess *m_dhtProcess;
    QProcess *m_fsProcess;
    QProcess *m_nseProcess;
    QProcess *m_peerinfoProcess;
    QProcess *m_statsProcess;
    QProcess *m_transportProcess;
    QProcess *m_meshProcess;
    QProcess *m_resolverProcess;




    bool startHostList();
    bool startCore();
    bool startTopology();
    bool startAts();
    bool startArm();
    bool startDht();
    bool startFs();
    bool startTransport();
    bool startNse();
    bool startMesh();
    bool startPeerinfo();
    bool startStats();
    bool startDatastore();
    
};

#endif // GNUNETLAUNCHER_H
