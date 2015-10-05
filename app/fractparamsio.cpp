// ---------------------------------------------------------------------------
// File:    fractparamsio.cpp
// 
// Purpose: Source file for reading and writing data for class
//	    CFractalParamsIO
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

static const char *str_blockname = "fractal";

static const char *str_escaperadius = "escaperadius";
static const char *str_xcen = "xcen";
static const char *str_ycen = "ycen";
static const char *str_xwidth = "xwidth";
static const char *str_ywidth = "ywidth";
static const char *str_maxiter = "maxiter";
static const char *str_angle = "angle";
static const char *str_power = "power";
static const char *str_banding = "banding";
static const char *str_minclamp = "minclamp";
static const char *str_modesmooth = "modesmooth";
static const char *str_modepower = "modepower";
static const char *str_texpalette = "texpalette";
static const char *str_makemipmaps = "makemipmaps";
static const char *str_texwidth = "texwidth";
static const char *str_texheight = "texheight";
static const char *str_autocycle = "autocycle";
static const char *str_modeinvert = "modeinvert";
static const char *str_cycleoffset = "cycleoffset";

// --------------------------------------------------------------------------
// Token ID numbers
// --------------------------------------------------------------------------

#define TOKEN_BLOCKNAME	0x1001

#define TOKEN_ESCAPERADIUS	0x1002
#define TOKEN_XCEN	0x1003
#define TOKEN_YCEN	0x1004
#define TOKEN_XWIDTH	0x1005
#define TOKEN_YWIDTH	0x1006
#define TOKEN_MAXITER	0x1007
#define TOKEN_ANGLE	0x1008
#define TOKEN_POWER	0x1009
#define TOKEN_BANDING	0x100A
#define TOKEN_MINCLAMP	0x100B
#define TOKEN_MODESMOOTH	0x100C
#define TOKEN_MODEPOWER	0x100D
#define TOKEN_TEXPALETTE	0x100E
#define TOKEN_MAKEMIPMAPS	0x100F
#define TOKEN_TEXWIDTH	0x1010
#define TOKEN_TEXHEIGHT	0x1011
#define TOKEN_AUTOCYCLE	0x1012
#define TOKEN_MODEINVERT	0x1013
#define TOKEN_CYCLEOFFSET	0x1014

// --------------------------------------------------------------------------
// Token entry list
// --------------------------------------------------------------------------

static CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_ESCAPERADIUS, str_escaperadius ),
CTokenEntry( TOKEN_XCEN, str_xcen ),
CTokenEntry( TOKEN_YCEN, str_ycen ),
CTokenEntry( TOKEN_XWIDTH, str_xwidth ),
CTokenEntry( TOKEN_YWIDTH, str_ywidth ),
CTokenEntry( TOKEN_MAXITER, str_maxiter ),
CTokenEntry( TOKEN_ANGLE, str_angle ),
CTokenEntry( TOKEN_POWER, str_power ),
CTokenEntry( TOKEN_BANDING, str_banding ),
CTokenEntry( TOKEN_MINCLAMP, str_minclamp ),
CTokenEntry( TOKEN_MODESMOOTH, str_modesmooth ),
CTokenEntry( TOKEN_MODEPOWER, str_modepower ),
CTokenEntry( TOKEN_TEXPALETTE, str_texpalette ),
CTokenEntry( TOKEN_MAKEMIPMAPS, str_makemipmaps ),
CTokenEntry( TOKEN_TEXWIDTH, str_texwidth ),
CTokenEntry( TOKEN_TEXHEIGHT, str_texheight ),
CTokenEntry( TOKEN_AUTOCYCLE, str_autocycle ),
CTokenEntry( TOKEN_MODEINVERT, str_modeinvert ),
CTokenEntry( TOKEN_CYCLEOFFSET, str_cycleoffset )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read CFractalParamsData in from an open stream
// --------------------------------------------------------------------------

int CFractalParamsDataAsciiIO::ReadFileInternal( ifstream &stream )
{
string tokenid;
int result;

while ( g_filesysascii.ReadOpenClosePar( stream ) != 0 )
	{
	g_filesysascii.ReadString( stream, tokenid );

	if (tokenid.compare( str_blockname ) == 0 )
		{
		result = CFractalParamsDataAsciiIO::ReadFile( stream );
		}
	else
		{
		result = false;
		}
	}

return( result );
}

// --------------------------------------------------------------------------
// Read CFractalParamsData in from an open stream
// --------------------------------------------------------------------------

int CFractalParamsDataAsciiIO::ReadFile( ifstream &stream )
{
int result;
string tokenid;

result = true;

if ( g_verbose )
	{
	cout << "Reading CFractalParamsDataAsciiIO" << endl;
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
		case TOKEN_ESCAPERADIUS:
			g_filesysascii.ReadFloat( stream, m_escaperadius );

			if ( g_verbose )
				{
				cout << "Read <escaperadius> = <" << m_escaperadius << ">" << endl;
				}
			break;

		case TOKEN_XCEN:
			g_filesysascii.ReadFloat( stream, m_xcen );

			if ( g_verbose )
				{
				cout << "Read <xcen> = <" << m_xcen << ">" << endl;
				}
			break;

		case TOKEN_YCEN:
			g_filesysascii.ReadFloat( stream, m_ycen );

			if ( g_verbose )
				{
				cout << "Read <ycen> = <" << m_ycen << ">" << endl;
				}
			break;

		case TOKEN_XWIDTH:
			g_filesysascii.ReadFloat( stream, m_xwidth );

			if ( g_verbose )
				{
				cout << "Read <xwidth> = <" << m_xwidth << ">" << endl;
				}
			break;

		case TOKEN_YWIDTH:
			g_filesysascii.ReadFloat( stream, m_ywidth );

			if ( g_verbose )
				{
				cout << "Read <ywidth> = <" << m_ywidth << ">" << endl;
				}
			break;

		case TOKEN_MAXITER:
			g_filesysascii.ReadInteger( stream, m_maxiter );

			if ( g_verbose )
				{
				cout << "Read <maxiter> = <" << m_maxiter << ">" << endl;
				}
			break;

		case TOKEN_ANGLE:
			g_filesysascii.ReadFloat( stream, m_angle );

			if ( g_verbose )
				{
				cout << "Read <angle> = <" << m_angle << ">" << endl;
				}
			break;

		case TOKEN_POWER:
			g_filesysascii.ReadFloat( stream, m_power );

			if ( g_verbose )
				{
				cout << "Read <power> = <" << m_power << ">" << endl;
				}
			break;

		case TOKEN_BANDING:
			g_filesysascii.ReadFloat( stream, m_banding );

			if ( g_verbose )
				{
				cout << "Read <banding> = <" << m_banding << ">" << endl;
				}
			break;

		case TOKEN_MINCLAMP:
			g_filesysascii.ReadFloat( stream, m_minclamp );

			if ( g_verbose )
				{
				cout << "Read <minclamp> = <" << m_minclamp << ">" << endl;
				}
			break;

		case TOKEN_MODESMOOTH:
			g_filesysascii.ReadInteger( stream, m_modesmooth );

			if ( g_verbose )
				{
				cout << "Read <modesmooth> = <" << m_modesmooth << ">" << endl;
				}
			break;

		case TOKEN_MODEPOWER:
			g_filesysascii.ReadInteger( stream, m_modepower );

			if ( g_verbose )
				{
				cout << "Read <modepower> = <" << m_modepower << ">" << endl;
				}
			break;

		case TOKEN_TEXPALETTE:
			g_filesysascii.ReadInteger( stream, m_texpalette );

			if ( g_verbose )
				{
				cout << "Read <texpalette> = <" << m_texpalette << ">" << endl;
				}
			break;

		case TOKEN_MAKEMIPMAPS:
			g_filesysascii.ReadInteger( stream, m_makemipmaps );

			if ( g_verbose )
				{
				cout << "Read <makemipmaps> = <" << m_makemipmaps << ">" << endl;
				}
			break;

		case TOKEN_TEXWIDTH:
			g_filesysascii.ReadInteger( stream, m_texwidth );

			if ( g_verbose )
				{
				cout << "Read <texwidth> = <" << m_texwidth << ">" << endl;
				}
			break;

		case TOKEN_TEXHEIGHT:
			g_filesysascii.ReadInteger( stream, m_texheight );

			if ( g_verbose )
				{
				cout << "Read <texheight> = <" << m_texheight << ">" << endl;
				}
			break;

		case TOKEN_AUTOCYCLE:
			g_filesysascii.ReadInteger( stream, m_autocycle );

			if ( g_verbose )
				{
				cout << "Read <autocycle> = <" << m_autocycle << ">" << endl;
				}
			break;

		case TOKEN_MODEINVERT:
			g_filesysascii.ReadInteger( stream, m_modeinvert );

			if ( g_verbose )
				{
				cout << "Read <modeinvert> = <" << m_modeinvert << ">" << endl;
				}
			break;

		case TOKEN_CYCLEOFFSET:
			g_filesysascii.ReadInteger( stream, m_cycleoffset );

			if ( g_verbose )
				{
				cout << "Read <cycleoffset> = <" << m_cycleoffset << ">" << endl;
				}
			break;

		default:
			cout << "CFractalParamsIO::Unknown token <" << tokenid << ">\n";
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

int CFractalParamsDataAsciiIO::WriteFile( ofstream &stream, int depth )
{
return( WriteFile( stream, depth, str_blockname ) );
}

// --------------------------------------------------------------------------
// Write data out to an open stream at specified tab depth
// --------------------------------------------------------------------------

int CFractalParamsDataAsciiIO::WriteFile( ofstream &stream, int depth, const char *pstr )
{
int result = true;

g_filesysascii.WriteOpenPar( stream, depth, pstr );

g_filesysascii.WriteNamedFloat( stream, depth, str_escaperadius, m_escaperadius );
g_filesysascii.WriteNamedFloat( stream, depth, str_xcen, m_xcen );
g_filesysascii.WriteNamedFloat( stream, depth, str_ycen, m_ycen );
g_filesysascii.WriteNamedFloat( stream, depth, str_xwidth, m_xwidth );
g_filesysascii.WriteNamedFloat( stream, depth, str_ywidth, m_ywidth );
g_filesysascii.WriteNamedInteger( stream, depth, str_maxiter, m_maxiter );
g_filesysascii.WriteNamedFloat( stream, depth, str_angle, m_angle );
g_filesysascii.WriteNamedFloat( stream, depth, str_power, m_power );
g_filesysascii.WriteNamedFloat( stream, depth, str_banding, m_banding );
g_filesysascii.WriteNamedFloat( stream, depth, str_minclamp, m_minclamp );
g_filesysascii.WriteNamedInteger( stream, depth, str_modesmooth, m_modesmooth );
g_filesysascii.WriteNamedInteger( stream, depth, str_modepower, m_modepower );
g_filesysascii.WriteNamedInteger( stream, depth, str_texpalette, m_texpalette );
g_filesysascii.WriteNamedInteger( stream, depth, str_makemipmaps, m_makemipmaps );
g_filesysascii.WriteNamedInteger( stream, depth, str_texwidth, m_texwidth );
g_filesysascii.WriteNamedInteger( stream, depth, str_texheight, m_texheight );
g_filesysascii.WriteNamedInteger( stream, depth, str_autocycle, m_autocycle );
g_filesysascii.WriteNamedInteger( stream, depth, str_modeinvert, m_modeinvert );
g_filesysascii.WriteNamedInteger( stream, depth, str_cycleoffset, m_cycleoffset );

g_filesysascii.WriteClosePar( stream, depth );

return( result );
}
