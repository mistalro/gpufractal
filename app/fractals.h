/* Copyright (C) 2015 Dr. Michael Robb

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General License
   as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Public License for more details.

   You should have received a copy of the GNU Public License 
   along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef FRACTALS_H_
#define FRACTALS_H_

// ----- Kernel/systems programming -----

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <assert.h>

// ----- C++ library -----

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

// ----- File reading/writing -----

#include "filesysascii.h"
#include "texlib.h"

// ----- Timers -----

#include "cputimer.h"

// ----- Network configuration -----

typedef unsigned char FRbyte;

#include "netnodeentryio.h"
#include "netnode.h"
#include "netnodeentrylistio.h"

// ----- Fractal parameters -----

#include "fractparamsio.h"
#include "fractparams.h"
#include "fractparamslistio.h"
#include "fractparamslist.h"

// ----- Compute shaders -----

#include "computeformats.h"

// ----- GUI level -----

#include "glx.h"
#include "fractplayer.h"
#include "fractwindow.h"
#include "fractnet.h"
#include "fractsystem.h"

extern CSystemParameters g_sysparams;

#endif	// FRACTALS_H_
