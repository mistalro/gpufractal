// --------------------------------------------------------------------------
// File:   io_color3i.h
//
// Purpose: Routines to handle RGB integer colors
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_COLOR3I_H_
#define _IO_COLOR3I_H_

// --------------------------------------------------------------------------
// File system for byte management
// --------------------------------------------------------------------------

class CFileSystemColor3i : virtual public CFileSystemPar
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

void ReadColor3i( ifstream &ifs, col3i &color );

// ----- Write routines -----------------------------------------------------

// ----- Color data -------------------------------------------------------

void WriteColor3i( ostream &stream );

void WriteNamedColor3i( ostream &stream, int depth, const char *name,
                                                         col3i &color );

void WriteNamedColor3i( ostream &stream, int depth, string &strname,
                                                        col3i &color );

};

#endif	// _IO_COLOR3I_H_
