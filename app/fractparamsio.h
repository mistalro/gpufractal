// ---------------------------------------------------------------------------
// File:    fractparamsio.h
// 
// Purpose: Header file for reading and writing data for class
//	    CFractalParamsIO
//
// Author:  Autofile generator
// 
// Date:    Wed Jul 22 19:59:20 2015
// ----------------------------------------------------------------------------

#ifndef _CFRACTALPARAMSIO_H_
#define _CFRACTALPARAMSIO_H_

// UseChangeFlags = 0
// UseGetSetters = 0
// --------------------------------------------------------------------------- 
// Main class definition for CFractalParamsData
// --------------------------------------------------------------------------- 

class CFractalParamsData
{
// ----- Class members ------------------------------------------------------- 
public:

float	m_escaperadius;		// Escape radius
float	m_xcen;		// X-Center
float	m_ycen;		// Y-Center
float	m_xwidth;		// X-Width
float	m_ywidth;		// Y-Width
int	m_maxiter;		// Max Iterations
float	m_angle;		// Angle
float	m_power;		// Power
float	m_banding;		// Banding
float	m_minclamp;		// Minimum clamping
int	m_modesmooth;		// Smoothing mode
int	m_modepower;		// Mode power
int	m_texpalette;		// Texture palette index
int	m_makemipmaps;		// Make mipmaps
int	m_texwidth;		// Texture width
int	m_texheight;		// Texture height
int	m_autocycle;		// Automatic color cycling
int	m_modeinvert;		// Invert (or flip) texture lookup
int	m_cycleoffset;		// Offset for color cycling

// ----- Constructor and destructor ------------------------------------------ 

CFractalParamsData( void )
	{
	CFractalParamsData::Init();
	}

~CFractalParamsData( void )
	{
	CFractalParamsData::Deallocate();
	}

// ----- Functions and Procedures -------------------------------------------- 

void Init( void )
	{
	m_escaperadius = 0.0f;
	m_xcen = 0.0f;
	m_ycen = 0.0f;
	m_xwidth = 0.0f;
	m_ywidth = 0.0f;
	m_maxiter = 0;
	m_angle = 0.0f;
	m_power = 0.0f;
	m_banding = 0.0f;
	m_minclamp = 0.0f;
	m_modesmooth = 0;
	m_modepower = 0;
	m_texpalette = 0;
	m_makemipmaps = 0;
	m_texwidth = 0;
	m_texheight = 0;
	m_autocycle = 0;
	m_modeinvert = 0;
	m_cycleoffset = 0;
	}

void Deallocate()
	{
	Init();
	}
};

// ---------------------------------------------------------------------
// File IO class for ASCII data
// ---------------------------------------------------------------------

class CFractalParamsDataAsciiIO : virtual public CVirtualFileSystemGlobalAscii,
				virtual public CFractalParamsData
{
public:
// ----- File reading and writing -------------------------------------------

using CVirtualFileSystemGlobalAscii::ReadFile;

int ReadFile( ifstream &stream );
int ReadFileInternal( ifstream &stream );

using CVirtualFileSystemGlobalAscii::WriteFile;

int WriteFile( ofstream &stream, int depth );
int WriteFile( ofstream &stream, int depth, const char *pstr );
};

// ---------------------------------------------------------------------
// Combined IO class for Ascii and Binary data
// --------------------------------------------------------------------

class CFractalParamsIO: virtual public CFractalParamsDataAsciiIO

{
// ----- Constructor and Destructor ----------------------------

public:
CFractalParamsIO( void )
	{
	Init();
	}

// ----- Functions ---------------------------------------------

void Init( void )
	{
	CFractalParamsData::Init();
	}
};

#endif	// _CFRACTALPARAMSIO_H_
