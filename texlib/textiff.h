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
// -----------------------------------------------------------------------
// Header file for use with the texture TIFF file read and write routines
//
// Author: Michael S. A. Robb
//
// Date:   10th October 2003
// -----------------------------------------------------------------------

typedef unsigned char TIFF_BYTE;
typedef unsigned int  TIFF_SHORT;
typedef signed long TIFF_LONG;

// -----------------------------------------------------------------------
// TIFF TAGS  
// -----------------------------------------------------------------------
 
#define T_VERSION   42

#define TAG_NewSubFileType            254     // MS Paint - long 
#define TAG_Width                     256     // OK Basic 
#define TAG_Length                    257     // OK Basic 
#define TAG_BitsPerSample             258     // OK Basic 
#define TAG_Compression               259     // OK Basic 
#define TAG_PhotoMetricInterpretation 262     // OK Basic 
#define TAG_StripOffsets              273     // OK Basic 
#define TAG_SamplesPerPixel           277     // OK Basic 
#define TAG_RowsPerStrip              278     // OK Basic 
#define TAG_StripByteCounts           279     // OK Basic 
#define TAG_XResolution               282     // MS Paint - rational 
#define TAG_YResolution               283     // MS Paint - rational 
#define TAG_PlanarConfiguration       284     // OK Basic 
#define TAG_ResolutionUnit            296     // MS Paint - short 

#define TAG_SubFileType               255     // OK 
#define TAG_Thresholding              263     // OK 
#define TAG_CellWidth                 264     // OK 
#define TAG_CellLength                265     // OK 
#define TAG_FillOrder                 266     // OK 

#define TAG_DocumentName              269
#define TAG_ImageDescription          270
#define TAG_Make                      271
#define TAG_Model                     272
#define TAG_Orientation               274     // MS Paint - short 
#define TAG_MinSampleValue            280
#define TAG_MaxSampleValue            281
#define TAG_PageName                  285
#define TAG_XPosition                 286
#define TAG_YPosition                 287
#define TAG_FreeOffsets               288
#define TAG_FreeByteCounts            289
#define TAG_GrayResponseUnit          290
#define TAG_GrayResponseCurve         291
#define TAG_Group3Options             292
#define TAG_Group4Options             293

#define TAG_PageNumber                297
#define TAG_ColorResponseUnit         300
#define TAG_ColorResponseCurves       301
#define TAG_Software                  305     // MS Paint - Ascii 

#define TAG_Mystery                  32394    // MS Paint - ???? 

// -------------------------------------------------------------------------
// TIFF DATA FILE
// -------------------------------------------------------------------------
 
typedef struct tiff_data_st
  {
  TIFF_LONG  m_width;                // The Basics 
  TIFF_LONG  m_length;
  TIFF_LONG  m_bitspersample;
  TIFF_LONG  m_compression;
  TIFF_LONG  m_photometricinterp;
  TIFF_LONG  m_stripoffsets;
  TIFF_LONG  m_samplesperpixel;
  TIFF_LONG  m_stripbytecounts;
  TIFF_LONG  m_planarconfiguration; 

  TIFF_LONG  m_subfiletype;          // Other fields 
  TIFF_LONG  m_fillorder;
  TIFF_LONG  m_thresholding;
  TIFF_LONG  m_cellwidth;
  TIFF_LONG  m_celllength;

  TIFF_SHORT m_redsample;
  TIFF_SHORT m_bluesample;
  TIFF_SHORT m_greensample;
  TIFF_SHORT m_alphasample;
  TIFF_SHORT m_orientation;
  TIFF_LONG  m_rowsperstrip;
  TIFF_SHORT m_resolutionunit;
  TIFF_LONG  m_newsubfiletype;
  TIFF_LONG  m_xresolution;
  TIFF_LONG  m_yresolution;
  TIFF_LONG *m_stripoffsetslist;
  TIFF_LONG *m_stripbytecountslist;

  TIFF_BYTE *m_stripdata;            // Pixel data 

  TIFF_LONG  m_stripsperimage;
  } TIFF_DATA;

// -------------------------------------------------------------------------
// TIFF HEADER
// -------------------------------------------------------------------------
 
typedef struct tiff_st
  {
  TIFF_SHORT m_order;       // Either II (LSB->MSB) or MM (MSB->LSB) 
  TIFF_SHORT m_version;     // Version 0x2A 
  TIFF_LONG  m_imagedir;    // Image directory offset 
  } TIFF_HEADER;

#define T_ORDER_MSB  0x4D4D   // 'MM' - MSB->LSB 
#define T_ORDER_LSB  0x4949   // 'II' - LSB->MSB 

// -------------------------------------------------------------------------
// TIFF FIELD ENTRY
// -------------------------------------------------------------------------
 

typedef struct tiff_imagedir_st
  {
  TIFF_SHORT m_tag;    // 2 bytes 
  TIFF_SHORT m_field;  // 2 
  TIFF_LONG  m_count;  // 4 
  TIFF_LONG  m_offset; // 4 
  } TIFF_FIELD;

