// --------------------------------------------------------------------------
// File:   io_bytearray.cpp
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

static const char *str_yslice = "yslice";
static const char *str_zslice = "zslice";

#define STRING_YSLICE   str_yslice
#define STRING_ZSLICE   str_zslice

#define TOKEN_YSLICE 0x1001
#define TOKEN_ZSLICE 0x1002

static CTokenEntry token_list[] =
{
CTokenEntry( TOKEN_YSLICE, STRING_YSLICE ),
CTokenEntry( TOKEN_ZSLICE, STRING_ZSLICE )
};

static int token_num = sizeof(token_list)/sizeof(CTokenEntry);

// --------------------------------------------------------------------------
// Read 1D integer arrays
// --------------------------------------------------------------------------

int CFileSystemByteArray::ReadByteArray1D( ifstream &stream,
                                        int nx, BYTE *pdata )
{
int result = true;

for ( int pn = 0; pn < nx; pn++ )
        {
        stream >> pdata[pn];

        if ( g_verbose> 1 )
                {
                cout << "Read byte <" << pdata[pn] << ">\n";
                }
        }

return( result );
}

// --------------------------------------------------------------------------
// Read 2D integer arrays
// --------------------------------------------------------------------------

int CFileSystemByteArray::ReadByteArray2D( ifstream &stream,
                                        int nx, int ny, BYTE *pdata )
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

                        result &= ReadByteArray1D( stream, nx, pdata );
                        pdata += nx;
                        break;

                default:
                        cout << "ReadByteArray2D::Unknown token <";
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

int CFileSystemByteArray::ReadByteArray3D( ifstream &stream,
                                int nx, int ny, int nz, BYTE *pdata )
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

                        result &= ReadByteArray2D( stream, nx,ny, pdata );
                        pdata += ny*nz;
                        break;

                default:
                        cout << "ReadByteArray3D::Unknown token <";
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

int CFileSystemByteArray::WriteByteArray1D( ostream &stream,
                                        int nx, BYTE *pdata )
{
stream << " ";

for (int px = 0; px < nx; px++ )
        {
        stream << pdata[px] << " ";
        }

return true;
}

// --------------------------------------------------------------------------
// Write 1D array
// --------------------------------------------------------------------------

int CFileSystemByteArray::WriteNamedByteArray1D( ostream &stream, int depth,
        			const char *pstr, int nx, BYTE *pdata )
{
WriteOpenPar( stream, depth, pstr );

for (int px = 0; px < nx; px++ )
        {
        stream << pdata[px] << " ";
        }

WriteClosePar( stream, depth );

return true;
}

// --------------------------------------------------------------------------
// Write 2D array
// --------------------------------------------------------------------------

int CFileSystemByteArray::WriteByteArray2D( ostream &stream,
                                        int nx, int ny, BYTE *pdata )
{
for (int py = 0; py < ny; py++ )
        {
        WriteByteArray1D( stream, nx, pdata+py*nx );
        }

return true;
}

int CFileSystemByteArray::WriteNamedByteArray2D( ostream &stream, int depth,
        const char *pstr, int nx, int ny, BYTE *pdata )
{
WriteOpenPar( stream, depth, pstr );

for (int py = 0; py < ny; py++ )
        {
        WriteNamedByteArray1D( stream, depth, STRING_YSLICE,
                                nx, pdata+py*nx);
        }

WriteClosePar( stream, depth );

return true;
}

// --------------------------------------------------------------------------
// Write 3D array
// --------------------------------------------------------------------------

int CFileSystemByteArray::WriteByteArray3D( ostream &stream,
                                        int nx, int ny, int nz, BYTE *pdata )
{
for (int pz = 0; pz < nz; pz++ )
        {
        WriteByteArray2D( stream, nx, ny, pdata+pz*nx*ny );
        }

return true;
}

int CFileSystemByteArray::WriteNamedByteArray3D( ostream &stream, int depth,
        const char *pstr, int nx, int ny, int nz, BYTE *pdata )
{
WriteOpenPar( stream, depth, pstr );

for (int pz = 0; pz < nz; pz++ )
        {
        WriteNamedByteArray2D( stream, depth, STRING_ZSLICE,
                                nx, ny, pdata+pz*nx*ny);
        }

WriteClosePar( stream, depth );

return true;
}
