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

#include "fractals.h"

using namespace std;

//#define DEBUG

// --------------------------------------------------------------------------
// Set parameters to something sane
// --------------------------------------------------------------------------

void CFractalParameters::Reset(void)
{
m_escaperadius = 4.0f;
m_xcen = -0.5f;
m_ycen = 0.0f;

m_xwidth = 4.0f;
m_ywidth = 4.0f;
m_maxiter = 1024;
m_angle = 0.0f;
m_power = 2.0f;
m_banding = 1.0f;
m_minclamp = 0.0f;
m_modesmooth = true;

m_modepower = MANDELBROT_P2;
m_texpalette = 0;
m_makemipmaps = 0;
m_texwidth = 512;
m_texheight = 512;
m_cycleoffset = 0;
m_modeinvert = 0;
m_autocycle = 0;

m_changebits = CHANGEBIT_NONE;
m_msgtype = MSG_NONE;
m_port = 0;
m_windowto = 0;
m_windowfrom = 0;

m_maxmessagesize = GetMaxMessageSize();
}

// --------------------------------------------------------------------------
// Define the strings used to encode the parameters into a text string
// --------------------------------------------------------------------------

#define bytestring(X)   ((char *) (X) )
#define strbyte char

static const strbyte *str_start = bytestring("ss");
static const strbyte *str_type = bytestring("ty");
static const strbyte *str_escaperadius = bytestring("er");
static const strbyte *str_xcen = bytestring("xc");
static const strbyte *str_ycen = bytestring("yc");
static const strbyte *str_xwidth = bytestring("xw");
static const strbyte *str_ywidth = bytestring("yw");
static const strbyte *str_maxiter = bytestring("mi");
static const strbyte *str_angle = bytestring("an");
static const strbyte *str_power = bytestring("pw");
static const strbyte *str_banding = bytestring("ba");
static const strbyte *str_modesmooth = bytestring("ms");
static const strbyte *str_modepower = bytestring("mp");
static const strbyte *str_texpalette = bytestring("te");
static const strbyte *str_makemipmaps = bytestring("mm");
static const strbyte *str_minclamp = bytestring("mc");
static const strbyte *str_texwidth = bytestring("tw");
static const strbyte *str_texheight = bytestring("th");
static const strbyte *str_cycleoffset = bytestring("co");
static const strbyte *str_modeinvert = bytestring("mv");
static const strbyte *str_autocycle = bytestring("ac");
static const strbyte *str_windowfrom = bytestring("wf");
static const strbyte *str_windowto = bytestring("wt");
static const strbyte *str_port = bytestring("po");
static const strbyte *str_address = bytestring("ad");
static const strbyte *str_windowwidth = bytestring("ww");
static const strbyte *str_windowheight = bytestring("wh");

static const strbyte *str_eof = bytestring("ee");

// --------------------------------------------------------------------------
// Define the codes used to decode the parameters from a text string
// --------------------------------------------------------------------------

#define CODE_START        MAKE_CHCODE( 's', 's')
#define CODE_TYPE         MAKE_CHCODE( 't', 'y')
#define CODE_ESCAPERADIUS MAKE_CHCODE( 'e', 'r')
#define CODE_XCEN         MAKE_CHCODE( 'x', 'c')
#define CODE_YCEN         MAKE_CHCODE( 'y', 'c')
#define CODE_XWIDTH       MAKE_CHCODE( 'x', 'w')
#define CODE_YWIDTH       MAKE_CHCODE( 'y', 'w')
#define CODE_MAXITER      MAKE_CHCODE( 'm', 'i')
#define CODE_ANGLE        MAKE_CHCODE( 'a', 'n')
#define CODE_POWER        MAKE_CHCODE( 'p', 'w')
#define CODE_BANDING      MAKE_CHCODE( 'b', 'a')
#define CODE_MODESMOOTH   MAKE_CHCODE( 'm', 's')
#define CODE_MODEPOWER    MAKE_CHCODE( 'm', 'p')
#define CODE_TEXPALETTE   MAKE_CHCODE( 't', 'e')
#define CODE_MAKEMIPMAPS  MAKE_CHCODE( 'm', 'm')
#define CODE_MINCLAMP     MAKE_CHCODE( 'm', 'c')
#define CODE_TEXWIDTH     MAKE_CHCODE( 't', 'w')
#define CODE_TEXHEIGHT    MAKE_CHCODE( 't', 'h')
#define CODE_CYCLEOFFSET  MAKE_CHCODE( 'c', 'o')
#define CODE_MODEINVERT   MAKE_CHCODE( 'm', 'v')
#define CODE_AUTOCYCLE    MAKE_CHCODE( 'a', 'c')
#define CODE_WINDOWFROM   MAKE_CHCODE( 'w', 'f')
#define CODE_WINDOWTO     MAKE_CHCODE( 'w', 't')
#define CODE_PORT         MAKE_CHCODE( 'p', 'o')
#define CODE_ADDRESS      MAKE_CHCODE( 'a', 'd')
#define CODE_WINDOWWIDTH  MAKE_CHCODE( 'w', 'w')
#define CODE_WINDOWHEIGHT MAKE_CHCODE( 'w', 'h')
#define CODE_EOF          MAKE_CHCODE( 'e', 'e')

// --------------------------------------------------------------------------
// Helper function to dump messages
// --------------------------------------------------------------------------

static const char table[] = "0123456789ABCDEF";

void CFractalParameters::HexDump( FRbyte *pptr, int len)
{
int col = 0;

cout << endl;

for (int idx = 0; idx < len; idx++)
	{
	cout << table[ (pptr[idx] >> 4 ) &0xF];
	cout << table[ (pptr[idx] & 0xF)] << " ";

	if (++col == 16)
		{
		col = 0;
		cout << endl;
		}
	}

cout << endl;
}

// ==========================================================================
// BINARY UNPACKING METHOD
// ==========================================================================

// --------------------------------------------------------------------------
// Create a request message
//
// This only requires the reply-to port, address and window ID's
// --------------------------------------------------------------------------

void CFractalParameters::CreateRequest( FRbyte *pstr, int port,struct in_addr &addr, int &len)
{
FRbyte *pptr = pstr;

memset(pstr, 0, m_maxmessagesize);

pptr = PackCode(pptr, str_start);
pptr = PackInteger( pptr, MSG_REQPARAM, str_type);
pptr = PackInteger( pptr, port, str_port);
pptr = PackAddress( pptr, addr, str_address);
pptr = PackInteger( pptr, m_windowfrom, str_windowfrom);
pptr = PackInteger( pptr, m_windowto, str_windowto);
pptr = PackCode(pptr, str_eof);

len = m_maxmessagesize;
}

// --------------------------------------------------------------------------
// Create a basic ping
//
// This requires the reply-to port and address and window ID's
// --------------------------------------------------------------------------

void CFractalParameters::CreatePing( FRbyte *pstr, int port,struct in_addr &addr, int &len)
{
FRbyte *pptr = pstr;

memset(pstr, 0, m_maxmessagesize);

pptr = PackCode(pptr, str_start);
pptr = PackInteger(pptr, MSG_PING, str_type);
pptr = PackInteger(pptr, port, str_port);
pptr = PackAddress(pptr, addr, str_address);
pptr = PackInteger(pptr, m_windowfrom, str_windowfrom);
pptr = PackInteger(pptr, m_windowto, str_windowto);
pptr = PackCode(pptr, str_eof);

len = m_maxmessagesize;
}

// --------------------------------------------------------------------------
// Tell servers to terminate
//
// This requires the reply-to port and address and window ID's
// --------------------------------------------------------------------------

void CFractalParameters::CreateTerminate( FRbyte *pstr, int &len )
{
FRbyte *pptr = pstr;

memset(pstr, 0, m_maxmessagesize );

pptr = PackCode(pptr, str_start);
pptr = PackInteger(pptr, MSG_TERMINATE, str_type);
pptr = PackInteger(pptr, m_windowfrom, str_windowfrom);
pptr = PackInteger(pptr, m_windowto, str_windowto);
pptr = PackCode(pptr, str_eof);

len = m_maxmessagesize;
}

// --------------------------------------------------------------------------
// Query window size from server
// --------------------------------------------------------------------------

void CFractalParameters::CreateQueryWindowSize(FRbyte *pstr, int port, struct in_addr &addr, int &len)
{
FRbyte *pptr = pstr;

memset(pstr, 0, m_maxmessagesize );

pptr = PackCode(pptr, str_start);
pptr = PackInteger(pptr, MSG_QUERYWINDOWSIZE, str_type);
pptr = PackInteger(pptr, port, str_port);
pptr = PackAddress(pptr, addr, str_address);
pptr = PackInteger(pptr, m_windowfrom, str_windowfrom);
pptr = PackInteger(pptr, m_windowto, str_windowto);
pptr = PackInteger(pptr, m_windowwidth, str_windowwidth);
pptr = PackInteger(pptr, m_windowheight, str_windowheight);
pptr = PackCode(pptr, str_eof);

len = m_maxmessagesize;
}

// --------------------------------------------------------------------------
// Pack all the fractal parameters into binary format
//
// The size of this message should match the maximum message size
// --------------------------------------------------------------------------

void CFractalParameters::PackData( FRbyte *pstr, int &len)
{
FRbyte *pptr = pstr;

pptr = PackCode( pptr,  str_start);
pptr = PackInteger( pptr, m_msgtype, str_type);
pptr = PackFloat( pptr, m_escaperadius, str_escaperadius);
pptr = PackFloat( pptr, m_xcen, str_xcen);
pptr = PackFloat( pptr, m_ycen, str_ycen);
pptr = PackFloat( pptr, m_xwidth, str_xwidth);
pptr = PackFloat( pptr, m_ywidth, str_ywidth);
pptr = PackInteger( pptr, m_maxiter, str_maxiter);
pptr = PackFloat( pptr, m_angle, str_angle);
pptr = PackFloat( pptr, m_power, str_power);
pptr = PackFloat( pptr, m_banding, str_banding);
pptr = PackFloat( pptr, m_minclamp, str_minclamp);
pptr = PackInteger( pptr, m_modesmooth, str_modesmooth);
pptr = PackInteger( pptr, m_modepower, str_modepower);
pptr = PackInteger( pptr, m_texpalette, str_texpalette);
pptr = PackInteger( pptr, m_makemipmaps, str_makemipmaps);
pptr = PackInteger( pptr, m_texwidth, str_texwidth);
pptr = PackInteger( pptr, m_texheight, str_texheight);
pptr = PackInteger( pptr, m_cycleoffset, str_cycleoffset);
pptr = PackInteger( pptr, m_modeinvert, str_modeinvert);
pptr = PackInteger( pptr, m_autocycle, str_autocycle);
pptr = PackInteger( pptr, m_windowfrom, str_windowfrom);
pptr = PackInteger( pptr, m_windowto, str_windowto);
pptr = PackInteger( pptr, m_windowwidth, str_windowwidth);
pptr = PackInteger( pptr, m_windowheight, str_windowheight);

pptr = PackCode( pptr, str_eof);

len = pptr - pstr;

assert(len <= m_maxmessagesize);
}

// --------------------------------------------------------------------------
// Unpack binary data string pointed to by "pptr" and with length len
// --------------------------------------------------------------------------

void CFractalParameters::UnpackData( FRbyte *pmessage, int len)
{
int code = 0;
int changebits = 0;
FRbyte *pcur = pmessage;

m_msgtype = MSG_NONE;

while ((code != CODE_EOF) && (pcur - pmessage < m_maxmessagesize))
	{
	pcur = UnpackCode( pcur, code);

	switch (code)
		{
		case CODE_START:
		case CODE_EOF:
			break;

		case CODE_TYPE:
			pcur = UnpackInteger( pcur, m_msgtype);
			changebits |= CHANGEBIT_TYPE;
			break;

		case CODE_PORT:		
			pcur = UnpackInteger( pcur, m_port);
			changebits |= CHANGEBIT_PORT;
			break;

		case CODE_ADDRESS:
			pcur = UnpackAddress( pcur, m_addr);
			changebits |= CHANGEBIT_ADDRESS;
			break;

		case CODE_ESCAPERADIUS:
			pcur = UnpackFloat( pcur, m_escaperadius);
			changebits |= CHANGEBIT_ESCAPERADIUS;
                        break;

                case CODE_XCEN:
			pcur = UnpackFloat( pcur, m_xcen);
			changebits |= CHANGEBIT_XCEN;
                        break;

                case CODE_YCEN:
			pcur = UnpackFloat( pcur, m_ycen);
			changebits |= CHANGEBIT_YCEN;
                        break;

                case CODE_MAXITER:
			pcur = UnpackInteger( pcur, m_maxiter);
			changebits |= CHANGEBIT_MAXITER;
                        break;

                case CODE_XWIDTH:
			pcur = UnpackFloat( pcur, m_xwidth);
			changebits |= CHANGEBIT_XWIDTH;
                        break;

                case CODE_YWIDTH:
			pcur = UnpackFloat( pcur, m_ywidth);
			changebits |= CHANGEBIT_YWIDTH;
                        break;

                case CODE_ANGLE:
			pcur = UnpackFloat( pcur, m_angle);
			changebits |= CHANGEBIT_ANGLE;
                        break;

                case CODE_POWER:
			pcur = UnpackFloat( pcur, m_power);
			changebits |= CHANGEBIT_POWER;
                        break;

                case CODE_BANDING:
			pcur = UnpackFloat( pcur, m_banding);
			changebits |= CHANGEBIT_BANDING;
                        break;

                case CODE_MODESMOOTH:
			pcur = UnpackInteger( pcur, m_modesmooth);
			changebits |= CHANGEBIT_MODESMOOTH;
                        break;

                case CODE_MODEPOWER:
			pcur = UnpackInteger( pcur, m_modepower);
			changebits |= CHANGEBIT_MODEPOWER;
                        break;

                case CODE_TEXPALETTE:
			pcur = UnpackInteger( pcur, m_texpalette);
			changebits |= CHANGEBIT_TEXPALETTE;
                        break;

                case CODE_MAKEMIPMAPS:
			pcur = UnpackInteger( pcur, m_makemipmaps);
			changebits |= CHANGEBIT_MAKEMIPMAPS;
                        break;

		case CODE_MINCLAMP:
			pcur = UnpackFloat( pcur, m_minclamp);	
			changebits |= CHANGEBIT_MINCLAMP;
			break;

		case CODE_TEXWIDTH:
			pcur = UnpackInteger( pcur, m_texwidth);
			changebits |= CHANGEBIT_TEXWIDTH;
			break;

		case CODE_TEXHEIGHT:
			pcur = UnpackInteger( pcur, m_texheight);
			changebits |= CHANGEBIT_TEXHEIGHT;
			break;

		case CODE_CYCLEOFFSET:
			pcur = UnpackInteger( pcur, m_cycleoffset);
			changebits |= CHANGEBIT_CYCLEOFFSET;
			break;

		case CODE_MODEINVERT:
			pcur = UnpackInteger( pcur, m_modeinvert);
			changebits |= CHANGEBIT_MODEINVERT;
			break;
			
		case CODE_AUTOCYCLE:
			pcur = UnpackInteger( pcur, m_autocycle);
			changebits |= CHANGEBIT_AUTOCYCLE;
			break;

		case CODE_WINDOWFROM:
			pcur = UnpackInteger( pcur, m_windowfrom);
			changebits |= CHANGEBIT_WINDOWFROM;
			break;

		case CODE_WINDOWTO:
			pcur = UnpackInteger( pcur, m_windowto);
			changebits |= CHANGEBIT_WINDOWTO;
			break;

		case CODE_WINDOWWIDTH:		
			pcur = UnpackInteger( pcur, m_windowwidth);
			changebits |= CHANGEBIT_WINDOWWIDTH;
			break;
	
		case CODE_WINDOWHEIGHT:
			pcur = UnpackInteger( pcur, m_windowheight);
			changebits |= CHANGEBIT_WINDOWHEIGHT;
			break;

		default:
			cout << "Error: Unrecognised code " << code << endl;
			break;
		}
	}

m_changebits |= changebits;
}

// --------------------------------------------------------------------------
// Merge parameters together
// --------------------------------------------------------------------------

void CFractalParameters::Merge( CFractalParameters &src)
{
int changebits = src.m_changebits;

if (changebits & CODE_ESCAPERADIUS)
	{
	m_escaperadius = src.m_escaperadius;
	}

if (changebits & CODE_XCEN)
	{
	m_xcen = src.m_xcen;
	}

if (changebits & CODE_YCEN)
	{
	m_ycen = src.m_ycen;
	}

if (changebits & CODE_XWIDTH)
	{
	m_xwidth = src.m_xwidth;
	}

if (changebits & CODE_YWIDTH)
	{
	m_ywidth = src.m_ywidth;
	}

if (changebits & CODE_MAXITER)
	{
	m_maxiter = src.m_maxiter;
	}

if (changebits & CODE_ANGLE)
	{
	m_angle = src.m_angle;
	}

if (changebits & CODE_POWER)
	{
	m_power = src.m_power;
	}

if (changebits & CODE_BANDING)
	{
	m_banding = src.m_banding;
	}

if (changebits & CODE_MINCLAMP)
	{
	m_minclamp = src.m_minclamp;
	}

if (changebits & CODE_MODESMOOTH)
	{
	m_modesmooth = src.m_modesmooth;
	}

if (changebits & CODE_MODEPOWER)
	{
	m_modepower = src.m_modepower;
	}

if (changebits & CODE_TEXPALETTE)
	{
	m_texpalette = src.m_texpalette;
	}

if (changebits & CODE_MAKEMIPMAPS)
	{
	m_makemipmaps = src.m_makemipmaps;
	}

if (changebits & CODE_TEXWIDTH)
	{
	m_texwidth = src.m_texwidth;
	}

if (changebits & CODE_TEXHEIGHT)
	{
	m_texheight = src.m_texheight;
	}

if (changebits & CODE_AUTOCYCLE)	
	{
	m_autocycle = src.m_autocycle;
	}

if (changebits & CODE_MODEINVERT)
	{
	m_modeinvert = src.m_modeinvert;
	}

if (changebits & CODE_CYCLEOFFSET)
	{
	m_cycleoffset = src.m_cycleoffset;
	}

if (changebits & CODE_WINDOWFROM)
	{
	m_windowfrom = src.m_windowfrom;
	}

if (changebits & CODE_WINDOWTO)
	{
	m_windowfrom = src.m_windowto;
	}

if (changebits & CODE_PORT)
	{
	m_port = src.m_port;
	}

if (changebits & CODE_ADDRESS)
	{
	m_addr = src.m_addr;
	}

if (changebits & CODE_WINDOWWIDTH)
        {
        m_windowwidth = src.m_windowwidth;
        }

if (changebits & CODE_WINDOWHEIGHT)
        {
        m_windowheight = src.m_windowheight;
        }
}

// --------------------------------------------------------------------------
// Display information as data
// --------------------------------------------------------------------------

void CFractalParameters::DisplayAscii(void)
{
cout << "{fractal" << endl;
cout << "\t{escaperadius " << m_escaperadius << " }" << endl;
cout << "\t{xcen " << m_xcen << " }" << endl;
cout << "\t{ycen " << m_ycen << " }" << endl;
cout << "\t{xwidth " << m_xwidth << " }" << endl;
cout << "\t{ywidth " << m_ywidth << " }" << endl;
cout << "\t{maxiter " << m_maxiter << " }" << endl;
cout << "\t{angle " << m_angle << " }" << endl;
cout << "\t{power " << m_power << " }" << endl;
cout << "\t{banding " << m_banding << " }" << endl;
cout << "\t{modesmooth " << m_modesmooth << " }" << endl;

cout << "\t{modepower " << m_modepower << " }" << endl;
cout << "\t{texpalette " << m_texpalette << " }" << endl;
cout << "\t{makemipmaps " << m_makemipmaps << " }" << endl;
cout << "\t{minclamp " << m_minclamp << " }" << endl;
cout << "\t{texwidth " << m_texwidth << " }" << endl;
cout << "\t{texheight " << m_texheight << " }" << endl;
cout << "\t{cycleoffset " << m_cycleoffset << " }" << endl;
cout << "\t{modeinvert " << m_modeinvert << " }" << endl;
cout << "\t{autocycle " << m_autocycle << " }" << endl;
cout << "}" << endl;
}

// --------------------------------------------------------------------------
// Calculate the parameters for a secondary display window. The window may
// simply duplicate the current display or provide a view from one side of 
// the current display
// --------------------------------------------------------------------------

void CFractalParameters::CalculateNodeParameters( CFractalParameters &src, CNetworkNode &data)
{
// Copy constant terms
m_escaperadius = src.m_escaperadius;
m_maxiter = src.m_maxiter;
m_power = src.m_power;
m_banding = src.m_banding;
m_modesmooth = src.m_modesmooth;
m_modepower = src.m_modepower;
m_texpalette = src.m_texpalette;
m_minclamp = src.m_minclamp;
m_texwidth = src.m_texwidth;
m_texheight = src.m_texheight;
m_cycleoffset = src.m_cycleoffset;
m_modeinvert = src.m_modeinvert;
m_autocycle = src.m_autocycle;
m_makemipmaps = src.m_makemipmaps;
m_windowwidth = src.m_windowwidth;
m_windowheight = src.m_windowheight;

// Rotation angle only needs to be offset
m_angle = src.m_angle + data.m_offheading;

CalculateCentrePoint(src, data, src.m_xwidth, src.m_ywidth);

m_changebits |= CHANGEBIT_ALL;
}

// --------------------------------------------------------------------------
// Calculate scale in width and height
// --------------------------------------------------------------------------

void CFractalParameters::CalculateCentrePoint(CFractalParameters &src, 
				CNetworkNode &data, float fw, float fh)
{
m_xwidth = fw * data.m_width;
m_ywidth = fh * data.m_height;

// Calculate the rotation angle
float fsa, fca;
sincosf( m_angle, &fsa, &fca);

// Calculate the offset to the new centre point without rotation
float fdx = fw * data.m_offx;
float fdy = fh * data.m_offy / data.m_aspect;

// Calculate the new centre point factoring in rotation
m_xcen = src.m_xcen + fdx * fca - fdy * fsa;
m_ycen = src.m_ycen + fdx * fsa + fdy * fca;

m_changebits |= CHANGEBIT_XWIDTH|CHANGEBIT_YWIDTH|CHANGEBIT_XCEN|CHANGEBIT_YCEN;
}

// --------------------------------------------------------------------------
// For replay mode, perform linear interpolation between two sets of
// parameters.
// --------------------------------------------------------------------------

#define BLEND(X, S1, S2)    X = S1.X * fnval + S2.X * fval;

void CFractalParameters::Mix(CFractalParameters &s1, CFractalParameters &s2, float fval)
{
float fnval = 1.0f - fval;

BLEND(m_escaperadius, s1, s2);
BLEND(m_xcen, s1, s2);
BLEND(m_ycen, s1, s2);
BLEND(m_xwidth, s1, s2);
BLEND(m_ywidth, s1, s2);
BLEND(m_maxiter, s1, s2);
BLEND(m_angle, s1, s2);
BLEND(m_power, s1, s2);
BLEND(m_banding, s1, s2);
BLEND(m_minclamp, s1, s2);

m_modesmooth = s1.m_modesmooth;
m_modepower = s1.m_modepower;
m_texpalette = s1.m_texpalette;
m_modeinvert = s1.m_modeinvert;
m_cycleoffset = s1.m_cycleoffset;
m_autocycle = s1.m_autocycle;
m_windowfrom = s1.m_windowfrom;
m_windowto = s1.m_windowto;
m_makemipmaps = s1.m_makemipmaps;
m_windowwidth = s1.m_windowwidth;
m_windowheight = s1.m_windowheight;

BLEND( m_texwidth, s1, s2);
BLEND( m_texheight, s1, s2);

m_changebits |= CHANGEBIT_ALL;
}

