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
// Implementation of the BMP file reader/writer program
//
// Author: Michael S. A. Robb
//
// Date:   19th August 2002
//
// --------------------------------------------------------------------------

#include "texturelib.h"

#define BMP_RLE8      0x01
#define BMP_RLE4      0x02
#define BMP_BITFIELDS 0x03
#define BMP_MAGIC     0x4D42

// -----------------------------------------------------------------------
// Read a BMP file
//
// Inputs: path - Path to the selected file
//
// Outputs: None
//
// Results: 1 - If the file can be read, 0 otherwise
//
// Effects: The file is read
// -----------------------------------------------------------------------

int CTexture::TextureReadbmp( const char *path )
{
int    bmp_comp;
int    bmp_maskr,  bmp_maskg,  bmp_maskb;
int    bmp_shiftr, bmp_shiftg, bmp_shiftb;
int    cr, cg, cb, cmax, rowbytes, dx, dy;
int    padbytes, done, runcol, runlen, runpos, databits;
colmap4f  *colormap;
col4f *cptr;
TEXBYTE   *dbptr;
FILE *fp;

if ( !(fp = fopen( path, "rb" ) ))
	{
	return( 0 );
	}

bmp_comp = bmp_maskr = bmp_maskg = bmp_maskb = bmp_shiftr = bmp_shiftg = bmp_shiftb = 0;

int bmp_type = readshortlsb( fp );	// Read file header
int bmp_size = readlonglsb(  fp );
int bmp_res1 = readshortlsb( fp );
int bmp_res2 = readshortlsb( fp );
int bmp_off  = readlonglsb(  fp );  

bmp_size = readlonglsb( fp );		// Read image header

int bmp_width,  bmp_height, bmp_planes, bmp_bitcount;
int bmp_imsize, bmp_xpel,   bmp_ypel,   bmp_cnum,   bmp_clrsig;

if ( bmp_size <= 12 )
	{ 
	bmp_width    = readshortlsb( fp );
	bmp_height   = readshortlsb( fp );
	bmp_planes   = readshortlsb( fp );
	bmp_bitcount = readshortlsb( fp );
	}
else
	{
	bmp_width    = readlonglsb(  fp );
	bmp_height   = readlonglsb(  fp );
	bmp_planes   = readshortlsb( fp );
	bmp_bitcount = readshortlsb( fp );
	bmp_comp     = readlonglsb(  fp );
   
	bmp_imsize   = readlonglsb( fp );
	bmp_xpel     = readlonglsb( fp );
	bmp_ypel     = readlonglsb( fp );
	bmp_cnum     = readlonglsb( fp );
	bmp_clrsig   = readlonglsb( fp );
	}

#ifdef DEBUG
printf( "BMP file %s, Width %d, Height %d, Bitcount %d\n",
  path, bmp_width, bmp_height, bmp_bitcount );
#endif

if ( bmp_bitcount == 24 )			// Create the pixelmap 
	{
	Allocate( bmp_width, bmp_height, TEX_RGB );
	}
else if ( bmp_bitcount == 32 )
		{
    		Allocate( bmp_width, bmp_height, TEX_RGBA );
		}
  	else if ( bmp_bitcount <= 8 )
		{
      		Allocate( bmp_width, bmp_height, TEX_PALETTE );
		}

// ----- Read the color palette

cmax             = 1 << bmp_bitcount;

if ( bmp_bitcount <= 8 && bmp_size >= 40 )
	{
	colormap         = m_pcolormap;
	colormap->m_num = cmax;

	cptr = colormap->m_list;

	for (int cn = 0; cn < cmax; cn++, cptr++ )
      		{
      		cb = readbytelsb( fp );
      		cg = readbytelsb( fp );
     		cr = readbytelsb( fp ); 

      		readbytelsb( fp );

      		cptr->m_red   = (float) cr / 255.0f;
      		cptr->m_green = (float) cg / 255.0f;
      		cptr->m_blue  = (float) cb / 255.0f; 
      		}

	m_pcolormap = colormap;
    	}
else if ( bmp_bitcount <= 8 && bmp_size >= 12 )
	{
	colormap        = m_pcolormap;
      	colormap->m_num = cmax;

      	cptr = colormap->m_list;

	for (int cn = 0; cn < cmax; cn++, cptr++ )
        	{
        	cb = readbytelsb( fp );
        	cg = readbytelsb( fp ); 
        	cr = readbytelsb( fp );
     
        	cptr->m_red   = (float) cr / 255.0f;
        	cptr->m_green = (float) cg / 255.0f;
        	cptr->m_blue  = (float) cb / 255.0f;
        	}
       
	m_pcolormap = colormap;
	}	 

if (( bmp_bitcount == 16 || bmp_bitcount == 32) && bmp_comp == BMP_BITFIELDS )
	{
	bmp_maskr = readlonglsb( fp );
	bmp_maskg = readlonglsb( fp );  
	bmp_maskb = readlonglsb( fp );

	bmp_shiftr = bmp_shiftg = bmp_shiftb = 0;
  
	while ( !(bmp_maskr >>bmp_shiftr) & 0x01 ) 
		{
      		bmp_shiftr++;
		}

	while ( !(bmp_maskg >>bmp_shiftg) & 0x01 ) 
		{
      		bmp_shiftg++;
		}

    	while ( !(bmp_maskb >>bmp_shiftb) & 0x01 ) 
		{
      		bmp_shiftb++;
		}
    	}

// ----- Read the image data --------------------------------------
  
fseek( fp, bmp_off, SEEK_SET );

rowbytes = (( (bmp_width * bmp_bitcount + 7  ) / 8 ) + 3 ) / 4;

padbytes = ((bmp_width * bmp_bitcount) / 8 ) % 4;
 
if ( padbytes )
	{
	padbytes = 4 - padbytes;
	}
  
switch ( bmp_bitcount )
    {
    case 1:                      // 1 bits - pad to 8-bit index 
      rowbytes = (bmp_width + 7) / 8;
      padbytes = rowbytes % 4;

      if ( padbytes )
        padbytes = 4 - padbytes;

      for (int py = 0; py < bmp_height; py++ )
        {
        dbptr = m_pdata + (bmp_height-1 - py) * bmp_width;
        int px    = 0;

        while ( px < bmp_width )
          {
          databits = readbytelsb( fp ); 

          for (int pn = 0; ( pn < 8 ) && px < bmp_width; pn++, px++ ) 
            *dbptr++ = (databits >> (7-pn)) & 0x01;
          } 

        for (int px = 0; px < padbytes; px++ )
          readbytelsb( fp );
        }
      break;

    case 2:                      // 2 bits - pad to 8-bit index 
      for (int py = 0; py < bmp_height; py++ )
        {
        dbptr = m_pdata + (bmp_height-1 - py) * bmp_width;
        int px    = 0;

        while ( px < bmp_width )
          {
          databits = readbytelsb( fp ); 

          for (int pn = 0; ( pn < 4 ) && px < bmp_width; pn++, px++ )
            *dbptr++ = (databits >> (6-pn*2)) & 0x03;
          } 

        for (int px = 0; px < padbytes; px++ )
          readbytelsb( fp );
        }
      break;

    case 4:   // 4 bits - pad to 8 bit index, check for RLE encoding 
      if ( bmp_comp == BMP_RLE4 )
        {
        int py    = bmp_height-1;
        int px    = 0;
        dbptr = m_pdata + py * bmp_width;
        done  = 0;

        while ( !done ) 
          {
          runlen = readbytelsb( fp );
          runcol = readbytelsb( fp );
         
          if ( runlen > 0 )      // Run of fixed colors? 
            {
            runpos = 0;

            while ( runlen-- )
              {     
              if ( runpos & 0x01 )
                *dbptr++ =  runcol & 0xF;
              else
                *dbptr++ = (runcol & 0xF0) >> 4;
 
              runpos++;
              }
            }
          else
            switch( runcol )     // Escape code 
              {
              case 0:            // Run 0, Color 0 - move to next line 
                py--;
                px = 0;
                dbptr = m_pdata + py * bmp_width;
                break;

              case 1:            // Run 0, Color 1 - end of image 
                done++;
                break;

              case 2:            // Run 0, Color 2 - move to new location 
                dx = readbytelsb( fp );
                dy = readbytelsb( fp );

                px += dx;
                py -= dy;
                dbptr += dx; 
                dbptr = m_pdata + py * bmp_width;
                break;

              default:           // Color > 2, literal byte codes 
                runpos = runcol;

                while ( runcol-- )
                  {
                  *dbptr++ = (TEXBYTE) readbytelsb( fp );
                  px++;
                  }

                if ( runpos & 0x01 )
                  readbytelsb( fp );
                break;            
              }
          }
        }
      else
        for (int py = 0; py < bmp_height; py++ )
          {
          dbptr = m_pdata + (bmp_height-1 - py) * bmp_width;
          int px    = 0;

          rowbytes = (bmp_width+ 1 ) / 2;
          padbytes = rowbytes % 4;
    
          if ( padbytes )
		{
            	padbytes = 4 - padbytes;
		}

          while ( px < bmp_width )
            {
            databits = readbytelsb( fp ); 

            dbptr[0] = (databits & 0xF0) >> 4;
            px++;
            dbptr++;

            if ( px < bmp_width )
              dbptr[0] = databits & 0x0F;

            px ++;
            dbptr ++;
            } 

          for ( px = 0; px < padbytes; px++ )
            readbytelsb( fp );

          }
      break;

    case 8:          // 8-bits - 8 bit index, check for RLE encoding 
      if ( bmp_comp == BMP_RLE8 )
        {
        int py    = bmp_height-1;
        int px    = 0;
        dbptr = m_pdata + py * bmp_width;
        done  = 0;

        while ( !done )
          {
          runlen = readbytelsb( fp );
          runcol = readbytelsb( fp );  

          if ( runlen )
            while ( runlen-- )
              {
              px++;
              *dbptr++ = runcol; 
              }
          else
            switch ( runcol )
              {
              case 0:  // Run 0, Color 0 - move to next line 
                py--;
                px    = 0;
                dbptr = m_pdata + py * bmp_width;
                break;
 
              case 1:  // Run 0, Color 1 - end of image 
                done++;
                break;

              case 2:  // Run 0, Color 2 - move to new location 
                dx = readbytelsb( fp );
                dy = readbytelsb( fp );
 
                px += dx;
                py -= dy;

                dbptr += dx;
                dbptr = m_pdata + py * bmp_width;
                break;

              default: // Color > 2 - literal byte codes 
                runpos = runcol;
             
                while ( runcol-- )
                  {
                  *dbptr++ = (TEXBYTE) readbytelsb( fp );
                  px++;
                  }

                if ( runpos & 0x01 )     // Pad if odd number 
                  readbytelsb( fp );
                break;
              }
          }
        }
      else 
        for (int py = 0; py < bmp_height; py++ )
          {
          dbptr = m_pdata + (bmp_height-1 - py) * bmp_width;

          for (int px = 0; px < bmp_width; px++ ) 
            {
            databits = readbytelsb( fp ); 

            *dbptr++ = databits;
            } 

          for (int px = 0; px < padbytes; px++ )
            readbytelsb( fp );
          }
      break;

    case 16:                         // 16-bit - scale up to 24 bits 
      for (int py = 0; py < bmp_height; py++ )
        {
        dbptr = m_pdata + (bmp_height-1 - py) * bmp_width * 3;

        for (int px = 0; px < bmp_width; px++ ) 
          {
          databits = readshortlsb( fp ); 

          dbptr[0] = (databits & bmp_maskr ) >> bmp_shiftr;
          dbptr[1] = (databits & bmp_maskg ) >> bmp_shiftg;
          dbptr[2] = (databits & bmp_maskb ) >> bmp_shiftb;

          dbptr += 3; 
          } 

        for (int px = 0; px < padbytes; px++ )
          readbytelsb( fp );
        }
      break;

    case 24:                         // 24-bits - 24 bit RGB 
      for (int py = 0; py < bmp_height; py++ )
        {
        dbptr = m_pdata + (bmp_height-1 - py) * bmp_width * 3;

        for (int px = 0; px < bmp_width; px++ )
          {
          dbptr[2] = (TEXBYTE) readbytelsb( fp );
          dbptr[1] = (TEXBYTE) readbytelsb( fp );
          dbptr[0] = (TEXBYTE) readbytelsb( fp );
          dbptr += 3;
          }

        for (int px = 0; px < padbytes; px++ )
          readbytelsb( fp );
        }
      break;

    case 32:                         // 32-bits - 32 bit RGBA 
      for (int py = 0; py < bmp_height; py++ )
        {
        dbptr = m_pdata + (bmp_height-1 - py) * bmp_width * 4;

        for (int px = 0; px < bmp_width; px++ )
          {
          dbptr[3] = (TEXBYTE) readbytelsb( fp );
          dbptr[2] = (TEXBYTE) readbytelsb( fp );
          dbptr[1] = (TEXBYTE) readbytelsb( fp );
          dbptr[0] = (TEXBYTE) readbytelsb( fp );
 
          dbptr += 4; 
          }
        }
      break;
    
    default:
      break;
    }

  fclose( fp );			// Return new image
 
  return( 1 );
  }

// --------------------------------------------------------------------
// Write a BMP file - either 8 bit palette or 24-bit color
//
// Inputs:  path - Pointer to to the file path
//
// Outputs: None
//
// Results: 1 if the file was written successfully, 0 otherwise
//
// Effects: None
// --------------------------------------------------------------------

int CTexture::TextureWritebmp( const char * path )
  {
  FILE       *fp;
  int    len, dstart, cr, cg, cb, cn, padwidth, padbytes, bpp, padarea;
  int        px, py, dpitch;
  colmap4f  *colormap;
  col4f     *cptr;
  TEXBYTE        *sbptr;

  if ( m_type & TEX_16BIT )			// Sanity check
    return(0);

  if ( !(fp = fopen( path, "wb" ) ))		// Open file for writing
    return(0);

  if ( m_type & TEX_RGB )
    bpp = 24;
  else 
    bpp = 8;

  colormap = m_pcolormap;

  padwidth  = ((m_width*(bpp>>3))+3) / 4;
  padwidth *= 4;
  padbytes = padwidth - m_width*(bpp>>3);
  padarea  = padwidth * m_height;

  // -- Write the file header 

  writeshortlsb( fp, BMP_MAGIC );  // Magic number 
  writelonglsb(  fp, 0x0 );        // Filled later - File size 
  writeshortlsb( fp, 0x0 );        // Not used 
  writeshortlsb( fp, 0x0 );        // Not used 
  writelonglsb(  fp, 0x0 );        // Filled later - Offset to pixel data 

  // -- Write image header

  writelonglsb(  fp, 0x28 );		// Header size 
  writelonglsb(  fp, m_width );		// Width 
  writelonglsb(  fp, m_height );	// Height 
  writeshortlsb( fp, 0x01 );        // Planes 
  
  writeshortlsb( fp, bpp  );        // Bits per pixel 
  writelonglsb( fp, 0x0000 );       // No compression 
  writelonglsb( fp, padarea );      // Size of pixel data block 
  writelonglsb( fp, 0x0 );          // Pixels per Meter (X) 
  writelonglsb( fp, 0x0 );          // Pixels per Meter (Y) 

  if ( colormap )                   // Save number of colors 
    {
    writelonglsb( fp, colormap->m_max );
    writelonglsb( fp, colormap->m_max );
    }
  else
    {
    writelonglsb( fp, 0x0 );
    writelonglsb( fp, 0x0 );
    }

  // -- Write color palette 

  if ( colormap )
    {
    cptr = colormap->m_list;

    for ( cn = 0; cn < colormap->m_max; cn++, cptr++ )
      {
      cr = (TEXBYTE) (cptr->m_red   * 255.0f); 
      cg = (TEXBYTE) (cptr->m_green * 255.0f);
      cb = (TEXBYTE) (cptr->m_blue  * 255.0f);

      writebytelsb( fp, cb ); 
      writebytelsb( fp, cg );
      writebytelsb( fp, cr );
      writebytelsb( fp, 0x00 );
      }
    }

  // ------------ Write pixel data ------------------------------------------

  dstart = ftell(fp);
  dpitch = m_width * m_pixelsize;

  if ( colormap )
    for ( py = 0; py < m_height; py++ )					// For each row 
      {
      sbptr = m_pdata + (m_height-1 - py) * dpitch;		// start of row
    
      for ( px = 0; px < m_width; px++, sbptr++ )     
        writebytelsb( fp, *sbptr );						// Write color indices 

      for ( px = 0; px < padbytes; px++ )				// Write padding 
        writebytelsb( fp, 0x00 );
      }
  else
    for ( py = 0; py < m_height; py++ )					// For each row 
      {
      sbptr = m_pdata + (m_height-1 - py) * dpitch;

      for ( px = 0; px < m_width; px++ )
        {
        writebytelsb( fp, sbptr[2] );					// Blue 
        writebytelsb( fp, sbptr[1] );					// Green  
        writebytelsb( fp, sbptr[0] );					// Red 
        
        sbptr += m_pixelsize;
        }

      for ( px = 0; px < padbytes; px++ )				// Padding 
        writebytelsb( fp, 0x00 );
      }

  // -- Update all the dynamic fields --------------------------- 

  len = ftell(fp);                 // Final file size 

  fseek( fp, 0x02, SEEK_SET );     // Save file size in file 
  
  writelonglsb( fp, len );

  fseek( fp, 0x0A, SEEK_SET );

  writelonglsb( fp, dstart );

  fseek( fp, len, SEEK_SET );      // Go back to end of file 

  fclose( fp ); 

  return(1);
  } 
