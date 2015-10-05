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
// Source file used to provide the definition of the texture class
// 
// Date:   19th August 2002
//
// Author: Michael S. A. Robb
//
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// Correct texture gamma scale
// --------------------------------------------------------------------------

void CTextureEdit::TextureGammaCorrection( float gamma )
{
col4b *psrc4b;
col3b *psrc3b;
int px, py;
int colorramp[256];

for ( px = 0; px < 256; px++ )
	colorramp[px] = (int) (pow( (float) px/255.0f, gamma) * 255.0f); 

switch( m_type )
	{
	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

		for ( py= 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc3b++ )
				{
				psrc3b->m_red   = colorramp[psrc3b->m_red];
				psrc3b->m_green = colorramp[psrc3b->m_green];
				psrc3b->m_blue  = colorramp[psrc3b->m_blue];
				}
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc4b++ )
				{
				psrc4b->m_red   = colorramp[psrc4b->m_red];
				psrc4b->m_green = colorramp[psrc4b->m_green];
				psrc4b->m_blue  = colorramp[psrc4b->m_blue];
				}
		break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Perform Gamma Correction using a pre-defined look-up table
// --------------------------------------------------------------------------

void CTextureEdit::TextureGammaCorrectionRamp( int *prampred, int *prampgreen, 
								    int *prampblue )
{
col4b *psrc4b;
col3b *psrc3b;
int px, py;

switch( m_type )
	{
	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc3b++ )
				{
				psrc3b->m_red   = prampred[psrc3b->m_red];
				psrc3b->m_green = prampgreen[psrc3b->m_green];
				psrc3b->m_blue  = prampblue[psrc3b->m_blue];
				}
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc4b++ )
				{
				psrc4b->m_red   = prampred[psrc4b->m_red];
				psrc4b->m_green = prampgreen[psrc4b->m_green];
				psrc4b->m_blue  = prampblue[psrc4b->m_blue];
				}
		break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Perform statistical analysis of the texture
// --------------------------------------------------------------------------

void CTextureEdit::TextureFindLimits( col4f &clo, col4f &chi )
{
col4b  cmin4b, cmax4b, *psrc4b;
col3b  cmin3b, cmax3b, *psrc3b;
col1f  cmin1f, cmax1f, *psrc1f;
col2f  cmin2f, cmax2f, *psrc2f;
col3f  cmin3f, cmax3f, *psrc3f;
col4f  cmin4f, cmax4f, *psrc4f;

int px, py;

switch( m_type )
	{
	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

		cmin3b.setmax();
		cmax3b.setmin();

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc3b++ )
				{
				cmin3b.minimum( *psrc3b );
				cmax3b.maximum( *psrc3b );
				}

		clo.fromc3b( cmin3b );
		chi.fromc3b( cmax3b );
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;

		cmin4b.setmax();
		cmax4b.setmin();

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc4b++ )
				{
				cmin4b.minimum( *psrc4b );
				cmax4b.maximum( *psrc4b );
				}

		clo.fromc3b( cmin3b );	
		chi.fromc3b( cmax3b );
		break;

	case TEX_MONOFLOAT:
		psrc1f = (col1f *) m_pdata;

                cmin1f.setmax();
                cmax1f.setmin();

         	for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrc1f++ )
                                {
                                cmin1f.minimum( *psrc1f );
                                cmax1f.maximum( *psrc1f );
                                }

                clo.fromc1f( cmin1f );
                chi.fromc1f( cmax1f );
		break;

	case TEX_DUALFLOAT:
		psrc2f = (col2f *) m_pdata;

                cmin2f.setmax();
                cmax2f.setmin();

      		for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrc2f++ )
                                {
                                cmin2f.minimum( *psrc2f );
                                cmax2f.maximum( *psrc2f );
                                }

                clo.fromc2f( cmin2f );
                chi.fromc2f( cmax2f );
		break;

	case TEX_RGBFLOAT:
  		psrc3f = (col3f *) m_pdata;

                cmin3f.setmax();
                cmax3f.setmin();

                for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrc3f++ )
                                {
                                cmin3f.minimum( *psrc3f );
                                cmax3f.maximum( *psrc3f );
                                }

                clo.fromc3f( cmin3f );
                chi.fromc3f( cmax3f );
		break;

	case TEX_RGBAFLOAT:
    		psrc4f = (col4f *) m_pdata;

                cmin4f.setmax();
                cmax4f.setmin();

                for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrc4f++ )
                                {
                                cmin4f.minimum( *psrc4f );
                                cmax4f.maximum( *psrc4f );
                                }

                clo= cmin4f;
                chi= cmax4f;
		break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Scale the texture
// --------------------------------------------------------------------------

void CTextureEdit::TextureScale( float fred, float fgreen, 
			     float fblue, float falpha )
{
col3b *psrc3b;
col4b *psrc4b;
col2f *psrc2f;
col3f *psrc3f;
col4f *psrc4f;
float    *psrcf;

int px, py;

switch( m_type )
	{
	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc3b++ )
				{
				psrc3b->m_red   = (TEXBYTE)( fred   * (float) psrc3b->m_red   );
				psrc3b->m_green = (TEXBYTE)( fgreen * (float) psrc3b->m_green );	
				psrc3b->m_blue  = (TEXBYTE)( fblue  * (float) psrc3b->m_blue  );
				}
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc4b++ )
				{
				psrc4b->m_red   = (TEXBYTE)( fred   * (float) psrc4b->m_red   );
				psrc4b->m_green = (TEXBYTE)( fgreen * (float) psrc4b->m_green );	
				psrc4b->m_blue  = (TEXBYTE)( fblue  * (float) psrc4b->m_blue  );
				psrc4b->m_alpha = (TEXBYTE)( falpha * (float) psrc4b->m_alpha );
				}
		break;

	case TEX_MONOFLOAT:
		psrcf = (float *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrcf++ )
				{
				*psrcf *= fred;
				}
		break;
	
	case TEX_DUALFLOAT:
		psrc2f = (col2f *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc2f++ )
				{
				psrc2f->m_mono   *= fred;
				psrc2f->m_alpha *= fgreen;
				}
		break;

	case TEX_RGBFLOAT:
		psrc3f = (col3f *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc3f++ )
				{
				psrc3f->m_red   *= fred;
				psrc3f->m_green *= fgreen;
				psrc3f->m_blue  *= fblue;
				}
		break;
	
	case TEX_RGBAFLOAT:
		psrc4f = (col4f *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc4f++ )
				{
				psrc4f->m_red   *= fred;
				psrc4f->m_green *= fgreen;
				psrc4f->m_blue  *= fblue;
				psrc4f->m_alpha *= falpha;
				}
		break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Scale the texture
// --------------------------------------------------------------------------

void CTextureEdit::TextureBias( float fred, float fgreen, 
			    float fblue, float falpha )
{
col4b *psrc4b;
col3b *psrc3b;
float *psrcf;
col2f *psrc2f;
col3f *psrc3f;
col4f *psrc4f;

int px, py;

switch( m_type )
	{
	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc3b++ )
				{
				psrc3b->m_red   = (TEXBYTE)( fred   + (float) psrc3b->m_red   );
				psrc3b->m_green = (TEXBYTE)( fgreen + (float) psrc3b->m_green );	
				psrc3b->m_blue  = (TEXBYTE)( fblue  + (float) psrc3b->m_blue  );
				}
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc4b++ )
				{
				psrc4b->m_red   = (TEXBYTE)( fred   + (float) psrc4b->m_red   );
				psrc4b->m_green = (TEXBYTE)( fgreen + (float) psrc4b->m_green );	
				psrc4b->m_blue  = (TEXBYTE)( fblue  + (float) psrc4b->m_blue  );
				}
		break;

     case TEX_MONOFLOAT:
                psrcf = (float *) m_pdata;

                for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrcf++ )
                                {
                                *psrcf += fred;
                                }
                break;

        case TEX_DUALFLOAT:
                psrc2f = (col2f *) m_pdata;

                for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrc2f++ )
                                {
                                psrc2f->m_mono  += fred;
                                psrc2f->m_alpha += fgreen;
                                }
                break;

        case TEX_RGBFLOAT:
                psrc3f = (col3f *) m_pdata;

                for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrc3f++ )
                                {
                                psrc3f->m_red   += fred;
                                psrc3f->m_green += fgreen;
                                psrc3f->m_blue  += fblue;
                                }
                break;

        case TEX_RGBAFLOAT:
                psrc4f = (col4f *) m_pdata;

                for ( py = 0; py < m_height; py++ )
                        for ( px = 0; px < m_width; px++, psrc4f++ )
                                {
                                psrc4f->m_red   += fred;
                                psrc4f->m_green += fgreen;
                                psrc4f->m_blue  += fblue;
                                psrc4f->m_alpha += falpha;
                                }
                break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Scale the texture
// --------------------------------------------------------------------------

void CTextureEdit::TextureScale8bit( float fred, float fgreen, float fblue )
{
col4b *psrc4b;
col3b *psrc3b;

int px, py;

switch( m_type )
	{
	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc3b++ )
				{
				psrc3b->m_red   = (TEXBYTE)( ((float) psrc3b->m_red   - 128.0f)*fred   + 128.0f );
				psrc3b->m_green = (TEXBYTE)( ((float) psrc3b->m_green - 128.0f)*fgreen + 128.0f );	
				psrc3b->m_blue  = (TEXBYTE)( ((float) psrc3b->m_blue  - 128.0f)*fblue  + 128.0f );
				}
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;

		for ( py = 0; py < m_height; py++ )
			for ( px = 0; px < m_width; px++, psrc4b++ )
				{
				psrc4b->m_red   = (TEXBYTE)( ((float) psrc4b->m_red   - 128.0f)*fred   + 128.0f );
				psrc4b->m_green = (TEXBYTE)( ((float) psrc4b->m_green - 128.0f)*fgreen + 128.0f );	
				psrc4b->m_blue  = (TEXBYTE)( ((float) psrc4b->m_blue  - 128.0f)*fblue  + 128.0f );
				}
		break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Extract a rectangular block from one image into another
//
// Inputs: xlo - Lower X coordinate
//         xhi - Higher X coordinate
//         ylo - Lower Y coordinate
//         yhi - Higher Y coordinate
//
// Outputs: scopeblock - Resulting scope image
//
// Effects: None
//
// Results: The selected block is copied from one texture to another
// --------------------------------------------------------------------------

void CTextureEdit::TextureCut( CTexture &texdst, int xlo, int ylo, int xhi, int yhi )
{
int px, py;
TEXBYTE  *pbsrc, *pbdst, *pbtsrc;
int width, height, temp;

if ( xlo > xhi )
	{
	temp = xhi;
	xhi  = xlo;
	xlo  = temp;
	}

if ( ylo > yhi )
	{
	temp = yhi;
	yhi  = ylo;
	ylo  = temp;
	}

if ( xlo < 0 )
	xlo = 0;

if ( ylo < 0 )
	ylo = 0;

if ( xhi >= m_width )
	xhi = m_width-1;

if ( yhi >= m_height )
	yhi = m_height-1;

width  = xhi-xlo+1;
height = yhi-ylo+1;

texdst.Deallocate();
texdst.Allocate( width, height, m_type );

pbdst = (TEXBYTE *) texdst.m_pdata;
pbsrc = (TEXBYTE *) m_pdata + m_width *m_pixelsize* ylo + xlo*m_pixelsize;

for ( py = 0; py < height; py++ )
	{
	pbtsrc = pbsrc;

	for ( px = 0; px < width*m_pixelsize; px++ )
		*pbdst++ = *pbtsrc++;
		
	pbsrc += m_pitch;
	}
}

// --------------------------------------------------------------------------
// Paste a rectangular block from one texture into another
//
// Inputs: texsrc - Source texture
//         xlo - X coordinate
//         ylo - Y coordinate
//		   
// Outputs: None
// 
// Results: None
//
// Effects: The source block is pasted into the destination block
// --------------------------------------------------------------------------

void CTextureEdit::TexturePaste( CTexture &texsrc, int xlo, int ylo )
{
int px, py, offx, offy, xhi, yhi, width, height;
TEXBYTE *pbsrc, *pbdst, *ptbsrc, *ptbdst;

if ( texsrc.m_type != m_type )		// Sanity check
	return;

if ( xlo < 0 )						// Clamp to the left
	{
	xlo = 0;
	offx = -xlo;
	}
else
	offx = 0;

if ( ylo < 0 )						// Clamp to the top
	{
	ylo = 0;
	offy = -ylo;
	}
else
	offy = 0;

xhi = xlo + texsrc.m_width-1;		// Determine upper coordinates
yhi = ylo + texsrc.m_height-1;

if ( xhi >= m_width )	
	xhi = m_width-1;

if ( yhi >= m_height )
	yhi = m_height-1;

width  = xhi - xlo + 1;		// Determine dimensions of area to copy
height = yhi - ylo + 1;

pbdst = (TEXBYTE *) m_pdata         + ylo  * m_pitch + xlo * m_pixelsize;
pbsrc = (TEXBYTE *) texsrc.m_pdata + offy * texsrc.m_pitch + offx * m_pixelsize;
	
for ( py = 0; py < height; py++ )	// For each src row
	{
	ptbdst = pbdst;	
	ptbsrc = pbsrc;

	for ( px = 0; px < width*m_pixelsize; px++ )	// Copy a single row
		*ptbdst++ = *ptbsrc++;

	pbdst += m_pitch;				// Move down by one scan line
	pbsrc += texsrc.m_pitch;
	}
}

// --------------------------------------------------------------------------
// Paste one texture into another using wraparound
//
// Inputs: texsrc - Source texture
//         xlo    - Starting coordinate
//         ylo    - Destination coordinate
//
// Outputs: None
//
// Results: The source texture is pasted into the destination texture
//
// Effects: None
// --------------------------------------------------------------------------

void CTextureEdit::TexturePasteWraparound( CTexture &texsrc, int xlo, int ylo )
{
int px, py, pn, dx, dy;
TEXBYTE *psrc, *pdst, *ptdst;

if ( texsrc.m_type != m_type )      // Sanity check
    return;

dy = ylo;

psrc = texsrc.m_pdata;
pdst = m_pdata;

for ( py = 0; py < texsrc.m_height; py++ )
    {
    dx = xlo;
    dy = (dy+1) % m_height;

    for ( px = 0; px < texsrc.m_width; px++ )
        {
        dx = (dx+1) % m_width;

        ptdst = pdst+dy * m_pitch+dx * m_pixelsize;
     
        for ( pn= 0; pn <m_pixelsize; pn++ )
            *ptdst++ = *psrc++;
        }
    }
}

// --------------------------------------------------------------------------
// Compare two textures together. Ignore those pixels which match the 
// "transparent" colour
//
// Inputs: texsrc - Source texture
//         xlo - X coordinate
//         ylo - Y coordinate
//
// Outputs: None
//
// Results: TRUE if the source image would overwrite the destination area
//          FALSE otherwise
//
// Effects: None
// --------------------------------------------------------------------------

int CTextureEdit::TextureCheckWraparound( CTexture &texsrc, int xlo, int ylo, 
                               col3b &transp3b )
{
col4b transp4b = col4b(transp3b.m_red, transp3b.m_green, transp3b.m_blue, 0);

if ( texsrc.m_type != m_type )      // Sanity check
	{
    	return( 0 );
	}

int overwritten = 0;

int dx, dy;

switch ( m_type )
    {
    case TEX_RGB:
	{
        col3b *psrc3b = (col3b *) texsrc.m_pdata;
        col3b *pdst3b = (col3b *) m_pdata;

        dy = ylo;

        for (int py = 0; py < texsrc.m_height; py++ )
            {
            dx = xlo;
            dy = (dy+1) % m_height;

            for (int px = 0; px < texsrc.m_width; px++ )
                {
                dx = (dx+1) % m_width;
    
                col3b *ptdst3b = pdst3b + dy * m_width+dx;
     
                if ( *psrc3b != transp3b )
			{
	                if ( *ptdst3b != transp3b )
				{	
                        	overwritten++;
				}
			}
                }
            }
	}
        break;

    case TEX_RGBA:
	{
        col4b *psrc4b = (col4b *) texsrc.m_pdata;
        col4b *pdst4b = (col4b *) m_pdata;

        dy = ylo;

        for (int py = 0; py < texsrc.m_height; py++ )
            {
            dx = xlo;
            dy = (dy+1) % m_height;

            for (int px = 0; px < texsrc.m_width; px++ )
                {
                dx = (dx+1) % m_width;
    
                col4b *ptdst4b = pdst4b +dy * m_width+dx;
     
                if ( *psrc4b != transp4b )
                    if ( *ptdst4b != transp4b )
                        overwritten++;
                }
            }
	}
        break;

    default:
        break;
    }

return( overwritten );
}
