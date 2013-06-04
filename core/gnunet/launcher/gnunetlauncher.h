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
    
    
    void relaunchServices()
    {
        emit relaunchServicesSignal();
    }
    void stop()
    {
        emit stopSignal();
    }


signals:
    void relaunchServicesSignal();
    void stopSignal();

public slots:
    void start();
    void stopSlot();

private slots:
    void relaunchServicesSlot();
    void CoreError(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void errorHandler(QProcess::ProcessError error);
    void stateChanged(QProcess::ProcessState state);
private:
    QProcessEnvironment env;
    QString m_path;

    QProcess *m_armProcess;


    bool startArm();

    
    void cleanOldProcesses();

    void setEnvironment();
    bool startResolver();
    void connectSignals();


};

#endif // GNUNETLAUNCHER_H
