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

#include <QHBoxLayout>
#include <QLabel>

#include "friendstatus.h"

FriendStatus::FriendStatus(QWidget *parent)
 : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setMargin(0);
    hbox->setSpacing(6);
    
    iconLabel = new QLabel( this );
    iconLabel->setPixmap(QPixmap(":/res/statusbar/identitygray16.png"));
    // iconLabel doesn't change over time, so we didn't need a minimum size
    hbox->addWidget(iconLabel);
    
    statusPeers = new QLabel( tr("Friends: 0/0"), this );
//    statusPeers->setMinimumSize( statusPeers->frameSize().width() + 0, 0 );
    hbox->addWidget(statusPeers);
    
    setLayout(hbox);

}

void FriendStatus::getPeerStatus(unsigned int nFriendCount, unsigned int nOnlineCount)
{
    /* set users/friends/network */

    statusPeers->setToolTip(tr("Online Friends/Total Friends") );

    if (statusPeers)
        statusPeers -> setText(QString("<strong>%1:</strong> %2/%3 ").arg(tr("Friends")).arg(nOnlineCount).arg(nFriendCount));
    		
    if (nOnlineCount > 0)
    {
        iconLabel->setPixmap(QPixmap(":/res/statusbar/identity16.png"));
    }
    else
    {
        iconLabel->setPixmap(QPixmap(":/res/statusbar/identitygray16.png"));
    }
   		

}


