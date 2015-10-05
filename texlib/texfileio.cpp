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
// Utility functions used to read and write 8-bit, 16-bit and 32-bit data
// values in either LSB or MSB format
// 
// Author: Michael S. A. Robb
//
// Date:   20th August 2002
// --------------------------------------------------------------------------
 
#include "texturelib.h"

// --------------------------------------------------------------------------
// Read a single 8-bit value MSB
//
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: The 8-bit value read in
//
// Effects: None
// --------------------------------------------------------------------------

ULONG readbytemsb( FILE *fp )
  {
  return( fgetc( fp ) );
  }

// --------------------------------------------------------------------------
// Read a single 16-bit value MSB
//
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: The 16-bit value read in
//
// Effects: None
// --------------------------------------------------------------------------
 
ULONG readshortmsb( FILE *fp )
  {
  ULONG byte0, byte1;

  byte0 = fgetc( fp );
  byte1 = fgetc( fp );

  return( (byte0<<8) + byte1 );
  }

// --------------------------------------------------------------------------
// Read a single 32-bit value MSB
//
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: 32-bit value containing the value read in
// --------------------------------------------------------------------------
 
ULONG readlongmsb( FILE *fp )
  {
  ULONG byte0, byte1, byte2, byte3;

  byte0 = fgetc( fp );
  byte1 = fgetc( fp );
  byte2 = fgetc( fp );
  byte3 = fgetc( fp );

  return( (byte0<<24) + (byte1<<16) + (byte2<<8) + byte3 );
  }

// --------------------------------------------------------------------------
// Read a single 8-bit value LSB
//
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: The 8-bit value read in
//
// Effects: None
// --------------------------------------------------------------------------

ULONG readbytelsb( FILE *fp )
  {
  return( fgetc( fp ) );
  }

// --------------------------------------------------------------------------
// Read a single 16-bit value LSB
//
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: The 16-bit value read in
//
// Effects: None
// --------------------------------------------------------------------------

ULONG readshortlsb( FILE *fp )
  {
  ULONG byte0, byte1;

  byte0 = fgetc( fp );
  byte1 = fgetc( fp );

  return( (byte1<<8) + byte0 );
  }

// --------------------------------------------------------------------------
// Read a single 32-bit value LSB
//
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: 32-bit value containing the value read in
//
// Effects: None
// --------------------------------------------------------------------------
 
ULONG readlonglsb( FILE *fp )
  {
  ULONG byte0, byte1, byte2, byte3; 
  
  byte0 = fgetc( fp );
  byte1 = fgetc( fp );
  byte2 = fgetc( fp );
  byte3 = fgetc( fp );

  return( (byte3<<24) + (byte2<<16) + (byte1<<8) + byte0 );
  }

// --------------------------------------------------------------------------
// Write a single 8-bit value MSB
// 
// Inputs:  fp   - File pointer
//			uval - 32-bit value
//
// Outputs: None
//
// Results: None
//
// Effects: A byte value is written onto the file
// --------------------------------------------------------------------------

void writebytemsb( FILE *fp, ULONG val )
  {
  fputc( val & 0xFF, fp );
  }

// --------------------------------------------------------------------------
// Write a single 16-bit value MSB
//
// Inputs: fp   - File pointer
//         uval - 32-bit value
//
//
// Outputs: None
//
// Results: None
//
// Effects: Two byte values are written out
// --------------------------------------------------------------------------

void writeshortmsb( FILE *fp, ULONG val )
  {
  ULONG byte0, byte1;

  byte0 = ( val & 0xFF00 ) >> 8;
  byte1 = ( val & 0x00FF );

  fputc( (TEXBYTE) byte0, fp );
  fputc( (TEXBYTE) byte1, fp );
  }

// --------------------------------------------------------------------------
// Write a single 32-bit value MSB
//
// Inputs: fp   - File pointer
//         uval - 32-bit value
//
// Outputs: None
//
// Results: None
//
// Effects: Four byte values are written out
// --------------------------------------------------------------------------

void writelongmsb( FILE *fp, ULONG val )
  {
  ULONG byte0, byte1, byte2, byte3;

  byte0 = ( val & 0xFF000000 ) >> 24;
  byte1 = ( val & 0x00FF0000 ) >> 16;
  byte2 = ( val & 0x0000FF00 ) >>  8;
  byte3 = ( val & 0x000000FF );

  fputc( byte0, fp );
  fputc( byte1, fp );
  fputc( byte2, fp );
  fputc( byte3, fp );
  }

// --------------------------------------------------------------------------
// Write a single 8-bit value LSB
// 
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: None
//
// Effects: A byte value is written out
// --------------------------------------------------------------------------

void writebytelsb( FILE *fp, ULONG val )
  {
  fputc( val & 0xFF, fp );
  }

// --------------------------------------------------------------------------
// Write a single 16-bit value LSB
//
// Inputs: fp - File pointer
// 
// Outputs: None
//
// Results: None
//
// Effects: Two byte values are written out
// --------------------------------------------------------------------------

void writeshortlsb( FILE *fp, ULONG val )
  {
  ULONG byte0, byte1;

  byte0 = ( val & 0x00FF );
  byte1 = ( val & 0xFF00 ) >> 8;

  fputc( (TEXBYTE) byte0, fp );
  fputc( (TEXBYTE) byte1, fp );
  }

// --------------------------------------------------------------------------
// Write a single-32-bit value LSB
// 
// Inputs: fp - File pointer
//
// Outputs: None
//
// Results: None
//
// Effects: Four byte values are written out
// --------------------------------------------------------------------------

void writelonglsb( FILE *fp, ULONG val )
  {
  ULONG byte0, byte1, byte2, byte3;

  byte0 = ( val & 0x000000FF );
  byte1 = ( val & 0x0000FF00 ) >> 8;
  byte2 = ( val & 0x00FF0000 ) >> 16;
  byte3 = ( val & 0xFF000000 ) >> 24;
  
  fputc( byte0, fp );
  fputc( byte1, fp );
  fputc( byte2, fp );
  fputc( byte3, fp );
  }
