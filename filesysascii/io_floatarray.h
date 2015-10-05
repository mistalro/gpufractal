// --------------------------------------------------------------------------
// File:   io_float.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_FLOATARRAY_H_
#define _IO_FLOATARRAY_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemFloatArray : virtual public CFileSystemPar,
				virtual public CFileSystemString
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

// ----- Float arrays -------------------------------------------------------

int ReadFloatArray1D( ifstream &stream,
                int ncols, float *pdata );

int ReadFloatArray2D( ifstream &stream,
                int ncols, int nrows, float *pdata );

int ReadFloatArray3D( ifstream &stream,
                int ncols, int nrows, int ndep, float *pdata );

// ----- Write routines -----------------------------------------------------

int WriteFloatArray1D( ostream &stream, int ncols, float *pdata );

int WriteNamedFloatArray1D( ostream &stream, int depth,
        const char *pstr, int ncols, float *pdata );

int WriteFloatArray2D( ostream &stream, 
	int ncols, int nrows, float *pdata );

int WriteNamedFloatArray2D( ostream &stream, int depth,
        const char *pstr, int ncols, int nrows, float *pdata );

int WriteFloatArray3D( ostream &stream, 
	int ncols, int nrows, int ndep, float *pdata );

int WriteNamedFloatArray3D( ostream &stream, int depth,
        const char *pstr, int ncols, int rows, int ndep, float *pdata );
};

#endif	// _IO_FLOATARRAY_H_
