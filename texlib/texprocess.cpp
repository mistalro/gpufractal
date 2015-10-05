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
// File:  texprocess.cpp
//
// Purpose: Source file used to handle the post-processing of textures
//
// Date:   19th August 2002
//
// Author: Michael S. A. Robb
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// Process the texture
// 
// Inputs: absolute  - Calculate the absolute of the texture
//         normalize - Normalize the texture
//         rgbflag   - Convert the colour mode to 8-bit channel data
//         floatflag - Convert the colour mode to floating point data
//
// Outputs: None
//
// Results: None
//
// Effects: The texture is processed
// --------------------------------------------------------------------------

void CTextureEdit::TextureProcess( int absolute, int normalize, 
			       int rgbflag,  int floatflag, 
			       char *dstfile, int verbose )
{
float flo, fhi;

// ----- Calculate the absolute of the image --------------------------------

if ( absolute )
        {
        if ( verbose )
		printf( "Calculating absolute image\n" );
	
        TextureCalculateAbsolute();
        }

// ----- Normalize the image ------------------------------------------------

if ( normalize )
        {
        if ( verbose )
                printf( "Scaling image into range\n" );

        TextureScaleRange(0.0f, 1.0f, TEX_GLOBALSCALE );
        }

// ----- Sanity check -------------------------------------------------------

if ( verbose )
        {
        TextureFindLimitsChannel( TEX_CHANNELMONO, flo, fhi );

        printf( "Texture limits = %12.6f, %12.6f\n", flo, fhi );
	}

// ----- Change the colour mode ---------------------------------------------

if ( rgbflag || TextureCheckRGB( dstfile ) )
        {
        if ( verbose )
                printf( "Converting to RGB\n" );

        TextureChangeMode( TEX_RGB );
        }

// ----- Convert the image to FLOAT if using scope format -------------------

if ( floatflag || TextureCheckFloat( dstfile ) )
        {
        if ( verbose )
                printf( "Converting to FLOAT\n" );

        TextureChangeMode( TEX_MONOFLOAT32 );
        }
}

