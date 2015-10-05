// ---------------------------------------------------------------------------
// File:    netnodeentrylistio.cpp
// 
// Purpose: Source file for reading and writing data for class
//	    CNetNodeEntryListIO
//
// Author:  Autofile generator
// 
// Date:    Mon Jul 27 22:23:20 2015
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

static const char *str_blockname = "nodelist";

static const char *str_listnum = "listnum";
static const char *str_nodedata = "nodedata";

// --------------------------------------------------------------------------
// Token ID numbers
// --------------------------------------------------------------------------

#define TOKEN_BLOCKNAME	0x1001

#define TOKEN_LISTNUM	0x1002
#define TOKEN_NODEDATA	0x1003

// --------------------------------------------------------------------------
// Token entry list
// --------------------------------------------------------------------------

static CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_LISTNUM, str_listnum ),
CTokenEntry( TOKEN_NODEDATA, str_nodedata )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read CNetNodeEntryListData in from an open stream
// --------------------------------------------------------------------------

int CNetNodeEntryListDataAsciiIO::ReadFileInternal( ifstream &stream )
{
string tokenid;
int result;

while ( g_filesysascii.ReadOpenClosePar( stream ) != 0 )
	{
	g_filesysascii.ReadString( stream, tokenid );

	if (tokenid.compare( str_blockname ) == 0 )
		{
		result = CNetNodeEntryListDataAsciiIO::ReadFile( stream );
		}
	else
		{
		result = false;
		}
	}

return( result );
}

// --------------------------------------------------------------------------
// Read CNetNodeEntryListData in from an open stream
// --------------------------------------------------------------------------

int CNetNodeEntryListDataAsciiIO::ReadFile( ifstream &stream )
{
int result;
string tokenid;

int entry_listnum;
CNetworkNode * entry_nodedata;

result = true;

#ifdef DEBUG
cout << "CNetNodeEntryListDataAsciiIO::ReadFile\n";
#endif

if ( g_verbose )
	{
	cout << "Reading CNetNodeEntryListDataAsciiIO" << endl;
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

		case TOKEN_NODEDATA:
			entry_nodedata = new CNetworkNode;

			entry_nodedata->ReadFile( stream );
			push_back( entry_nodedata );

#ifdef DEBUG
			cout << "Read <nodedata> = <" << &at( size()-1 ) << ">" << endl;
#endif

			if ( g_verbose )
				{
				cout << "Read <nodedata> = <" << &at( size()-1 ) << ">" << endl;
				}
			break;

		default:
			cout << "CNetNodeEntryListIO::Unknown token <" << tokenid << ">\n";
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

int CNetNodeEntryListDataAsciiIO::WriteFile( ofstream &stream, int depth )
{
return( WriteFile( stream, depth, str_blockname ) );
}

// --------------------------------------------------------------------------
// Write data out to an open stream at specified tab depth
// --------------------------------------------------------------------------

int CNetNodeEntryListDataAsciiIO::WriteFile( ofstream &stream, int depth, const char *pstr )
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
