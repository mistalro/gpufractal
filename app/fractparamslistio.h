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

#ifndef _CFRACTALPARAMSLISTIO_H_
#define _CFRACTALPARAMSLISTIO_H_

// -------------------------------------------------------------------------
// Change flags (dirty flags)
// -------------------------------------------------------------------------

enum CFractalParamsListIOChangeFlags
	{
	CFRACTALPARAMSLISTIO_CHANGEFLAG_LISTNUM = 0x0001,
	CFRACTALPARAMSLISTIO_CHANGEFLAG_GROUP,
	};

#define CFRACTALPARAMSLISTIO_CHANGEFLAG_NUM 2

// --------------------------------------------------------------------------- 
// Main class definition for CFractalParamsListData
// --------------------------------------------------------------------------- 

class CFractalParamsListData : public vector <CFractalParameters>
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
	vector <CFractalParameters>::clear();

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
