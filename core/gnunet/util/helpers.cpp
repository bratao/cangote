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

#include "helpers.h"
#include <QString>

Helpers::Helpers()
{
}



bool Helpers::isValidUTF8(const char * str)
{
  return(QString::fromUtf8(str).toUtf8() == str);


 }
char *
Helpers::GnunetFsDubiousMetaToUtf8 (enum EXTRACTOR_MetaFormat format,
                                    const char *data, size_t data_len)
{
  switch (format)
  {
  case EXTRACTOR_METAFORMAT_UTF8:
    /* data must not contain NULLs (hence the -1) */
    if (isValidUTF8 (data))
      return GNUNET_strdup (data);
    GNUNET_log (GNUNET_ERROR_TYPE_INFO,
                _("Failed to validate supposedly utf-8 string `%s' of length %u, assuming it to be a C string\n"),
                data,
                (unsigned int) data_len);
    format = EXTRACTOR_METAFORMAT_C_STRING;
    /* fall-through */
  case EXTRACTOR_METAFORMAT_C_STRING:
    if (data_len > 0)
    {
      /* There are no guarantees that data is NULL-terminated, AFAIU,
       * so let's play it safe, shall we?
       */
      char data_copy[data_len + 1];

      memcpy (data_copy, data, data_len);
      data_copy[data_len] = '\0';
      return "Implement me !";//GNUNET_GTK_from_loc_to_utf8 (data_copy);
    }
    break;
  default:
    break;
  }
  return NULL;
}
