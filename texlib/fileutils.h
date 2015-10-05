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
// File: fileutils.h
//
// Purpose: Definition file for utility functions to assist in reading
//          data files
//
// Author:  Michael S. A. Robb
//
// Date:    12th August 2004
// --------------------------------------------------------------------------

extern void WaitForOpenPar( FILE *fp );

extern void WaitForClosePar( FILE *fp );

extern void WaitForIntegerVariable( FILE *fp, const char *name, int &value );

extern void WaitForFloatVariable( FILE *fp,const char *name, float &value );

extern void WaitForStringVariable( FILE *fp, const char *name, int &value );

extern void WaitForDimensions1D( FILE *fp, const char *str, 
				int &nfilters, int &nchan );

extern void WaitForDimensions2D( FILE *fp, int &nfreq, 
				int &ndir, int &nchan );

extern void WaitForParameters( FILE *fp, float &freqlo, float &freqhi,
				float &freqstep, float &freqsd);

extern void WaitForParametersRadius( FILE *fp, 
				float &fradinner, float &fradouter );
