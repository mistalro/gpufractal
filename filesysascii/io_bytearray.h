// --------------------------------------------------------------------------
// File:   io_bytearray.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_BYTEARRAY_H_
#define _IO_BYTEARRAY_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemByteArray : virtual public CFileSystemPar,
				virtual public CFileSystemString
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

int ReadByteArray1D( ifstream &stream,
                int nx, BYTE *pdata );

int ReadByteArray2D( ifstream &stream,
                int nx, int ny, BYTE *pdata );

int ReadByteArray3D( ifstream &stream,
                int nx, int ny, int nz, BYTE *pdata );

// ----- Write routines -----------------------------------------------------

int WriteByteArray1D( ostream &stream, int nx, BYTE *pdata );

int WriteNamedByteArray1D( ostream &stream, int depth,
        const char *pstr, int nx, BYTE *pdata );

int WriteByteArray2D( ostream &stream, int nx, int ny, BYTE *pdata );

int WriteNamedByteArray2D( ostream &stream, int depth,
        const char *pstr, int nx, int ny, BYTE *pdata );

int WriteByteArray3D( ostream &stream, int nx, int ny, int nz, BYTE *pdata );

int WriteNamedByteArray3D( ostream &stream, int depth,
        const char *pstr, int nx, int ny, int nz, BYTE *pdata );

};

#endif	// _IO_BYTEARRAY_H_
