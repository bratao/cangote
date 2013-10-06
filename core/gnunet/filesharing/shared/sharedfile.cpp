/**************************************************************************
** This file is part of Cangote
** (C)2/26/2013 2013 Bruno Cabral (and other contributing authors)
**
** Cangote is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published
** by the Free Software Foundation; either version 3, or (at your
** option) any later version.
**
** Cangote is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Cangote; see the file COPYING.  If not, write to the
** Free Software Foundation, Inc., 59 Temple Place - Suite 330,
** Boston, MA 02111-1307, USA.
**************************************************************************/

#include "sharedfile.h"

SharedFile::SharedFile(QObject *parent) :
  QObject(parent)
{
  m_index = -1;
  m_size = 0;
  m_progress = 0;
  m_status = Unknown;
}

/**
 * @brief Get the status as a string.
 *        if is an activity, will display the percentage of the activity.
 * @return The formated status
 */
QString SharedFile::getFancyStatus()
{
  QString str;

  switch(m_status)
    {
    case Publishing:
      {
        str = QString("Publishing %1").arg(progress());
        break;
      }
    case Published:
      {
        str = "Published";
        break;
      }
    case Indexed:
      {
        str = "Indexed";
        break;
      }
    case Unindexing:
      {
        str = "Unindexing";
        break;
      }
    case Unindexed:
      {
        str = "Unindexed";
        break;
      }
    case Error:
      {
        str = "Error";
        break;
      }
    case Unknown:
      {
        str = "Unknown";
        break;
      }

    }
  return str;
}


void SharedFile::setStatus(Status status)
{
  m_status = status;
  emit statusChanged(m_index);
}

void SharedFile::setIndex(int index)
{
  m_index = index;
}

QString SharedFile::dummy()
{
    return "c:/teste";
}
