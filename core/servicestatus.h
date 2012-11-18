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

#ifndef CANGOTESERVICESTATUS_H
#define CANGOTESERVICESTATUS_H

#include <QList>
#include <QString>
#include <QObject>

class ServiceStatus: public QObject
{
Q_OBJECT
public:
    explicit ServiceStatus(QObject *parent = 0);
    enum Service_Status { STATUS_STARTING, STATUS_PARTIAL ,STATUS_OK, STATUS_ERROR };


    void setErrorState(QString error);
    void setOkState();
    void setChildrenService(ServiceStatus *service);
    ServiceStatus::Service_Status getStatus();
private:


     Service_Status status;


     QList<ServiceStatus*> m_childServices;


signals:
     void stateChangedSignal(int signal);
};

#endif // CANGOTESERVICESTATUS_H
