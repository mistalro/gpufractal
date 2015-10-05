// --------------------------------------------------------------------------
// File:    io_shortarray.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_SHORTARRAY_H_
#define _IO_SHORTARRAY_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemShortArray : virtual public CFileSystemPar
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

int ReadShortArray1D( ifstream &stream,
                int ncols, short *pdata );

int ReadShortArray2D( ifstream &stream,
                int ncols, int nrows, short *pdata );

int ReadShortArray3D( ifstream &stream,
                int ncols, int nrows, int ndep, short *pdata );

// ----- Write routines -----------------------------------------------------

int WriteShortArray1D( ostream &stream, int ncols, short *pdata );

int WriteNamedShortArray1D( ostream &stream, int depth,
        const char *pstr, int ncols, short *pdata );

int WriteShortArray2D( ostream &stream, int ncols, int nrows, short *pdata );

int WriteNamedShortArray2D( ostream &stream, int depth,
        const char *pstr, int ncols, int rows, short *pdata );

int WriteShortArray3D( ostream &stream, int ncols, int nrows, int ndep, short *pdata );

int WriteNamedShortArray3D( ostream &stream, int depth,
        const char *pstr, int ncols, int rows, int ndep, short *pdata );
};

#endif	// _IO_SHORTARRAY_H_
