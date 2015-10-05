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

/*
void CTexture::Init( void )
{
m_name[0]='\0';
m_width     = 0;
m_height    = 0;
m_area      = 0;
m_size      = 0;
m_type      = 0;
m_compsize  = 0;
m_pixelsize = 0;
m_nelements = 0;
m_pitch     = 0;
m_pdata     = NULL;
m_pcolormap = NULL;
m_textureid = -1;
m_userflags = 0;
}
*/

// --------------------------------------------------------------------------
// Determine texel size and element size of a selected color type
// --------------------------------------------------------------------------
 
void CTexture::TextureGetSize( int ctype, int *csize, int *psize, int *nelems)
{
switch ( ctype & TEX_MODEMASK )
	{
	case TEX_PALETTE:     // Indexed palette and monochrome 
		*csize  = 1;
        	*nelems = 1;
		break;

	case TEX_DUAL:		 // Dual 8-bit format 
		*csize = 1;
		*nelems = 2;	
		break;

	case TEX_DUAL16:	// Dual 16-bit format
		*csize  = 2;
        	*nelems = 2;
		break;

	case TEX_DUALFLOAT:	// Dual 32-bit float
		*csize = 4;
		*nelems = 2;
		break;

	case TEX_MONO8:        // Maximum 256 colors - 1 byte pixels 
		*csize  = 1;
        	*nelems = 1;
		break;

	case TEX_MONO16:	// Monochrome 16-bit
		*csize  = 2;
		*nelems = 1;
		break;

	case TEX_MONOA8:	// Monochrome       - with alpha   
		*csize  = 1;    // Two channels     - 2 bytes each 
        	*nelems = 2;
		break;

    	case TEX_MONOA16:	// Monochrome 16    - with alpha   
		*csize  = 2;
        	*nelems = 2;
		break;

    	case TEX_FLOAT:
    	case TEX_MONOFLOAT:
        	*csize  = 4;
        	*nelems = 1;
        	break;

	case TEX_MONOAFLOAT:
		*csize = 4;
		*nelems = 2;
		break;

    	case TEX_RGB:		// Truecolor RGB    - no alpha     
		*csize  = 1;    // Three channels   - 1 byte each  
        	*nelems = 3;
		break;

	case TEX_RGBA:		// Truecolor RGB    - with alpha   
		*csize  = 1;    // Four channels    - 1 byte each  
        	*nelems = 4;
		break;

	case TEX_RGB16:		// Truecolor RGB-16 - no alpha     
		*csize  = 2;    // Three channels   - 2 bytes each 
        	*nelems = 3;
		break;

	case TEX_RGBA16:	// Truecolor RGB-16 - with alpha   
		*csize  = 4;    // Four channels    - 2 bytes each 
        	*nelems = 4;
		break;

	case TEX_RGBFLOAT:      // RGB floating point
	    	*csize  =  4;
        	*nelems =  3;      
		break;

	case TEX_RGBAFLOAT:     // RGBA floating point
        	*csize  =  4;
        	*nelems =  4;
        	break;

	default:		// Anything else we don't care about 
		printf( "Unknown texture format %08X\n", ctype & TEX_MODEMASK);
		*csize  = 0;
        	*nelems = 0;
		break;
	}

*psize = *csize * *nelems;
}

// --------------------------------------------------------------------------
// Allocate memory for a texture
// --------------------------------------------------------------------------
 
void CTexture::Allocate( int width, int height, int ctype )
{
if ( (m_width == width) && (m_height == height) && (m_type == ctype) )
	return;

Deallocate();

TextureGetSize( ctype, &m_compsize, &m_pixelsize, &m_nelements );

if ( m_compsize == 0 || m_pixelsize == 0 || m_nelements == 0)     // Sanity check 
	{
	printf ("CTexture::Allocate - Unknown format %08X\n", ctype );
  return;
	}

m_width  = width;
m_height = height;
m_area   = width * height;
m_type   = ctype;
m_size   = m_area * m_pixelsize;
m_pdata  = new TEXBYTE[m_size];

m_pitch  = m_pixelsize * m_width;

if ( ctype == TEX_PALETTE )
		m_pcolormap = new colmap4f[256];

}

// --------------------------------------------------------------------------
// Allocate memory for a texture
// --------------------------------------------------------------------------

void CTexture::Allocate( CTexture &texsrc )
{
if ( (texsrc.m_width  == m_width) &&
     (texsrc.m_height == m_height) &&
     (texsrc.m_type   == m_type) )
    return;

Deallocate();
TextureGetSize( texsrc.m_type, &m_compsize, &m_pixelsize, &m_nelements );

if ( (m_compsize == 0) || (m_pixelsize == 0) || (m_nelements == 0) )
    return;

m_width  = texsrc.m_width;
m_height = texsrc.m_height;
m_area   = m_width * m_height;
m_type   = texsrc.m_type;
m_size   = m_area * m_pixelsize;
m_pdata  = new TEXBYTE[m_size];

m_pitch  = m_pixelsize * m_width;

if ( m_type == TEX_PALETTE )
		m_pcolormap = new colmap4f[256];
}

// --------------------------------------------------------------------------
// Deallocate the memory for a texture
// --------------------------------------------------------------------------
 
void CTexture::Deallocate( void )
{
if ( m_pdata )
  delete [] m_pdata;

if ( m_pcolormap )
	delete [] m_pcolormap;

Init();
}

// --------------------------------------------------------------------------
// Duplicate a texture 
// --------------------------------------------------------------------------
 
void CTexture::Duplicate( CTexture &psrc )
{
Allocate( psrc.m_width, psrc.m_height, psrc.m_type );

memcpy( m_pdata, psrc.m_pdata, m_size );
}

// --------------------------------------------------------------------------
// Swap two textures
// --------------------------------------------------------------------------

void CTexture::Copy( CTexture &tsrc )
{
strncpy( m_name, tsrc.m_name, sizeof(CTextureName)-1 );
m_width = tsrc.m_width;
m_height = tsrc.m_height;
m_area = tsrc.m_area;
m_size = tsrc.m_size;
m_type = tsrc.m_type;
m_compsize = tsrc.m_compsize;
m_pixelsize = tsrc.m_pixelsize;
m_nelements = tsrc.m_nelements;
m_pitch = tsrc.m_pitch;
m_pdata = tsrc.m_pdata;
m_pcolormap = tsrc.m_pcolormap;
m_textureid = tsrc.m_textureid;
m_userflags = tsrc.m_userflags;
}

void CTexture::Transfer( CTexture &tsrc )
{
Copy( tsrc);
tsrc.Init();
}

void CTexture::Swap( CTexture &tsrc )
{
CTexture temp;

temp.Copy( *this );
Copy( tsrc );
tsrc.Copy( temp );
temp.Init();
}

// --------------------------------------------------------------------------
// Half size
// --------------------------------------------------------------------------

void CTexture::TextureReadPixel( int x, int y, col4f &pixel )
{
col4f *psrc4f;
col4s *psrc4s;
col4b *psrc4b;
col3s *psrc3s;
col3f *psrc3f;
col3b *psrc3b;
col2b *psrc2b;
col2s *psrc2s;
col2f *psrc2f;

switch ( m_type )
	{
	case TEX_DUAL:
		psrc2b = (col2b *) m_pdata;
		
		pixel = psrc2b[y * m_width + x];
		break;

	case TEX_DUAL16:
		psrc2s = (col2s *) m_pdata;

		pixel = psrc2s[y * m_width + x];
		break;

	case TEX_DUALFLOAT:
		psrc2f = (col2f *) m_pdata;

		pixel = psrc2f[y * m_width + x];
		break;

	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

		pixel = psrc3b[y * m_width + x];
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;
	
		pixel = psrc4b[y * m_width + x];
		break;

	case TEX_RGB16:
		psrc3s = (col3s *) m_pdata;

		pixel = psrc3s[y*m_width + x];
		break;

	case TEX_RGBA16:
		psrc4s = (col4s *) m_pdata;

		pixel = psrc4s[y*m_width+x];
		break;

	case TEX_RGBFLOAT:
		psrc3f = (col3f *) m_pdata;

		pixel = psrc3f[y*m_width+x];
		break;

	case TEX_RGBAFLOAT:
		psrc4f = (col4f *) m_pdata;

		pixel = psrc4f[y*m_width+x];
		break;

	default:
		break;
	}
}

void CTexture::TextureWritePixel( int x, int y, col4f &pixel )
{
col4f *psrc4f;
col4s *psrc4s;
col4b *psrc4b;
col3s *psrc3s;
col3f *psrc3f;
col3b *psrc3b;

switch ( m_type )
	{
	case TEX_RGB:
		psrc3b = (col3b *) m_pdata;

	    	psrc3b[y * m_width + x] = pixel.GetColor3b();
		break;

	case TEX_RGBA:
		psrc4b = (col4b *) m_pdata;
	
		psrc4b[y * m_width + x] = pixel.GetColor4b();
		break;

	case TEX_RGB16:
		psrc3s = (col3s *) m_pdata;

		psrc3s[y*m_width + x] = pixel.GetColor3s();
		break;

	case TEX_RGBA16:
		psrc4s = (col4s *) m_pdata;

		psrc4s[y*m_width+x] = pixel.GetColor4s();
		break;

	case TEX_RGBFLOAT:
		psrc3f = (col3f *) m_pdata;

		psrc3f[y*m_width+x] = pixel.GetColor3f();
		break;

	case TEX_RGBAFLOAT:
		psrc4f = (col4f *) m_pdata;

		psrc4f[y*m_width+x] = pixel;
		break;

	default:
		break;
	}
}

void CTexture::TextureHalfSize( CTexture &psrc )
{
int halfw, halfh, px, py;

col4f  psum, psamples[4];

halfh = psrc.m_width >> 1;
halfw = psrc.m_height >> 1;

Allocate( halfh, halfw, psrc.m_type );

for ( py = 0; py < halfh; py++ )
	for ( px = 0; px < halfw; px++ )
		{
		psrc.TextureReadPixel( (px<<1), (py<<1),     psamples[0] );
		psrc.TextureReadPixel( (px<<1)+1, (py<<1),   psamples[1] );
		psrc.TextureReadPixel( (px<<1)+1, (py<<1)+1, psamples[2] );	
		psrc.TextureReadPixel( (px<<1),   (py<<1)+1, psamples[3] );

		psum = (psamples[0] + psamples[1] + psamples[2] + psamples[3] ) * 0.25f;		
		
		TextureWritePixel( px, py, psum );		
		}
}
