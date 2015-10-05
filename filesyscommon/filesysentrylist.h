// ---------------------------------------------------------------------------
// File:    filesysentrylist.h
// 
// Purpose: Source file for managing the list of super tokens
//
// Author:  Michael S. A. Robb
// 
// Date:    Fri Apr 20 00:02:16 2012
// ----------------------------------------------------------------------------

#ifndef _FILESYSENTRYLIST_H_
#define _FILESYSENTRYLIST_H_

class CFileSysEntryList : public CFileSysEntryListIO
{
// ----- Class members ------------------------------------------------------
public:
map <int, CFileSysEntry *> m_tokenlist;
map <string, int > m_stringlist;

// ----- Constructor and destructor -----------------------------------------

CFileSysEntryList( void )
	{
	Init();
	}

// ----- Functions ----------------------------------------------------------

void Init();

void Deallocate( void );

// ----- These are the two core functions -----------------------------------

CFileSysEntry *FindEntry( int tokenid );
int FindEntryIndex( string &strmatch );

// ----- The following functions depend on the two above --------------------

int IdentifyDataType( string &buffer );

string *GetReadRoutine( int tokenid, int binarymode );
string *GetWriteRoutine( int tokenid, int binarymode );

string *GetReadBasicRoutine( int tokenid, int binarymode );
string *GetWriteBasicRoutine( int tokenid, int binarymode );
string *GetClassName( int tokenid );
string *GetSuffix( int tokenid );
string *GetTokenString( int tokenid );
};

#endif
