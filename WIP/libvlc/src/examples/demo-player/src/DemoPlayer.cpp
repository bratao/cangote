/****************************************************************************
* VLC-Qt Demo Player
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtGui/QFileDialog>
#include <QtGui/QInputDialog>

#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>

#include "DemoPlayer.h"
#include "ui_DemoPlayer.h"

DemoPlayer::DemoPlayer(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::DemoPlayer),
      _media(0)
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(_player);
    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(50);
    ui->seek->setMediaPlayer(_player);

    connect(ui->actionOpenLocal, SIGNAL(triggered()), this, SLOT(openLocal()));
    connect(ui->actionOpenUrl, SIGNAL(triggered()), this, SLOT(openUrl()));
    connect(ui->actionPause, SIGNAL(triggered()), _player, SLOT(pause()));
    connect(ui->actionStop, SIGNAL(triggered()), _player, SLOT(stop()));
    connect(ui->openLocal, SIGNAL(clicked()), this, SLOT(openLocal()));
    connect(ui->openUrl, SIGNAL(clicked()), this, SLOT(openUrl()));
    connect(ui->pause, SIGNAL(clicked()), _player, SLOT(pause()));
    connect(ui->stop, SIGNAL(clicked()), _player, SLOT(stop()));
}

DemoPlayer::~DemoPlayer()
{
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}

void DemoPlayer::openLocal()
{
    QString file =
            QFileDialog::getOpenFileName(this, tr("Open file"),
                                         QDir::homePath(),
                                         tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media = new VlcMedia(file, true, _instance);

    _player->open(_media);
}

void DemoPlayer::openUrl()
{
    QString url =
            QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"));

    if (url.isEmpty())
        return;

    _media = new VlcMedia(url, _instance);

    _player->open(_media);
}
