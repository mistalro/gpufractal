// --------------------------------------------------------------------------
// File:    filesysilbm.h 
//
// Purpose: Implementation of ILBM support functions
//
// Author:  Michael S. A. Robb
// 
// --------------------------------------------------------------------------

#ifndef _FILESYSILBM_H_
#define _FILESYSILBM_H_

// --------------------------------------------------------------------------
// Base class to support reading and writing of ILBM binary files
// --------------------------------------------------------------------------

class CVirtualFileSystemILBM : virtual public CFileSystemBinary
{
// ----- Class members ------------------------------------------------------

public:
vector <int> m_stack;
int m_stackpos;

// ----- Constructors and Destructors ---------------------------------------

CVirtualFileSystemILBM( void )
	{
	m_stack.clear();
	m_stackpos = 0;	
	}

~CVirtualFileSystemILBM( void )
	{
	}

// ----- Functions ----------------------------------------------------------

// ----- Read routines ------------------------------------------------------

int ReadBlockHeaderILBM( ifstream &stream, string &tag, int &length )
        {
	int pos;
	string filetag;
	BYTE temp[5];
	
	for ( int pn = 0; pn < 4; pn++ )
		{
		ReadBinaryByte( stream, temp[pn] );
		}

	temp[4] = '\0';

	filetag.reserve(5);
	filetag = (char *) temp;

	ReadBinaryInteger( stream, length );

	pos = stream.tellg();

	if ( filetag == tag )
		{
		return(1);		
		}

	stream.seekg( pos + length );	
	return(0);
        }

// ----- Write routines -----------------------------------------------------

int WriteBlockHeaderILBM( ofstream &stream, string &tag )
        {
	int pos;
	int length = 0;

	for (int pn = 0; pn< 4; pn++)
		{
		WriteBinaryByte( stream, tag.at(pn) );
		}

	pos = stream.tellp();
	
	WriteBinaryInteger( stream, length );	// Fake length

	m_stack.push_back( pos );	// Save for later

	return pos;
        }

int WriteBlockTailILBM( ofstream &stream )
        {
	int pos;
	int headerpos;

	pos = stream.tellp();		// Save for later

	m_stackpos--;
	headerpos = m_stack[m_stackpos];

	stream.seekp( headerpos );

	WriteBinaryInteger( stream, pos );	// Save block length

	stream.seekp( pos );		// Restore final position	
	
	return pos;
        }

int ReadILBMFile( string &strpath )
        {
	ifstream stream;
	int result = true;

	stream.open( strpath.data(), ios::in|ios::binary );
	
	return(result);
        }

int ReadILBMFile( char *pstr )
        {
	ifstream stream;
	int result = true;

	stream.open( pstr, ios::in|ios::binary );

	return(result);
        }

int WriteILBMFile( string &strpath )
        {
	ofstream stream;
	int result = true;

	stream.open( strpath.data(), ios::out|ios::binary );

	if ( !stream.is_open() )
		{
		result = false;
		}
	else
		{
		result = WriteILBMFile( stream );

		stream.close();
		}
	
	return(result);
        }

int WriteILBMFile( char *pstr )
        {
	ofstream stream;
	int result = true;

	stream.open( pstr, ios::out|ios::binary );

	if (!stream.is_open() )
		{
		result = false;
		}
	else
		{
		result = WriteILBMFile( stream );
		
		stream.close();
		}

	return(result);
        }

virtual int ReadILBMFile( ifstream &stream ) = 0;
virtual int WriteILBMFile( ofstream &stream ) = 0;
};

#endif	 // _FILESYSILBM_H_
