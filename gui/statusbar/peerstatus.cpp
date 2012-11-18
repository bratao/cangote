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

#include "peerstatus.h"

#include <QLayout>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include "utils/misc.h"

#include <iomanip>

PeerStatus::PeerStatus(QWidget *parent)
 : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setMargin(0);
    hbox->setSpacing(6);
       
    statusDHT = new QLabel("<strong>" + tr("Status") + ":</strong>", this );
    hbox->addWidget(statusDHT);
    
    dhtstatusLabel = new QLabel( this );
    dhtstatusLabel->setPixmap(QPixmap(":/res/statusbar/grayled.png"));
    hbox->addWidget(dhtstatusLabel);
    
    spaceLabel = new QLabel( "|", this );
    spaceLabel->setVisible(false);
    hbox->addWidget(spaceLabel);

    dhtnetworkLabel = new QLabel( this );
    dhtnetworkLabel->setVisible(false);
    dhtnetworkLabel->setPixmap(QPixmap(":/res/statusbar/network16.png"));
    hbox->addWidget(dhtnetworkLabel);

    dhtnetworksizeLabel = new QLabel( "0 (0) ",this );
    dhtnetworksizeLabel->setVisible(false);
    hbox->addWidget(dhtnetworksizeLabel);

    hbox->addSpacing(2);

    setLayout( hbox );
}

void PeerStatus::setStatus(bool gnunetConnected, int connectedNodes, int estimatedNodes)
{


    if (!(gnunetConnected))
	{
		// GRAY.
		dhtstatusLabel->setPixmap(QPixmap(":/res/statusbar/grayled.png"));
        dhtstatusLabel->setToolTip(tr("GNUNet Off"));
		
		spaceLabel->setVisible(false);
		dhtnetworkLabel->setVisible(false);
		dhtnetworksizeLabel->setVisible(false);
		
		dhtnetworksizeLabel->setText("");
		dhtnetworksizeLabel->setToolTip("");
	}
	else
	{
        if (connectedNodes)
		{
            #define MIN_RS_NET_SIZE		5
			// YELLOW or GREEN.
            if (connectedNodes < MIN_RS_NET_SIZE)
			{
				dhtstatusLabel->setPixmap(QPixmap(":/res/statusbar/yellowled.png"));
                dhtstatusLabel->setToolTip(tr("GNUNet Searching for Peers"));
				
				spaceLabel->setVisible(true);
				dhtnetworkLabel->setVisible(true);
				dhtnetworksizeLabel->setVisible(true);
				
                dhtnetworksizeLabel->setText(QString("%1 (%2)").arg(misc::userFriendlyUnit(connectedNodes, 1)).arg(misc::userFriendlyUnit(estimatedNodes, 1)));
                dhtnetworksizeLabel->setToolTip(tr("Number of connected users (Total network users)") );
			}
			else
			{
				dhtstatusLabel->setPixmap(QPixmap(":/res/statusbar/greenled.png"));
                dhtstatusLabel->setToolTip(tr("GNUNet Good"));
				
				spaceLabel->setVisible(true);
				dhtnetworkLabel->setVisible(true);
				dhtnetworksizeLabel->setVisible(true);
				
                dhtnetworksizeLabel->setText(QString("%1 (%2)").arg(misc::userFriendlyUnit(connectedNodes, 1)).arg(misc::userFriendlyUnit(estimatedNodes, 1)));
                dhtnetworksizeLabel->setToolTip(tr("Number of connected users (Total network users)") );
			}
				
		

		}
		else
		{
			// RED - some issue.
			dhtstatusLabel->setPixmap(QPixmap(":/res/statusbar/redled.png"));
            dhtstatusLabel->setToolTip(tr("GNUNet Error"));
			
			spaceLabel->setVisible(false);
			dhtnetworkLabel->setVisible(false);
			dhtnetworksizeLabel->setVisible(false);
			
			dhtnetworksizeLabel->setText("");
			dhtnetworksizeLabel->setToolTip("");
		}
	}


}
