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
// --------------------------------------------------------------------------
// Definition file for the texture library
// 
// Author: Michael S. A. Robb
//
// Date:   August 2002
// --------------------------------------------------------------------------

#define LINUX

#ifndef __TEXTURELIB__
#define __TEXTURELIB__

typedef unsigned char TEXBYTE;
typedef unsigned short USHORT;
typedef short SHORT;
typedef unsigned long  ULONG;

#ifndef MATHS_NAME_MAX
#define                 MATHS_NAME_MAX    32
#define                 MATHS_PATH_MAX  260
#endif

typedef char          CTextureName[MATHS_NAME_MAX];
typedef char          CPath[MATHS_PATH_MAX];

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#ifdef WINDOWS
#include <sys\types.h>
#include <sys\stat.h>
#endif
#endif

#include <math.h>


#include "texcolor.h"
#include "colormap.h"
#include "fileutils.h"

// File loaders
#include "texture.h"
#include "texedit.h"
#include "textiff.h"

#endif // __TEXTURELIB__
