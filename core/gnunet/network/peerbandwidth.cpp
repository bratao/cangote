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

#include "peerbandwidth.h"

PeerBandwidth::PeerBandwidth(QObject *parent) :
  QObject(parent)
{
  total = 0;
  MAX_HISTORY = 100;
}


void PeerBandwidth::addMsg(int size)
{

  Msg* msg = NULL;
  QTime time = QTime::currentTime();

  if(!queue.isEmpty() && (queue.last()->time.second() == time.second()))
  {
      queue.last()->size += size;
  }
  else
  {
      if(queue.count() >= MAX_HISTORY)
        {
          //Reuse the messages
          msg = queue.dequeue();

        }
      else
        {
          msg = new Msg;
        }


      msg->size =size;
      msg->time = time;

      queue.append(msg);
  }

  total+= size;


}


long PeerBandwidth::getTotalTraffic()
{
    return total;
}

/**
 * Average Bandwidth in bytes used in the last WINDOW seconds
 */
float PeerBandwidth::getBandwidth(){

    int sum = 0;
    const int WIN = 4;   //4 seconds of window
    Msg* msg;

    QTime time = QTime::currentTime();


   time = time.addSecs(-WIN);

   for(int i =queue.size()-1; i>0; i-- )
   {
        msg = queue.at(i);
        if(msg->time >= time)
        {
            sum+= msg->size;
        }
        else
            break;
    }


  return sum/(float)WIN ;


}

