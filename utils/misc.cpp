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

#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QByteArray>
#include <QBuffer>
#include <QPainter>
#include <QStyleOptionViewItemV4>
#include <QApplication>

#include "misc.h"

// return best userfriendly storage unit (B, KiB, MiB, GiB, TiB)
// use Binary prefix standards from IEC 60027-2
// see http://en.wikipedia.org/wiki/Kilobyte
// value must be given in bytes
QString misc::friendlyUnit(float val)
{
    if(val < 0) {
        return tr("Unknown", "Unknown (size)");
    }
    const QString units[5] = {tr(" B", "bytes"), tr(" KB", "kilobytes (1024 bytes)"), tr(" MB", "megabytes (1024 kilobytes)"), tr(" GB", "gigabytes (1024 megabytes)"), tr(" TB,", "terabytes (1024 gigabytes)") };
    for(unsigned int i=0; i<5; ++i) {
        if (val < 1024.) {
            return QString(QByteArray::number(val, 'f', 1)) + units[i];
        }
        val /= 1024.;
    }
    return  QString(QByteArray::number(val, 'f', 1)) + tr(" TB", "terabytes (1024 gigabytes)");
}

void misc::drawWidgetBackground(QStyleOptionViewItemV4* opt,QPainter * painter )
{
    //Lets get the widget to pain the background
    const QWidget *widget = opt->widget;
    QStyle *style = widget ? widget->style() : QApplication::style();

    QString oldText = opt->text;
    opt->text = "";
    style->drawControl(QStyle::CE_ItemViewItem, opt, painter, widget);
    opt->text = oldText;

}



bool misc::isPreviewable(QString extension)
{
    extension = extension.toUpper();
    if(extension == "AVI") return true;
    if(extension == "MP3") return true;
    if(extension == "OGG") return true;
    if(extension == "OGM") return true;
    if(extension == "WMV") return true;
    if(extension == "WMA") return true;
    if(extension == "MPEG") return true;
    if(extension == "MPG") return true;
    if(extension == "ASF") return true;
    if(extension == "QT") return true;
    if(extension == "RM") return true;
    if(extension == "RMVB") return true;
    if(extension == "RMV") return true;
    if(extension == "SWF") return true;
    if(extension == "FLV") return true;
    if(extension == "WAV") return true;
    if(extension == "MOV") return true;
    if(extension == "VOB") return true;
    if(extension == "MID") return true;
    if(extension == "AC3") return true;
    if(extension == "MP4") return true;
    if(extension == "MP2") return true;
    if(extension == "AVI") return true;
    if(extension == "FLAC") return true;
    if(extension == "AU") return true;
    if(extension == "MPE") return true;
    if(extension == "MOV") return true;
    if(extension == "MKV") return true;
    if(extension == "AIF") return true;
    if(extension == "AIFF") return true;
    if(extension == "AIFC") return true;
    if(extension == "RA") return true;
    if(extension == "RAM") return true;
    if(extension == "M4P") return true;
    if(extension == "M4A") return true;
    if(extension == "3GP") return true;
    if(extension == "AAC") return true;
    if(extension == "SWA") return true;
    if(extension == "MPC") return true;
    if(extension == "MPP") return true;
    return false;
}


// Take a number of seconds and return an user-friendly
// time duration like "1d 2h 10m".
QString misc::userFriendlyDuration(qlonglong seconds)
{
    if(seconds < 0) {
        return tr("Unknown");
    }
    if(seconds < 60) {
        return tr("< 1m", "< 1 minute");
    }
    int minutes = seconds / 60;
    if(minutes < 60) {
        return tr("%1 minutes","e.g: 10minutes").arg(minutes);
    }
    int hours = minutes / 60;
    minutes = minutes - hours*60;
    if(hours < 24) {
        return tr("%1h %2m", "e.g: 3hours 5minutes").arg(hours).arg(minutes);
    }
    int days = hours / 24;
    hours = hours - days * 24;
    if(days < 365) {
        return tr("%1d %2h", "e.g: 2days 10hours").arg(days).arg(hours);
    }
    int years = days / 365;
    days = days - years * 365;
    return tr("%1y %2d", "e.g: 2 years 2days ").arg(years).arg(days);
}

QString misc::userFriendlyUnit(double count, unsigned int decimal, double factor)
{
    if (count <= 0.0) {
        return "0";
    }

    QString output;

    int i;
    for (i = 0; i < 5; i++) {
        if (count < factor) {
            break;
        }

        count /= factor;
    }

    QString unit;
    switch (i) {
    case 0:
        decimal = 0; // no decimal
        break;
    case 1:
        unit = tr("k", "e.g: 3.1 k");
        break;
    case 2:
        unit = tr("M", "e.g: 3.1 M");
        break;
    case 3:
        unit = tr("G", "e.g: 3.1 G");
        break;
    default: // >= 4
        unit = tr("T", "e.g: 3.1 T");
    }

    return QString("%1 %2").arg(count, 0, 'f', decimal).arg(unit);
}

QString misc::bytesToString(float num)
{
     QStringList list;
     list << "KB" << "MB" << "GB" << "TB";

     QStringListIterator i(list);
     QString unit("bytes");

     while(num >= 1024.0 && i.hasNext())
      {
         unit = i.next();
         num /= 1024.0;
     }
     return QString().setNum(num,'f',2)+" "+unit;
}
