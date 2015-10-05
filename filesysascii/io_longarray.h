// --------------------------------------------------------------------------
// File:   io_longarray.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_LONGARRAY_H_
#define _IO_LONGARRAY_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemLongArray : virtual public CFileSystemPar,
				virtual public CFileSystemString
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

int ReadLongArray1D( ifstream &stream,
                int ncols, long *pdata );

int ReadLongArray2D( ifstream &stream,
                int ncols, int nrows, long *pdata );

int ReadLongArray3D( ifstream &stream,
                int ncols, int nrows, int ndep, long *pdata );

// ----- Write routines -----------------------------------------------------

int WriteLongArray1D( ostream &stream, int ncols, long *pdata );

int WriteNamedLongArray1D( ostream &stream, int depth,
        const char *pstr, int ncols, long *pdata );

int WriteLongArray2D( ostream &stream, int ncols, int nrows, long *pdata );

int WriteNamedLongArray2D( ostream &stream, int depth,
        const char *pstr, int ncols, int rows, long *pdata );

int WriteLongArray3D( ostream &stream, int ncols, int nrows, int ndep, long *pdata );

int WriteNamedLongArray3D( ostream &stream, int depth,
        const char *pstr, int ncols, int rows, int ndep, long *pdata );

};

#endif	// _IO_LONGARRAY_H_
