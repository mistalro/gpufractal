// ---------------------------------------------------------------------------
// File:    fractalparamslistio.h
// 
// Purpose: Header file for reading and writing data for class
//	    CFractalParamsListIO
//
// Author:  Autofile generator
// 
// Date:    Wed Jul 22 19:59:20 2015
// ----------------------------------------------------------------------------

#ifndef _CFRACTALPARAMSLISTIO_H_
#define _CFRACTALPARAMSLISTIO_H_

// UseChangeFlags = 0
// UseGetSetters = 1
// --------------------------------------------------------------------------- 
// Main class definition for CFractalParamsListData
// --------------------------------------------------------------------------- 

class CFractalParamsListData : public vector <CFractalParametersIO *>
{
// ----- Class members ------------------------------------------------------- 
public:

// ----- Constructor and destructor ------------------------------------------ 

CFractalParamsListData( void )
	{
	CFractalParamsListData::Init();
	}

~CFractalParamsListData( void )
	{
	CFractalParamsListData::Deallocate();
	}

// ----- Functions and Procedures -------------------------------------------- 

void Init( void )
	{
	}

void Deallocate()
	{
	vector <CFractalParametersIO *>::clear();

	Init();
	}
};

// ---------------------------------------------------------------------
// File IO class for ASCII data
// ---------------------------------------------------------------------

class CFractalParamsListDataAsciiIO : virtual public CVirtualFileSystemGlobalAscii,
				virtual public CFractalParamsListData
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

class CFractalParamsListIO: virtual public CFractalParamsListDataAsciiIO

{
// ----- Constructor and Destructor ----------------------------

public:
CFractalParamsListIO( void )
	{
	Init();
	}

// ----- Functions ---------------------------------------------

void Init( void )
	{
	CFractalParamsListData::Init();
	}
};

#endif	// _CFRACTALPARAMSLISTIO_H_
