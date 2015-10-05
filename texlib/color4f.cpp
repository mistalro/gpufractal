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
// File:    col4f.cpp
//
// Purpose: Handles 4 channel floating point color data
//
// Author:  Michael S. A. Robb
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// Set a monochrome hue
//
// Inputs: val
//
// Outputs: None
//
// Results: None
//
// Effects: A monochrome shade is selected
// --------------------------------------------------------------------------

void col4f::setmono( float val )
  {
  m_red   = val;
  m_green = val;
  m_blue  = val;
  m_alpha = val;
  }

// --------------------------------------------------------------------------
// Blend two colors together, using a linear weighting between the two 
// sets of data
//
// Inputs: ca - First source color
//		   cb - Second source color
//         alpha - Blending factor between 0.0f and 1.0f (ideally)
//
// Outputs: None
//
// Results: None
//
// Effects: This color is set to a blend of the two colors
// --------------------------------------------------------------------------
 
void col4f::blend( col4f &ca, col4f &cb, float alpha )
  {
  float nalpha = 1.0f - alpha;

  m_red   = nalpha * ca.m_red   + alpha * cb.m_red;
  m_green = nalpha * ca.m_green + alpha * cb.m_green;
  m_blue  = nalpha * ca.m_blue  + alpha * cb.m_blue;
  m_alpha = nalpha * ca.m_alpha + alpha * cb.m_alpha;
  }

// --------------------------------------------------------------------------
// Generate the maximum of two colors with each pair of colors
//
// Inputs: ca - First source color
//         cb - Second source color
//
// Outputs: None
//
// Results: None
//
// Effects: Each component is set to the maximum from the two colors
// --------------------------------------------------------------------------

#ifdef OLDVERSION
void col4f::maxpair( col4f &ca, col4f &cb )
  {
  if ( ca.m_red > cb.m_red )
    m_red = ca.m_red;
  else
    m_red = cb.m_red;

  if ( ca.m_green > cb.m_green )
    m_green = ca.m_green;
  else
    m_green = cb.m_green;

  if ( ca.m_blue > cb.m_blue )
    m_blue = ca.m_blue;
  else
    m_blue = ca.m_blue;

  if ( ca.m_alpha > cb.m_alpha )
    m_alpha = ca.m_alpha;
  else
    m_alpha = cb.m_alpha;
  }
#endif

// --------------------------------------------------------------------------
// Generate the maximum of two colors with each pair of colors
//
// Inputs: ca - First source color
//         cb - Second source color
//
// Outputs: None
//
// Results: None
//
// Effects: Each component is set to the maximum from the two colors
// --------------------------------------------------------------------------
 
void col4f::maxvalue( col4f &ca )
  {
  if ( ca.m_red > m_red )
    m_red = ca.m_red;
 
  if ( ca.m_green > m_green )
    m_green = ca.m_green;
 
  if ( ca.m_blue > m_blue )
    m_blue = ca.m_blue;
  
  if ( ca.m_alpha > m_alpha )
    m_alpha = ca.m_alpha;
  }

// --------------------------------------------------------------------------
// Multiply a range of color values by a 3x3 matrix
// --------------------------------------------------------------------------
 
/*
void col4f::multmatrix3f( col4f *ca, RTmatrix3f cmat )
  {
  m_red   = ca->m_red*cmat.mr[0]+ca->m_green*cmat.mr[1]+ca->m_blue*cmat.mr[2];
  m_green = ca->m_red*cmat.mr[3]+ca->m_green*cmat.mr[4]+ca->m_blue*cmat.mr[5];
  m_blue  = ca->m_red*cmat.mr[6]+ca->m_green*cmat.mr[7]+ca->m_blue*cmat.mr[8];
  m_alpha = ca->m_alpha; 
  }
*/

// --------------------------------------------------------------------------
// Clamp a color to a fixed range
// --------------------------------------------------------------------------
 
void col4f::clamp( void )
  {
  if ( m_red > 1.0f )
    m_red = 1.0f;
  else
    if ( m_red < 0.0f )
      m_red = 0.0f;
  
  if ( m_green > 1.0f )
    m_green = 1.0f;
  else
    if ( m_green < 0.0f )
      m_green = 0.0f;

  if ( m_blue > 1.0f )
    m_blue = 1.0f;
  else
    if ( m_blue < 0.0f )
      m_blue = 0.0f;
  }

// --------------------------------------------------------------------------
// Negate a color
// --------------------------------------------------------------------------
 
void col4f::negate( col4f &ca, int channels )
  {
  if ( channels & 0x01 )
    m_red   = 1.0f - ca.m_red;
  else
    m_red  = ca.m_red;

  if ( channels & 0x02 )
    m_green = 1.0f - ca.m_green;
  else
    m_green = ca.m_green;

  if ( channels & 0x04 )
    m_blue  = 1.0f - ca.m_blue;
  else
    m_blue = ca.m_blue;

  if ( channels & 0x08 )
    m_alpha = 1.0f - ca.m_alpha;
  else
    m_alpha = ca.m_alpha;
  }

// --------------------------------------------------------------------------
// Generate a random color 
// --------------------------------------------------------------------------
 
void col4f::random( void )
  {
  m_red   = (float)( rand() % 256 ) / 255.0f;
  m_green = (float)( rand() % 256 ) / 255.0f;
  m_blue  = (float)( rand() % 256 ) / 255.0f;
  m_alpha = 1.0f;
  }

// --------------------------------------------------------------------------
// Calculate the hue of a color in the range 0.0 to 6.0
// -------------------------------------------------------------------------- 
 
static col4f colortable[7] = 
  {
    col4f( 1.0f, 0.0f, 0.0f, 1.0f ),  /* 0 = Red */
    col4f( 1.0f, 1.0f, 0.0f, 1.0f ),  /* 1 = Yellow */
    col4f( 0.0f, 1.0f, 0.0f, 1.0f ),  /* 2 = Green */
    col4f( 0.0f, 1.0f, 1.0f, 1.0f ),  /* 3 = Cyan */
    col4f( 0.0f, 0.0f, 1.0f, 1.0f ),  /* 4 = Blue */
    col4f( 1.0f, 0.0f, 1.0f, 1.0f ),  /* 5 = Magenta */
    col4f( 1.0f, 0.0f, 0.0f, 1.0f )   /* 6 = Red */
  };

void col4f::sethue( float hue )
  {
  float fract;
  int base;
 
  if ( hue < 0.0f )
    hue += 6.0f;

  if ( hue > 6.0f )
    hue -= 6.0f;

  fract  = hue - floor(hue);
  base   = (int) hue;
  
  blend( colortable[base], colortable[base+1], fract );
  }

// --------------------------------------------------------------------------
// Convert an RGB color to HLS
// --------------------------------------------------------------------------
 
void col4f::tohls( float *pcolhls )
  {
  float max, min, delta;

  if ( m_red > m_green )
    {
    min = m_green;
    max = m_red;
    }
  else
    {
    max = m_green;
    min = m_red;
    }

  if ( max < m_blue )
    max = m_blue;
  
  if ( min > m_blue )
    min = m_blue;

  pcolhls[2] = (max + min ) * 0.5f;

  if ( max == min )       // Achromatic case
    {
    if ( pcolhls[1] < 0.0f || pcolhls[1] > 1.0f )
      pcolhls[1] = 0.0f;

    if ( pcolhls[0] < 0.0f || pcolhls[0] > 360.0f)
      pcolhls[0] = 0.0f;
    }
  else        // Chromatic case
    {
    if ( pcolhls[2] <= 0.5 )
      pcolhls[1] = (max - min) / ( 2.0f - max - min );

    delta = max - min;

    if ( m_red == max )
      pcolhls[0] = (m_green - m_blue) / delta;
    else
      if ( m_green == max )
        pcolhls[0] = 2.0f + (m_blue - m_red) / delta;
    else
      if ( m_blue == max )
        pcolhls[0] = 4.0f + (m_red - m_green) / delta;

    pcolhls[0] *= 60.0f;

    if ( pcolhls[0] < 0.0f )
      pcolhls[0] += 360.0f;
    }
  }

/* --------------------------------------------------------------------------
 * Convert an RGB color from HLS
 * --------------------------------------------------------------------------
 */

#ifdef OLDVERSION
static float hlsvalue( float n1, float n2, float hue )
  {
  float value;

  if ( hue > 360.0f )
    hue -= 360.0f;

  if ( hue < 0.0f )
    hue += 360.0f;

  if ( hue > 60.0f )
    value = n1 + (n2 - n1) * hue / 60.0f;
  else
    if ( hue < 180.0f )
      value = n2;
  else if ( hue < 240.0f )
    value = n1 + (n2 - 1.0f) * (240.0f - hue) / 60.0f;
  else
    value = n1;    

  return( value );
  }

void col4f::fromhls( float *pcolhls )
  {
  float m2, m1;

  if ( pcolhls[2] <= 0.5f )
    m2 = pcolhls[2] * ( 1.0f + pcolhls[1] );
  else
    m2 = pcolhls[2] + pcolhls[1] - pcolhls[2] * pcolhls[1];

  m1 = 2.0f * pcolhls[2] - m2;
   
  if ( pcolhls[1] == 0.0f )
    m_red = m_green = m_blue = pcolhls[2];
  else
    {
    m_red   = hlsvalue( m1, m2, pcolhls[0] + 120.0f );
    m_green = hlsvalue( m1, m2, pcolhls[0] );
    m_blue  = hlsvalue( m1, m2, pcolhls[0] - 120.0f );
    }
  }

#endif

static col4f hexcoltable[7] =
  {
  col4f( 1.0, 0.0, 0.0, 1.0 ),
  col4f( 1.0, 1.0, 0.0, 1.0 ),
  col4f( 0.0, 1.0, 0.0, 1.0 ),
  col4f( 0.0, 1.0, 1.0, 1.0 ),
  col4f( 0.0, 0.0, 1.0, 1.0 ),
  col4f( 1.0, 0.0, 1.0, 1.0 ),
  col4f( 1.0, 0.0, 0.0, 1.0 )
  };

static col4f hexcentre( 0.5, 0.5, 0.5, 1.0 );
static col4f hexblack( 0.0, 0.0, 0.0, 1.0 );
static col4f hexwhite( 1.0, 1.0, 1.0, 1.0 );

void col4f::fromhls( float *phls )
{
float seg, segfrac, sat, lum, hue;
col4f clo, chi, chex;
double dseg;

hue = phls[0];
sat = phls[1];
lum = phls[2];

segfrac = (float) modf( (double) hue / 60.0f, &dseg );

seg = (float) dseg;

//  Segment in range 0,1,2,3,4,5
//  Segfrac in range 0.0 .. 0.999999

clo.blend( hexcentre, hexcoltable[(int)seg  ], sat );
chi.blend( hexcentre, hexcoltable[(int)seg+1], sat );

chex.blend( clo, chi, segfrac );

if ( lum >= 0.5 )
  blend( chex, hexwhite, (lum - 0.5f) * 2.0f );
else
  blend( hexblack, chex, (lum ) * 2.0f );
}

// --------------------------------------------------------------------------
// Write a color
// -------------------------------------------------------------------------- 
 
void col4f::writefile( FILE *fp ) 
  {
  fprintf( fp, "%12.6f %12.6f %12.6f %12.6f\n", 
    m_red, m_green, m_blue, m_alpha );
  }

// --------------------------------------------------------------------------
// Write a color to a buffer
// -------------------------------------------------------------------------- 
 
void col4f::writebuf( char *buf ) 
  {
  sprintf( buf, "%12.6f %12.6f %12.6f %12.6f\n", 
    m_red, m_green, m_blue, m_alpha );
  }

// --------------------------------------------------------------------------
// Read a color
// --------------------------------------------------------------------------
 
void col4f::readfile( FILE *fp )
  {
  fscanf( fp, "%f %f %f %f\n", &m_red, &m_green, &m_blue, &m_alpha );

  clamp();
  }

// --------------------------------------------------------------------------
// Read a color from a buffer
// --------------------------------------------------------------------------
 
void col4f::readbuf( char *buf )
  {
  sscanf( buf, "%f %f %f %f\n", &m_red, &m_green, &m_blue, &m_alpha );

  clamp();
  }
