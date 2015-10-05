// --------------------------------------------------------------------------
// File:    filesysentry.h
//
// Purpose: Class definitions for the super-tokens
//
// Author:  Michael S. A. Robb
//
// Date:    25th September 2009
// --------------------------------------------------------------------------

#ifndef _FILESYSENTRY_H_
#define _FILESYSENTRY_H_

// --------------------------------------------------------------------------
// Define a single super token entry
// --------------------------------------------------------------------------

class CFileSysEntry : public CFileSysEntryIO
{
public:

CFileSysEntry( void )
	{
	}

CFileSysEntry( char const *pkeyword, int token, char const *ptype, char const *psuffix, char const *pclass,
            char const *preadascii, char const *pwritebasicascii, char const *pwriteascii, 
	    char const *preadbinary, char const *pwritebinary )
       	{ 
        m_keyword   	= pkeyword;
        m_tokenid   	= token;
        m_type      	= ptype;
        m_readfunc  	= preadascii;
	m_writebasicfunc = pwritebasicascii;
        m_writefunc 	= pwriteascii;
	m_readbinaryfunc = preadbinary;
	m_writebinaryfunc = pwritebinary;
        m_suffix    	= psuffix;
        m_classname 	= pclass;
        }

~CFileSysEntry( void )
	{
	}
};

#endif	// _FILESYSENTRY_H_
