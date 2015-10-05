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
// Implementation of the TGA file reader/writer program
//
// Author: Michael S. A. Robb
//
// Date:   19th August 2002
//
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// TGA data structures
// --------------------------------------------------------------------------

typedef struct 
{
TEXBYTE  m_idlength;		// ID Length		 - 1 byte  Field 1
TEXBYTE  m_colormaptype;	// Color Map Type    - 1 byte  Field 2
TEXBYTE  m_imagetype;		// Image Type        - 1 byte  Field 3
SHORT m_firstentryindex;	// First entry index - 2 bytes Field 4.1
SHORT m_colormaplength;		// Color map length  - 2 bytes       4.2
TEXBYTE  m_colormapentry;	// Color map entry   - 1 byte        4.3
SHORT m_xorigin;		// X origin		 - 2 bytes Field 5.1
SHORT m_yorigin;		// Y origin          - 2 bytes       5.2
SHORT m_width;			// Image width       - 2 bytes       5.3 
SHORT m_height;			// Image height      - 2 bytes       5.4
TEXBYTE  m_pixeldepth;		// Pixel depth       - 1 byte        5.5
TEXBYTE  m_imagedescriptor;	// Image descriptor  - 1 byte        5.6
} TGA_HEADER;

typedef struct
{
TEXBYTE  m_imageid[256];	// Image length
TEXBYTE *m_pcolormap;		// Color map data
int   m_colorbytes;         	// Number of bytes per color      
} TGA_MISC;

typedef struct
{
SHORT m_extensionsize;        // Field 10 - Extension size
TEXBYTE  m_authorname[41];       // Field 11 - Author name
TEXBYTE  m_authorcomments[324];  // Field 12 - Author comments
SHORT m_month;                // Field 13.1 - Date month
SHORT m_day;                  // Field 13.2 - Date day
SHORT m_year;                 // Field 13.3 - Date year
SHORT m_hour;				  // Field 13.4 - Date hour
SHORT m_minute;			      // Field 13.5 - Date minute
SHORT m_second;				  // Field 13.6 - Date second
TEXBYTE  m_jobname[41];          // Field 14   - Job name/ID
SHORT m_jobhours;             // Field 15.1 - Job time/hours
SHORT m_jobminutes;           // Field 15.2 - Job time/minutes
SHORT m_jobseconds;           // Field 15.3 - Job time/seconds
TEXBYTE  m_softwareid[41];       // Field 16   - Software ID
TEXBYTE  m_softwareversion[3];   // Field 17   - Software version
TEXBYTE  m_keycolor[4];          // Field 18   - Key color
SHORT m_pixelrationum;        // Field 19.1 - Pixel ratio numerator
SHORT m_pixelratiodenom;      // Field 19.2 - Pixel ration denominator
SHORT m_gammanumerator;       // Field 20.1 - Gamma numerator
SHORT m_gammdenominator;      // Field 20.2 - Gamma denominator
ULONG m_colorcorrection;      // Field 21   - Color correction offset
ULONG m_postagestamp;         // Field 22   - Postage stamp offset
ULONG m_scanline;             // Field 23   - Scan line offset
TEXBYTE  m_attributes;           // Field 24   - Attributes type
} TGA_EXTENSION;

// Color Map Type - Field 2 (1 byte)

#define TGA_COLORMAPTYPEMASK 0x01		 // Color map type mask

//  Image Type - Field 3 (1 byte)

#define TGA_COLOURMAP   0x01			 // Colormapped image
#define TGA_TRUECOLOUR  0x02			 // True-color image
#define TGA_BLACKWHITE  0x03			 // Black and White image
#define TGA_COMPRESSED  0x08			 // Compressed image

#define TGA_RLEPACKET   0x80             // RLE Packet
#define TGA_PIXELCOUNT  0x7F             // RLE pixel count

#define TGA_IMAGE_NONE   0x00			 // No image data
#define TGA_IMAGE_UCM 	(TGA_COLOURMAP)  // Uncompressed colormap
#define TGA_IMAGE_URGB  (TGA_TRUECOLOUR) // Uncompressed RGB(A)
#define TGA_IMAGE_UBW   (TGA_BLACKWHITE) // Uncompressed BW

#define TGA_IMAGE_RLECM (TGA_COMPRESSED|TGA_COLOURMAP) // Compressed colormap
#define TGA_IMAGE_RLETC (TGA_COMPRESSED|TGA_TRUECOLOUR) // Compressed RGB
#define TGA_IMAGE_RLEBW (TGA_COMPRESSED|TGA_BLACKWHITE) // Compressed B/W

// --------------------------------------------------------------------------
// Debug routine to dump the header of a TGA file
// --------------------------------------------------------------------------

void tga_dumpheader( TGA_HEADER &header, char *path )
{
FILE *fp;

if ( !( fp = fopen( path, "w" ) ) )
	return;

fprintf( fp, "ID length        = %d\n", header.m_idlength     );
fprintf( fp, "Colormap type    = %d ", header.m_colormaptype );

if ( header.m_colormaptype == 0 )
	fprintf( fp, "(None)\n" );
else
	fprintf( fp, "(Present)\n" );

fprintf( fp, "Image type       = %d ", header.m_imagetype    );

switch ( header.m_imagetype )
	{
	case 0: 
		fprintf( fp, "No Image Data Included\n" );		
		break;	

	case 1:
		fprintf( fp, "Uncompressed, Color-mapped Image\n" );
		break;

	case 2: 
		fprintf( fp, "Uncompressed, True-color Image\n" );
		break;

	case 3:
		fprintf( fp, "Uncompressed, Black-and-white Image\n" );
		break;

	case 9:
		fprintf( fp, "Run-length encoded, Color-mapped Image\n" );
		break;

	case 10:
		fprintf( fp, "Run-length encoded, True-color Image\n" );
		break;

	case 11:
		fprintf( fp, "Run-length encoded, Black-and-white Image\n" );
		break;

	default:
		fprintf( fp, "Unknown format\n" );
		break;
	}
	
fprintf( fp, "CMAP first index = %d\n", header.m_firstentryindex );
fprintf( fp, "CMAP length      = %d\n", header.m_colormaplength );
fprintf( fp, "CMAP entry size  = %d\n", header.m_colormapentry );
fprintf( fp, "X origin         = %d\n", header.m_xorigin );
fprintf( fp, "Y origin         = %d\n", header.m_yorigin );
fprintf( fp, "Image Width      = %d\n", header.m_width );
fprintf( fp, "Image Height     = %d\n", header.m_height );
fprintf( fp, "Pixel Depth      = %d\n", header.m_pixeldepth );
fprintf( fp, "Image descriptor = %02X", header.m_imagedescriptor );

if ( header.m_imagedescriptor & 0x20 )
	fprintf( fp, "(top " );
else	
	fprintf( fp, "(bottom " );

if ( header.m_imagedescriptor & 0x10 )
	fprintf( fp, "right )\n" );
else
	fprintf( fp, "left )\n" );

fclose( fp );
}

// --------------------------------------------------------------------------
// Read the TGA file header
//
// Inputs: pheader - Pointer to the header
//         fp      - File handler
//
// Outputs: None
//
// Results: None
//
// Effects: The file handler will read in 18 bytes
// --------------------------------------------------------------------------

void readtgaheader( TGA_HEADER &tgaheader, FILE *fp )
{
tgaheader.m_idlength        = (TEXBYTE)  readbytelsb(  fp );	// Field 1
tgaheader.m_colormaptype    = (TEXBYTE)  readbytelsb(  fp );	// Field 2
tgaheader.m_imagetype       = (TEXBYTE)  readbytelsb(  fp );	// Field 3
tgaheader.m_firstentryindex = (SHORT) readshortlsb( fp );	// Field 4.1
tgaheader.m_colormaplength  = (SHORT) readshortlsb( fp );	// Field 4.2
tgaheader.m_colormapentry   = (TEXBYTE)  readbytelsb(  fp );	// Field 4.3
tgaheader.m_xorigin         = (SHORT) readshortlsb( fp );	// Field 5.1
tgaheader.m_yorigin	= (SHORT) readshortlsb( fp );		// Field 5.2
tgaheader.m_width	= (SHORT) readshortlsb( fp );		// Field 5.3
tgaheader.m_height	= (SHORT) readshortlsb( fp );		// Field 5.4
tgaheader.m_pixeldepth  = (TEXBYTE)  readbytelsb(  fp );	// Field 5.5
tgaheader.m_imagedescriptor = (TEXBYTE)  readbytelsb(  fp );	// Field 5.6
}

// --------------------------------------------------------------------------
// Write the TGA file header
//
// Inputs: pheader - Pointer to the header
//         fp      - File handler
//
// Outputs: None
//
// Results: None
//
// Effects: The file handler will read in 18 bytes
//
// Notes: This header occupies  18 bytes
//
// Name              Size Offset
// -----------------------------
// idlength          1    0
// colormaptype      1    1 
// imagetype         1    2
// firstentryindex   2    3 
// colormaplength    2    5 
// colormapentry     1    7
// xorigin           2    8
// yorigin           2   10
// width             2   12
// height            2   14
// pixeldepth        1   16
// imagedescriptor   1   17
// -----------------------------
//
// --------------------------------------------------------------------------

void writetgaheader( TGA_HEADER &tgaheader, FILE *fp )
{
writebytelsb(  fp, (TEXBYTE)  tgaheader.m_idlength        );	// Field 1
writebytelsb(  fp, (TEXBYTE)  tgaheader.m_colormaptype    );	// Field 2
writebytelsb(  fp, (TEXBYTE)  tgaheader.m_imagetype       );	// Field 3
writeshortlsb( fp, (SHORT) tgaheader.m_firstentryindex );	// Field 4.1
writeshortlsb( fp, (SHORT) tgaheader.m_colormaplength  );	// Field 4.2
writebytelsb(  fp, (TEXBYTE)  tgaheader.m_colormapentry   );	// Field 4.3
writeshortlsb( fp, (SHORT) tgaheader.m_xorigin         );	// Field 5.1
writeshortlsb( fp, (SHORT) tgaheader.m_yorigin		   );	// Field 5.2
writeshortlsb( fp, (SHORT) tgaheader.m_width		   );	// Field 5.3
writeshortlsb( fp, (SHORT) tgaheader.m_height		   );	// Field 5.4
writebytelsb(  fp, (TEXBYTE)  tgaheader.m_pixeldepth	   );	// Field 5.5
writebytelsb(  fp, (TEXBYTE)  tgaheader.m_imagedescriptor );	// Field 5.6
}

// --------------------------------------------------------------------------
// Read in a TGA file
//
// Inputs: path - character pointer to full path of file
//
// Outputs: None
//
// Results: Non-zero if file was written, zero otherwise
//
// Effects: The image data is written to the file in TGA format
// --------------------------------------------------------------------------

static char truevisioncodes[] = 
	{
        "\000\000\000\000\000\000\000\000TRUEVISION-XFILE.\000"
	};

int CTexture::TextureReadtga( const char *path )
{
TGA_HEADER tgaheader;
TGA_MISC   tgamisc;
col4f *pcol;
col3b *p3bdst, p3btemp;
col4b *p4bdst, p4btemp;
int px, py;

int	 packtype, elsize, npixels, pn, bits;
TEXBYTE pixel[4], *pdst;
FILE *fp;
struct stat statbuf;
char signature[32];

// ----- 1. Open the file and read the file header --------------------------

if ( !(fp = fopen( path, "rb" ) ) )
    return( 0 );

stat( path, &statbuf );		// 1. Determine file length

fseek( fp, statbuf.st_size-26L, SEEK_SET ); // 2. Seek to length -26 bytes

fread( signature, 16, 1, fp ); // 3. Read the 26 byte

				// 4. Check to see if the 26 bytes match "TRUEVISION-XFILE"

fseek( fp, 0, SEEK_SET );

readtgaheader( tgaheader, fp );
/*
if (strncmp(signature, tga_signature, 16) != 0)
	{
	return -1;
	}
*/
// tga_dumpheader( tgaheader, "dump.txt" );

// ----- 2. Read the image ID -----------------------------------------------

if ( tgaheader.m_idlength > 0 )
	{
	fread( tgamisc.m_imageid, tgaheader.m_idlength, 1, fp );
	}
	
// ----- 3. Read the color map data -----------------------------------------

if ( tgaheader.m_colormaptype == 1 )   // Colormap exists?
	{
	tgamisc.m_colorbytes = (tgaheader.m_colormapentry+7) /8;
	tgamisc.m_colorbytes *= tgaheader.m_colormaplength;

	tgamisc.m_pcolormap = new TEXBYTE[ tgamisc.m_colorbytes ];

	fread( tgamisc.m_pcolormap, tgamisc.m_colorbytes, 1, fp );
	}
else
	{
	tgamisc.m_colorbytes = 0;
	tgamisc.m_pcolormap = NULL;
	}

// ----- 4. Sanity check - Ensure that the image and colormap share the same -
//          thoughts on using colormaps

if ( tgaheader.m_colormapentry != ((tgaheader.m_imagetype & 0x03) == 0x01) )
	{
	fclose(fp);
	return(0);
	}

// ----- 5. Allocate memory for the image data ------------------------------

elsize = (tgaheader.m_pixeldepth + 7 ) / 8;

switch( tgaheader.m_imagetype )
	{
	case 1:		// Uncompressed Color Mapped Images	
		Allocate( tgaheader.m_width, tgaheader.m_height, TEX_PALETTE );
		break;

	case 2:		// Uncompressed True Color Images
		if ( tgaheader.m_pixeldepth == 24)
			Allocate( tgaheader.m_width, tgaheader.m_height, TEX_RGB );
		else
		if ( tgaheader.m_pixeldepth == 32)
			Allocate( tgaheader.m_width, tgaheader.m_height, TEX_RGBA );
		break;

	case 3:		// Uncompressed Black and White (Unmapped) images

		if ( tgaheader.m_pixeldepth <= 8)
 			Allocate( tgaheader.m_width, tgaheader.m_height, TEX_MONO );	
		else
			Allocate( tgaheader.m_width, tgaheader.m_height, TEX_MONO16 );	
		break;

	case 9:     // RLE Compressed color mapped images
		Allocate( tgaheader.m_width, tgaheader.m_height, TEX_PALETTE );
		break;

	case 10:    // RLE Compressed True color images
		if ( tgaheader.m_pixeldepth == 24)
			Allocate( tgaheader.m_width, tgaheader.m_height, TEX_RGB );
		else
		if ( tgaheader.m_pixeldepth == 32)
			Allocate( tgaheader.m_width, tgaheader.m_height, TEX_RGBA );
		break;

	case 11:    // RLE Compressed Black and White images
		Allocate( tgaheader.m_width, tgaheader.m_height, TEX_MONO );
		break;

	default:	
		break;
	}

// ----- 6. Read in the image data from the file ----------------------------

if ( tgaheader.m_imagetype & TGA_COMPRESSED )
	{	
	npixels = m_area;		// Number of pixels to write
	pdst	= m_pdata;		// Pointer to destination framebuffer

	while ( npixels > 0 )
		{
		packtype = readbytelsb( fp );	  // Read packet type/pixel count

		if ( packtype & TGA_RLEPACKET )	  
			{							     
			packtype &= TGA_PIXELCOUNT;   // Mask off PACKET flag
			packtype++;				      // Increment

			fread( pixel, elsize,1, fp ); // Read 1 x Pixel data
			npixels -= packtype;		  // npixels -= N

			while ( packtype-- )		  //		While ( pixelcount-- )
				{
				memcpy( pdst, pixel, elsize );	//	WritePixel( PixelData )
				pdst += elsize;					//	pixelbuffer++
				}							//		End
			}								//	End
		else							
			{		
			packtype++;								//  N++
			fread( pdst, packtype, elsize, fp );	//	Read N Pixels
		
			pdst += packtype*elsize;				// pixelbuffer += N
			npixels -= packtype;					// npixels		-= N
			}					
		}
	}
else
	{
	fread( m_pdata, m_width*m_height, elsize, fp );
	}

// ----- Swap the pixel round here -------------------------------------------

//if ( tgaheader.m_imagetype & TGA_COMPRESSED )
switch (tgaheader.m_pixeldepth )
	{
	case 24:
#ifdef DEBUG
		printf( "TGA Swapping RGB\n");
#endif
		p3bdst = (col3b *) m_pdata + (m_height-1)*m_width;

		for ( py = 0; py < m_height; py++ )
			{
			for ( px = 0; px < m_width; px++ )
				{	
				p3btemp = *p3bdst;

				p3bdst->m_red   = p3btemp.m_blue;
				p3bdst->m_green = p3btemp.m_green;
				p3bdst->m_blue  = p3btemp.m_red;

				p3bdst++;
				}

			p3bdst -= (m_width<<1);
			}
		break;

	case 32:
#ifdef DEBUG
		printf( "TGA Swapping RGBA\n");
#endif
		p4bdst = (col4b *) m_pdata + (m_height-1) *m_width;

		for ( py = 0; py < m_height; py++ )
			{
			for ( px = 0; px < m_width; px++ )	
				{
				p4btemp = *p4bdst;

				p4bdst->m_red   = p4btemp.m_blue;
				p4bdst->m_green = p4btemp.m_green;	
				p4bdst->m_blue  = p4btemp.m_red;
				p4bdst->m_alpha = p4btemp.m_alpha;

				p4bdst++;
				}

			p4bdst -= (m_width<<1);
			}
		break;

	default:
		break;
	}
	
// ----- 7. Read the colormap data ------------------------------------------

if ( tgamisc.m_pcolormap && m_type == TEX_PALETTE )
	{
	switch ( tgaheader.m_colormapentry )
		{
		case 15:		// Does this happen?
		case 16:
			pcol = m_pcolormap->m_list;
			
			for ( pn = 0; pn < tgaheader.m_colormaplength; pn++, pcol++ )
				{
				bits = tgamisc.m_pcolormap[pn*2] + (tgamisc.m_pcolormap[pn*2+1] << 8);
				pcol->m_red   = ((float)((bits>>10) & 0x1F)) / 255.0f;
				pcol->m_green = ((float)((bits>>5)  & 0x1F)) / 255.0f;
				pcol->m_blue  =  (float)((bits      & 0x1F)) / 255.0f;
				pcol->m_alpha = 1.0f;
				}
	
			m_pcolormap->m_num = tgaheader.m_colormaplength;
			break;

		case 24:
			pcol = m_pcolormap->m_list;

			for ( pn = 0; pn < tgaheader.m_colormaplength; pn++, pcol++ )
				{
				pcol->m_red   = tgamisc.m_pcolormap[pn*3];
				pcol->m_green = tgamisc.m_pcolormap[pn*3+1];
				pcol->m_blue  = tgamisc.m_pcolormap[pn*3+2];
				pcol->m_alpha = 1.0f;
				}

			m_pcolormap->m_num = tgaheader.m_colormaplength;
			break;
		
		case 32:
			pcol = m_pcolormap->m_list;

			for ( pn = 0; pn < tgaheader.m_colormaplength; pn++, pcol++ )
				{
				pcol->m_red   = tgamisc.m_pcolormap[pn*4];
				pcol->m_green = tgamisc.m_pcolormap[pn*4+1];
				pcol->m_blue  = tgamisc.m_pcolormap[pn*4+2];
				pcol->m_alpha = 1.0f;
				}

			m_pcolormap->m_num = tgaheader.m_colormaplength;
			break;

		default:
			break;
		}
	}

// ----- 8. Close the file and continue -------------------------------------

fclose( fp );

// Notes: 00 = bottom left
//        01 = bottom right
//        10 = top left
//        11 = top right

if (!(tgaheader.m_imagedescriptor & 0x20) )
	TextureFlipv();
/*
if ( !(tgaheader.m_imagedescriptor & 0x10) )
	TextureFliph();
*/
return( 1 );
}

// --------------------------------------------------------------------------
// Write out TGA image data for RGB data
// 
// Inputs: CTexture - Reference to CTexture class
//         fp       - File stream to write data to
//
// Outputs: None
//
// Results: Non-zero if file was written, zero otherwise
//
// Effects: The image data is written to the file
// --------------------------------------------------------------------------

void writetgaimagergb( CTexture &texture, FILE *fp )
{
col3b ccur, cnext, *pcur, *pstart, *pdata;
int max, npixels, ny, px, py;

if  ( !(texture.m_type & TGA_COMPRESSED) )
        {
        pdata = (col3b *) texture.m_pdata 
	      + (texture.m_height-1) * texture.m_width;

        for ( py = 0; py < texture.m_height; py++ )
                {
                for ( px = 0; px < texture.m_width; px++ )
                        {
                        writebytelsb( fp, pdata->m_blue );
                        writebytelsb( fp, pdata->m_green );
                        writebytelsb( fp, pdata->m_red );

                        pdata++;
                        }

                pdata -= (texture.m_width<<1);
                }

	fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block

        return;
        }

for ( ny = 0; ny < texture.m_height; ny++ )		// For each row
	{
	pcur = (col3b *) texture.m_pdata + texture.m_width * ny;	// Start of row	
	max = texture.m_width;

	while ( max > 0 )					// While row not complete
		{
		ccur = pcur[0];					// Read first pixel

		if ( max == 1 )					// Only one pixel left?
			{
			writebytelsb( fp, 0x00       );	// Write out RLE tag
			writebytelsb( fp, ccur.m_red );	// Write out RGB colour
			writebytelsb( fp, ccur.m_green );
			writebytelsb( fp, ccur.m_blue );

			max -= 1;
			pcur += 1;			
			}	
		else							// More than one pixel?
			{
			cnext = pcur[1];			// Read second pixel
	
			if ( cnext == ccur )		// Do the pixels match?
				{
				npixels  = 2;			// Yes, so use RLE blocks
				pcur	+= 2;
				max     -= 2;

				while ( (*pcur == ccur ) && (max > 0) && (npixels<127) )
					{
					pcur++;
					max--;
					npixels++;
					}

				writebytelsb( fp, (npixels-1)|0x80 ); // Write tag
				writebytelsb( fp, ccur.m_red );		  // Write color
				writebytelsb( fp, ccur.m_green );
				writebytelsb( fp, ccur.m_blue );
				}
			else
				{			
				pstart  = pcur;		// First pixel to write
				npixels = 2;
				max    -= 2;

				while ( (pcur[npixels-1] != pcur[npixels]) && (max >0) && (npixels<128) )
					{
					npixels++;		
					max--;
					}

				pcur += npixels;
			
				writebytelsb( fp, npixels-1 );	  // Write out the block tag
		
				fwrite( pstart, sizeof(ccur), npixels, fp ); // Write out the pixel block
				}
			}
		}
	}			

fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block
}


// --------------------------------------------------------------------------
// Write out TGA image data for RGBA data
// 
// Inputs: CTexture - Reference to CTexture class
//         fp       - File stream to write data to
//
// Outputs: None
//
// Results: Non-zero if file was written, zero otherwise
//
// Effects: The image data is written to the file
// --------------------------------------------------------------------------

void writetgaimagergba( CTexture &texture, FILE *fp )
{
col4b ccur, cnext, *pcur, *pstart, *pdata;
int max, npixels, ny, px, py;

// ----- Handle the uncompressed case ---------------------------------------

if  ( !(texture.m_type & TEX_COMPRESSED) )
        {
	pdata = (col4b *) texture.m_pdata + (texture.m_height-1) * texture.m_width;
	for ( py = 0; py < texture.m_height; py++ )
		{
		for ( px = 0; px < texture.m_width; px++ )
			{
			writebytelsb( fp, pdata->m_blue );
			writebytelsb( fp, pdata->m_green );
			writebytelsb( fp, pdata->m_red );
			writebytelsb( fp, pdata->m_alpha );

			pdata++;
			}

		pdata -= (texture.m_width<<1);
		}

	fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block
        return;
        }

for ( ny = 0; ny < texture.m_height; ny++ )		// For each row
	{
	pcur = (col4b *) texture.m_pdata + texture.m_width * ny;	// Start of row	
	max = texture.m_width;

	while ( max > 0 )					// While row not complete
		{
		ccur = pcur[0];					// Read first pixel

		if ( max == 1 )					// Only one pixel left?
			{
			writebytelsb( fp, 0x00       );	// Write out RLE tag
			writebytelsb( fp, ccur.m_blue );			// Write out RGB colour
			writebytelsb( fp, ccur.m_green );
			writebytelsb( fp, ccur.m_red );	
			writebytelsb( fp, ccur.m_alpha );		

			max -= 1;
			pcur += 1;
			}	
		else							// More than one pixel?
			{
			cnext = pcur[1];			// Read second pixel
	
			if ( cnext == ccur )		// Do the pixels match?
				{
				npixels  = 2;			// Yes, so use RLE blocks
				pcur	+= 2;
				max     -= 2;

				while ( (*pcur == ccur ) && (max > 0) && (npixels<127) )
					{
					pcur++;
					max--;
					npixels++;
					}

				writebytelsb( fp, (npixels-1)|0x80 ); // Write tag
				writebytelsb( fp, ccur.m_blue );		  // Write color
				writebytelsb( fp, ccur.m_green );
				writebytelsb( fp, ccur.m_red );
				writebytelsb( fp, ccur.m_alpha );
				}
			else
				{			
				pstart  = pcur;		// First pixel to write
				npixels = 2;
				max    -= 2;

				while ( (pcur[npixels-1] != pcur[npixels]) && (max >0) && (npixels<127) )
					{
					npixels++;		
					max--;
					}

				pcur += npixels;
	
				writebytelsb( fp, npixels-1 );	  // Write out the block tag
		
				fwrite( pstart, sizeof(ccur), npixels, fp ); // Write out the pixel block
				}
			}
		}
	}			

fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block
}

// --------------------------------------------------------------------------
// Write out TGA image data for 8-bit index/black-white data
// 
// Inputs: CTexture - Reference to CTexture class
//         fp       - File stream to write data to
//
// Outputs: None
//
// Results: Non-zero if file was written, zero otherwise
//
// Effects: The image data is written to the file
// --------------------------------------------------------------------------

void writetgaimagepalette( CTexture &texture, FILE *fp )
{
TEXBYTE ccur, cnext, *pcur, *pstart;
int max, npixels, ny;

if  ( !(texture.m_type & TEX_COMPRESSED) )
        {
	fwrite( texture.m_pdata, texture.m_size, 1, fp );
	fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block
        return;
        }

for ( ny = 0; ny < texture.m_height; ny++ )		// For each row
	{
	pcur = (TEXBYTE *) texture.m_pdata + texture.m_width * ny;	// Start of row	
	max = texture.m_width;

	while ( max > 0 )					// While row not complete
		{
		ccur = pcur[0];					// Read first pixel

		if ( max == 1 )					// Only one pixel left?
			{
			writebytelsb( fp, 0x00 );	// Write out RLE tag
			writebytelsb( fp, ccur );	// Write out colour

			max -= 1;
			pcur += 1;
			}	
		else							// More than one pixel?
			{
			cnext = pcur[1];			// Read second pixel
	
			if ( cnext == ccur )		// Do the pixels match?
				{
				npixels  = 2;			// Yes, so use RLE blocks
				pcur	+= 2;
				max     -= 2;

				while ( (*pcur == ccur ) && (max > 0) && (npixels<127) )
					{
					pcur++;
					max--;
					npixels++;
					}

				writebytelsb( fp, (npixels-1)|0x80 ); // Write tag
				writebytelsb( fp, ccur );		      // Write color
				}
			else
				{			
				pstart  = pcur;		// First pixel to write
				npixels = 2;
				max    -= 2;

				while ( (pcur[npixels-1] != pcur[npixels]) && (max >0) && (npixels<127) )
					{
					npixels++;		
					max--;
					}

				pcur += npixels;
			
				writebytelsb( fp, npixels-1 );	  // Write out the block tag
		
				fwrite( pstart, sizeof(ccur), npixels, fp ); // Write out the pixel block
				}
			}
		}
	}   			

fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block
}

// --------------------------------------------------------------------------
// Write out TGA image data for 16-bit index data
// 
// Inputs: CTexture - Reference to CTexture class
//         fp       - File stream to write data to
//
// Outputs: None
//
// Results: Non-zero if file was written, zero otherwise
//
// Effects: The image data is written to the file
// --------------------------------------------------------------------------

void writetgaimagemono16( CTexture &texture, FILE *fp )
{
SHORT ccur, cnext, *pcur, *pstart;
int max, npixels, ny, nx;
TEXBYTE *pcolor;
ULONG val;

if  ( !(texture.m_type & TEX_COMPRESSED) )
        {
        pcolor = texture.m_pdata;

        for ( ny = 0; ny < texture.m_height; ny++ )
            for ( nx = 0; nx < texture.m_width; nx++, pcolor += 2 ) 
                {
                val = *( (SHORT *) pcolor );

                writeshortlsb( fp, val );
                }
	fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block
        return;
        }

for ( ny = 0; ny < texture.m_height; ny++ )		// For each row
	{
	pcur = (SHORT *) texture.m_pdata + texture.m_width * ny;	// Start of row	
	max = texture.m_width;

	while ( max > 0 )					// While row not complete
		{
		ccur = pcur[0];					// Read first pixel

		if ( max == 1 )					// Only one pixel left?
			{
			writebytelsb( fp, 0x00 );	// Write out RLE tag
			writeshortlsb( fp, ccur );	// Write out colour

			max -= 1;
			pcur += 1;
			}	
		else							// More than one pixel?
			{
			cnext = pcur[1];			// Read second pixel
	
			if ( cnext == ccur )		// Do the pixels match?
				{
				npixels  = 2;			// Yes, so use RLE blocks
				pcur	+= 2;
				max     -= 2;

				while ( (*pcur == ccur ) && (max > 0) && (npixels<127) )
					{
					pcur++;
					max--;
					npixels++;
					}

				writebytelsb( fp, (npixels-1)|0x80 ); // Write tag
				writeshortlsb( fp, ccur );		      // Write color
				}
			else
				{			
				pstart  = pcur;		// First pixel to write
				npixels = 2;
				max    -= 2;

				while ( (pcur[npixels-1] != pcur[npixels]) && (max >0) && (npixels<127) )
					{
					npixels++;		
					max--;
					}

				pcur += npixels;
			
				writebytelsb( fp, npixels-1 );	  // Write out the block tag
		
				fwrite( pstart, sizeof(ccur), npixels, fp ); // Write out the pixel block
				}
			}
		}
	}			

fwrite( truevisioncodes, 26, 1, fp ); // Write out the pixel block
}

// --------------------------------------------------------------------------
// Write out a TGA file
//
// Inputs: path - character pointer to full path of file
//
// Outputs: None
//
// Results: Non-zero if file was read, zero otherwise
//
// Effects: The image data is read from the file
// --------------------------------------------------------------------------

int CTexture::TextureWritetga( const char *path )
{
TGA_HEADER tgaheader;
FILE *fp;
col4f *pcol;
int np;

// ----- 1. Open the file ---------------------------------------------------

if ( !(fp = fopen( path, "wb" ) ) )
    return( 0 );

// ----- 2. Configure the file header ---------------------------------------

tgaheader.m_idlength = 0;		 	 	// Field 1
tgaheader.m_colormaptype = (m_type == TEX_PALETTE ); 	// Field 2
				
switch ( m_type & TEX_MODEMASK )		       	// Field 3
	{
	case TEX_RGB:
		tgaheader.m_imagetype = TGA_TRUECOLOUR; // Field 4
		tgaheader.m_firstentryindex = 0;	// Field 4.1
		tgaheader.m_colormaplength = 0;		// Field 4.2
		tgaheader.m_colormapentry = 0;		// Field 4.3
		tgaheader.m_pixeldepth = 24;		// Field 5.5
		break;

	case TEX_RGBA:
		tgaheader.m_imagetype = TGA_TRUECOLOUR; // Field 4
		tgaheader.m_firstentryindex = 0;	// Field 4.1
		tgaheader.m_colormaplength = 0;		// Field 4.2
		tgaheader.m_colormapentry = 0;		// Field 4.3
		tgaheader.m_pixeldepth = 32;		// Field 5.5
		break;	

	case TEX_PALETTE:
		tgaheader.m_imagetype = TGA_COLOURMAP;  // Field 4
		tgaheader.m_firstentryindex = 0;	// Field 4.1
		tgaheader.m_colormaplength = 256;	// Field 4.2
		tgaheader.m_colormapentry = 24;		// Field 4.3
		tgaheader.m_pixeldepth = 8;		// Field 5.5
		break;

	case TEX_MONO:
		tgaheader.m_imagetype = TGA_BLACKWHITE; // Field 4
		tgaheader.m_firstentryindex = 0;	// Field 4.1
		tgaheader.m_colormaplength = 0;		// Field 4.2
		tgaheader.m_colormapentry = 0;		// Field 4.3
		tgaheader.m_pixeldepth = 8;		// Field 5.5
		break;

	case TEX_MONO16:
		tgaheader.m_imagetype = TGA_BLACKWHITE; // Field 4
		tgaheader.m_firstentryindex = 0;	// Field 4.1
		tgaheader.m_colormaplength = 0;		// Field 4.2
		tgaheader.m_colormapentry = 0;		// Field 4.3
		tgaheader.m_pixeldepth = 16;		// Field 5.5
		break;

	default:		
		break;
	}

if ( m_type & TEX_COMPRESSED )
    tgaheader.m_imagetype |= TGA_COMPRESSED;

tgaheader.m_xorigin = 0;		// Field 5.1
tgaheader.m_yorigin = 0;		// Field 5.2
tgaheader.m_width   = m_width;  // Field 5.3
tgaheader.m_height = m_height;  // Field 5.4
	
tgaheader.m_imagedescriptor = 0x8; // Field 5.6

// ----- 3. Write the file header --------------------------------------------

writetgaheader( tgaheader, fp );

// ----- 3. Write the color map data -----------------------------------------

if ( m_type == TEX_PALETTE )
	{
	pcol = m_pcolormap->m_list;

	for ( np = 0; np < 256; np++, pcol++ )	
		{
		writebytelsb( fp, (int)(pcol->m_red   * 255.0f) );
		writebytelsb( fp, (int)(pcol->m_green * 255.0f) );
		writebytelsb( fp, (int)(pcol->m_blue  * 255.0f) );
		}
	}

// ----- 4. Write out the image data -----------------------------------------

// We have to process each row in turn
//
// Each row is comprised of a set of run-length compressed and uncompressed
// blocks.

// If a block of unrelated pixels are run-length encoded, then this will
// increase the file size by 20% to 25%. 
// Therefore it is better to classify unrelated pixels in uncompressed blocks
// The TGA file format can support blocks up to 128 pixels in length
//
// So, when is the saving made?
//
// N unrelated pixels = N+N.Psize bytes RLE
// N unrelated pixels = 1+N.Psize bytes block encoded
//
// Difference = N-1 bytes
//
// How do we tell when RLE encoding should be used?
//
// If two pixels are identical it is obviously more efficient to use run
// length encoding
//
// If two pixels are different, it is more efficient to use uncompressed
// encoding. 

switch ( m_type & TEX_MODEMASK )
	{
	case TEX_RGB:	
		writetgaimagergb( *this, fp );
		break;

	case TEX_RGBA:
		writetgaimagergba( *this, fp );
		break;

	case TEX_MONO:
	case TEX_PALETTE:
		writetgaimagepalette( *this, fp );
		break;

	case TEX_MONO16:
		writetgaimagemono16( *this, fp );
		break;

	default:
		break;
	}
	
// ----- 5. Close the file and return ----------------------------------------

fclose( fp );

return( 1 );
}
