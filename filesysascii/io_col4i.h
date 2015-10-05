// --------------------------------------------------------------------------
// File:   io_color4i.h
//
// Purpose: Routines to handle byteenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_COLOR4I_H_
#define _IO_COLOR4I_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemColor4i : virtual public CFileSystemPar
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

void ReadColor4i( ifstream &ifs, col4i &color );

// ----- Write routines -----------------------------------------------------

// ----- Plane data -------------------------------------------------------

void WriteColor4i( ostream &stream );

void WriteNamedColor4i( ostream &stream, int depth, const char *name,
                                                         col4i &color );

void WriteNamedColor4i( ostream &stream, int depth, string &strname,
                                                        col4i &color );

};

#endif	// _IO_COLOR4I_H_
