// ---------------------------------------------------------------------------
// File:    netnodeentrylistio.h
// 
// Purpose: Header file for reading and writing data for class
//	    CNetNodeEntryListIO
//
// Author:  Autofile generator
// 
// Date:    Mon Jul 27 22:23:20 2015
// ----------------------------------------------------------------------------

#ifndef _CNETNODEENTRYLISTIO_H_
#define _CNETNODEENTRYLISTIO_H_

// UseChangeFlags = 0
// UseGetSetters = 1
// --------------------------------------------------------------------------- 
// Main class definition for CNetNodeEntryListData
// --------------------------------------------------------------------------- 

class CNetNodeEntryListData : public vector <CNetworkNode *>
{
// ----- Class members ------------------------------------------------------- 
public:

// ----- Constructor and destructor ------------------------------------------ 

CNetNodeEntryListData( void )
	{
	CNetNodeEntryListData::Init();
	}

~CNetNodeEntryListData( void )
	{
	CNetNodeEntryListData::Deallocate();
	}

// ----- Functions and Procedures -------------------------------------------- 

void Init( void )
	{
	}

void Deallocate()
	{
	vector <CNetworkNode *>::clear();

	Init();
	}
};

// ---------------------------------------------------------------------
// File IO class for ASCII data
// ---------------------------------------------------------------------

class CNetNodeEntryListDataAsciiIO : virtual public CVirtualFileSystemGlobalAscii,
				virtual public CNetNodeEntryListData
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

class CNetNodeEntryListIO: virtual public CNetNodeEntryListDataAsciiIO

{
// ----- Constructor and Destructor ----------------------------

public:
CNetNodeEntryListIO( void )
	{
	Init();
	}

// ----- Functions ---------------------------------------------

void Init( void )
	{
	CNetNodeEntryListData::Init();
	}
};

#endif	// _CNETNODEENTRYLISTIO_H_
