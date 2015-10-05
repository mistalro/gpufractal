// --------------------------------------------------------------------------
// File:    autoentry.cpp
//
// Purpose: Data entry
//
// Author:  Michael S. A. Robb
//
// Date:    25th September 2009
// --------------------------------------------------------------------------

#ifdef _WINDOWS_
#include "stdafx.h"
#endif

#include "filesyscommon.h"

using namespace std;

//#define DEBUG

// --------------------------------------------------------------------------
// List of known file system types
// --------------------------------------------------------------------------

static CFileSysEntry supertoken_list[] =
{
#include "filesysmisc.h"	
#include "filesysbool.h"
#include "filesysint.h"
#include "filesysfloat.h"
#include "filesysdouble.h"
};

static int supertoken_num = sizeof(supertoken_list)/sizeof(CFileSysEntry);

// --------------------------------------------------------------------------
// Initializer
// --------------------------------------------------------------------------

void CFileSysEntryList::Init( void )
{
CFileSysEntry *pentry;

for ( int pn = 0; pn < supertoken_num; pn++ )
	{
	pentry = supertoken_list +pn;

	m_tokenlist[ pentry->m_tokenid] = pentry;
	m_stringlist[  pentry->m_keyword] = pn;
	}
}

// --------------------------------------------------------------------------
// Utility finder function
// --------------------------------------------------------------------------

CFileSysEntry *CFileSysEntryList::FindEntry( int tokenid )
{
map <int, CFileSysEntry*>::iterator it;

if ( (it = m_tokenlist.find(tokenid) ) != m_tokenlist.end() )
	{
	return( it->second );
	}
else
	{
	return( NULL );
	}
}

// --------------------------------------------------------------------------
// Utility finder function
// --------------------------------------------------------------------------

int CFileSysEntryList::FindEntryIndex( string &strmatch )
{
map <string, int>::iterator it;

it = m_stringlist.find( strmatch);

if ( (it = m_stringlist.find(strmatch)) != m_stringlist.end() )
	{
	return( it->second );
	}
else
	{
	return( TYPE_UNKNOWN );
	}
}

// ==========================================================================
// The following functions depend on the two above
// ==========================================================================

// --------------------------------------------------------------------------
// Function to identify the data type
// --------------------------------------------------------------------------

int CFileSysEntryList::IdentifyDataType( string &buffer )
{
int index;

#ifdef DEBUG
cout << "DataType = <" << buffer << ">\n";
#endif

index = FindEntryIndex( buffer );

if ( index == -1 )
	{
#ifdef DEBUG
cout << "Unknown\n";
#endif
	return( TYPE_UNKNOWN );
	}
else
	{
#ifdef DEBUG
cout << "Token ID =" << supertoken_list[index].m_tokenid << endl;
#endif
	return( supertoken_list[index].m_tokenid );
	}
}

// --------------------------------------------------------------------------
// Function to identify the read routine
// --------------------------------------------------------------------------

string *CFileSysEntryList::GetReadBasicRoutine( int tokenid, int binarymode )
{
CFileSysEntry *pentry;
string *presult;

pentry = FindEntry( tokenid );

if ( pentry )
        {
        if ( binarymode )
                {
                presult = &pentry->m_readbinaryfunc;
                }
        else
                {
                presult = &pentry->m_readbasicfunc;
                }
        }
else
        {
#ifdef DEBUG
        cout << "Error - No read routine found for tokenid <" << tokenid << ">\n";
#endif
        presult = NULL;
        }

return( presult );
}

string *CFileSysEntryList::GetReadRoutine( int tokenid, int binarymode )
{
CFileSysEntry *pentry;
string *presult;

pentry = FindEntry( tokenid );

if ( pentry )
	{
	if ( binarymode )
		{
		presult = &pentry->m_readbinaryfunc;
		}
	else
		{
		presult = &pentry->m_readfunc;
		}
	}
else
	{
#ifdef DEBUG
	cout << "Error - No read routine found for tokenid <" << tokenid << ">\n";
#endif
	presult = NULL;
	}

return( presult );
}

// --------------------------------------------------------------------------
// Function to identify the write routine
// --------------------------------------------------------------------------

string *CFileSysEntryList::GetWriteBasicRoutine( int tokenid, int binarymode )
{
CFileSysEntry *pentry;
string *presult;

pentry = FindEntry( tokenid );

if ( pentry )
        {
        if ( binarymode )
                {
                presult = &pentry->m_writebinaryfunc;
                }
        else
                {
                presult = &pentry->m_writebasicfunc;
                }
#ifdef DEBUG
	cout << "GetWriteBasicRoutine: tokenid = " << tokenid << ", binarymode = " << binarymode << "|" << present << "|" << endl;
#endif
        }
else
        {
#ifdef DEBUG
        cout << "Error - No write routine found for tokenid <" << tokenid << ">\n";
#endif
        presult = NULL;
        }

return( presult );
}

string *CFileSysEntryList::GetWriteRoutine( int tokenid, int binarymode )
{
CFileSysEntry *pentry;
string *presult;

pentry = FindEntry( tokenid );

if ( pentry )
        {
	if ( binarymode )
		{
		presult = &pentry->m_writebinaryfunc;
		}
	else
		{
        	presult = &pentry->m_writefunc;
		}
        }
else
	{
#ifdef DEBUG
	cout << "Error - No write routine found for tokenid <" << tokenid << ">\n";
#endif
	presult = NULL;
	}

return( presult );
}

// --------------------------------------------------------------------------
// Function to identify the class name
// --------------------------------------------------------------------------

string *CFileSysEntryList::GetClassName( int tokenid )
{
CFileSysEntry *pentry;

#ifdef DEBUG
cout << "Looking for token id = " << tokenid << endl;
#endif

pentry = FindEntry( tokenid );

if ( pentry )
        {
        return( &pentry->m_classname );
        }
else
	{
#ifdef DEBUG
	cout << "Error - No class name found for tokenid <" << tokenid << ">\n";
#endif
	return( NULL  );
	}
}

// --------------------------------------------------------------------------
// Function to identify the suffix name
// --------------------------------------------------------------------------

string *CFileSysEntryList::GetSuffix( int tokenid )
{
CFileSysEntry *pentry;

pentry = FindEntry( tokenid );

if ( pentry )
        {
        return( &pentry->m_suffix );
        }
else
        {
#ifdef DEBUG
	cout << "Error - No suffix found for tokenid <" << tokenid << ">\n";
#endif

        return( NULL );
        }
}


// --------------------------------------------------------------------------
// Function to identify the token string 
// --------------------------------------------------------------------------

string *CFileSysEntryList::GetTokenString( int tokenid )
{
CFileSysEntry *pentry;

pentry = FindEntry( tokenid );

if ( pentry )
        {
        return( &pentry->m_keyword );
        }
else
        {
        return( NULL );
        }
}

