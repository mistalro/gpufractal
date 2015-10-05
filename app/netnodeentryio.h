// ---------------------------------------------------------------------------
// File:    netnodeentryio.h
// 
// Purpose: Header file for reading and writing data for class
//	    CNodeDataIO
//
// Author:  Autofile generator
// 
// Date:    Mon Jul 27 22:23:20 2015
// ----------------------------------------------------------------------------

#ifndef _CNODEDATAIO_H_
#define _CNODEDATAIO_H_

// UseChangeFlags = 0
// UseGetSetters = 0
// --------------------------------------------------------------------------- 
// Main class definition for CNetNodeEntryData
// --------------------------------------------------------------------------- 

class CNetNodeEntryData
{
// ----- Class members ------------------------------------------------------- 
public:

string	m_hostname;		// Hostname
int	m_port;		// Port
int	m_windowid;		// Window ID
float	m_offx;		// Offset in X
float	m_offy;		// Offset in Y
float	m_width;		// Width
float	m_height;		// Height
float	m_offheading;		// Offset in Heading
float	m_aspect;		// Aspect ratio for calculations

// ----- Constructor and destructor ------------------------------------------ 

CNetNodeEntryData( void )
	{
	CNetNodeEntryData::Init();
	}

~CNetNodeEntryData( void )
	{
	CNetNodeEntryData::Deallocate();
	}

// ----- Functions and Procedures -------------------------------------------- 

void Init( void )
	{
	m_hostname = "";
	m_port = 0;
	m_windowid = 0;
	m_offx = 0.0f;
	m_offy = 0.0f;
	m_width = 0.0f;
	m_height = 0.0f;
	m_offheading = 0.0f;
	m_aspect = 0.0f;
	}

void Deallocate()
	{
	m_hostname.clear();

	Init();
	}
};

// ---------------------------------------------------------------------
// File IO class for ASCII data
// ---------------------------------------------------------------------

class CNetNodeEntryDataAsciiIO : virtual public CVirtualFileSystemGlobalAscii,
				virtual public CNetNodeEntryData
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

class CNodeDataIO: virtual public CNetNodeEntryDataAsciiIO

{
// ----- Constructor and Destructor ----------------------------

public:
CNodeDataIO( void )
	{
	Init();
	}

// ----- Functions ---------------------------------------------

void Init( void )
	{
	CNetNodeEntryData::Init();
	}
};

#endif	// _CNODEDATAIO_H_
