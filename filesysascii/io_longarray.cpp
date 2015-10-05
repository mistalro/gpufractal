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

int CFileSystemLongArray::ReadLongArray1D( ifstream &stream,
                                        int nx, long *pdata )
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

int CFileSystemLongArray::ReadLongArray2D( ifstream &stream,
                                        int nx, int ny, long *pdata )
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

                        result &= ReadLongArray1D( stream, nx, pdata );
                        pdata += nx;
                        break;

                default:
                        cout << "ReadLongArray2D::Unknown token <";
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

int CFileSystemLongArray::ReadLongArray3D( ifstream &stream,
                                int nx, int ny, int nz, long *pdata )
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

                        result &= ReadLongArray2D( stream, nx,ny, pdata );
                        pdata += ny*nz;
                        break;

                default:
                        cout << "ReadLongArray3D::Unknown token <";
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

int CFileSystemLongArray::WriteLongArray1D( ostream &stream,
                                        int nx, long *pdata )
{
stream << " ";

for ( int px = 0; px < nx; px++ )
        {
        stream << pdata[px] << " ";
        }

return true;
}

// --------------------------------------------------------------------------
// Write 1D array
// --------------------------------------------------------------------------

int CFileSystemLongArray::WriteNamedLongArray1D( ostream &stream, int depth,
        const char *pstr, int nx, long *pdata )
{
WriteTabbedDepth( stream, depth );

stream << "{" << pstr << " ";

for ( int px = 0; px < nx; px++ )
        {
        stream << pdata[px] << " ";
        }

stream << "}\n";

return true;
}

// --------------------------------------------------------------------------
// Write 2D array
// --------------------------------------------------------------------------

int CFileSystemLongArray::WriteLongArray2D( ostream &stream,
                                        int nx, int ny, long *pdata )
{
for ( int py = 0; py < ny; py++ )
        {
        WriteLongArray1D( stream, nx, pdata+py*nx );
        }

return true;
}

int CFileSystemLongArray::WriteNamedLongArray2D( ostream &stream, int depth,
        const char *pstr, int nx, int ny, long *pdata )
{
WriteOpenPar( stream, depth, pstr );

for ( int py = 0; py < ny; py++ )
        {
        WriteNamedLongArray1D( stream, depth, STRING_YSLICE,
                                nx, pdata+py*nx);
        }

WriteClosePar( stream, depth );

return true;
}

// --------------------------------------------------------------------------
// Write 3D array
// --------------------------------------------------------------------------

int CFileSystemLongArray::WriteLongArray3D( ostream &stream,
                                        int nx, int ny, int nz, long *pdata )
{
for ( int pz = 0; pz < nz; pz++ )
        {
        WriteLongArray2D( stream, nx, ny, pdata+pz*nx*ny );
        }

return true;
}

int CFileSystemLongArray::WriteNamedLongArray3D( ostream &stream, int depth,
        const char *pstr, int nx, int ny, int nz, long *pdata )
{
WriteOpenPar( stream, depth, pstr );

for ( int pz = 0; pz < nz; pz++ )
        {
        WriteNamedLongArray2D( stream, depth, STRING_ZSLICE,
                                nx, ny, pdata+pz*nx*ny);
        }

WriteClosePar( stream, depth );

return true;
}
