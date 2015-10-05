// ---------------------------------------------------------------------------
// File:    filesysentrylistio.h
// 
// Purpose: Header file for reading and writing data for class
//	    CFileSysEntryListIO
//
// Author:  Autofile generator
// 
// Date:    Mon May 28 15:49:34 2012
// ----------------------------------------------------------------------------

#ifndef _CFILESYSENTRYLISTIO_H_
#define _CFILESYSENTRYLISTIO_H_

// -------------------------------------------------------------------------
// Change flags (dirty flags)
// -------------------------------------------------------------------------

enum CFileSysEntryListIOChangeFlags
	{
	CFILESYSENTRYLISTIO_CHANGEFLAG_LISTNUM = 0x0001,
	CFILESYSENTRYLISTIO_CHANGEFLAG_LISTDATA,
	};

#define CFILESYSENTRYLISTIO_CHANGEFLAG_NUM 2

// --------------------------------------------------------------------------- 
// Main class definition for CFileSysEntryListData
// --------------------------------------------------------------------------- 

class CFileSysEntryListData : public vector <CFileSysEntry>


{
// ----- Class members ------------------------------------------------------- 
public:


// ----- Constructor and destructor ------------------------------------------ 

CFileSysEntryListData( void )
	{
	CFileSysEntryListData::Init();
	}

~CFileSysEntryListData( void )
	{
	CFileSysEntryListData::Deallocate();
	}

// ----- Functions and Procedures -------------------------------------------- 

void Init( void )
	{
	}

void Deallocate()
	{
	vector <CFileSysEntry>::clear();

	Init();
	}
};

// ---------------------------------------------------------------------
// File IO class for ASCII data
// ---------------------------------------------------------------------

class CFileSysEntryListDataAsciiIO : virtual public CVirtualFileSystemAscii,
				virtual public CFileSysEntryListData
{
public:
// ----- File reading and writing -------------------------------------------

using CVirtualFileSystemAscii::ReadFile;

int ReadFile( ifstream &stream );
int ReadFileInternal( ifstream &stream );

using CVirtualFileSystemAscii::WriteFile;

int WriteFile( ofstream &stream, int depth );
int WriteFile( ofstream &stream, int depth, const char *pstr );
};

// ---------------------------------------------------------------------
// Combined IO class for Ascii and Binary data
// --------------------------------------------------------------------

class CFileSysEntryListIO : virtual public CFileSysEntryListDataAsciiIO
{
// ----- Constructor and Destructor ----------------------------

public:
CFileSysEntryListIO( void )
	{
	Init();
	}

// ----- Functions ---------------------------------------------

void Init( void )
	{
	CFileSysEntryListData::Init();
	}
};

#endif	// _CFILESYSENTRYLISTIO_H_
