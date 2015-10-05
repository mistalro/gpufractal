// --------------------------------------------------------------------------
// File:   io_par.cpp
//
// Purpose: Routines to handle parenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// --------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "filesysascii.h"

// --------------------------------------------------------------------------
// Keep reading characters until an open parenthesis or EOF is read
// --------------------------------------------------------------------------

int CFileSystemPar::ReadOpenPar( ifstream &stream )
{
int ch;

while ( !stream.eof() && ( (ch = stream.get() ) != '{' ) );

return ( ch == '{' );
}

// --------------------------------------------------------------------------
// Keep reading characters until an close parenthesis or EOF is read
// --------------------------------------------------------------------------

int CFileSystemPar::ReadClosePar( ifstream &stream )
{
int ch;

while ( !stream.eof() && (( ch = stream.get() ) != '}' ) );

return( ch == '}');
}

// --------------------------------------------------------------------------
// Keep reading characters until an open parenthesis or EOF is read
// --------------------------------------------------------------------------

int CFileSystemPar::ReadOpenClosePar( ifstream &stream )
{
int ch = 0;

while ( !stream.eof() && ((ch = stream.get() ) != '}' ) && (ch != '{' ) );

return( ch == '{' );
}

// --------------------------------------------------------------------------
// Write Open parenthesis
// --------------------------------------------------------------------------

int CFileSystemPar::WriteOpenParBasic( ostream &stream,
                                        int depth, const char *name )
{
stream << "{" << name << " ";

return depth;
}

int CFileSystemPar::WriteOpenPar( ostream &stream, 
					int &depth, const char *name )
{
int result = WriteTabbedDepth( stream, depth );

stream << "{" << name << "\n";
depth++;

return result;
}

int CFileSystemPar::WriteOpenPar( ostream &stream, 
					int &depth, string &str )
{
int result = WriteTabbedDepth( stream, depth );

stream << "{" << str.c_str() << "\n";
depth++;

return result;
}

// --------------------------------------------------------------------------
// Write close parenthesis
// --------------------------------------------------------------------------

int CFileSystemPar::WriteCloseParBasic( ostream &stream, int depth )
{
stream << "}";

return depth;
}

int CFileSystemPar::WriteClosePar( ostream &stream, int &depth )
{
int result = true;

depth--;
result = WriteTabbedDepth( stream, depth );
stream << "}\n";

return result;
}

// --------------------------------------------------------------------------
// Write tabbed depth
// --------------------------------------------------------------------------

int CFileSystemPar::WriteTabbedDepth( ostream &stream, int depth )
{
int result = true;

while ( depth--)
        stream << "\t";

return result ;
}
