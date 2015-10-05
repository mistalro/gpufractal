// --------------------------------------------------------------------------
// File:    io_doublearray.cpp
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

// ===========================================================================
// READ ROUTINES
// ===========================================================================

// --------------------------------------------------------------------------
// Read 1D integer arrays
// --------------------------------------------------------------------------

int CFileSystemDoubleArray::ReadDoubleArray1D( ifstream &stream,
                                        int nx, double *pdata )
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

int CFileSystemDoubleArray::ReadDoubleArray2D( ifstream &stream,
                                        int nx, int ny, double *pdata )
{
string buffer;
int result;

ReadOpenPar( stream );          //        {

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

                        result &= ReadDoubleArray1D( stream, nx, pdata );
                        pdata += nx;
                        break;

                default:
                        cout << "ReadDoubleArray2D::Unknown token <";
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

int CFileSystemDoubleArray::ReadDoubleArray3D( ifstream &stream,
                                int nx, int ny, int nz, double *pdata )
{
string buffer;
int result;

ReadOpenPar( stream );          //        {

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

                        result &= ReadDoubleArray2D( stream, nx,ny, pdata );
                        pdata += ny*nz;
                        break;

                default:
                        cout << "ReadIntArray3D::Unknown token <";
                        cout << buffer.c_str() << " >\n";
                        break;
                }

        ReadClosePar( stream );       // }
        }

stream.putback( '}' );

return true;
}

// ==========================================================================
// FILE WRITING
// ==========================================================================

// --------------------------------------------------------------------------
// Write 1D array
// --------------------------------------------------------------------------

int CFileSystemDoubleArray::WriteDoubleArray1D( ostream &stream,
                                        int nx, double *pdata )
{
stream << " ";

for ( int px = 0; px < nx; px++ )
        {
        stream << pdata[px] << " ";
        }

return true;
}

int CFileSystemDoubleArray::WriteNamedDoubleArray1D( ostream &stream, 
			int depth, const char *pstr, int nx, double *pdata )
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

int CFileSystemDoubleArray::WriteDoubleArray2D( ostream &stream,
                                        int nx, int ny, double *pdata )
{
for ( int py = 0; py < ny; py++ )
        {
        WriteDoubleArray1D( stream, nx, pdata+py*nx );
        }

return true;
}

int CFileSystemDoubleArray::WriteNamedDoubleArray2D( ostream &stream, 
	int depth, const char *pstr, int nx, int ny, double *pdata )
{
WriteOpenPar( stream, depth, pstr );

for ( int py = 0; py < ny; py++ )
        {
        WriteNamedDoubleArray1D( stream, depth, STRING_YSLICE,
                                nx, pdata+py*nx);
        }

WriteClosePar( stream, depth );

return true;
}

// --------------------------------------------------------------------------
// Write 3D array
// --------------------------------------------------------------------------

int CFileSystemDoubleArray::WriteDoubleArray3D( ostream &stream,
                                        int nx, int ny, int nz, double *pdata )
{
for ( int pz = 0; pz < nz; pz++ )
        {
        WriteDoubleArray2D( stream, nx, ny, pdata+pz*nx*ny );
        }

return true;
}

int CFileSystemDoubleArray::WriteNamedDoubleArray3D( ostream &stream, 
	int depth, const char *pstr, int nx, int ny, int nz, double *pdata )
{
WriteOpenPar( stream, depth, pstr );

for ( int pz = 0; pz < nz; pz++ )
        {
        WriteNamedDoubleArray2D( stream, depth, STRING_ZSLICE,
                                nx, ny, pdata+pz*nx*ny);
        }

WriteClosePar( stream, depth );

return true;
}
