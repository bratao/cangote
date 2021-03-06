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

#ifndef HELPERS_H
#define HELPERS_H

#include "core/gnunet/gnunet_includes.h"

class Helpers
{
public:
  Helpers();
  char *GnunetFsDubiousMetaToUtf8(EXTRACTOR_MetaFormat format, const char *data, size_t data_len);
  bool isValidUTF8(const char * str);
};

#endif // HELPERS_H
