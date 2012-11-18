/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

import QtQuick 1.1
import VLCQt 0.6

Rectangle {
    width: 640
    height: 480

    VlcVideoPlayer
    {
        id: vidwidget
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onClicked: {
                vidwidget.openFile("/home/tadej/Video/Yugo.mpeg")
                vidwidget.play()
            }
        }
    }
}
