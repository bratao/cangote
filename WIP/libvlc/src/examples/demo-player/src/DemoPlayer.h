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

#ifndef DEMOPLAYER_H_
#define DEMOPLAYER_H_

#include <QtGui/QMainWindow>

namespace Ui {
    class DemoPlayer;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class DemoPlayer : public QMainWindow
{
Q_OBJECT
public:
    explicit DemoPlayer(QWidget *parent = 0);
    ~DemoPlayer();

private slots:
    void openLocal();
    void openUrl();

private:
    Ui::DemoPlayer *ui;

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
};

#endif // DEMOPLAYER_H_
