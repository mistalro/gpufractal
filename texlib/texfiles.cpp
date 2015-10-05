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
// Source file used to handle file input and output with the CTexture class
//
// Author: Michael S. A. Robb
// 
// Date:   19th August 2002
//
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// Check whether a file requires to be converted to RGB mode or not
//
// Inputs:  path - Character path name
//
// Outputs: None
//
// Results: Non-zero if the texture needs converting or not
// 
// Effects: None
// --------------------------------------------------------------------------

int CTexture::TextureCheckRGB( const char *path )
{
int len = strlen( path );

if ( (m_type & (TEX_32BIT|TEX_FLOAT) ) || (m_type & TEX_16BIT) )
        {
        if ( strncmp( path+len-4, ".tga", 4 ) == 0 )
                return( 1 );

        if ( strncmp( path+len-4, ".bmp", 4 ) == 0 )
                return( 1 );

        if ( strncmp( path+len-4, ".tif", 4) == 0 )
                return( 1 );

        if ( strncmp( path+len-5, ".tiff", 5 ) == 0 )
                return( 1 );
        }

return( 0 );
}

// --------------------------------------------------------------------------
// Check to see whether a texture needs to be converted to floating 
// point mode or not
//
// Inputs:  path - Character path name
//
// Outputs: None
//
// Results: Non-zero if the texture needs converting or not
//
// Effects: None
// --------------------------------------------------------------------------

int CTexture::TextureCheckFloat( const char *path )
{
int len;

len = strlen( path );

if ( (m_type & TEX_8BIT ) || ( m_type & TEX_16BIT) )
        {
        if ( strncmp( path+len-2, ".f", 2 ) == 0 )
                return( 1 );
        }

return( 0 );
}

// --------------------------------------------------------------------------
// Read in a file
//
// Inputs: path - character pointer to the file
//
// Outputs: NONE
//
// Results: Boolean flag indicating whether file was successfully read or not
//
// Effects: The object is initialised with the image data from the file
// --------------------------------------------------------------------------

int CTexture::TextureReadFile( const char path[] )
{
const char *pext;
char fullpath[1024];

int len, result = 0;

pext = strrchr( path, '.' );      // Find last . character
len  = strlen(  path );           // Get string length

if ( (len < 4 ) && !pext )        // No default extension
    {
    sprintf( fullpath, "%s.tga", path );

    result = TextureReadtga( fullpath );
    }
else                              // We know the extension type
    {
    if ( strncmp( path+len-4, ".tga", 4 ) == 0 )
        result = TextureReadtga( path );

	if ( strncmp( path+len-4, ".bmp", 4 ) == 0 )
		result = TextureReadbmp( path );

	if ( strncmp( path+len-4, ".tif", 4 ) == 0 )
		result = TextureReadtiff( path );

	if ( strncmp( path+len-5, ".tiff", 5 ) == 0 )
		result = TextureReadtiff( path );

    // ... For all the other file types ...
    }

return( result );
}

// --------------------------------------------------------------------------
// Write out a file
//
// Inputs: path - character pointer to the file
//
// Outputs: NONE
//
// Results: Boolean flag indicating whether file was successfully written
//
// Effects: The image data of the object is written to the file
// --------------------------------------------------------------------------

int CTexture::TextureWriteFile( const char *path )
{
const char *pext;
char fullpath[1024];
int len, result;

pext = strrchr( path, '.' );      // Find last . character
len  = strlen(  path );           // Get string length
result = 0;

if ( (len < 4 ) && !pext )        // No default extension
    {
    sprintf( fullpath, "%s.tga", path );

    result = TextureWritetga( fullpath );
    }
else
    {
    if ( strncmp( path+len-4, ".tga", 4 ) == 0 )
        result = TextureWritetga( path );       

	if ( strncmp( path+len-4, ".bmp", 4 ) == 0 )
		result = TextureWritebmp( path );

	if ( strncmp( path+len-4, ".tif", 4 ) == 0 )
		result = TextureWritetiff( path );

	if ( strncmp( path+len-5, ".tiff", 5 ) == 0 )
		result = TextureWritetiff( path );

    // ... For all the other file types ...
    }

return( result );
}

