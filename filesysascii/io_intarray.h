// --------------------------------------------------------------------------
// File:   io_byte.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_INTEGERARRAY_H_
#define _IO_INTEGERARRAY_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemIntegerArray : virtual public CFileSystemPar,
				virtual public CFileSystemString
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

int ReadIntegerArray1D( ifstream &stream,
                int ncols, int *pdata );

int ReadIntegerArray2D( ifstream &stream,
                int ncols, int nrows, int *pdata );

int ReadIntegerArray3D( ifstream &stream,
                int ncols, int nrows, int ndep, int *pdata );

// ----- Write routines -----------------------------------------------------

// ----- Integer arrays -----------------------------------------------------

int WriteIntegerArray1D( ostream &stream, int ncols, int *pdata );

int WriteNamedIntegerArray1D( ostream &stream, int depth,
        const char *pstr, int ncols, int *pdata );

int WriteIntegerArray2D( ostream &stream, int ncols, int nrows, int *pdata );

int WriteNamedIntegerArray2D( ostream &stream, int depth,
        const char *pstr, int ncols, int nrows, int *pdata );

int WriteIntegerArray3D( ostream &stream, int ncols, int nrows, int ndep, int *pdata );

int WriteNamedIntegerArray3D( ostream &stream, int depth,
        const char *pstr, int ncols, int nrows, int ndep, int *pdata );
};

#endif	// _IO_INTEGERARRAY_H_
