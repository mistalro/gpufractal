// ---------------------------------------------------------------------------
// File:    filesysentrylistio.cpp
// 
// Purpose: Source file for reading and writing data for class
//	    CFileSysEntryListIO
//
// Author:  Autofile generator
// 
// Date:    Mon May 28 15:49:34 2012
// ----------------------------------------------------------------------------

#ifdef _WINDOWS_
#include "stdafx.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "filesyscommon.h"

// ---------------------------------------------------------------------------
// Keyword strings
// ---------------------------------------------------------------------------

static const char *str_blockname = "datalist";

static const char *str_listnum = "listnum";
static const char *str_listdata = "listdata";

// --------------------------------------------------------------------------
// Token ID numbers
// --------------------------------------------------------------------------

#define TOKEN_BLOCKNAME	0x1001

#define TOKEN_LISTNUM	0x1002
#define TOKEN_LISTDATA	0x1003

// --------------------------------------------------------------------------
// Token entry list
// --------------------------------------------------------------------------

static CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_LISTNUM, str_listnum ),
CTokenEntry( TOKEN_LISTDATA, str_listdata )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read CFileSysEntryListData in from an open stream
// --------------------------------------------------------------------------

int CFileSysEntryListDataAsciiIO::ReadFileInternal( ifstream &stream )
{
string tokenid;
int result;

while ( ReadOpenClosePar( stream ) != 0 )
	{
	ReadString( stream, tokenid );

	if (tokenid.compare( str_blockname ) == 0 )
		{
		result = ReadFile( stream );
		}
	else
		{
		result = false;
		}
	}

return( result );
}

// --------------------------------------------------------------------------
// Read CFileSysEntryListData in from an open stream
// --------------------------------------------------------------------------

int CFileSysEntryListDataAsciiIO::ReadFile( ifstream &stream )
{
int result;
string tokenid;

int entry_listnum;
CFileSysEntry entry_listdata;

result = true;


#ifdef DEBUG
cout << "CFileSysEntryListDataAsciiIO::ReadFile\n";
#endif


if ( g_verbose )
	{
	cout << "Reading CFileSysEntryListDataAsciiIO" << endl;
	}

while ( ReadOpenClosePar( stream ) != 0 )
	{
	ReadString( stream, tokenid );

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
			ReadInteger( stream, entry_listnum );
			reserve( entry_listnum );

#ifdef DEBUG
			cout << "Reading listnum" << endl;
#endif

			if ( g_verbose )
				{
				cout << "Read <listnum> = <" << entry_listnum << ">\n";
				}
			break;

		case TOKEN_LISTDATA:
			entry_listdata.ReadFile( stream );
			push_back( entry_listdata );

#ifdef DEBUG
			cout << "Reading listdata" << endl;
#endif

			if ( g_verbose )
				{
				cout << "Read <listdata>\n";
				}
			break;

		default:
			cout << "CFileSysEntryListIO::Unknown token <" << tokenid << ">\n";
			break;
		}

	ReadClosePar( stream );
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

int CFileSysEntryListDataAsciiIO::WriteFile( ofstream &stream, int depth )
{
return( WriteFile( stream, depth, str_blockname ) );
}

// --------------------------------------------------------------------------
// Write data out to an open stream at specified tab depth
// --------------------------------------------------------------------------

int CFileSysEntryListDataAsciiIO::WriteFile( ofstream &stream, int depth, const char *pstr )
{
int result;

result = true;

WriteOpenPar( stream, depth, pstr );

WriteNamedInteger( stream, depth, str_listnum, size() );

for ( iterator it = begin(); it != end(); ++it )
	{
	result &= it->WriteFile( stream, depth );
	}

WriteClosePar( stream, depth );

return( result );
}
