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
// --------------------------------------------------------------------------:
// Source file used to provide the definition of the texture class
// 
// Date:   19th August 2002
//
// Author: Michael S. A. Robb
//
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// Clear a texture
//
// Inputs: red   - Red in floating point
//         green - Green in floating point
//         blue  - Blue in floating point
//         alpha - Alpha in floating point
//
// Outputs: None
//
// Results: None
//
// Effects: The texture is cleared
// --------------------------------------------------------------------------

void CTextureEdit::TextureClear( float red,  float green, 
                             float blue, float alpha )
{ 
TEXBYTE  *p1bdst, p1bsrc;
TEXSHORT *p1sdst, p1ssrc;
float *p1fdst, p1fsrc;
col2b *p2bdst,p2bsrc;
col2s *p2sdst,p2ssrc;
col2f *p2fdst,p2fsrc;
col3b *p3bdst,p3bsrc;
col3s *p3sdst,p3ssrc;
col3f *p3fdst,p3fsrc;
col4b *p4bdst,p4bsrc;
col4s *p4sdst,p4ssrc;
col4f *p4fdst,p4fsrc;

int px, py;

switch ( m_type & TEX_MODEMASK )
    {
    case TEX_MONO:
        p1bsrc = (int)( red * 255.0f );
        p1bdst = (TEXBYTE *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p1bdst++ = p1bsrc;
        break;

    case TEX_MONOA8:
        p2bsrc.m_mono  = (int)(  red * 255.0f );
        p2bsrc.m_alpha = (int) ( alpha * 255.0f );

        p2bdst = (col2b *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p2bdst++ = p2bsrc;
        break;
        
    case TEX_MONO16:
        p1ssrc = (TEXSHORT) ( red * 65535.0f );
        p1sdst = (TEXSHORT *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p1sdst++ = p1ssrc; 
        break;

    case TEX_MONOA16:
        p2ssrc.m_mono  = (int)( red   * 65535.0f );
        p2ssrc.m_alpha = (int)( alpha * 65535.0f );
        
        p2sdst = (col2s *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p2sdst++ = p2ssrc;
        break;
        
    case TEX_MONOFLOAT:
        p1fsrc = red;

        p1fdst = (float *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p1fdst++ = p1fsrc;
        break;

    case TEX_MONOAFLOAT:
        p2fsrc.m_mono = red;
        p2fsrc.m_alpha = alpha;

        p2fdst = (col2f *) m_pdata;

        for ( py = 0; py < m_height; py++ )     
            for ( px = 0; px < m_width; px++ )
                *p2fdst++ = p2fsrc;
         
        break;

    case TEX_DUAL:
  	p2bsrc.m_mono  = (int) ( red   * 255.0f );
        p2bsrc.m_alpha = (int) ( green * 255.0f );

        p2bdst = (col2b *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p2bdst++ = p2bsrc;
	break;

    case TEX_DUAL16:
        p2ssrc.m_mono  = (int)( red   * 65535.0f );
        p2ssrc.m_alpha = (int)( green * 65535.0f );

        p2sdst = (col2s *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p2sdst++ = p2ssrc;
        break;

    case TEX_DUALFLOAT:
	p2fsrc.m_mono = red;
	p2fsrc.m_alpha = green;
	
	p2fdst = (col2f *) m_pdata;

        for ( py = 0; py < m_height; py++ )     
            for ( px = 0; px < m_width; px++ )
                *p2fdst++ = p2fsrc;
	break;

    case TEX_RGB:
        p3bsrc.m_red   = (TEXBYTE)( red   * 255.0f );
        p3bsrc.m_green = (TEXBYTE)( green * 255.0f );
        p3bsrc.m_blue  = (TEXBYTE)( blue  * 255.0f );

        p3bdst = (col3b *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p3bdst++ = p3bsrc;
        break;

    case TEX_RGBA:
        p4bsrc.m_red   = (TEXBYTE)( red   * 255.0f );
        p4bsrc.m_green = (TEXBYTE)( green * 255.0f );
        p4bsrc.m_blue  = (TEXBYTE)( blue  * 255.0f );
        p4bsrc.m_alpha = (TEXBYTE)( alpha * 255.0f );

        p4bdst = (col4b *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p4bdst++ = p4bsrc;

        break;

    case TEX_RGB16:
        p3ssrc.m_red   = (TEXSHORT)( red   * 65535.0f );
        p3ssrc.m_green = (TEXSHORT)( green * 65535.0f );
        p3ssrc.m_blue  = (TEXSHORT)( blue  * 65535.0f );
     
        p3sdst = (col3s *) m_pdata;

        for ( py = 0; py < m_height; py++ )
           for ( px = 0; px < m_width; px++ )
                *p3sdst++ = p3ssrc;

        break;

    case TEX_RGBA16: 
        p4ssrc.m_red   = (TEXSHORT)( red   * 65535.0f );
        p4ssrc.m_green = (TEXSHORT)( green * 65535.0f );
        p4ssrc.m_blue  = (TEXSHORT)( blue  * 65535.0f );
        p4ssrc.m_alpha = (TEXSHORT)( alpha * 65535.0f );

        p4sdst = (col4s *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p4sdst++ = p4ssrc;

        break;

    case TEX_RGBFLOAT:
        p3fsrc.m_red = red;
        p3fsrc.m_green = green;
        p3fsrc.m_blue = blue;

        p3fdst = (col3f *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p3fdst++ = p3fsrc;

        break;

    case TEX_RGBAFLOAT:
        p4fsrc.m_red = red;
        p4fsrc.m_green = green;
        p4fsrc.m_blue = blue;
        p4fsrc.m_alpha = alpha;

        p4fdst = (col4f *) m_pdata;

        for ( py = 0; py < m_height; py++ )
            for ( px = 0; px < m_width; px++ )
                *p4fdst++ = p4fsrc;
        break;

    default:
        break;  
    }
}

// --------------------------------------------------------------------------
// Clear a range of memory in the texture
//
// Inputs: xlo - Lower X coordinate
//         ylo - Lower Y coordinate
//         xhi - Higher X coordinate
//         yhi - Higher Y coordinate
//
// Outputs: None
//
// Results: None
//
// Effects: An area of the texture is cleared
// --------------------------------------------------------------------------

void CTextureEdit::TextureClearRange( int xlo, int ylo, int xhi, int yhi,
                                  float red, float green, float blue, float alpha )
{
TEXBYTE  *p1bdst, *p1btmp, p1bsrc;
TEXSHORT *p1sdst, *p1stmp, p1ssrc;
float    *p1fdst, *p1ftmp, p1fsrc;
col2b *p2bdst, *p2btmp, p2bsrc;
col2s *p2sdst, *p2stmp, p2ssrc;
col2f *p2fdst, *p2ftmp, p2fsrc;
col3b *p3bdst, *p3btmp, p3bsrc;
col3s *p3sdst, *p3stmp, p3ssrc;
col3f *p3fdst, *p3ftmp, p3fsrc;
col4b *p4bdst, *p4btmp, p4bsrc;
col4s *p4sdst, *p4stmp, p4ssrc;
col4f *p4fdst, *p4ftmp, p4fsrc;
int px, py, width, height;

TextureClipCoordinates( xlo, xhi, ylo, yhi );

width  = xhi - xlo + 1;
height = yhi - ylo + 1;

switch ( m_type & TEX_MODEMASK )
    {
    case TEX_MONO:
        p1bsrc = (int)( red * 255.0f );
        p1bdst = (TEXBYTE *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p1btmp = p1bdst;

            for ( px = 0; px < width; px++ )
                *p1btmp++ = p1bsrc;

            p1bdst += m_width;
            }
        break;

    case TEX_MONOA8:
        p2bsrc.m_mono  = (int)(  red * 255.0f );
        p2bsrc.m_alpha = (int) ( alpha * 255.0f );

        p2bdst = (col2b *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p2btmp = p2bdst;

            for ( px = 0; px < width; px++ )
                *p2btmp++ = p2bsrc;

            p2bdst += m_width;
            }
        break;
        
    case TEX_MONO16:
        p1ssrc = (TEXSHORT) ( red * 65535.0f );
        p1sdst = (TEXSHORT *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p1stmp = p1sdst;

            for ( px = 0; px < width; px++ )
                *p1stmp++ = p1ssrc;

            p1sdst += m_width;
            }
        break;

    case TEX_MONOA16:
        p2ssrc.m_mono  = (int)( red   * 65535.0f );
        p2ssrc.m_alpha = (int)( alpha * 65535.0f );
        
        p2sdst = (col2s *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p2stmp = p2sdst;

            for ( px = 0; px < width; px++ )
                *p2stmp++ = p2ssrc;

            p2sdst += m_width;
            }
        break;
        
    case TEX_DUAL8:
	p2bsrc.m_mono  = (int)( red   * 255.0f );
        p2bsrc.m_alpha = (int)( green * 255.0f );

        p2bdst = (col2b *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p2btmp = p2bdst;

            for ( px = 0; px < width; px++ )
                *p2btmp++ = p2bsrc;

            p2bdst += m_width;
            }

	break;

    case TEX_DUAL16:
     	p2ssrc.m_mono  = (int)( red   * 65535.0f );
        p2ssrc.m_alpha = (int)( green * 65535.0f );

        p2sdst = (col2s *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p2stmp = p2sdst;

            for ( px = 0; px < width; px++ )
                *p2stmp++ = p2ssrc;

            p2sdst += m_width;
            }
	break;

    case TEX_DUALFLOAT:
      	p2fsrc.m_mono  = red;
        p2fsrc.m_alpha = green;

        p2fdst = (col2f *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p2ftmp = p2fdst;

            for ( px = 0; px < width; px++ )
                *p2ftmp++ = p2fsrc;

            p2fdst += m_width;
            }
	break;

    case TEX_MONOFLOAT:
        p1fsrc = red;

        p1fdst = (float *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p1ftmp = p1fdst;

            for ( px = 0; px < width; px++ )
                *p1ftmp++ = p1fsrc;

            p1fdst += m_width;
            }
        break;

    case TEX_MONOAFLOAT:
        p2fsrc.m_mono = red;
        p2fsrc.m_alpha = alpha;

        p2fdst = (col2f *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )     
            {
            p2ftmp = p2fdst;

            for ( px = 0; px < width; px++ )
                *p2ftmp++ = p2fsrc;

            p2fdst += m_width;
            }
        break;

    case TEX_RGB:
        p3bsrc.m_red   = (TEXBYTE)( red   * 255.0f );
        p3bsrc.m_green = (TEXBYTE)( green * 255.0f );
        p3bsrc.m_blue  = (TEXBYTE)( blue  * 255.0f );

        p3bdst = (col3b *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p3btmp = p3bdst;

            for ( px = 0; px < width; px++ )
                *p3btmp++ = p3bsrc;

            p3bdst += m_width;
            }
        break;

    case TEX_RGBA:
        p4bsrc.m_red   = (TEXBYTE)( red   * 255.0f );
        p4bsrc.m_green = (TEXBYTE)( green * 255.0f );
        p4bsrc.m_blue  = (TEXBYTE)( blue  * 255.0f );
        p4bsrc.m_alpha = (TEXBYTE)( alpha * 255.0f );

printf( "Fill color = (%d,%d,%d,%d)\n", 
	p4bsrc.m_red, p4bsrc.m_green, p4bsrc.m_blue, p4bsrc.m_alpha );

        p4bdst = (col4b *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p4btmp = p4bdst;

            for ( px = 0; px < width; px++ )
                *p4btmp++ = p4bsrc;

            p4bdst += m_width;
            }
        break;

    case TEX_RGB16:
        p3ssrc.m_red   = (TEXSHORT)( red   * 65535.0f );
        p3ssrc.m_green = (TEXSHORT)( green * 65535.0f );
        p3ssrc.m_blue  = (TEXSHORT)( blue  * 65535.0f );
     
        p3sdst = (col3s *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p3stmp = p3sdst;

            for ( px = 0; px < width; px++ )
                *p3stmp++ = p3ssrc;

            p3sdst += m_width;
            }
        break;

    case TEX_RGBA16: 
        p4ssrc.m_red   = (TEXSHORT)( red   * 65535.0f );
        p4ssrc.m_green = (TEXSHORT)( green * 65535.0f );
        p4ssrc.m_blue  = (TEXSHORT)( blue  * 65535.0f );
        p4ssrc.m_alpha = (TEXSHORT)( alpha * 65535.0f );

        p4sdst = (col4s *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p4stmp = p4sdst;

            for ( px = 0; px < width; px++ )
                *p4stmp++ = p4ssrc;

            p4sdst += m_width;
            }
        break;

    case TEX_RGBFLOAT:
        p3fsrc.m_red = red;
        p3fsrc.m_green = green;
        p3fsrc.m_blue = blue;

        p3fdst = (col3f *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p3ftmp = p3fdst;

            for ( px = 0; px < width; px++ )
                *p3ftmp++ = p3fsrc;

            p3fdst += m_width;
            }
        break;

    case TEX_RGBAFLOAT:
        p4fsrc.m_red = red;
        p4fsrc.m_green = green;
        p4fsrc.m_blue = blue;
        p4fsrc.m_alpha = alpha;

        p4fdst = (col4f *) m_pdata + ylo * m_width + xlo;

        for ( py = 0; py < height; py++ )
            {
            p4ftmp = p4fdst;

            for ( px = 0; px < width; px++ )
                *p4ftmp++ = p4fsrc;

            p4fdst += m_width;
            }
        break;

    default:
        break;  
    }

}
