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

#include "servicestatus.h"

ServiceStatus::ServiceStatus(QObject *parent) :
    QObject(parent)
{
    status = STATUS_STARTING;
}


ServiceStatus::Service_Status ServiceStatus::getStatus()
{
    return status;
}

void ServiceStatus::setErrorState(QString error)
{
    status = STATUS_ERROR;
    emit stateChangedSignal(status);
}

void ServiceStatus::setOkState()
{
    status = STATUS_OK;
    emit stateChangedSignal(status);
}


void ServiceStatus::setChildrenService(ServiceStatus* service)
{
    m_childServices.append(service);
}
