// ---------------------------------------------------------------------------
// File:    filesysentryio.h
// 
// Purpose: Header file for reading and writing data for class
//	    CFileSysEntryIO
//
// Author:  Autofile generator
// 
// Date:    Mon Jun 17 01:01:41 2013
// ----------------------------------------------------------------------------

#ifndef _CFILESYSENTRYIO_XH_
#define _CFILESYSENTRYIO_H_

// -------------------------------------------------------------------------
// Change flags (dirty flags)
// -------------------------------------------------------------------------

enum CFileSysEntryIOChangeFlags
	{
	CFILESYSENTRYIO_CHANGEFLAG_TOKENID = 0x0001,
	CFILESYSENTRYIO_CHANGEFLAG_KEYWORD,
	CFILESYSENTRYIO_CHANGEFLAG_CLASSNAME,
	CFILESYSENTRYIO_CHANGEFLAG_TYPE,
	CFILESYSENTRYIO_CHANGEFLAG_READFUNC,
	CFILESYSENTRYIO_CHANGEFLAG_READBASICFUNC,
	CFILESYSENTRYIO_CHANGEFLAG_WRITEBASICFUNC,
	CFILESYSENTRYIO_CHANGEFLAG_WRITEFUNC,
	CFILESYSENTRYIO_CHANGEFLAG_SUFFIX,
	CFILESYSENTRYIO_CHANGEFLAG_READBINARYFUNC,
	CFILESYSENTRYIO_CHANGEFLAG_WRITEBINARYFUNC,
	};

#define CFILESYSENTRYIO_CHANGEFLAG_NUM 11

// --------------------------------------------------------------------------- 
// Main class definition for CFileSysEntryData
// --------------------------------------------------------------------------- 

class CFileSysEntryData
{
// ----- Class members ------------------------------------------------------- 
public:

bool m_masterchangeflag; // Indicates if any one field has changed
vector <bool> m_changeflags; // Clear all other flags

int	m_tokenid;		// Type
string	m_keyword;		// Key word
string	m_classname;		// Classname
string	m_type;			// Type
string	m_readfunc;		// Read function
string	m_writefunc;		// Write function
string	m_suffix;		// Suffix
string	m_readbinaryfunc;	// Read binary function
string	m_writebinaryfunc;	// Write binary function
string	m_readbasicfunc;	// Read basic raw data function
string	m_writebasicfunc;	// Write basic raw data function

// ----- Constructor and destructor ------------------------------------------ 

CFileSysEntryData( void )
	{
	CFileSysEntryData::Init();
	}

~CFileSysEntryData( void )
	{
	CFileSysEntryData::Deallocate();
	}

// ----- Functions and Procedures -------------------------------------------- 

void Init( void )
	{
	m_changeflags.reserve( CFILESYSENTRYIO_CHANGEFLAG_NUM );
	ClearChangeFlags();

	m_tokenid = -1;
	m_keyword = "";
	m_classname = "";
	m_type = "";
	m_readfunc = "";
	m_readbasicfunc = "";
	m_writebasicfunc = "";
	m_writefunc = "";
	m_suffix = "";
	m_readbinaryfunc = "";
	m_writebinaryfunc = "";
	}

void Deallocate()
	{
	m_keyword.clear();
	m_classname.clear();
	m_type.clear();
	m_readfunc.clear();
	m_readbasicfunc.clear();
	m_writebasicfunc.clear();
	m_writefunc.clear();
	m_suffix.clear();
	m_readbinaryfunc.clear();
	m_writebinaryfunc.clear();

	Init();
	}

// ----- Manage change flags  -----------------------------------------------

inline void ClearChangeFlags( void )
	{
	m_masterchangeflag = 0;
	m_changeflags.clear();
	}

inline void SetChangeFlag( unsigned int index )
	{
	m_masterchangeflag = true;
	m_changeflags[index] = true;
	}

inline bool GetChangeFlag( unsigned int index )
	{
	return( m_changeflags[index] );
	}

inline bool GetMasterChangeFlag( void )
	{
	return( m_masterchangeflag );
	}

inline void SetMasterChangeFlag( void )
	{
	m_masterchangeflag = true;
	}

// ----- Manage getting and setting values -----------------------------------

inline int GetTokenid( void )
	{
	return( m_tokenid );
	}

inline void SetTokenid( const int value )
	{
	m_tokenid = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_TOKENID );
	}

inline string & GetKeyword( void )
	{
	return( m_keyword );
	}

inline void SetKeyword( const string  &value )
	{
	m_keyword = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_KEYWORD );
	}

inline void SetKeyword( const char *  &value )
	{
	m_keyword = value;
	}

inline string & GetClassname( void )
	{
	return( m_classname );
	}

inline void SetClassname( const string  &value )
	{
	m_classname = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_CLASSNAME );
	}

inline void SetClassname( const char *  &value )
	{
	m_classname = value;
	}

inline string & GetType( void )
	{
	return( m_type );
	}

inline void SetType( const string  &value )
	{
	m_type = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_TYPE );
	}

inline void SetType( const char *  &value )
	{
	m_type = value;
	}

inline string & GetReadfunc( void )
	{
	return( m_readfunc );
	}

inline void SetReadfunc( const string  &value )
	{
	m_readfunc = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_READFUNC );
	}

inline void SetReadfunc( const char *  &value )
	{
	m_readfunc = value;
	}

inline string & GetReadbasicfunc( void )
	{
	return( m_readbasicfunc );
	}

inline void SetReadbasicfunc( const string  &value )
	{
	m_readbasicfunc = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_READBASICFUNC );
	}

inline void SetReadbasicfunc( const char *  &value )
	{
	m_readbasicfunc = value;
	}

inline string & GetWritebasicfunc( void )
	{
	return( m_writebasicfunc );
	}

inline void SetWritebasicfunc( const string  &value )
	{
	m_writebasicfunc = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_WRITEBASICFUNC );
	}

inline void SetWritebasicfunc( const char *  &value )
	{
	m_writebasicfunc = value;
	}

inline string & GetWritefunc( void )
	{
	return( m_writefunc );
	}

inline void SetWritefunc( const string  &value )
	{
	m_writefunc = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_WRITEFUNC );
	}

inline void SetWritefunc( const char *  &value )
	{
	m_writefunc = value;
	}

inline string & GetSuffix( void )
	{
	return( m_suffix );
	}

inline void SetSuffix( const string  &value )
	{
	m_suffix = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_SUFFIX );
	}

inline void SetSuffix( const char *  &value )
	{
	m_suffix = value;
	}

inline string & GetReadbinaryfunc( void )
	{
	return( m_readbinaryfunc );
	}

inline void SetReadbinaryfunc( const string  &value )
	{
	m_readbinaryfunc = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_READBINARYFUNC );
	}

inline void SetReadbinaryfunc( const char *  &value )
	{
	m_readbinaryfunc = value;
	}

inline string & GetWritebinaryfunc( void )
	{
	return( m_writebinaryfunc );
	}

inline void SetWritebinaryfunc( const string  &value )
	{
	m_writebinaryfunc = value;
	SetChangeFlag( CFILESYSENTRYIO_CHANGEFLAG_WRITEBINARYFUNC );
	}

inline void SetWritebinaryfunc( const char *  &value )
	{
	m_writebinaryfunc = value;
	}

};

// ---------------------------------------------------------------------
// File IO class for ASCII data
// ---------------------------------------------------------------------

class CFileSysEntryDataAsciiIO : virtual public CVirtualFileSystemGlobalAscii,
				virtual public CFileSysEntryData
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

class CFileSysEntryIO: virtual public CFileSysEntryDataAsciiIO
{
// ----- Constructor and Destructor ----------------------------

public:
CFileSysEntryIO( void )
	{
	Init();
	}

// ----- Functions ---------------------------------------------

void Init( void )
	{
	CFileSysEntryData::Init();
	}
};

#endif	// _CFILESYSENTRYIO_H_
