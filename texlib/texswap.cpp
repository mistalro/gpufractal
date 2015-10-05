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
// File:    texswap.cpp
//
// Purpose: Source file used to swap a texture image
//
// Author: Michael S. A. Robb
// 
// Date:   19th August 2002
// --------------------------------------------------------------------------

#include "texturelib.h"

/*
a=(orig.hd.npix)/2;
b=(orig.hd.nline)/2;

printf("%d %d\n",a,b);
for(y=0;y<orig.hd.nline;y++) 
	{
	for(x=0;x<orig.hd.npix;x++) 
		{

              	if (x>=a) x2=x-a;
									                        if (y>=b) y2=y-b;
									                        if (y<b) y2=y+b;
								                        	if (x<a) x2=x+a;
												original=PIX32(orig,x,y);
												PIX32(out,x2,y2)=original;
		}
*/

// --------------------------------------------------------------------------
// Swap the quadrants of a texture image
// 
// Inputs: None
// 
// Outputs: None
// 
// Results: None
// 
// Effects: The quadrants of the texture are swapped in all channels
// --------------------------------------------------------------------------

void CTextureEdit::TextureSwap( CTexture &texsrc )
{
int nx, ny, nc, sx, sy; 
int halfx, halfy;
TEXBYTE  *pbsrc, *pbdst;
TEXSHORT *pssrc, *psdst;
float    *pfsrc, *pfdst;

Allocate( texsrc );

halfx = m_width >> 1;
halfy = m_height >> 1;

switch ( m_type & TEX_BITSIZES )
	{
	case TEX_8BIT:
		pbdst = (TEXBYTE *) m_pdata;

		for ( ny = 0; ny < m_height; ny++ )
			{
			for ( nx = 0; nx < m_width; nx++ )
				{
				if ( nx >= halfx )
					sx = nx - halfx;
				else
					sx = nx + halfx;

				if ( ny >= halfy ) 
					sy = ny - halfy; 
				else 
					sy = ny + halfy;

				pbsrc = (TEXBYTE *) texsrc.m_pdata 
				      + sy * m_width * m_nelements + sx * m_nelements;

				for ( nc = 0; nc < m_nelements; nc++ )
					*pbdst++ = pbsrc[nc];
				}
			}	
		break;

	case TEX_16BIT:
		psdst = (TEXSHORT *) m_pdata;

		for ( ny = 0; ny < m_height; ny++ )
			{
			for ( nx = 0; nx < m_width; nx++ )
				{
				if ( nx >= halfx )
					sx = nx - halfx;
				else
					sx = nx + halfx;

				if ( ny >= halfy )
					sy = ny - halfy;
				else
					sy = ny + halfy;

				pssrc = (TEXSHORT *) texsrc.m_pdata 
				      + sy * m_width * m_nelements + sx * m_nelements;

				for ( nc = 0; nc < m_nelements; nc++ )
					*psdst++ = pssrc[nc];
				}
			}
		break;

	case TEX_32BIT:
	case TEX_32BIT|TEX_FLOAT:
		pfdst = (float *) m_pdata;
		
		for ( ny = 0; ny < m_height; ny++ )
			{
			for ( nx = 0; nx < m_width; nx++ )
				{
				if ( nx >= halfx )
					sx = nx - halfx;
				else
					sx = nx + halfx;

				if ( ny >= halfy )
					sy = ny - halfy;
				else
					sy = ny + halfy;

				pfsrc = (float *) texsrc.m_pdata
					  + sy * m_width * m_nelements + sx * m_nelements;

				for ( nc = 0; nc < m_nelements; nc++ )
					*pfdst++ = pfsrc[nc];
				}	
			}
		break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Swap a single texture
// 
// Inputs: None
//
// Outputs: None
//
// Results: None
//
// Effects: The texture is duplicated then swapped using the duplicate as a 
//          source image
// --------------------------------------------------------------------------

void CTextureEdit::TextureSwap( void )
{
CTexture textemp;

textemp.Duplicate( *this );

TextureSwap( textemp );
}
