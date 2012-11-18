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

#include "ratesstatus.h"
#include "utils/misc.h"

#include <iomanip>

RatesStatus::RatesStatus(QWidget *parent)
 : QWidget(parent)
{
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->setMargin(0);
    hbox->setSpacing(6);
    
    iconLabel = new QLabel( this );
    iconLabel->setPixmap(QPixmap(":/res/statusbar/up0down0.png"));
    // iconLabel doesn't change over time, so we didn't need a minimum size
    hbox->addWidget(iconLabel);



    statusRates = new QLabel( tr("<strong>Down:</strong> 0.00 KB/s | <strong>Up:</strong> 0.00 KB/s "), this );
//    statusPeers->setMinimumSize( statusPeers->frameSize().width() + 0, 0 );
    hbox->addWidget(statusRates);
    
    setLayout(hbox);
}

void RatesStatus::setRatesStatus(float downBytes, float upBytes)
{
    /* set users/friends/network */

    QString down = misc::bytesToString(downBytes)+"/s";
    QString up = misc::bytesToString(upBytes)+"/s";

    if (statusRates)
          statusRates -> setText(QString("<strong>%1:</strong> %2 | <strong>%3:</strong> %4 ").arg(tr("Down")).arg(down).arg(tr("Up")).arg(up));

    if( upBytes > 0 || downBytes < 0  )
    {
        iconLabel->setPixmap(QPixmap(":/res/statusbar/up1down0.png"));
    }
    
    if( upBytes < 0 || downBytes > 0 )
    {
        iconLabel->setPixmap(QPixmap(":/res/statusbar/up0down1.png"));
    }
    
    if( upBytes > 0 || downBytes > 0 )
    {
        iconLabel->setPixmap(QPixmap(":/res/statusbar/up1down1.png"));
    }
        
    else
    {
        iconLabel->setPixmap(QPixmap(":/res/statusbar/up0down0.png"));
    }
}
