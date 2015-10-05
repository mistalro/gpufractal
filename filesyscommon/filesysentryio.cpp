// ---------------------------------------------------------------------------
// File:    filesysentryio.cpp
// 
// Purpose: Source file for reading and writing data for class
//	    CFileSysEntryIO
//
// Author:  Autofile generator
// 
// Date:    Mon Jun 17 01:01:41 2013
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

static const char *str_blockname = "listdata";

static const char *str_tokenid = "tokenid";
static const char *str_keyword = "keyword";
static const char *str_classname = "classname";
static const char *str_type = "type";
static const char *str_readfunc = "readfunc";
static const char *str_readbasicfunc = "readbasicfunc";
static const char *str_writebasicfunc = "writebasicfunc";
static const char *str_writefunc = "writefunc";
static const char *str_suffix = "suffix";
static const char *str_readbinaryfunc = "readbinaryfunc";
static const char *str_writebinaryfunc = "writebinaryfunc";

// --------------------------------------------------------------------------
// Token ID numbers
// --------------------------------------------------------------------------

#define TOKEN_BLOCKNAME	0x1001

#define TOKEN_TOKENID	0x1002
#define TOKEN_KEYWORD	0x1003
#define TOKEN_CLASSNAME	0x1004
#define TOKEN_TYPE	0x1005
#define TOKEN_READFUNC	0x1006
#define TOKEN_READBASICFUNC	0x1007
#define TOKEN_WRITEBASICFUNC	0x1008
#define TOKEN_WRITEFUNC	0x1009
#define TOKEN_SUFFIX	0x100A
#define TOKEN_READBINARYFUNC	0x100B
#define TOKEN_WRITEBINARYFUNC	0x100C

// --------------------------------------------------------------------------
// Token entry list
// --------------------------------------------------------------------------

static CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_TOKENID, str_tokenid ),
CTokenEntry( TOKEN_KEYWORD, str_keyword ),
CTokenEntry( TOKEN_CLASSNAME, str_classname ),
CTokenEntry( TOKEN_TYPE, str_type ),
CTokenEntry( TOKEN_READFUNC, str_readfunc ),
CTokenEntry( TOKEN_READBASICFUNC, str_readbasicfunc ),
CTokenEntry( TOKEN_WRITEBASICFUNC, str_writebasicfunc ),
CTokenEntry( TOKEN_WRITEFUNC, str_writefunc ),
CTokenEntry( TOKEN_SUFFIX, str_suffix ),
CTokenEntry( TOKEN_READBINARYFUNC, str_readbinaryfunc ),
CTokenEntry( TOKEN_WRITEBINARYFUNC, str_writebinaryfunc )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read CFileSysEntryData in from an open stream
// --------------------------------------------------------------------------

int CFileSysEntryDataAsciiIO::ReadFileInternal( ifstream &stream )
{
string tokenid;
int result;

while ( g_filesysascii.ReadOpenClosePar( stream ) != 0 )
	{
	g_filesysascii.ReadString( stream, tokenid );

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
// Read CFileSysEntryData in from an open stream
// --------------------------------------------------------------------------

int CFileSysEntryDataAsciiIO::ReadFile( ifstream &stream )
{
int result;
string tokenid;

int entry_tokenid;
string entry_keyword;
string entry_classname;
string entry_type;
string entry_readfunc;
string entry_readbasicfunc;
string entry_writebasicfunc;
string entry_writefunc;
string entry_suffix;
string entry_readbinaryfunc;
string entry_writebinaryfunc;

result = true;


if ( g_verbose )
	{
	cout << "Reading CFileSysEntryDataAsciiIO" << endl;
	}

while ( g_filesysascii.ReadOpenClosePar( stream ) != 0 )
	{
	g_filesysascii.ReadString( stream, tokenid );

	if ( g_verbose > 1 )
		{
		cout << "Read Token = <" << tokenid << ">\n";
		}

	switch( token_match( tokenid, token_list, token_num ) )
		{
		case TOKEN_TOKENID:
			g_filesysascii.ReadInteger( stream, entry_tokenid );
			m_tokenid = entry_tokenid;

			if ( g_verbose )
				{
				cout << "Read <tokenid> = <" << entry_tokenid << ">" << endl;
				}
			break;

		case TOKEN_KEYWORD:
			g_filesysascii.ReadQuotedString( stream, entry_keyword );
			m_keyword = entry_keyword;

			if ( g_verbose )
				{
				cout << "Read <keyword> = <" << entry_keyword << ">" << endl;
				}
			break;

		case TOKEN_CLASSNAME:
			g_filesysascii.ReadQuotedString( stream, entry_classname );
			m_classname = entry_classname;

			if ( g_verbose )
				{
				cout << "Read <classname> = <" << entry_classname << ">" << endl;
				}
			break;

		case TOKEN_TYPE:
			g_filesysascii.ReadQuotedString( stream, entry_type );
			m_type = entry_type;

			if ( g_verbose )
				{
				cout << "Read <type> = <" << entry_type << ">" << endl;
				}
			break;

		case TOKEN_READFUNC:
			g_filesysascii.ReadQuotedString( stream, entry_readfunc );
			m_readfunc = entry_readfunc;

			if ( g_verbose )
				{
				cout << "Read <readfunc> = <" << entry_readfunc << ">" << endl;
				}
			break;

		case TOKEN_READBASICFUNC:
			g_filesysascii.ReadQuotedString( stream, entry_readbasicfunc );
			m_readbasicfunc = entry_readbasicfunc;

			if ( g_verbose )
				{
				cout << "Read <readbasicfunc> = <" << entry_readbasicfunc << ">" << endl;
				}
			break;

		case TOKEN_WRITEBASICFUNC:
			g_filesysascii.ReadQuotedString( stream, entry_writebasicfunc );
			m_writebasicfunc = entry_writebasicfunc;

			if ( g_verbose )
				{
				cout << "Read <writebasicfunc> = <" << entry_writebasicfunc << ">" << endl;
				}
			break;

		case TOKEN_WRITEFUNC:
			g_filesysascii.ReadQuotedString( stream, entry_writefunc );
			m_writefunc = entry_writefunc;

			if ( g_verbose )
				{
				cout << "Read <writefunc> = <" << entry_writefunc << ">" << endl;
				}
			break;

		case TOKEN_SUFFIX:
			g_filesysascii.ReadQuotedString( stream, entry_suffix );
			m_suffix = entry_suffix;

			if ( g_verbose )
				{
				cout << "Read <suffix> = <" << entry_suffix << ">" << endl;
				}
			break;

		case TOKEN_READBINARYFUNC:
			g_filesysascii.ReadQuotedString( stream, entry_readbinaryfunc );
			m_readbinaryfunc = entry_readbinaryfunc;

			if ( g_verbose )
				{
				cout << "Read <readbinaryfunc> = <" << entry_readbinaryfunc << ">" << endl;
				}
			break;

		case TOKEN_WRITEBINARYFUNC:
			g_filesysascii.ReadQuotedString( stream, entry_writebinaryfunc );
			m_writebinaryfunc = entry_writebinaryfunc;

			if ( g_verbose )
				{
				cout << "Read <writebinaryfunc> = <" << entry_writebinaryfunc << ">" << endl;
				}
			break;

		default:
			cout << "CFileSysEntryIO::Unknown token <" << tokenid << ">\n";
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

int CFileSysEntryDataAsciiIO::WriteFile( ofstream &stream, int depth )
{
return( WriteFile( stream, depth, str_blockname ) );
}

// --------------------------------------------------------------------------
// Write data out to an open stream at specified tab depth
// --------------------------------------------------------------------------

int CFileSysEntryDataAsciiIO::WriteFile( ofstream &stream, int depth, const char *pstr )
{
int result;

result = true;

g_filesysascii.WriteOpenPar( stream, depth, pstr );

g_filesysascii.WriteNamedInteger( stream, depth, str_tokenid, m_tokenid );
g_filesysascii.WriteNamedString( stream, depth, str_keyword, m_keyword );
g_filesysascii.WriteNamedString( stream, depth, str_classname, m_classname );
g_filesysascii.WriteNamedString( stream, depth, str_type, m_type );
g_filesysascii.WriteNamedString( stream, depth, str_readfunc, m_readfunc );
g_filesysascii.WriteNamedString( stream, depth, str_readbasicfunc, m_readbasicfunc );
g_filesysascii.WriteNamedString( stream, depth, str_writebasicfunc, m_writebasicfunc );
g_filesysascii.WriteNamedString( stream, depth, str_writefunc, m_writefunc );
g_filesysascii.WriteNamedString( stream, depth, str_suffix, m_suffix );
g_filesysascii.WriteNamedString( stream, depth, str_readbinaryfunc, m_readbinaryfunc );
g_filesysascii.WriteNamedString( stream, depth, str_writebinaryfunc, m_writebinaryfunc );

g_filesysascii.WriteClosePar( stream, depth );

return( result );
}
