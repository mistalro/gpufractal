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

void CTextureEdit::TextureAlphaFromColour( float tr, float tg, float tb )
{
int px, py;
col4b *psrc;

TextureChangeMode( TEX_RGBA );

psrc = (col4b *) m_pdata;

for ( py = 0; py < m_height; py++ )
	for ( px = 0; px < m_width; px++, psrc++ )
		{
		psrc->m_alpha = (TEXBYTE ((float)psrc->m_red * tr +
					(float)psrc->m_green * tg +
					(float)psrc->m_blue * tb)); 
		}
}
