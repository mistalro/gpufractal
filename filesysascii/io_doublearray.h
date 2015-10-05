// --------------------------------------------------------------------------
// File:   io_double.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_DOUBLEARRAY_H_
#define _IO_DOUBLEARRAY_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemDoubleArray : virtual public CFileSystemPar,
				virtual public CFileSystemString
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

// ----- Double arrays -------------------------------------------------------

int ReadDoubleArray1D( ifstream &stream,
                int ncols, double *pdata );

int ReadDoubleArray2D( ifstream &stream,
                int ncols, int nrows, double *pdata );

int ReadDoubleArray3D( ifstream &stream,
                int ncols, int nrows, int ndep, double *pdata );

// ----- Write routines -----------------------------------------------------

int WriteDoubleArray1D( ostream &stream, int icols, double *pdata );

int WriteNamedDoubleArray1D( ostream &stream, int depth,
        const char *pstr, int ncols, double *pdata );

int WriteDoubleArray2D( ostream &stream, int ncols, int nrows, double *pdata );

int WriteNamedDoubleArray2D( ostream &stream, int depth,
        const char *pstr, int ncols, int nrows, double *pdata );

int WriteDoubleArray3D( ostream &stream, int ncols, int nrows, int ndep, double *pdata );

int WriteNamedDoubleArray3D( ostream &stream, int depth,
        const char *pstr, int ncols, int nrows, int ndep, double *pdata );
};

#endif	// _IO_DOUBLEARRAY_H_
