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
// --------------------------------------------------------------------------- 
// File:    texmode.cpp
//
// Purpose: Convert between different texture types 
//
// Author:  Michael S. A. Robb
//
// Date:    August 2002
//
// --------------------------------------------------------------------------
 
#include "texturelib.h"

//#define DEBUG

// --------------------------------------------------------------------------
// Module to handle the changing of pixelmap modes
//
// There are twelve different pixelmap modes (for the moment):
//
// TEX_MONO      TEX_MONOA      TEX_PALETTE     TEX_RGB      TEX_RGBA
// TEX_MONO16    TEX_MONOA16                    TEX_RGB16    TEX_RGBA16
// TEX_MONOFLOAT TEX_MONOAFLOAT                 TEX_RGBFLOAT TEX_RGBAFLOAT
//
// TEX_DUAL
// TEX_DUAL16
// TEX_DUALFLOAT
//                                              
// In theory, there are 12x11 (or 132) different conversions that can be
// performed. Implementing and maintaining these would be very time
// consuming. Fortunately, by arranging the data types into a 3D graph
// a reduction in the number of required paths can be achieved:
//
//        TEX_RGBAFLOAT O<----------------->O TEX_MONOAFLOAT
//                     7^                  7^
//                    / |                 / | 
//                   /  |                /  |
//                  /   |               /   |
//                 L    |TEX_DUALFLOAT L    |
//   TEX_RGBFLOAT O<--------O-------->O  TEX_MONOFLOAT
//                |     |   |         |     |
//                |     |   |         |     |
//           TEX_RGBA16 O<--|---------|---->O TEX_MONOA16
//                |    7^   |         |    7^
//                |   / |   |         |   / | 
//                |  /  |   |         |  /  |
//                | /   |  TEX_DUAL16 | /   |
//                |L    |   |         |L TEX_MONO16
//      TEX_RGB16 O<--------O-------->O     |
//                ^     v   |         ^     v
//                |     O<--|---------|---->O TEX_MONOA
//                |    7  TEX_RGBA    |    7
//                |   /     |         |   /
//                |  /      |         |  /
//                | /       |         | /
//                vL        |         vL
//        TEX_RGB O<--------O-------->O  TEX_MONO
//                 \     TEX_DUAL    7
//                  \               / 
//                   \             /
//                    \           /
//                     \         / 
//                      \       /
//                       \     /
//                        \   / 
//                         \ /
//                          O TEX_PALETTE
//
// These can be reduced down to five stages:
// 
//   o Alpha addition/removal
//   o 8 bit/16 bit conversion 
//   O Colorification/Monochromatisation
//   o Quantisation/Palette expansion
//   
// Add Alpha/Remove Alpha:             8 bit/16 bit conversion
//
//   TEX_MONO     <-> TEX_MONOA         TEX_MONO    <-> TEX_MONO16
//   TEX_RGB      <-> TEX_RGBA          TEX_RGB     <-> TEX_RGB16
//   TEX_MONO16   <-> TEX_MONOA16       TEX_MONOA   <-> TEX_MONOA16
//   TEX_RGB16    <-> TEX_RGBA16        TEX_RGBA    <-> TEX_RGBA16
//   TEX_MONOFLOAT<-> TEX_MONOAFLOAT
//   TEX_RGBFLOAT <-> TEX_RGBAFLOAT     
//
// Monochromatisation/Colorification   Quantisation/Palette Expansion
//
//   TEX_RGB      <-> TEX_MONO          TEX_RGB     <-> TEX_PALETTE
//   TEX_RGBA     <-> TEX_MONOA         TEX_MONO    <-> TEX_PALETTE
//   TEX_RGB16    <-> TEX_MONO16
//   TEX_RGBA16   <-> TEX_MONOA16
//   TEX_RGBFLOAT <-> TEX_MONOFLOAT
//   TEX_RGBAFLOAT <-> TEX_MONOAFLOAT
//
// 16 bit/float conversion             
//
//   TEX_MONO16  <-> TEX_MONOFLOAT
//   TEX_RGB16   <-> TEX_RGBFLOAT
//   TEX_MONOA16 <-> TEX_MONOAFLOAT
//   TEX_RGBA16  <-> TEX_RGBAFLOAT
//
// Dual/Mono conversion                 RGB/Dual conversion
//
//   TEX_MONO      <-> TEX_DUAL         TEX_DUAL      <-> TEX_RGB
//   TEX_MONO16    <-> TEX_DUAL16       TEX_DUAL16    <-> TEX_RGB16
//   TEX_MONOFLOAT <-> TEX_DUALFLOAT    TEX_DUALFLOAT <-> TEX_RGBFLOAT
// 
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Set the alpha color
// --------------------------------------------------------------------------

void CTextureEdit::TextureAlphaSet( float value )
{
int nx, ny, compval;
TEXBYTE *dbptr;
SHORT *dsptr;
float *dfptr;

#ifdef DEBUG
printf( "Called; TextureAlphaSet\n");
#endif

if ( !(m_type & TEX_RGB) )	// Only handle RGB data 
	return;	

if ( !(m_type & TEX_ALPHA ))
	TextureAlphaInsert();			// Or Return?...

switch ( m_type & TEX_BITSIZES )
    {
    case TEX_8BIT:
	    compval = (int) (value * 255.0f);

	    dbptr = (TEXBYTE *) m_pdata+m_nelements-1;

	    for ( ny = 0; ny < m_height; ny++ )
		    for ( nx = 0; nx < m_width; nx++ )
                { 
			    *dbptr = compval;
                dbptr += m_nelements;
                }
        break;

    case TEX_16BIT:
	    compval = (int) (value * 65535.0f);

	    dsptr = (SHORT *) m_pdata+m_nelements-1;

	    for ( ny = 0; ny < m_height; ny++ )
		    for ( nx = 0; nx < m_width; nx++ )
                {
			    *dsptr = compval;
                dsptr += m_nelements;
                }
        break;

    case TEX_32BIT|TEX_FLOAT:
        dfptr = (float *) m_pdata+m_nelements-1;
        
        for ( ny = 0; ny < m_height; ny++ )
            for ( nx = 0; nx < m_width; nx++ )
                {
                *dfptr = value;
                dfptr += m_nelements;
                }
        break;

    default:
        break;
    }
}

// --------------------------------------------------------------------------
// Remove the Alpha channel
// --------------------------------------------------------------------------

void CTextureEdit::TextureAlphaRemove( void )
{
int  newmode, npixels, pn, cn, ncomps;
TEXBYTE  *newbuf, *sbptr, *dbptr;
SHORT *ssptr, *dsptr;
float *sfptr, *dfptr;

#ifdef DEBUG
printf( "Called: TextureAlphaRemove\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( ~(newmode & TEX_ALPHA) )                  // Sanity check 
  return;

newmode &= ~TEX_ALPHA;

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );  

npixels = m_area;
ncomps  = m_nelements;

newbuf  = new TEXBYTE[npixels*m_pixelsize];

if ( !newbuf  )                    // No new buffer, so return 
  return;

switch ( newmode & TEX_BITSIZES )
    {
    case TEX_8BIT:
        dbptr = newbuf;
        sbptr = m_pdata;
     
        for ( pn = 0; pn < npixels; pn++ )
	    {
            for ( cn = 0; cn < ncomps-1; cn++ )   // Copy all 
                *dbptr++ = *sbptr++;

            sbptr++;  // Skip alpha 
	    }
        break;

    case TEX_16BIT:
        dsptr = (SHORT *) newbuf;
        ssptr = (SHORT *) m_pdata;

        for ( pn = 0; pn < npixels; pn++ )
  	    {
            for ( cn = 0; cn < ncomps-1; cn++ )  // Copy all but alpha 
                *dsptr++ = *ssptr++;

            ssptr++;    // Skip alpha 
	    }
        break;

    case TEX_32BIT|TEX_FLOAT:
        dfptr = (float *) newbuf;
        sfptr = (float *) m_pdata;

        for ( pn = 0; pn < npixels; pn++ )
	    {
            for ( cn = 0; cn < ncomps-1; cn++ )  // Copy all but alpha 
                *dfptr++ = *sfptr++;

            sfptr++;    // Skip alpha 
	    }
        break;

    default:
        break;
    }
   
// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;       // Remove old buffer 

m_pdata  = newbuf;     // Set new buffer 
m_size   = m_pixelsize * m_area;   // Set new memory size 
m_type   = newmode;   // Conversion is done 
}

// --------------------------------------------------------------------------
// Insert the Alpha channel
// --------------------------------------------------------------------------
 
void CTextureEdit::TextureAlphaInsert( void )
{
int  newmode, npixels, pn, cn, ncomps;
TEXBYTE  *newbuf, *sbptr, *dbptr;
SHORT *ssptr, *dsptr;
float *sfptr, *dfptr;

#ifdef DEBUG
printf( "Called; TextureAlphaInsert\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( newmode & (TEX_ALPHA|TEX_PALETTE) ) // Sanity check 
  return;

newmode |= TEX_ALPHA;

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

npixels = m_width * m_height;
ncomps  = m_nelements-1;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];

if ( !newbuf )                // No new buffer, so return 
  return;

switch ( newmode & TEX_BITSIZES )
    {
    case TEX_8BIT:
        dbptr = newbuf;
        sbptr = m_pdata;
    
        for ( pn = 0; pn < npixels; pn++ )
            {
            for ( cn = 0; cn < ncomps; cn++ )
                *dbptr++ = *sbptr++;
       
            *dbptr++ = 0xFF;        // Add default alpha 
            }
        break;

    case TEX_16BIT:
        dsptr = (SHORT *) newbuf;
        ssptr = (SHORT *) m_pdata;
    
        for ( pn = 0; pn < npixels; pn++ )
            {
            for ( cn = 0; cn < ncomps; cn++ ) 
                *dsptr++ = *ssptr++;

            *dsptr++ = (SHORT) 0xFFFF;  // Add default alpha 
            }
        break;

    case TEX_32BIT|TEX_FLOAT:
        dfptr = (float *) newbuf;
        sfptr = (float *) m_pdata;
    
        for ( pn = 0; pn < npixels; pn++ )
            {
            for ( cn = 0; cn < ncomps; cn++ ) 
                *dfptr++ = *sfptr++;

            *dfptr++ = (float) 1.0f;  // Add default alpha 
            }
        break;

    default:
        break;
    }
  
// ----- Destroy old memory and set new sizes -----

delete [] m_pdata;

m_pdata  = newbuf;

m_size  = m_pixelsize * m_area;
m_pitch = m_pixelsize * m_width;
m_type  = newmode;   
}

// --------------------------------------------------------------------------
// Expand component size from 8-bits to 16-bits
// --------------------------------------------------------------------------

void CTextureEdit::TextureExpand8to16bit( void )
{
int  newmode, npixels, ncomps, pn;
SHORT *dsptr, *newbuf;
TEXBYTE  *sbptr;

#ifdef DEBUG
printf( "Called: TextureExpand8to16bit\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( newmode & (TEX_16BIT|TEX_32BIT|TEX_FLOAT|TEX_PALETTE) )  // Sanity check 
  return;

newmode ^= (TEX_16BIT|TEX_8BIT);

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

ncomps  = m_pixelsize / m_compsize;
npixels = m_width * m_height * ncomps;

newbuf  = new short[ npixels*m_pixelsize ];
                   
sbptr   = m_pdata;
dsptr   = (SHORT *) newbuf;
  
for ( pn = 0; pn < npixels; pn++ )
  *dsptr++ = (SHORT) ( *sbptr++ * 0x0101 );
  
// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;

m_pdata  = (TEXBYTE *) newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_pixelsize * m_width;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Reduce component size from 8-bits to 16-bits
// --------------------------------------------------------------------------
 
void CTextureEdit::TextureReduce16to8bit( void )
{
int  newmode, npixels, ncomps, pn;
SHORT *ssptr;
TEXBYTE  *dbptr, *newbuf;

#ifdef DEBUG
printf( "Called: TextureReduce16to8bit\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( !(newmode & TEX_16BIT ) )
  return;

newmode ^= (TEX_16BIT|TEX_8BIT);

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

ncomps  = m_pixelsize / m_compsize;
npixels = m_width * m_height * ncomps;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];

ssptr = (SHORT *) m_pdata;
dbptr = newbuf;

for ( pn = 0; pn < npixels; pn++ )
  *dbptr++ = (TEXBYTE) ( *ssptr++ / 0x0101 );
   
// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;

m_pdata  = newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Convert from RGB to dual 
// --------------------------------------------------------------------------

void CTextureEdit::TextureRGBToDual( void )
{
int  newmode, pn, npixels;
float *dfptr, *sfptr;
SHORT *dsptr, *ssptr;
TEXBYTE  *dbptr, *sbptr, *newbuf;

#ifdef DEBUG
printf( "Called: TextureRGBToDual\n");
#endif
// ----- Determine new mode ------------

newmode = m_type;

if ( newmode & TEX_DUAL )   // Sanity check
  return;

newmode ^= (TEX_DUAL|TEX_RGB3);
newmode &= ~TEX_ALPHA;

// ----- Allocate new memory and determine pixel size ----------

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

npixels = m_width * m_height;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];

switch ( newmode & TEX_BITSIZES )
    {
    case TEX_8BIT:
        sbptr = m_pdata;
        dbptr = newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dbptr++ = *sbptr++;        // Write red
            *dbptr++ = *sbptr++;        // Write green
	    dbptr++;			// Skip blue

	     if ( newmode & TEX_ALPHA )	// Skip alpha
		dbptr++;
            }
        break;

    case TEX_16BIT:
        ssptr = (SHORT *) m_pdata;
        dsptr = (SHORT *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dsptr++ = *ssptr++;          // Write red
            *dsptr++ = *ssptr++;          // Write green
	     dsptr++;			  // Skip blue

	     if ( newmode & TEX_ALPHA )	  // Skip alpha
		dbptr++;
            }
        break;

    case TEX_32BIT|TEX_FLOAT:
        sfptr = (float *) m_pdata;
        dfptr = (float *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dfptr++ = *sfptr++;        // Write red
            *dfptr++ = *sfptr++;        // Write green
	     dfptr++;			// Skip blue

	     if ( newmode & TEX_ALPHA )	// Skip alpha
		dbptr++;
            }
        break;

    default:
        break;
    }

// ----- Destroy old memory and set new sizes -----

delete [] m_pdata;

m_pdata  = newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Convert from dual to RGB
// --------------------------------------------------------------------------

void CTextureEdit::TextureDualToRGB( void )
{
int  newmode, pn, npixels;
float *dfptr, *sfptr;
SHORT *dsptr, *ssptr;
TEXBYTE  *dbptr, *sbptr, *newbuf;

#ifdef DEBUG
printf( "Called: TextureDualToRGB\n");
#endif
// ----- Determine new mode ------------

newmode = m_type;

if ( newmode & TEX_RGB3 )   // Sanity check
  return;

newmode ^= (TEX_DUAL|TEX_RGB3);

// ----- Allocate new memory and determine pixel size ----------

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

npixels = m_width * m_height;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];

switch ( newmode & TEX_BITSIZES )
    {
    case TEX_8BIT:
        sbptr = m_pdata;
        dbptr = newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dbptr++ = *sbptr++;        // Write red
            *dbptr++ = *sbptr++;        // Write green
            *dbptr++ = 0;               // Write blue
            }
        break;

    case TEX_16BIT:
        ssptr = (SHORT *) m_pdata;
        dsptr = (SHORT *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dsptr++ = *ssptr++;          // Write red
            *dsptr++ = *ssptr++;          // Write green
	    *dsptr++ = 0;		  // Write blue
            }
        break;

    case TEX_32BIT|TEX_FLOAT:
        sfptr = (float *) m_pdata;
        dfptr = (float *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dfptr++ = *sfptr++;        // Write red
            *dfptr++ = *sfptr++;        // Write green
	    *dfptr++ = 0;		// Write blue
            }
        break;

    default:
        break;
    }

// ----- Destroy old memory and set new sizes -----

delete [] m_pdata;

m_pdata  = newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Convert from dual to mono
// --------------------------------------------------------------------------

void CTextureEdit::TextureDualToMono( void )
{

}

// --------------------------------------------------------------------------
// Convert from mono to dual
// --------------------------------------------------------------------------

void CTextureEdit::TextureMonoToDual( void )
{

}

// --------------------------------------------------------------------------
// Convert from monochrome to RGB
// --------------------------------------------------------------------------
 
void CTextureEdit::TextureMonoToRGB( void ) 
{
int  newmode, pn, npixels;
float *dfptr, *sfptr;
SHORT *dsptr, *ssptr;
TEXBYTE  *dbptr, *sbptr, *newbuf;

#ifdef DEBUG
printf( "Called: TextureMonoToRGB\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( newmode & TEX_RGB3 )   // Sanity check 
  return;

newmode ^= (TEX_MONO|TEX_RGB3);

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

npixels = m_width * m_height;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];

switch ( newmode & TEX_BITSIZES )
    {
    case TEX_8BIT:
#ifdef DEBUG
	printf( "(8-bit)\n");
#endif
        sbptr = m_pdata;
        dbptr = newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dbptr++ = *sbptr;		// Write red   
            *dbptr++ = *sbptr;		// Write green 
            *dbptr++ = *sbptr;		// Write blue  
            sbptr++;

            if ( newmode & TEX_ALPHA )  // Write alpha 
                *dbptr++ = *sbptr++;
            }
        break;

    case TEX_16BIT:
#ifdef DEBUG
	printf( "(16-bit)\n");
#endif
        ssptr = (SHORT *) m_pdata;
        dsptr = (SHORT *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dsptr++ = *ssptr;          // Write red   
            *dsptr++ = *ssptr;          // Write green 
            *dsptr++ = *ssptr;          // Write blue  
            ssptr++;

            if ( newmode & TEX_ALPHA )  // Write alpha 
                *dsptr++ = *ssptr++;      
            }
        break;

    case TEX_32BIT|TEX_FLOAT:
#ifdef DEBUG
	printf( "(32-bit)\n");
#endif
        sfptr = (float *) m_pdata;
        dfptr = (float *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            *dfptr++ = *sfptr;          // Write red   
            *dfptr++ = *sfptr;          // Write green 
            *dfptr++ = *sfptr;          // Write blue  
            sfptr++;

            if ( newmode & TEX_ALPHA )  // Write alpha 
                *dfptr++ = *sfptr++;
            }
        break;

    default:
	printf( "MonoToRGB: Unknown mode conversion\n");
        break;
    }

// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;

m_pdata  = newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = newmode;
}
   
// --------------------------------------------------------------------------
// Convert from monochrome to color
// --------------------------------------------------------------------------

void CTextureEdit::TextureRGBToMono( void )
{
int curmode, newmode, pn, npixels;
SHORT   *dsptr, *ssptr;
TEXBYTE *dbptr, *sbptr, *newbuf, resbyte;
float   *dfptr, *sfptr;
float    cr,cg,cb, result;

#ifdef DEBUG
printf( "Called: TextureRGBToMono\n");
#endif
// ----- Determine new mode ------------

newmode = curmode = m_type;
newmode &= ~TEX_RGB;

newmode |= TEX_MONO ;

// ----- Allocate new memory and determine pixel size ----------

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

npixels = m_width * m_height;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];
                       
switch ( curmode & TEX_BITSIZES )
    {
    case TEX_8BIT:
        sbptr = m_pdata;
        dbptr = newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            cr = (float) *sbptr++;    // Read red   
            cg = (float) *sbptr++;    // Read green 
            cb = (float) *sbptr++;    // Read blue  

            result = ( cr * 0.299f + cg * 0.587f + cb * 0.114f );

			resbyte = (TEXBYTE) result;

			*dbptr = resbyte;

			dbptr++;

            if ( curmode & TEX_ALPHA )   // Write alpha
                *dbptr++ = *sbptr++;
            }
        break;

    case TEX_16BIT:
        ssptr = (SHORT *) m_pdata;
        dsptr = (SHORT *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            cr = (float) *ssptr++;   // Read red    
            cg = (float) *ssptr++;   // Read green 
            cb = (float) *ssptr++;   // Read blue  

           *dsptr++ = (SHORT) (cr * 0.299f + cg * 0.587f + cb * 0.114f );

           if ( curmode & TEX_ALPHA )   // Write alpha
                *dsptr++ = *ssptr++;
            }
        break;

    case TEX_32BIT|TEX_FLOAT:
        sfptr = (float *) m_pdata;
        dfptr = (float *) newbuf;

        for ( pn = 0; pn < npixels; pn++ )
            {
            cr = (float) *sfptr++;   // Read red    
            cg = (float) *sfptr++;   // Read green 
            cb = (float) *sfptr++;   // Read blue  

            *dfptr++ = (float) (cr * 0.299f + cg * 0.587f + cb * 0.114f );

            if ( curmode & TEX_ALPHA )   // Write alpha
                *dfptr++ = *sfptr++;
            }
        break;

    default:
        break;
    }
        
// ----- Destroy old memory and set new sizes -----

delete [] m_pdata;

m_pdata  = newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_pixelsize * m_width;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Convert monochrome to palette
// --------------------------------------------------------------------------

void CTextureEdit::TextureMonoToPalette( void )
{
#ifdef DEBUG
printf( "Called: TextureMonoToPalette\n");
#endif

if ( m_type == TEX_MONO )       // MONOCHROME to PALETTE
  m_type = TEX_PALETTE;    // Same size, so just toggle mode
}

// --------------------------------------------------------------------------
// Convert palette to monochrome
// --------------------------------------------------------------------------

void CTextureEdit::TexturePaletteToRGB( void )
{
int   newmode, pn, npixels, idx;
TEXBYTE   *dbptr, *sbptr, *newbuf;
colmap4f *cptr;

#ifdef DEBUG
printf( "Called: TexturePaletteToRGB\n");
#endif
// ----- Determine new mode ------------

newmode = m_type;

if ( newmode != TEX_PALETTE )
  return;

newmode = TEX_RGB;

// ----- Allocate new memory and determine pixel size ----------

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

npixels = m_width * m_height * m_nelements;

newbuf = new TEXBYTE[ npixels*m_pixelsize ];

dbptr  = newbuf;
sbptr  = m_pdata;
cptr   = m_pcolormap;

for ( pn = 0; pn < npixels; pn++ )     
  {
  idx = *sbptr++;     // Read index

  *dbptr++ = (TEXBYTE)( cptr->m_list[idx].m_red   * 255.0f);  // Write red  
  *dbptr++ = (TEXBYTE)( cptr->m_list[idx].m_green * 255.0f);  // Write green
  *dbptr++ = (TEXBYTE)( cptr->m_list[idx].m_blue  * 255.0f);  // Write blue 
  }

if ( cptr )
  {
  delete cptr;

  m_pcolormap = NULL;
  }
  
// ----- Destroy old memory and set new sizes -----

delete [] m_pdata;

m_pdata  = newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Convert palette to monochrome
// --------------------------------------------------------------------------

void CTextureEdit::TexturePaletteToMono( void )
{
int   newmode, pn, idx, npixels;
TEXBYTE   *dbptr, *sbptr, *newbuf;
colmap4f *cptr;
float   cr,cg,cb;

#ifdef DEBUG
printf( "Called: TexturePaletteToMono\n");
#endif
// ----- Determine new mode ------------

newmode = m_type;

if ( newmode != TEX_PALETTE || !m_pcolormap )
  return;

// ----- Allocate new memory and determine pixel size ----------
TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

npixels = m_width * m_height * m_compsize;

newbuf = new TEXBYTE[ npixels*m_pixelsize ];

dbptr  = newbuf;
sbptr  = m_pdata;
cptr   = m_pcolormap;

for ( pn = 0; pn < npixels; pn++ )
  {
  idx = *sbptr++;     // Read index

  cr  = cptr->m_list[idx].m_red;
  cg  = cptr->m_list[idx].m_green;
  cb  = cptr->m_list[idx].m_blue;

  *dbptr++ = 
    (TEXBYTE)(( cr * 0.299f + cg * 0.587f + cb * 0.114f ) * 255.0f);
  }

TexturePaletteToMono();

// ----- Destroy old memory and set new sizes -----

delete [] m_pdata;

m_pdata  = newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = TEX_MONO;
}

// ==========================================================================
// NEW STUFF
// ==========================================================================

// --------------------------------------------------------------------------
// Expand component size from 8-bits to float
// --------------------------------------------------------------------------

void CTextureEdit::TextureExpand8bitToFloat( void )
{
int      newmode, npixels, ncomps, pn;
float   *dsptr;
TEXBYTE *newbuf;
TEXBYTE *sbptr;

#ifdef DEBUG
printf( "Called: TextureExpand8bitToFloat\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( newmode & TEX_FLOAT || newmode == TEX_PALETTE )  // Sanity check 
  return;

newmode |= TEX_FLOAT|TEX_32BIT;

newmode &= ~TEX_8BIT;

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

ncomps  = m_pixelsize / m_compsize;
npixels = m_width * m_height * ncomps;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];
                   
sbptr   = (TEXBYTE *) m_pdata;
dsptr   = (float *) newbuf;
  
for ( pn = 0; pn < npixels; pn++ )
  *dsptr++ = ( (float) *sbptr++ / 255.0f );
  
// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;

m_pdata  = (TEXBYTE *) newbuf;
m_size   = m_pixelsize * m_area;
m_pitch  = m_pixelsize * m_width;
m_type   = newmode;
}

// --------------------------------------------------------------------------
// Expand component size from 16-bits to float
// --------------------------------------------------------------------------

void CTextureEdit::TextureExpand16bitToFloat( void )
{
int  newmode, npixels, ncomps, pn;
float *dsptr;
TEXBYTE *newbuf;
short *sbptr;

#ifdef DEBUG
printf( "Called: TextureExpand16bitToFloat\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( newmode & TEX_FLOAT || newmode == TEX_PALETTE )  // Sanity check 
  return;

newmode |=  TEX_FLOAT|TEX_32BIT;
newmode &= ~TEX_16BIT;

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

ncomps  = m_pixelsize / m_compsize;
npixels = m_width * m_height * ncomps;

newbuf  = new TEXBYTE[ npixels*m_pixelsize ];
                   
sbptr   = (short *) m_pdata;
dsptr   = (float *) newbuf;
  
for ( pn = 0; pn < npixels; pn++ )
  *dsptr++ = ( (float) *sbptr++ / 65535.0f );
  
// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;

m_pdata  = (TEXBYTE *) newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_pixelsize * m_width;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Reduce component size from float to 8-bits
// --------------------------------------------------------------------------

void CTextureEdit::TextureReduceFloatTo8bit( void )
{int  newmode, npixels, ncomps, pn;
float *ssptr;
TEXBYTE *dbptr, *newbuf;

#ifdef DEBUG
printf( "Called: TextureReduceFloatTo8bit\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( !(newmode & TEX_FLOAT ) )
  return;

newmode ^= (TEX_FLOAT|TEX_8BIT|TEX_32BIT);

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

ncomps  = m_pixelsize * m_compsize;
npixels = m_width * m_height * ncomps;
newbuf  = new TEXBYTE[ npixels*m_pixelsize ];
ssptr   = (float *) m_pdata;
dbptr   = newbuf;

for ( pn = 0; pn < npixels; pn++ )
  *dbptr++ = (TEXBYTE) ( *ssptr++ * 255.0f );
   
// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;

m_pdata = (TEXBYTE *) newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Reduce component size from float to 16-bits
// --------------------------------------------------------------------------
 
void CTextureEdit::TextureReduceFloatTo16bit( void )
{
int  newmode, npixels, ncomps, pn;
float *ssptr;
SHORT *dbptr, *newbuf;

#ifdef DEBUG
printf( "Called: TextureReduceFloatTo16bit\n");
#endif
// ----- Determine new mode ------------ 

newmode = m_type;

if ( !(newmode & TEX_FLOAT ) )
  return;

newmode ^= (TEX_FLOAT|TEX_16BIT);

// ----- Allocate new memory and determine pixel size ---------- 

TextureGetSize( newmode, &m_compsize, &m_pixelsize, &m_nelements );

ncomps  = m_pixelsize * m_compsize;
npixels = m_width * m_height * ncomps;
newbuf  = new short[ npixels*m_pixelsize ];
ssptr   = (float *) m_pdata;
dbptr   = newbuf;

for ( pn = 0; pn < npixels; pn++ )
  *dbptr++ = (TEXSHORT) ( *ssptr++ * 65535.0f );
   
// ----- Destroy old memory and set new sizes ----- 

delete [] m_pdata;

m_pdata = (TEXBYTE *) newbuf;
m_size  = m_pixelsize * m_area;
m_pitch = m_width * m_pixelsize;
m_type  = newmode;
}

// --------------------------------------------------------------------------
// Given a pixelmap and the pixel format, convert the pixelmap
// --------------------------------------------------------------------------

void CTextureEdit::TextureChangeMode( int newmode )
{
int curmode, diffmode;

#ifdef DEBUG
printf( "Called: TextureChangeMode\n");
#endif
curmode = m_type;

if ( curmode == newmode )               // Same type? Then do nothing
    return;

diffmode = curmode ^ newmode;

// ----- Get from TEX_PALETTE to TEX_RGB or TEX_MONO ---------------

if ( curmode == TEX_PALETTE && (newmode & TEX_MONO) )
    TexturePaletteToMono();

if ( curmode == TEX_PALETTE && (newmode & TEX_RGB) )
    TexturePaletteToRGB();

// ----- Traverse through the TEX_RGB and TEX_MONO types -----------

if (diffmode & TEX_ALPHA )			  // Need to modify alpha?
	{
	if ( curmode & TEX_ALPHA )          
		TextureAlphaRemove();		  // Remove alpha
	else
		TextureAlphaInsert();		  // Insert alpha
	}

// Conversion from float to 16-bit or 8-bit
// Conversion from 16-bit to float
// Conversion from 8-bit to float
// In all cases float will be set

if ( diffmode & TEX_FLOAT )		      // Need to modify float?
	{
	if ( curmode & TEX_FLOAT )		  // Already in float
		{
		if ( diffmode & TEX_16BIT )
			TextureReduceFloatTo16bit();

		if ( diffmode & TEX_8BIT )
			TextureReduceFloatTo8bit();
		}
	else
		{
		if ( diffmode & TEX_16BIT )
			TextureExpand16bitToFloat();
	
		if ( diffmode & TEX_8BIT )
			TextureExpand8bitToFloat();
		}
	}

diffmode = newmode ^ m_type;

if ( diffmode & TEX_16BIT )           // Need to modify component size?
	{
	if ( curmode & TEX_16BIT )
		TextureReduce16to8bit();      // Reduce component size
	else
		TextureExpand8to16bit();      // Enlarge component size
	}

if ( diffmode & TEX_DUAL )	      // Change RGB <-> Dual?
	{
	if ( curmode & TEX_RGB3 )		
		TextureRGBToDual();	      // RGB to Dual
	else
		TextureDualToRGB();	      // Dual to RGB
	}

if ( diffmode & TEX_MONO )            // Change RGB <-> MONO?
	{
	if ( curmode & TEX_RGB3 )
		TextureRGBToMono();           // RGB to MONO
	else
		TextureMonoToRGB();           // MONO TO RGB
	}

// ----- Get from TEX_RGB or TEX_MONO to TEX_PALETTE ------------------

if ((curmode & TEX_MONO) && (newmode == TEX_PALETTE)) // MONO to PALETTE
    TextureMonoToPalette();

if ((curmode == TEX_RGB) && (newmode == TEX_PALETTE)) // RGB to PALETTE
    TextureQuantize( 256 );
}
