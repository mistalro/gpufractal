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
// --------------------------------------------------------------------------
// File:    fileutils.cpp
//
// Purpose: Module containing utility functions for reading/writing files
//
// Author:  Michael S. A. Robb
//
// Date:    12th August 2004
// --------------------------------------------------------------------------

#include "texturelib.h"

// --------------------------------------------------------------------------
// Utility functions
// --------------------------------------------------------------------------

void WaitForOpenPar( FILE *fp )
{
#ifdef DEBUG
	printf( "OpenPar: waiting\n" );
#endif

	while ( fgetc(fp) != '{' );

#ifdef DEBUG
	printf( "OpenPar: found\n" );
#endif
}

void WaitForClosePar( FILE *fp )
{
#ifdef DEBUG
	printf( "ClosePar: waiting\n" );
#endif

	while ( fgetc(fp) != '}' );

#ifdef DEBUG
	printf( "ClosePar: found\n" );
#endif
}

void WaitForIntegerVariable( FILE *fp, char *name, int &value )
{
	WaitForOpenPar( fp );

#ifdef DEBUG
	printf( "IntegerVariable: waiting\n" );
#endif

	fscanf( fp, "%s %d", name, &value );

#ifdef DEBUG
	printF( "IntegerVariable: found\n" );
#endif

	WaitForClosePar( fp );
}

void WaitForDimensions1D( FILE *fp, 
			const char * /* str */, int &nfilters, int &nchan )
{
int gotfilter=0, gotchan=0;

char buffer[1024];
int value;

#ifdef DEBUG
	printf( "WaitForDimensions: waiting\n" );
#endif

while ( (!gotfilter || !gotchan) && !feof(fp) )
       {
        WaitForIntegerVariable( fp, buffer, value );

       if ( strncmp( buffer, "channels", 8 ) == 0 )
               {
               gotchan=1;
               nchan = value;

#ifdef DEBUG
	printf( "WaitForDimensions: channels\n" );
#endif
        	}
	else
//	if ( strncmp( buffer, str, 10 ) == 0 )
       		{
        	gotfilter=1;
        	nfilters = value;

#ifdef DEBUG
	printf( "WaitForDimensions: rings\n" );
#endif
		}
	}

#ifdef DEBUG
	printf( "WaitForDimensions: found\n" );
#endif
}

void WaitForFloatVariable( FILE *fp, char *name, float &value )
{
	WaitForOpenPar( fp );

#ifdef DEBUG
	printf( "FloatVariable: waiting\n" );
#endif

	fscanf( fp, "%s %f", name, &value );

#ifdef DEBUG
	printf( "FloatVariable: found\n" );
#endif

	WaitForClosePar( fp );
}

void WaitForStringVariable( FILE *fp, char *name, int &value )
{
	WaitForOpenPar( fp );

	fscanf( fp, "%s %d", name, &value );

	WaitForClosePar( fp );
}

void WaitForParametersRadius( FILE *fp, float &fradinner, float &fradouter )
{
int gotradinner=0, gotradouter=0;
char buffer[1024];
float value;

while ( !gotradinner || !gotradouter )
	{
	WaitForFloatVariable( fp, buffer, value );

	if ( strncmp( buffer, "radinner", 8 ) == 0 )
		{
		fradinner = value;
		gotradinner = 1;
		}

	if ( strncmp( buffer, "radouter", 8 ) == 0 )
		{
		fradouter = value;
		gotradouter = 1;
		}
	}
}


void WaitForParameters( FILE *fp, float &freqlo, float &freqhi,
                        float &freqstep, float &freqsd )
{
int gotfreqlo=0, gotfreqhi=0, gotfreqstep=0, gotfreqsd=0;
char buffer[1024];
float value;

#ifdef DEBUG
	printf( "WaitForParameters: waiting\n" );
#endif

while (!gotfreqlo || !gotfreqhi || !gotfreqstep || !gotfreqsd )
        {
        WaitForFloatVariable( fp, buffer, value );

        if ( strncmp( buffer, "freqlo", 6 ) == 0 )
		{
	        freqlo = value;
	        gotfreqlo = 1;

#ifdef DEBUG
										                printf( "WaitForParameters: freqlo\n" );
#endif
		}

	if ( strncmp( buffer, "freqhi", 6 ) == 0 )
	        {
	        freqhi = value;
	        gotfreqhi = 1;

#ifdef DEBUG
	        printf( "WaitForParameters: freqhi\n" );
#endif
		}

	if ( strncmp( buffer, "freqstep", 8 ) == 0 )
	        {
	        freqstep = value;
	        gotfreqstep = 1;

#ifdef DEBUG
                printf( "WaitForParameters: freqstep\n" );
#endif
                }

        if ( strncmp( buffer, "freqstepsd", 10 ) == 0 )
                {
                freqsd = value;
                gotfreqsd = 1;

#ifdef DEBUG
                printf( "WaitForParameters: freqsd\n" );
#endif
                }
        }

#ifdef DEBUG
	printf( "WaitForParameters: done\n" );
#endif
}


void WaitForDimensions2D( FILE *fp, int &nfreq, int &ndir, int &nchan )
{
int gotfreq=0, gotdir=0, gotchan=0;
char buffer[1024];
int value;

while ( (!gotfreq || !gotdir || !gotchan) && !feof(fp) )
       {
       WaitForStringVariable( fp, buffer, value );

       if ( strncmp( buffer, "channels", 8 ) == 0 )
		{
	        gotchan=1;
	        nchan = value;
	        }

	if ( strncmp( buffer, "directions", 10 ) == 0 )
		{
		gotdir=1;
		ndir = value;
		}

       if ( strncmp( buffer, "frequencies", 11 ) == 0 )
		{
		gotfreq=1;
		nfreq = value;
		}
       }
}
