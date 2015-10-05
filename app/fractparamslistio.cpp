/* Copyright (C) 2015 Dr. Michael Robb

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General License
   as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Public License for more details.

   You should have received a copy of the GNU Public License 
   along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifdef _WINDOWS_
#include "stdafx.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "fractals.h"

// ---------------------------------------------------------------------------
// Keyword strings
// ---------------------------------------------------------------------------

static const char *str_blockname = "fractallist";

static const char *str_listnum = "listnum";
static const char *str_fractal = "fractal";

// --------------------------------------------------------------------------
// Token ID numbers
// --------------------------------------------------------------------------

#define TOKEN_BLOCKNAME	0x1001

#define TOKEN_LISTNUM	0x1002
#define TOKEN_GROUP	0x1003

// --------------------------------------------------------------------------
// Token entry list
// --------------------------------------------------------------------------

static CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_LISTNUM, str_listnum ),
CTokenEntry( TOKEN_GROUP, str_fractal )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read CFractalParamsListData in from an open stream
// --------------------------------------------------------------------------

int CFractalParamsListDataAsciiIO::ReadFileInternal( ifstream &stream )
{
string tokenid;
int result;

while ( g_filesysascii.ReadOpenClosePar( stream ) != 0 )
	{
	g_filesysascii.ReadString( stream, tokenid );

	if (tokenid.compare( str_blockname ) == 0 )
		{
		result = CFractalParamsListDataAsciiIO::ReadFile( stream );
		}
	else
		{
		result = false;
		}
	}

return( result );
}

// --------------------------------------------------------------------------
// Read CFractalParamsListData in from an open stream
// --------------------------------------------------------------------------

int CFractalParamsListDataAsciiIO::ReadFile( ifstream &stream )
{
int result;
string tokenid;

int entry_listnum;
CFractalParameters * entry_fractal;

result = true;

#ifdef DEBUG
cout << "CFractalParamsListDataAsciiIO::ReadFile\n";
#endif

if ( g_verbose )
	{
	cout << "Reading CFractalParamsListDataAsciiIO" << endl;
	}

while ( g_filesysascii.ReadOpenClosePar( stream ) != 0 )
	{
	g_filesysascii.ReadString( stream, tokenid );

#ifdef DEBUG
cout << "Token = " << tokenid << endl;
#endif

	if ( g_verbose > 1 )
		{
		cout << "Read Token = <" << tokenid << ">\n";
		}

	switch( token_match( tokenid, token_list, token_num ) )
		{
		case TOKEN_LISTNUM:
			g_filesysascii.ReadInteger( stream, entry_listnum );
			reserve( entry_listnum );

#ifdef DEBUG
			cout << "Read <listnum> = <" << entry_listnum << ">" << endl;
#endif

			if ( g_verbose )
				{
				cout << "Read <listnum> = <" << entry_listnum << ">" << endl;
				}
			break;

		case TOKEN_GROUP:
			entry_fractal = new CFractalParameters;

			entry_fractal->ReadFile( stream );
			push_back( *entry_fractal );

#ifdef DEBUG
			cout << "Read <fractal> = <" << &at( size()-1 ) << ">" << endl;
#endif

			if ( g_verbose )
				{
				cout << "Read <fractal> = <" << &at( size()-1 ) << ">" << endl;
				}
			break;

		default:
			cout << "CFractalParamsListIO::Unknown token <" << tokenid << ">\n";
			break;
		}

	g_filesysascii.ReadClosePar( stream );
	}

stream.putback( '}' );

if ( g_verbose )
	{
	cout << "Reading complete." << endl << endl;
	}

return( result );
}

// --------------------------------------------------------------------------
// Write data out to an open stream at specified tab depth
// --------------------------------------------------------------------------

int CFractalParamsListDataAsciiIO::WriteFile( ofstream &stream, int depth )
{
return( WriteFile( stream, depth, str_blockname ) );
}

// --------------------------------------------------------------------------
// Write data out to an open stream at specified tab depth
// --------------------------------------------------------------------------

int CFractalParamsListDataAsciiIO::WriteFile( ofstream &stream, int depth, const char *pstr )
{
int result = true;

g_filesysascii.WriteOpenPar( stream, depth, pstr );

g_filesysascii.WriteNamedInteger( stream, depth, str_listnum, size() );

for ( iterator it = begin(); it != end(); ++it )
	{
	result &= (it)->WriteFile( stream, depth );
	}

g_filesysascii.WriteClosePar( stream, depth );

return( result );
}
