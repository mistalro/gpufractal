// --------------------------------------------------------------------------
// File:   io_generic.cpp
//
// Purpose: Routines to handle parenthesis
//
// Author:  Michael S. A. Robb
//
// Date:    2005/01/27
// ---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "filesysascii.h"

// ===========================================================================
// READ ROUTINES
// ===========================================================================

// ==========================================================================
// FILE READING
// ==========================================================================

static const char *str_yslice = "yslice";
static const char *str_zslice = "zslice";

#define STRING_YSLICE   str_yslice
#define STRING_ZSLICE   str_zslice

#define TOKEN_YSLICE 0x1001
#define TOKEN_ZSLICE 0x1002

CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_YSLICE, STRING_YSLICE ),
CTokenEntry( TOKEN_ZSLICE, STRING_ZSLICE )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read 1D integer arrays
// --------------------------------------------------------------------------

int CFileSystemShortArray::ReadShortArray1D( ifstream &stream,
                                        int nx, short *pdata )
{
int result = true;

for ( unsigned int pn = 0; pn < nx; pn++ )
        {
        stream >> pdata[pn];

        if ( g_verbose> 1 )
                {
                cout << "Read short <" << pdata[pn] << ">\n";
                }
        }

return( result );
}

// --------------------------------------------------------------------------
// Read 2D integer arrays
// --------------------------------------------------------------------------

int CFileSystemShortArray::ReadShortArray2D( ifstream &stream,
                                        int nx, int ny, short *pdata )
{
string buffer;
int result;

while ( ReadOpenClosePar( stream ) != 0 )
        {
        ReadString( stream, buffer ); // str

        if ( g_verbose > 1)
                {
                cout << "Read token <" << buffer << ">\n";
                }

        switch( token_match( buffer, token_list, token_num ) )
                {
                case TOKEN_YSLICE:
                        if ( g_verbose > 1 )
                                {
                                cout << "Reading Y-slice\n";
                                }

                        result &= ReadShortArray1D( stream, nx, pdata );
                        pdata += nx;
                        break;

                default:
                        cout << "ReadShortArray2D::Unknown token <";
                        cout << buffer.c_str() << " >\n";
                        break;
                }

        ReadClosePar( stream );       // }
        }

stream.putback( '}' );

return true;
}

// --------------------------------------------------------------------------
// Read 3D integer arrays
// --------------------------------------------------------------------------

int CFileSystemShortArray::ReadShortArray3D( ifstream &stream,
                                int nx, int ny, int nz, short *pdata )
{
string buffer;
int result;

while ( ReadOpenClosePar( stream ) != 0 )
        {
        ReadString( stream, buffer ); // str

        if ( g_verbose > 1 )
                {
                cout << "Read token <" << buffer << ">\n";
                }

        switch( token_match( buffer, token_list, token_num ) )
                {
                case TOKEN_ZSLICE:
                        if ( g_verbose > 1 )
                                {
                                cout << "Reading Z-slice\n";
                                }

                        result &= ReadShortArray2D( stream, nx,ny, pdata );
                        pdata += ny*nz;
                        break;

                default:
                        cout << "ReadShortArray3D::Unknown token <";
                        cout << buffer.c_str() << " >\n";
                        break;
                }

        ReadClosePar( stream );       // }
        }

stream.putback( '}' );

return true;
}

// ===========================================================================
// WRITE ROUTINES
// ===========================================================================

int CFileSystemByteArray::WriteShortArray1D( ostream &stream,
                                        int nx, short *pdata )
{
stream << " ";

for ( unsigned int px = 0; px < nx; px++ )
        {
        stream << pdata[px] << " ";
        }
}

// --------------------------------------------------------------------------
// Write 1D array
// --------------------------------------------------------------------------

int CFileSystemShortArray::WriteNamedShortArray1D( ostream &stream, 
		int depth, const char *pstr, int nx, short *pdata )
{
WriteTabbedDepth( stream, depth );

stream << "{" << pstr << " ";

for ( unsigned int px = 0; px < nx; px++ )
        {
        stream << pdata[px] << " ";
        }

stream << "}\n";
}

// --------------------------------------------------------------------------
// Write 2D array
// --------------------------------------------------------------------------

int CFileSystemByteArray::WriteByteArray2D( ostream &stream,
                                        int nx, int ny, short *pdata )
{
for ( unsigned int py = 0; py < ny; py++ )
        {
        WriteShortArray1D( stream, nx, pdata+py*nx );
        }
}

int CFileSystemShortArray::WriteNamedShortArray2D( ostream &stream, 
		int depth, const char *pstr, int nx, int ny, short *pdata )
{
WriteOpenPar( stream, depth, pstr );

for ( unsigned int py = 0; py < ny; py++ )
        {
        WriteNamedShortArray1D( stream, depth, STRING_YSLICE,
                                nx, pdata+py*nx);
        }

WriteClosePar( stream, depth );
}

// --------------------------------------------------------------------------
// Write 3D array
// --------------------------------------------------------------------------

int CFileSystemByteArray::WriteShortArray3D( ostream &stream,
                                        int nx, int ny, int nz, short *pdata )
{
for ( unsigned int py = 0; py < ny; py++ )
        {
        WriteShortArray3D( stream, nx, ny, pdata+pz*nx*ny );
        }
}

int CFileSystemShortArray::WriteNamedShortArray3D( ostream &stream, 
		int depth, const char *pstr, int nx, int ny, int nz,
        		short *pdata )
{
WriteOpenPar( stream, depth, pstr );

for ( unsigned int pz = 0; pz < nz; pz++ )
        {
        WriteNamedShortArray2D( stream, depth, STRING_ZSLICE,
                                nx, ny, pdata+pz*nx*ny);
        }

WriteClosePar( stream, depth );
}

