// --------------------------------------------------------------------------
// File:   io_par.h
//
// Purpose: Routines to handle parenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#ifndef _IO_PAR_H_
#define _IO_PAR_H_

// --------------------------------------------------------------------------
// File system for parenthesis management
// --------------------------------------------------------------------------

class CFileSystemPar
{
// ----- Class members ------------------------------------------------------
public:

// ----- Read routines ------------------------------------------------------

int ReadOpenPar( ifstream &ifs );
int ReadClosePar( ifstream &ifs );
int ReadOpenClosePar( ifstream &ifs );

// ----- Write routines -----------------------------------------------------

int WriteTabbedDepth( ostream &stream, int depth );

int WriteOpenParBasic( ostream &stream, int depth, const char *name );
int WriteOpenPar( ostream &stream, int &depth, const char *name );
int WriteOpenPar( ostream &stream, int &depth, string &string );
int WriteClosePar( ostream &stream, int &depth );
int WriteCloseParBasic( ostream &stream, int depth );
};

#endif	// _IO_PAR_H_
