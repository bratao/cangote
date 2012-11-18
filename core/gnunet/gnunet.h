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


#ifndef GNUNET_H
#define GNUNET_H
#include <QtCore>
#include <QString>

#include "gnunet_includes.h"



class FileSharing;
class GNetwork;
class GNUnetFsSearchModel;
class GNUNetPeersModel;
class ServiceStatus;
class DownloadModel;
class GNUNet : public QObject
{
    Q_OBJECT
public:
    explicit GNUNet(QObject *parent = 0);



    void ProcessEvents();

    static void mainLoopCallback(void *cls, char *const *args, const char *cfgfile,
                   const struct GNUNET_CONFIGURATION_Handle *cfg);

    static struct GNUNET_CONFIGURATION_Handle *config;

    static void keepaliveTask (void *cls, const struct GNUNET_SCHEDULER_TaskContext *tc);


    ServiceStatus* getStatus();


public slots:
    void Start();

public:
    FileSharing* filesharing;
    GNetwork*  network;

    int numEstimateNodes;

    GNUNetPeersModel *getPeersModel();
    void StartServices();

    void mainLoop(char *const*args, const char *cfgfile, const GNUNET_CONFIGURATION_Handle *cfg);
    GNUnetFsSearchModel *getSearchModel();
    DownloadModel *getDownloadsModel();
private:
    ServiceStatus* status;



};

#endif // GNUNET_H
