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

#ifndef GNUNET_INCLUDES_H
#define GNUNET_INCLUDES_H


#ifndef HAVE_USED_CONFIG_H
#define HAVE_USED_CONFIG_H
#include <gnunet/gnunet_config.h>
#endif

#include <gnunet/platform.h>
#include <gnunet/gnunet_util_lib.h>

#include <gnunet/gnunet_peerinfo_service.h>
#include <gnunet/gnunet_transport_service.h>
#include <gnunet/gnunet_ats_service.h>
#include <gnunet/gnunet_fs_service.h>
#include <gnunet/gnunet_nse_service.h>
#include <gnunet/gnunet_core_service.h>
#include <gnunet/gnunet_arm_service.h>
#include <gnunet/gnunet_transport_plugin.h>
#include <gnunet/gnunet_hello_lib.h>

#endif // GNUNET_INCLUDES_H
