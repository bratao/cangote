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

#ifndef MISC_H
#define MISC_H

#include <stdexcept>
#include <QObject>
#include <QPair>
#include <QThread>



/*  Miscellaneaous functions that can be useful */
class misc : public QObject
{
    Q_OBJECT

 public:

    // return best userfriendly storage unit (B, KiB, MiB, GiB, TiB)
    // use Binary prefix standards from IEC 60027-2
    // see http://en.wikipedia.org/wiki/Kilobyte
    // value must be given in bytes
    static QString friendlyUnit(float val);

    static bool isPreviewable(QString extension);

    // Take a number of seconds and return an user-friendly
    // time duration like "1d 2h 10m".
    static QString userFriendlyDuration(qlonglong seconds);

    static QString userFriendlyUnit(double count, unsigned int decimal, double factor = 1000);

    static QString bytesToString(float num);
    static void drawWidgetBackground(class QStyleOptionViewItemV4 *opt, class QPainter *painter);
};

//  Trick to get a portable sleep() function
class SleeperThread : public QThread{
  public:
    static void msleep(unsigned long msecs)
    {
      QThread::msleep(msecs);
    }
};

#endif
