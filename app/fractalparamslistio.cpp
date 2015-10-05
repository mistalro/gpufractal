// ---------------------------------------------------------------------------
// File:    fractalparamslistio.cpp
// 
// Purpose: Source file for reading and writing data for class
//	    CFractalParamsListIO
//
// Author:  Autofile generator
// 
// Date:    Wed Jul 22 19:59:20 2015
// ----------------------------------------------------------------------------

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

static const char *str_blockname = "grouplist";

static const char *str_listnum = "listnum";
static const char *str_group = "group";

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
CTokenEntry( TOKEN_GROUP, str_group )
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
CFractalParametersIO * entry_group;

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
			entry_group = new CFractalParametersIO;

			entry_group->ReadFile( stream );
			push_back( entry_group );

#ifdef DEBUG
			cout << "Read <group> = <" << &at( size()-1 ) << ">" << endl;
#endif

			if ( g_verbose )
				{
				cout << "Read <group> = <" << &at( size()-1 ) << ">" << endl;
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
	result &= (*it)->WriteFile( stream, depth );
	}

g_filesysascii.WriteClosePar( stream, depth );

return( result );
}
