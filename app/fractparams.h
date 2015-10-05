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

#ifndef _FRACTALPARAMS_H_
#define _FRACTALPARAMS_H_

typedef enum
{
MANDELBROT_PN = 0x01,  // Generic power equation
MANDELBROT_P2 = 0x02,  // Power of 2
MANDELBROT_P3 = 0x04  // Power of 3
} MandelbrotMode;

// -------------------------------------------------------------------------
// Change bit flags for each parameter
// -------------------------------------------------------------------------

typedef enum
{
CHANGEBIT_NONE        = 0x00000,
CHANGEBIT_ESCAPERADIUS= 0x00001,
CHANGEBIT_XCEN        = 0x00002,
CHANGEBIT_YCEN        = 0x00004,
CHANGEBIT_XWIDTH      = 0x00008,
CHANGEBIT_YWIDTH      = 0x00010,
CHANGEBIT_MAXITER     = 0x00020,
CHANGEBIT_ANGLE       = 0x00040,
CHANGEBIT_POWER       = 0x00080,
CHANGEBIT_BANDING     = 0x00100,
CHANGEBIT_MINCLAMP    = 0x00200,
CHANGEBIT_MODESMOOTH  = 0x00400,
CHANGEBIT_MODEPOWER   = 0x00800,
CHANGEBIT_MAKEMIPMAPS = 0x01000,
CHANGEBIT_TEXPALETTE  = 0x02000,
CHANGEBIT_TEXWIDTH    = 0x04000,
CHANGEBIT_TEXHEIGHT   = 0x08000,
CHANGEBIT_CYCLEOFFSET = 0x10000,
CHANGEBIT_MODEINVERT = 0x020000,
CHANGEBIT_AUTOCYCLE  = 0x040000,
CHANGEBIT_WINDOWFROM = 0x080000,
CHANGEBIT_WINDOWTO   = 0x100000,
CHANGEBIT_PORT       = 0x200000,
CHANGEBIT_ADDRESS    = 0x400000,
CHANGEBIT_TYPE       = 0x800000,
CHANGEBIT_WINDOWWIDTH  = 0x1000000,
CHANGEBIT_WINDOWHEIGHT = 0x2000000,
CHANGEBIT_ALL        = 0xFFFFFF
} ChangeBits;

typedef unsigned int ChangeFlags;

// --------------------------------------------------------------------------
// Types of message
// --------------------------------------------------------------------------

typedef enum
{
MSG_NONE = 0x00,	// None or Unknown
MSG_PARAMS = 0x01,	// Parameters sent
MSG_REQPARAM = 0x02, 	// Request for parameters
MSG_REQPARAMREPLY = 0x03, // Request for parameters
MSG_COPYPARAM = 0x04,	// Request for copy of parameters
MSG_PING = 0x04,	// Ping
MSG_PINGREPLY = 0x05,   // Ping reply
MSG_TERMINATE = 0x06,	// Kill server
MSG_QUERYWINDOWSIZE = 0x07, // Query window size
MSG_QUERYWINDOWSIZEREPLY = 0x08 // Query window size reply
} MessageType;

// --------------------------------------------------------------------------
// Fractal parameters
// --------------------------------------------------------------------------

class CFractalParameters : public CFractalParamsIO
{
public:
ChangeFlags m_changebits;	// Which fields have been changed by user
int	    m_msgtype;		// Request for parameters to be sent back
int	    m_port;		// Port for sending back to server
struct in_addr  m_addr;		// Address to send data to
int       m_cycleoffset;	// Cycle offset
int	  m_windowfrom;		// Message originator ID
int	  m_windowto;		// Message destination ID
int	  m_windowwidth;	// Window width
int	  m_windowheight;	// Window height
int       m_maxmessagesize;	// Maximum message size

void ClearChangeBits(void)
	{
	m_changebits = CHANGEBIT_NONE;
	}

CFractalParameters(void)
        {
        Reset();
        }

~CFractalParameters(void)
        {
        }

void Reset(void);
void DisplayAscii(void);

void Mix(CFractalParameters &s1, CFractalParameters &s2, float fval);
void CalculateNodeParameters( CFractalParameters &src, CNetworkNode &data);
void CalculateCentrePoint(CFractalParameters &src, CNetworkNode &data, float fx, float fy);

void Merge( CFractalParameters &src);
void HexDump( FRbyte *pptr, int len);

// ----- Networking routines -----

void CreateRequest( FRbyte *pstr, int port, struct in_addr &addr, int &len);
void CreatePing( FRbyte *pstr, int port, struct in_addr &addr, int &len);
void CreateTerminate( FRbyte *pstr, int &len);

void CreateQueryWindowSize(FRbyte *pstr, int port, struct in_addr &addr, int &len);

// --------------------------------------------------------------------------
// Messages are packed to a maximum size, so return size of the largest
// message. This is the parameters field
//
// The magic numbers are as follows:
//
// MAX_FLOATS x (  floats (4 bytes) + tags +
// MAX_ITEGERS x ( integers (4 bytes) + tags +
// 1 x start tag +
// 1 x finish tag
// --------------------------------------------------------------------------

#define MAKE_CHCODE(HI,LO)              ((HI << 8) + LO)
#define MAKE_CODE(X)                    ((int)X)

#define MAX_INTEGER_BYTES 4	// How many bytes of each integer to save
#define MAX_FLOAT 9
#define MAX_INTEGER 15
#define MAX_TAGSIZE 2

inline int GetMaxMessageSize(void)
	{
	return ((sizeof(float)+MAX_TAGSIZE)*MAX_FLOAT 	// Floats
	  + (MAX_INTEGER_BYTES+MAX_TAGSIZE)*MAX_INTEGER  // Integers
	  + MAX_TAGSIZE*2);	// Start and end tags
	}


void PackData( FRbyte *pstr, int &len );
void UnpackData( FRbyte *str, int len );

inline FRbyte *PackAddress( FRbyte *pptr, struct in_addr &addr, const char *pcode)
	{
	pptr = PackCode(pptr, pcode);

	memcpy(pptr, &addr, sizeof(in_addr) );

	return pptr + sizeof(in_addr);
	}

inline FRbyte *PackInteger( FRbyte *pptr, int value, const char *pcode)
	{
	pptr = PackCode(pptr, pcode);

	for (int idx = 0; idx < MAX_INTEGER_BYTES; idx++)
       		{
        	pptr[idx] = value >> (idx*8) & 0xFF;
        	}

	return pptr + MAX_INTEGER_BYTES;
	}

inline FRbyte *PackFloat( FRbyte *pptr, float value, const char *pcode)
	{
	pptr = PackCode(pptr, pcode);

	memcpy( pptr, &value, sizeof(float) );

	return pptr + sizeof(float);
	}

inline FRbyte *PackDouble( FRbyte *pptr, double value, const char *pcode)
        {
        pptr = PackCode(pptr, pcode);

        memcpy( pptr, &value, sizeof(double) );

        return pptr + sizeof(double);
        }

inline FRbyte *PackCode( FRbyte *pptr, const char *pcode)
	{
	pptr[0] = pcode[0];
	pptr[1] = pcode[1];

	return pptr+2;
	}

inline FRbyte *UnpackCode( FRbyte *pptr, int &code)
	{
	FRbyte hi = *pptr++;
	assert( hi >= 'a' && hi <= 'z');

	FRbyte lo = *pptr++;
	assert( lo >= 'a' && lo <= 'z');

	code = MAKE_CHCODE(hi, lo);

	return pptr;
	}

inline FRbyte *UnpackAddress( FRbyte *pptr, struct in_addr &addr)
        {
        memcpy(&addr, pptr, sizeof(in_addr) );

        return pptr + sizeof(in_addr);
        }

inline FRbyte *UnpackInteger( FRbyte *pptr, int &value)
	{
	value = 0;

	for (int idx = 0; idx < MAX_INTEGER_BYTES; idx++)
       		{
        	value |= pptr[idx] << (idx*8);
        	}

	return pptr + MAX_INTEGER_BYTES;
	}

inline FRbyte *UnpackFloat( FRbyte *pptr, float &value)
	{
	memcpy( &value, pptr, sizeof(float));

	return pptr + sizeof(float);
	}

inline FRbyte *UnpackDouble( FRbyte *pptr, float &value)
	{
	memcpy( &value, pptr, sizeof(double));

	return pptr + sizeof(double);
	}
};

#endif	 // _FRACTALPARAMS_H_
