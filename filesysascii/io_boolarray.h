// --------------------------------------------------------------------------
// File:   io_byte.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_BOOLARRAY_H_
#define _IO_BOOLARRAY_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemBooleanArray : virtual public CFileSystemPar,
				virtual public CFileSystemString
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

int ReadBoolArray1D( ifstream &stream,
                int ncols, bool *pdata );

int ReadBoolArray2D( ifstream &stream,
                int ncols, int nrows, bool *pdata );

int ReadBoolArray3D( ifstream &stream,
                int ncols, int nrows, int ndep, bool *pdata );

// ----- Write routines -----------------------------------------------------

// ----- Bool arrays -----------------------------------------------------

int WriteBoolArray1D( ostream &stream, int ncols, bool *pdata );

int WriteNamedBoolArray1D( ostream &stream, int depth,
        const char *pstr, int ncols, bool *pdata );

int WriteBoolArray2D( ostream &stream, int ncols, int nrows, bool *pdata );

int WriteNamedBoolArray2D( ostream &stream, int depth,
        const char *pstr, int ncols, int nrows, bool *pdata );

int WriteBoolArray3D( ostream &stream, int ncols, int nrows, int ndep, bool *pdata );

int WriteNamedBoolArray3D( ostream &stream, int depth,
        const char *pstr, int ncols, int nrows, int ndep, bool *pdata );
};

#endif	// _IO_BOOLARRAY_H_
