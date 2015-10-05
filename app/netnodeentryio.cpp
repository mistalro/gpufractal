// ---------------------------------------------------------------------------
// File:    netnodeentryio.cpp
// 
// Purpose: Source file for reading and writing data for class
//	    CNodeDataIO
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

static const char *str_blockname = "nodedata";

static const char *str_hostname = "hostname";
static const char *str_port = "port";
static const char *str_windowid = "windowid";
static const char *str_offx = "offx";
static const char *str_offy = "offy";
static const char *str_width = "width";
static const char *str_height = "height";
static const char *str_offheading = "offheading";
static const char *str_aspect = "aspect";

// --------------------------------------------------------------------------
// Token ID numbers
// --------------------------------------------------------------------------

#define TOKEN_BLOCKNAME	0x1001

#define TOKEN_HOSTNAME	0x1002
#define TOKEN_PORT	0x1003
#define TOKEN_WINDOWID	0x1004
#define TOKEN_OFFX	0x1005
#define TOKEN_OFFY	0x1006
#define TOKEN_WIDTH	0x1007
#define TOKEN_HEIGHT	0x1008
#define TOKEN_OFFHEADING	0x1009
#define TOKEN_ASPECT	0x100A

// --------------------------------------------------------------------------
// Token entry list
// --------------------------------------------------------------------------

static CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_HOSTNAME, str_hostname ),
CTokenEntry( TOKEN_PORT, str_port ),
CTokenEntry( TOKEN_WINDOWID, str_windowid ),
CTokenEntry( TOKEN_OFFX, str_offx ),
CTokenEntry( TOKEN_OFFY, str_offy ),
CTokenEntry( TOKEN_WIDTH, str_width ),
CTokenEntry( TOKEN_HEIGHT, str_height ),
CTokenEntry( TOKEN_OFFHEADING, str_offheading ),
CTokenEntry( TOKEN_ASPECT, str_aspect )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read CNetNodeEntryData in from an open stream
// --------------------------------------------------------------------------

int CNetNodeEntryDataAsciiIO::ReadFileInternal( ifstream &stream )
{
string tokenid;
int result;

while ( g_filesysascii.ReadOpenClosePar( stream ) != 0 )
	{
	g_filesysascii.ReadString( stream, tokenid );

	if (tokenid.compare( str_blockname ) == 0 )
		{
		result = CNetNodeEntryDataAsciiIO::ReadFile( stream );
		}
	else
		{
		result = false;
		}
	}

return( result );
}

// --------------------------------------------------------------------------
// Read CNetNodeEntryData in from an open stream
// --------------------------------------------------------------------------

int CNetNodeEntryDataAsciiIO::ReadFile( ifstream &stream )
{
int result;
string tokenid;

result = true;

if ( g_verbose )
	{
	cout << "Reading CNetNodeEntryDataAsciiIO" << endl;
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
		case TOKEN_HOSTNAME:
			g_filesysascii.ReadQuotedString( stream, m_hostname );

			if ( g_verbose )
				{
				cout << "Read <hostname> = <" << m_hostname << ">" << endl;
				}
			break;

		case TOKEN_PORT:
			g_filesysascii.ReadInteger( stream, m_port );

			if ( g_verbose )
				{
				cout << "Read <port> = <" << m_port << ">" << endl;
				}
			break;

		case TOKEN_WINDOWID:
			g_filesysascii.ReadInteger( stream, m_windowid );

			if ( g_verbose )
				{
				cout << "Read <windowid> = <" << m_windowid << ">" << endl;
				}
			break;

		case TOKEN_OFFX:
			g_filesysascii.ReadFloat( stream, m_offx );

			if ( g_verbose )
				{
				cout << "Read <offx> = <" << m_offx << ">" << endl;
				}
			break;

		case TOKEN_OFFY:
			g_filesysascii.ReadFloat( stream, m_offy );

			if ( g_verbose )
				{
				cout << "Read <offy> = <" << m_offy << ">" << endl;
				}
			break;

		case TOKEN_WIDTH:
			g_filesysascii.ReadFloat( stream, m_width );

			if ( g_verbose )
				{
				cout << "Read <width> = <" << m_width << ">" << endl;
				}
			break;

		case TOKEN_HEIGHT:
			g_filesysascii.ReadFloat( stream, m_height );

			if ( g_verbose )
				{
				cout << "Read <height> = <" << m_height << ">" << endl;
				}
			break;

		case TOKEN_OFFHEADING:
			g_filesysascii.ReadFloat( stream, m_offheading );

			if ( g_verbose )
				{
				cout << "Read <offheading> = <" << m_offheading << ">" << endl;
				}
			break;

		case TOKEN_ASPECT:
			g_filesysascii.ReadFloat( stream, m_aspect );

			if ( g_verbose )
				{
				cout << "Read <aspect> = <" << m_aspect << ">" << endl;
				}
			break;

		default:
			cout << "CNodeDataIO::Unknown token <" << tokenid << ">\n";
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

int CNetNodeEntryDataAsciiIO::WriteFile( ofstream &stream, int depth )
{
return( WriteFile( stream, depth, str_blockname ) );
}

// --------------------------------------------------------------------------
// Write data out to an open stream at specified tab depth
// --------------------------------------------------------------------------

int CNetNodeEntryDataAsciiIO::WriteFile( ofstream &stream, int depth, const char *pstr )
{
int result = true;

g_filesysascii.WriteOpenPar( stream, depth, pstr );

g_filesysascii.WriteNamedString( stream, depth, str_hostname, m_hostname );
g_filesysascii.WriteNamedInteger( stream, depth, str_port, m_port );
g_filesysascii.WriteNamedInteger( stream, depth, str_windowid, m_windowid );
g_filesysascii.WriteNamedFloat( stream, depth, str_offx, m_offx );
g_filesysascii.WriteNamedFloat( stream, depth, str_offy, m_offy );
g_filesysascii.WriteNamedFloat( stream, depth, str_width, m_width );
g_filesysascii.WriteNamedFloat( stream, depth, str_height, m_height );
g_filesysascii.WriteNamedFloat( stream, depth, str_offheading, m_offheading );
g_filesysascii.WriteNamedFloat( stream, depth, str_aspect, m_aspect );

g_filesysascii.WriteClosePar( stream, depth );

return( result );
}
