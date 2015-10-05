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
// C++ Source file defining functions used to read and write TIFF files
//
// Author:  Michael S. A. Robb
//
// Date:    August 2002
// --------------------------------------------------------------------------
 
#include "texturelib.h"

// --------------------------------------------------------------------------
// Display TIFF data 
// --------------------------------------------------------------------------
 
void tiff_data_display( TIFF_DATA *tdptr, FILE *fp )
  {
  if ( tdptr->m_subfiletype )
    {
    fprintf( fp, "SubFileType   = %ld\n", tdptr->m_subfiletype );

    if ( tdptr->m_subfiletype == 1 )
      {
      fputs( "Full resolution image data", fp );
      fputs( " ImageWidth, ImageLength, and StripOffsets are required", fp );
      }

    if ( tdptr->m_subfiletype == 2 )
      {
      fputs( "Reduced resolution image data", fp );
      fputs( "ImageWidth, ImageLength, and StripOffsets", fp );
      }

    if ( tdptr->m_subfiletype == 3 )
      {
      fputs( "Single page of a multi-page image", fp );
      fputs( "(see the PageNumber tag description).", fp );
      }
    }

  if ( tdptr->m_thresholding )
    {
    fprintf( fp, "Thresholding = %ld\n", tdptr->m_thresholding );

    if ( tdptr->m_thresholding == 1)
      fputs( "Bilevel line art scan.  BitsPerSample must be 1.", fp );

    if ( tdptr->m_thresholding == 2 )
      {
      fputs( "A halftone or dithered scan, usually of continuous tone data", fp );
      fputs( "such as photographs.  BitsPerSample must be 1.", fp );
      }

    if ( tdptr->m_thresholding == 3 )
      fputs( "Error Diffused.", fp );
    }

  if ( tdptr->m_cellwidth )
    fprintf( fp, "CellWidth = %ld\n", tdptr->m_cellwidth );

  if ( tdptr->m_celllength )
    fprintf( fp, "CellLength = %ld\n", tdptr->m_celllength );

  if ( tdptr->m_fillorder )
    {
    fprintf( fp, "FillOrder = %ld\n", tdptr->m_fillorder );

    if ( tdptr->m_fillorder == 0x01 )
      {
      fputs( "Most significant bits of the byte are filled first.", fp );
      fputs( "That is, data values (or code words) are ordered from.", fp );
      fputs( "high order bit to low order bit within a byte.", fp );
      }

    if ( tdptr->m_fillorder == 0x02 )
      fputs( "Least significant bits are filled first.", fp );
    }

  fprintf( fp, "Width         = %ld\n", tdptr->m_width );
  fprintf( fp, "Length        = %ld\n", tdptr->m_length );
  fprintf( fp, "BitsPerSample = %2d %2d %2d\n",
    tdptr->m_redsample, tdptr->m_greensample, tdptr->m_bluesample );

      fputs( "  Number of bits per color plane.", fp );

  fprintf( fp, "Compression = %ld\n", tdptr->m_compression );

      if ( tdptr->m_compression == 0x01 )
        fputs( "  No Compression, but pack as tightly as possible.", fp );
      else
      if ( tdptr->m_compression == 0x02 )
        fputs( "  CCITT Group 3 1-Dimensional Modified RLE.", fp );
      else
      if ( tdptr->m_compression == 0x03 )
        fputs( "  Fax-compatible CCITT Group 3.", fp );
      else
      if ( tdptr->m_compression == 0x04 )
        fputs( "  Fax-compatible CCITT Group 4.", fp );

  fprintf( fp, "PhotoMetricInterpretation = %ld\n", tdptr->m_photometricinterp );

      if ( tdptr->m_photometricinterp == 0x00 )
        fputs( "  MinSampleValue imaged as white.", fp );

      if ( tdptr->m_photometricinterp == 0x01 )
        fputs( "  MinSampleValue imaged as black.", fp );

      if ( tdptr->m_photometricinterp == 0x02 )
        fputs( "  RGB in Red|Green|Blue order.", fp );

  fprintf( fp, "StripOffsets = %ld\n", tdptr->m_stripoffsets );

      fputs( "  Offset from start of file.", fp );

  fprintf( fp, "SamplesPerPixel = %ld\n", tdptr->m_samplesperpixel );

      fputs("  Number of bytes per pixel.", fp );

  fprintf( fp, "StripByteCounts = %ld\n", tdptr->m_stripbytecounts );

      fputs( "  Number of bytes in each strip.", fp );

  fprintf( fp, "PlanarConfiguration = %ld\n", tdptr->m_planarconfiguration );

      if ( tdptr->m_planarconfiguration == 0x01 )
        fputs( "  Sample values for each pixel are stored contiguously.\n", fp );

      if ( tdptr->m_planarconfiguration == 0x02 )
        fputs( "  Sample values are stored in separate planes.\n", fp );
  }

// -------------------------------------------------------------------------
// Extract field information 
// -------------------------------------------------------------------------
 
void tiff_field_handle( TIFF_FIELD *tfptr, TIFF_DATA *tdptr )
  {
  switch ( tfptr->m_tag )
    {
    case TAG_NewSubFileType:
      tdptr->m_newsubfiletype = tfptr->m_offset;
      break;

    case TAG_Orientation:  
      tdptr->m_orientation = tfptr->m_offset;
      break;

    case TAG_RowsPerStrip:
      tdptr->m_rowsperstrip = tfptr->m_offset;
      break;

    case TAG_XResolution:
      tdptr->m_xresolution = tfptr->m_offset;
      break;

    case TAG_YResolution:
      tdptr->m_yresolution = tfptr->m_offset;
      break;
 
    case TAG_SubFileType:
      tdptr->m_subfiletype = tfptr->m_offset;
      break;

    case TAG_FillOrder:
      tdptr->m_fillorder = tfptr->m_offset;
      break;

    case TAG_Thresholding:
      tdptr->m_thresholding = tfptr->m_offset;
      break;

    case TAG_CellWidth:
      tdptr->m_cellwidth = tfptr->m_offset;
      break;

    case TAG_CellLength:
      tdptr->m_celllength = tfptr->m_offset;
      break;

    case TAG_Width:
      tdptr->m_width = tfptr->m_offset;
      break;

    case TAG_Length:
      tdptr->m_length = tfptr->m_offset;
      break;

    case TAG_BitsPerSample:
      tdptr->m_bitspersample = tfptr->m_offset;
      break;

    case TAG_Compression:
      tdptr->m_compression = tfptr->m_offset;
      break;

    case TAG_PhotoMetricInterpretation:
      tdptr->m_photometricinterp = tfptr->m_offset;
      break;

    case TAG_StripOffsets:
      tdptr->m_stripoffsets = tfptr->m_offset;
      break;

    case TAG_SamplesPerPixel:
      tdptr->m_samplesperpixel = tfptr->m_offset;
      break;

    case TAG_StripByteCounts:
      tdptr->m_stripbytecounts = tfptr->m_offset;
      break;

    case TAG_PlanarConfiguration:
      tdptr->m_planarconfiguration = tfptr->m_offset;
      break;
  
    case TAG_ResolutionUnit:
      tdptr->m_resolutionunit = tfptr->m_offset;
      break;

    default:
#ifdef DEBUG
      printf( "Unknown tag type %d\n", tfptr->m_tag );
#endif
      break;
    }
  }

// -------------------------------------------------------------------------
// Read the TIFF strip data
// -------------------------------------------------------------------------

void tiff_readstrip( TIFF_DATA *tdptr, FILE *fp )
{
TIFF_LONG nstrips;
TIFF_BYTE *dptr;
int imagemem;
int total = 0;

for ( nstrips = 0; nstrips < tdptr->m_stripsperimage; nstrips++ )
	{
	total += tdptr->m_stripbytecountslist[nstrips];
	}

if ( tdptr->m_stripbytecountslist )
	{
	tdptr->m_stripdata = new TIFF_BYTE[ total ];
   
	dptr = tdptr->m_stripdata;

	for ( nstrips = 0; nstrips < tdptr->m_stripsperimage; nstrips++ )
		{
    		fseek( fp, tdptr->m_stripoffsetslist[nstrips], SEEK_SET );

    		fread( dptr, 1, tdptr->m_stripbytecountslist[nstrips], fp );
    
    		dptr += tdptr->m_stripbytecountslist[nstrips];
    		}
	}
else
	{
	fseek( fp, tdptr->m_stripoffsets, SEEK_SET );

	imagemem = tdptr->m_width * tdptr->m_length
		* tdptr->m_samplesperpixel * tdptr->m_bitspersample / 8;
	  
	tdptr->m_stripdata = new TIFF_BYTE[ tdptr->m_width * tdptr->m_length ];

	fread( tdptr->m_stripdata, 1, imagemem, fp );
	}
}

// -------------------------------------------------------------------------
// Read the TIFF bits per sample data
// -------------------------------------------------------------------------
 
void tiff_bitspersample_read( TIFF_DATA *tdptr, FILE *fp, 
                                                   ULONG (*rsp)(FILE *fp) )
  {
  fseek( fp, tdptr->m_bitspersample, SEEK_SET );

  tdptr->m_redsample   = (*rsp)( fp );
  tdptr->m_greensample = (*rsp)( fp );
  tdptr->m_bluesample  = (*rsp)( fp );
  tdptr->m_alphasample = (*rsp)( fp );
  }

// -------------------------------------------------------------------------
// Convert the TIFF strip data to a pixelmap
//
// Note: 24-bit pixels are 3 bytes in width
//       Odd width pixelmaps will have padding bytes
// -------------------------------------------------------------------------
 
void tiff_strip_convert( TIFF_DATA *tdptr, CTexture *pix )
  {
  col3b *pdst3b;
  col4b *pdst4b;
  short *psdst;
  TIFF_BYTE  *psrc, lobyte, hibyte;
  TIFF_LONG   nx, ny;

  int   bpp, bps;

  pdst3b = (col3b *) pix->m_pdata;
  pdst4b = (col4b *) pix->m_pdata;

  psrc = tdptr->m_stripdata;

  bpp = tdptr->m_samplesperpixel;
  bps = tdptr->m_bitspersample;

  if ( bpp == 4 )
    for ( ny = 0; ny < tdptr->m_length; ny++ )
      for ( nx = 0; nx < tdptr->m_width; nx++, pdst4b++, psrc+=4) 
        {
        pdst4b->m_red   = psrc[0];
        pdst4b->m_green = psrc[1];
        pdst4b->m_blue  = psrc[2]; 
        pdst4b->m_alpha = psrc[3];
        }

  if ( bpp == 3) 
  for ( ny = 0; ny < tdptr->m_length; ny++ )
    for ( nx = 0; nx < tdptr->m_width; nx++, pdst3b++, psrc+=3) 
      {
      pdst3b->m_red   = psrc[0];
      pdst3b->m_green = psrc[1];
      pdst3b->m_blue  = psrc[2]; 
//      pdst->m_alpha = psrc[3];
      }

  if ( ( bpp==1) && (bps==16) )
	{
	psdst = (short *) pdst4b;

	for ( ny = 0; ny < tdptr->m_length; ny++ )
		for ( nx = 0; nx < tdptr->m_width; nx++, psdst++ )
			{
			lobyte = *psrc++;
			hibyte = *psrc++;

			*psdst = lobyte + (hibyte<<8);
			}
	}
  }

// -------------------------------------------------------------------------
// Read the offsets to each strip
// -------------------------------------------------------------------------

void tiff_stripoffsets_read( TIFF_DATA *tdptr, FILE *fp, ULONG (*rsp)(FILE *fp) )
  {
  TIFF_LONG nstrips;

  tdptr->m_stripoffsetslist = new TIFF_LONG[ tdptr->m_stripsperimage ];
 
  if ( tdptr->m_stripsperimage == 1 )
    tdptr->m_stripoffsetslist[0] = tdptr->m_stripoffsets;
  else 
    {
    fseek( fp, tdptr->m_stripoffsets, SEEK_SET );

    for ( nstrips = 0; nstrips < tdptr->m_stripsperimage; nstrips++ ) 
      tdptr->m_stripoffsetslist[nstrips] = (*rsp)( fp );
    }
  }

// -------------------------------------------------------------------------
// Read the byte counts of each strip
// -------------------------------------------------------------------------
 
void tiff_stripbytecounts_read( TIFF_DATA *tdptr, FILE *fp, ULONG (*rsp)(FILE *fp) )
  {
  TIFF_LONG nstrips;

  tdptr->m_stripbytecountslist = new TIFF_LONG[tdptr->m_stripsperimage];
  
  if ( tdptr->m_stripsperimage == 1 )
    tdptr->m_stripbytecountslist[0] = tdptr->m_stripbytecounts;
  else 
    {
    fseek( fp, tdptr->m_stripbytecounts, SEEK_SET );

    for ( nstrips = 0; nstrips < tdptr->m_stripsperimage; nstrips++ ) 
      tdptr->m_stripbytecountslist[nstrips] = (*rsp)( fp );
    }
  }

// -------------------------------------------------------------------------
// Read a TIFF file
// -------------------------------------------------------------------------
 
int CTexture::TextureReadtiff(const char * name )
{
TIFF_HEADER tiff_header;
TIFF_FIELD  tiff_field;
TIFF_DATA   tiff_pdata;
TIFF_LONG   n, nfields, len;
FILE       *fp;
ULONG (*trbyte)( FILE *fp), (*trshort)(FILE *fp), (*trlong)( FILE *fp);
   
memset( (void *) &tiff_pdata, 0, sizeof(TIFF_DATA) );

fp = fopen( name, "rb" );

if ( !fp )
    {
    printf( "Error: tiff_read could not open file <%s>\n", name );
    return( 0 );
    }

tiff_header.m_order = readshortmsb( fp );

if ( tiff_header.m_order != T_ORDER_MSB && 
	tiff_header.m_order != T_ORDER_LSB)
	{
	printf( "Error: %s is not a TIFF file", name );
	fclose(fp);
	return( 0 );
	}

#ifdef DEBUG 
printf( "TIFF Header Order = %04X\n", tiff_header.m_order );
#endif

if ( tiff_header.m_order == T_ORDER_MSB )
	{
	trbyte  = readbytemsb;
	trshort = readshortmsb;
	trlong  = readlongmsb;

#ifdef DEBUG
printf( "TIFF Header = MSB\n" );
#endif
	}
else 
if ( tiff_header.m_order == T_ORDER_LSB )
	{
	trbyte  = readbytelsb;
	trshort = readshortlsb;
	trlong  = readlonglsb;

#ifdef DEBUG
printf( "TIFF Header = LSB\n" );
#endif
	}
else
	return(0);

tiff_header.m_version  =(*trshort)( fp );
tiff_header.m_imagedir = (*trlong)(  fp );

#ifdef DEBUG
printf( "TIFF Header Version  = %04X\n", m_header.m_version );
printf( "TIFF Header Imagedir = %08X\n", m_header.m_imagedir );
#endif

if ( tiff_header.m_order == T_ORDER_MSB || 
	tiff_header.m_order == T_ORDER_LSB )
	{
	fseek( fp, tiff_header.m_imagedir, SEEK_SET );

	nfields = (*trshort)( fp );

#ifdef DEBUG
printf( "TIFF Fields Number = %d\n", nfields );
#endif

	for ( n = 0; n < nfields; n++ )
		{ 
    	tiff_field.m_tag    = (*trshort)( fp );
      	tiff_field.m_field  = (*trshort)( fp );
      	tiff_field.m_count  = (*trlong)(  fp );
 
		switch( tiff_field.m_field ) 
       			{
       			case 1: 
       				len = tiff_field.m_count; 
       				break;

				case 3: 
       				len = tiff_field.m_count * 2; 
       				break;

       			case 4: 
       				len = tiff_field.m_count * 4; 
       				break;

       			default: 
       				len = tiff_field.m_count;
       				break;
       			}

		if ( len == 1 )
				{
        		tiff_field.m_offset = (*trbyte)( fp );
        		(*trbyte)(fp);
        		(*trbyte)(fp);
        		(*trbyte)(fp);
        		}

		if ( len == 2 )
        		{
        		tiff_field.m_offset = (*trshort)( fp );
        		(*trshort)(fp);
        		}

		if ( len >= 3 )
       			tiff_field.m_offset = (*trlong)( fp );

#ifdef DEBUG    
printf( "TIFF Field = " );
printf( "Tag %02X (%4d), Field %02X (%4d), Count %02X (%4d), Value (%08X)\n",
  tiff_field.m_tag, m_field.m_tag, 
  tiff_field.m_field, m_field.m_field,
  tiff_field.m_count, m_field.m_count,
  tiff_field.m_offset );
#endif

		tiff_field_handle( &tiff_field, &tiff_pdata );
      	}	

	if ( tiff_pdata.m_rowsperstrip >= 1 )
		tiff_pdata.m_stripsperimage = (TIFF_LONG)
         floor( (double) (tiff_pdata.m_length + tiff_pdata.m_rowsperstrip-1) 
                / tiff_pdata.m_rowsperstrip );
	else
		tiff_pdata.m_stripsperimage = 1;

#ifdef DEBUG
printf( "TIFF RowsPerStrip = %d\n", m_pdata.m_stripsperimage );
#endif

	if ( tiff_pdata.m_samplesperpixel >= 3 )
		{
   		tiff_bitspersample_read( &tiff_pdata, fp, trshort );

#ifdef DEBUG
printf( "TIFF BitsPerSample = %d %d %d\n",
   tiff_pdata.m_redsample, tiff_pdata.m_greensample, tiff_pdata.m_bluesample );
#endif
		}

	if ( tiff_pdata.m_samplesperpixel >= 3 )
		{
#ifdef DEBUG
		printf( "Reading strip byte counts\n" );
#endif
		if ( tiff_pdata.m_stripsperimage )
			{
    			tiff_stripbytecounts_read( &tiff_pdata, fp, trlong );
    			tiff_stripoffsets_read(    &tiff_pdata, fp, trlong );
			}
		}

	tiff_readstrip( &tiff_pdata, fp );

	if ( tiff_pdata.m_samplesperpixel == 3 )
		Allocate( tiff_pdata.m_width, tiff_pdata.m_length, TEX_RGB );
	else    
		if ( tiff_pdata.m_samplesperpixel == 4 )
			Allocate( tiff_pdata.m_width, tiff_pdata.m_length, TEX_RGBA );
    		else
			if ( tiff_pdata.m_samplesperpixel == 1 )
				{
				if ( tiff_pdata.m_bitspersample == 16 )
					{
					Allocate( tiff_pdata.m_width,
						tiff_pdata.m_length, TEX_MONO16 );
					}

	   			if ( tiff_pdata.m_bitspersample == 8 )
	   				{
					Allocate( tiff_pdata.m_width,
						tiff_pdata.m_length, TEX_MONO );
					}
	   			}

	tiff_strip_convert( &tiff_pdata, this );

	if ( tiff_pdata.m_stripoffsetslist )
		delete [] tiff_pdata.m_stripoffsetslist;

	if ( tiff_pdata.m_stripbytecountslist )
		delete [] tiff_pdata.m_stripbytecountslist;

	if ( tiff_pdata.m_stripdata )
		delete [] tiff_pdata.m_stripdata;
   	}

fclose( fp );

return( 1 );
}

// =========================================================================
// WRITE TIFF FILES
// =========================================================================
 
// -------------------------------------------------------------------------
// Write out the pixelmap data as a TIFF field block
// -------------------------------------------------------------------------
 

static TIFF_FIELD tiff_fieldlist[] =
  {
    { TAG_Width,               3, 1, 0x0000 },  // Value:  Width 
    { TAG_Length,              3, 1, 0x0000 },  // Value:  Length 
    { TAG_BitsPerSample,       3, 3, 0x0000 },  // Offset: Bits per Comp. 
    { TAG_Compression,         3, 1, 0x01 },    // Value:  Compression 
    { TAG_PhotoMetricInterpretation, 3, 1, 0x02 }, // Value: Format 
    { TAG_StripOffsets,        4, 1, 0x0008 },  // Offset: Strip Offsets 
    { TAG_SamplesPerPixel,     3, 1, 0x03 },    // Value:  Pixel size 
    { TAG_StripByteCounts,     4, 1, 0x0000 },  // Offset: Strip Lengths 
    { TAG_PlanarConfiguration, 3, 1, 0x01 }     // Value:  Format 
  };

#define NUM_FIELDS (sizeof(tiff_fieldlist) / sizeof(TIFF_FIELD) )

void tiff_initfields( TIFF_FIELD *tfptr, CTexture &tex )
  {
  TIFF_LONG totalbytes;

  memcpy( tfptr, tiff_fieldlist, sizeof(tiff_fieldlist) );

  tfptr[0].m_offset = tex.m_width;
  tfptr[1].m_offset = tex.m_height;

  totalbytes = tex.m_width * tex.m_height * 3;

  tfptr[7].m_offset = totalbytes;  // Ignore padding 

  if ( totalbytes & 0x01 )         // Add padding bytes 
    totalbytes++;

  tfptr[2].m_offset = 122 + totalbytes;   // Offset to bits-per-sample 
  }

// -------------------------------------------------------------------------
// Write a pixelmap as a TIFF file
// -------------------------------------------------------------------------
 
void tiff_fieldw( TIFF_LONG tag, TIFF_LONG type, TIFF_LONG num,
                     TIFF_LONG val, FILE *fp,
              void (*twlp)(FILE *fp, ULONG value),
              void (*twsp)(FILE *fp, ULONG value), 
              void (*twbp)(FILE *fp, ULONG value) )
  {
  TIFF_LONG len;

  (*twsp)( fp, tag );
  (*twsp)( fp, type );
  (*twlp)( fp, num );
  
  switch( type )
    {
    case 1: 
      len = num; 
      break;

    case 3: 
      len = num * 2;
      break;

    case 4: 
      len = num * 4;
      break;

    default:
      len = 4;
      break;
    }

  if ( len >= 4 )
    (*twlp)( fp, val );

  if ( len == 3 )
    (*twlp)( fp, val );

  if ( len == 2 )
    {
    (*twsp)( fp, val );
    (*twsp)( fp, 0 );
    }

  if ( len == 1 )
    {
    (*twbp)( fp, val );
    (*twbp)( fp, 0 );
    (*twbp)( fp, 0 );
    (*twbp)( fp, 0 );
    }
  }

// -------------------------------------------------------------------------
// Write out the pixelmap data as a TIFF strip
// -------------------------------------------------------------------------
 
void tiff_writestrip( CTexture &tex, FILE *fp )
  {
  int doalpha = ( tex.m_type & TEX_ALPHA ) != 0;

  TIFF_LONG total = tex.m_width * tex.m_height * (3+doalpha);

  TEXBYTE *psrc = tex.m_pdata;
  
  if ( doalpha )
    for (int py = 0; py < tex.m_height; py++ )
      for (int px = 0; px < tex.m_width; px++ )
        {
        TIFF_LONG pr = *psrc++;
        TIFF_LONG pg = *psrc++; 
        TIFF_LONG pb = *psrc++;
        TIFF_LONG pa = *psrc++;

        writebytemsb( fp, pr );
        writebytemsb( fp, pg );
        writebytemsb( fp, pb ); 
        writebytemsb( fp, pa );
        }
  else
    for (int py = 0; py < tex.m_height; py++ )
      for (int px = 0; px < tex.m_width; px++ )
        {
        TIFF_LONG pr = *psrc++;
        TIFF_LONG pg = *psrc++; 
        TIFF_LONG pb = *psrc++;
       
        psrc += doalpha;

        writebytemsb( fp, pr );
        writebytemsb( fp, pg );
        writebytemsb( fp, pb );
        }
 
  while( total % 4 )
    {
    total++;
    writebytemsb( fp, 0 );
    }
  }

// -------------------------------------------------------------------------
// Write a pixelmap as a TIFF file
// -------------------------------------------------------------------------
 
int CTexture::TextureWritetiff( const char * name )
{
FILE *fp;
TIFF_LONG nstrips, mode, nfields, bpp;
void  (*twbp)(FILE *fp, ULONG val);
void  (*twsp)(FILE *fp, ULONG val);
void  (*twlp)(FILE *fp, ULONG val);
TIFF_LONG offset_fields, offset_bps, offset_so, offset_sbc, offset_pix;
TIFF_LONG nrows, sn, stripoffn, stripoffd, striparea, striparead;
TIFF_LONG pixarea, offset_xres, offset_yres;

nstrips = 1;
mode    = T_ORDER_LSB;
nfields = 16;
 
bpp = 0;
 
if ( m_type == TEX_RGBA) 
    bpp = 4;
else
    if ( m_type == TEX_RGB )
      bpp = 3;
 
if ( !(fp = fopen( name, "wb" ) ) )// ----- Sanity check ------------------- 
    return(0);

if ( mode == T_ORDER_LSB )	 // ----- Select MSB/LSB mode ----------- 
    {
    twbp = writebytelsb;
    twsp = writeshortlsb;
    twlp = writelonglsb;
    }

if ( mode == T_ORDER_MSB )
    {
    twbp = writebytelsb;
    twsp = writeshortlsb;
    twlp = writelonglsb;
    }

pixarea = m_width * m_height * bpp;	 // ----- Calculate offsets ------------- 

while ( pixarea % 4 )
    pixarea++;

offset_fields = 8; 
offset_pix    = offset_fields + nfields * 12 + 6;
offset_bps    = offset_pix    + pixarea;
offset_xres   = offset_bps    + 8;
offset_yres   = offset_xres   + 8;

if ( nstrips > 1 )   
	{
	offset_so   = offset_yres    + 8;  
	offset_sbc  = offset_so      + nstrips * 4;
	nrows       = (m_height + (nstrips-1)) / nstrips;
	}
else
	{
	offset_so   = offset_pix;
	offset_sbc  = m_width * m_height * bpp;
	nrows       = m_height;
	}

writeshortmsb( fp, mode );	 // ----- Write header information ------ 

(*twsp)( fp, T_VERSION );
(*twlp)( fp,  offset_fields );

(*twsp)( fp, nfields );		// ----- Write field data ---------------

tiff_fieldw( TAG_NewSubFileType,   4, 1, 0x0,           fp, twlp, twsp, twbp);
tiff_fieldw( TAG_Width,            3, 1, m_width,  fp, twlp, twsp, twbp);
tiff_fieldw( TAG_Length,           3, 1, m_height, fp, twlp, twsp, twbp);
tiff_fieldw( TAG_BitsPerSample,    3, 3, offset_bps,    fp, twlp, twsp, twbp);
tiff_fieldw( TAG_Compression,      3, 1, 0x01,          fp, twlp, twsp, twbp);
tiff_fieldw( TAG_PhotoMetricInterpretation, 3, 1, 0x02, fp, twlp, twsp, twbp);
tiff_fieldw( TAG_FillOrder,        3, 1, 0x01,       fp, twlp, twsp, twbp);
tiff_fieldw( TAG_StripOffsets,     4, nstrips,offset_so,  fp, twlp, twsp, twbp);
tiff_fieldw( TAG_Orientation,      3, 1, 0x01,       fp, twlp, twsp, twbp);
tiff_fieldw( TAG_SamplesPerPixel,  3, 1, bpp,        fp, twlp, twsp, twbp);
tiff_fieldw( TAG_RowsPerStrip,     3, 1, nrows,      fp, twlp, twsp, twbp);
tiff_fieldw( TAG_StripByteCounts,  4, nstrips, offset_sbc, fp, twlp, twsp, twbp);
tiff_fieldw( TAG_XResolution,      5, 1, offset_xres,fp, twlp, twsp, twbp);
tiff_fieldw( TAG_YResolution,      5, 1, offset_yres,fp, twlp, twsp, twbp);
tiff_fieldw( TAG_PlanarConfiguration, 3, 1, 0x01,    fp, twlp, twsp, twbp);
tiff_fieldw( TAG_ResolutionUnit,   3, 1, 0x02,       fp, twlp, twsp, twbp);

(*twlp)( fp, 0x0000 ); 

tiff_writestrip( *this, fp );	// ----- Write pixelmap data 

(*twsp)( fp, 8L );		// ----- Write bits per sample data
(*twsp)( fp, 8L );
(*twsp)( fp, 8L );

if ( bpp == 3 )
	(*twsp)( fp, 0x000 );
else
	(*twsp)( fp, 0x008 );

(*twlp)( fp, m_width );		 // ----- Write X resolution ------------ 
(*twlp)( fp, 0x01 );

(*twlp)( fp, m_height );	 // ----- Write Y resolution ------------ 
(*twlp)( fp, 0x01 );

if ( nstrips > 1 )		 // ----- Write strip offsets -----------
	{
	stripoffn = offset_pix;
	stripoffd = nrows * m_width * bpp;

	for ( sn = 0; sn < nstrips; sn++, stripoffn += stripoffd )
		(*twlp)( fp, stripoffn );
	}

if ( nstrips > 1 )		 // ----- Write strip bytes counts ------
	{
	striparea  = m_width * m_height * bpp;
	striparead = m_width * bpp * nrows;

	for ( sn = 0; sn < nstrips; sn++, striparea -= striparead )
		if ( striparea > striparead )
			(*twlp)( fp, striparead );
		else
			(*twlp)( fp, striparea );
    	}

fclose( fp );			// ----- And we're all done ------------

return(1);
}
