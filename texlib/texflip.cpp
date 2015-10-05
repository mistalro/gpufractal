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
// C++ Source file defining functions used to flip images
//
// Author:  Michael S. A. Robb
//
// Date:    August 2002
// --------------------------------------------------------------------------
 
#include "texturelib.h"

// --------------------------------------------------------------------------
// Flip a texture vertically
// --------------------------------------------------------------------------
 
void CTexture::TextureFlipv( void )
{
int   ny, pitch;
TEXBYTE *tbuf, *psrc, *pdst;

psrc = m_pdata;
pdst = psrc + m_pitch * (m_height-1);
pitch = m_pitch;

tbuf = new TEXBYTE[pitch];

for ( ny = 0; ny < m_height >> 1; ny++ )
	{
	memcpy( tbuf, psrc, pitch );
	memcpy( psrc, pdst, pitch );
	memcpy( pdst, tbuf, pitch );

	psrc += pitch;
	pdst -= pitch;
	}

delete [] tbuf;
}

// --------------------------------------------------------------------------
// Flip a texture horizontally
// --------------------------------------------------------------------------

void CTexture::TextureFliph( void )
{

int		  ny, nx, nc, halfwidth, nelem2;
TEXBYTE  *pbsrc, *pbdst, pbtmp;
TEXSHORT *pssrc, *psdst, pstmp;
float    *pfsrc, *pfdst, pftmp;

halfwidth = m_width >> 1;
nelem2 = m_nelements<<1;

switch ( m_type & TEX_BITSIZES )
	{
	case TEX_8BIT:	
		for ( ny = 0; ny < m_height; ny++ )			// For each row
			{
			pbsrc = (TEXBYTE *) m_pdata + ny * m_pitch;
			pbdst = (TEXBYTE *) m_pdata + m_pitch-m_nelements;

			for ( nx = 0; nx < halfwidth; nx++ )
				{
				for ( nc = 0; nc < m_nelements; nc++ )
					{	
					 pbtmp = *pbdst;
					*pbdst = *pbsrc;
					*pbsrc =  pbtmp;

					pbsrc++;
					pbdst++;
					}

				pbdst -= nelem2;
				}
			}
		break;

	case TEX_16BIT:

		for ( ny = 0; ny < m_height; ny++ )			// For each row
			{
			pssrc = (TEXSHORT *) m_pdata + ny * m_pitch;
			psdst = (TEXSHORT *) m_pdata + m_pitch-m_nelements;

			for ( nx = 0; nx < halfwidth; nx++ )
				{
				for ( nc = 0; nc < m_nelements; nc++ )
					{
					 pstmp = *psdst;
					*psdst = *pssrc;
					*pssrc =  pstmp;

					pssrc++;
					psdst++;
					}

				psdst -= nelem2;
				} 
			}
		break;

	case TEX_32BIT:
		for ( ny = 0; ny < m_height; ny++ )			// For each row
			{
			pfsrc = (float *) m_pdata + ny * m_pitch;
			pfdst = (float *) m_pdata + m_pitch-m_nelements;

			for ( nx = 0; nx < halfwidth; nx++ )
				{
				for ( nc = 0; nc < m_nelements; nc++)
					{
					 pftmp = *pfdst;
					*pfdst = *pfsrc;
					*pfsrc =  pftmp;

					pfsrc++;
					pfdst++;
					}

				pfdst -= nelem2;
				}
			}
		break;

	default:
		break;
	}
}


// --------------------------------------------------------------------------
// Flip a texture diagonally
// 
// Two cases:
//
// If width and height are identical, then flipping the texture is simply
// a case of swapping diagonally opposite pixels
//
// If width and height are different, then we to create a new destination
// buffer, copy the contents, delete the old buffer and replace it with 
// the new one. We also have to update the stride and other attributes
//
// --------------------------------------------------------------------------

void CTexture::TextureFlipd( void )
{
if ( m_width == m_height )
        TextureFlipd_square();
else
        TextureFlipd_rectangle(); 
}

// --------------------------------------------------------------------------
// First case - flip the texture diagonally
// --------------------------------------------------------------------------

void CTexture::TextureFlipd_square( void )
{
int       ny, nx, nc;
TEXBYTE  *pbsrc, *pbdst, *ptbdst, pbtmp;
TEXSHORT *pssrc, *psdst, *ptsdst, pstmp;
float    *pfsrc, *pfdst, *ptfdst, pftmp;

switch ( m_type & TEX_BITSIZES )
        {
        case TEX_8BIT:
                pbsrc = (TEXBYTE *) m_pdata;
                pbdst = (TEXBYTE *) m_pdata;

                for ( ny = 0; ny < m_height; ny++ ) // For each row
                        {
                        ptbdst = pbdst;

                        for ( nx = 0; nx < m_width; nx++ )
                                {
                                for ( nc = 0; nc < m_compsize; nc++ )
                                        {
                                        pbtmp      = pbsrc[nc];
                                        pbsrc[nc]  = ptbdst[nc];
                                        ptbdst[nc] =  pbtmp;
                                        }

                                pbsrc++;                // Across
                                ptbdst += m_pitch;      // Down
                                }

                        pbdst += m_pixelsize;           // Across
                        }
                break;


        case TEX_16BIT:
                pssrc = (TEXSHORT *) m_pdata;
                psdst = (TEXSHORT *) m_pdata;

                for ( ny = 0; ny < m_height; ny++ ) // For each row
                        {
                        ptsdst = psdst;

                        for ( nx = 0; nx < m_width; nx++ )
                                {
                                for ( nc = 0; nc < m_compsize; nc++ )
                                        {
                                        pstmp      = pssrc[nc];
                                        pssrc[nc]  = ptsdst[nc];
                                        ptsdst[nc] =  pstmp;
                                        }

                                pssrc++;                // Across
                                ptsdst += m_pitch;      // Down
                                }

                        psdst += m_pixelsize;           // Across
                        }
                break;

        case TEX_32BIT:
                pfsrc = (float *) m_pdata;
                pfdst = (float *) m_pdata;

                for ( ny = 0; ny < m_height; ny++ ) // For each row
                        {
                        ptfdst = pfdst;

                        for ( nx = 0; nx < m_width; nx++ )
                                {
                                for ( nc = 0; nc < m_compsize; nc++ )
                                        {
                                        pftmp      = pfsrc[nc];
                                        pfsrc[nc]  = ptfdst[nc];
                                        ptfdst[nc] =  pftmp;
                                        }

                                pfsrc++;                // Across
                                ptfdst += m_pitch;      // Down
                                }

                        pfdst += m_pixelsize;           // Across
                        }
                break;

        default:
                break;
        }
}

// --------------------------------------------------------------------------
// Second case - flip the rectangular texture diagonally
// --------------------------------------------------------------------------

void CTexture::TextureFlipd_rectangle( void )
{
int       ny, nx, nc;
TEXBYTE  *pbsrc, *pbdst, *ptbdst;
TEXSHORT *pssrc, *psdst, *ptsdst;
float    *pfsrc, *pfdst, *ptfdst;
int temp, dstpitch;
void *pnew;

pnew = new TEXBYTE[ m_size]; // Create new buffer

dstpitch = m_height * m_pixelsize;

switch ( m_type & TEX_BITSIZES )
        {
        case TEX_8BIT:
                pbsrc = (TEXBYTE *) m_pdata;
                pbdst = (TEXBYTE *) pnew;

                for ( ny = 0; ny < m_height; ny++ ) // For each row
                        {
                        ptbdst = pbdst;

                        for ( nx = 0; nx < m_width; nx++ )
                                {
                                for ( nc = 0; nc < m_compsize; nc++ )
                                        ptbdst[nc] = pbsrc[nc];

                                pbsrc++;                // Across
                                ptbdst+= dstpitch;      // Down
                                }

                        pbdst+=m_compsize;              // Across
                        }
                break;

        case TEX_16BIT:
                pssrc = (TEXSHORT *) m_pdata;
                psdst = (TEXSHORT *) pnew;

                for ( ny = 0; ny < m_height; ny++ ) // For each row
                        {
                        ptsdst = psdst;

                        for ( nx = 0; nx < m_width; nx++ )
                                {
                                for ( nc = 0; nc < m_compsize; nc++ )
                                        ptsdst[nc] = pssrc[nc];

                                pssrc++;                // Across
                                ptsdst+= dstpitch;      // Down
                                }

                        psdst+=m_compsize;              // Across
                        }
                break;

        case TEX_32BIT:
                pfsrc = (float *) m_pdata;
                pfdst = (float *) pnew;

                for ( ny = 0; ny < m_height; ny++ ) // For each row
                        {
                        ptfdst = pfdst;

                        for ( nx = 0; nx < m_width; nx++ )
                                {
                                for ( nc = 0; nc < m_compsize; nc++ )
                                        ptfdst[nc] = pfsrc[nc];

                                pfsrc++;                // Across
                                ptfdst+= dstpitch;      // Down
                                }

                        pfdst+=m_compsize;              // Across
                        }
                break;

        default:
                break;
        }

temp     = m_width;                     // Update width and height
m_width  = m_height;
m_height = temp;
m_pitch  = m_width * m_pixelsize;       // Update pitch

delete [] m_pdata;      // Delete old pointer
m_pdata = (TEXBYTE *) pnew;     // Set new pointer
pnew    = NULL;         // Clear temporary pointer
}

