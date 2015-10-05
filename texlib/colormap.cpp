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
/* --------------------------------------------------------------------------
 * This module contains routines to manipulate a colormap
 * --------------------------------------------------------------------------
 */

#include "texturelib.h"

/* --------------------------------------------------------------------------
 * Expand a colormap
 * --------------------------------------------------------------------------
 */

void colmap4f::expand( int num )
{
if ( num < m_max )
	{
	return;
	}

col4f *cnew = new col4f[num];
int *cflags = new int[num];

if ( m_list )
	{
	for (int cn = 0; cn < m_num; cn++ )
		{
		cnew[cn] = m_list[cn];
		}
	}

delete m_list;

if ( m_flags )
	{
	for (int cn = 0; cn < m_num; cn++ )
		{
		cflags[cn] = m_flags[cn];
		}

	delete m_flags;
	}

m_list= cnew;
m_flags = cflags;
m_max = num;
}

/* --------------------------------------------------------------------------
 * Create a colormap
 * --------------------------------------------------------------------------
 */

colmap4f::colmap4f( void )
{
int num = 256;

m_max = num;
m_num = 0;

m_list= new col4f[num];
m_flags = new int[num];

init();
}

colmap4f::colmap4f( int num )
{
if ( num < 0 ) /* Default number */
	{	
	num = 256;
	}
 
m_max = num;
m_num = 0;
m_list= new col4f[num];
m_flags = new int[num];

init();
}

/* --------------------------------------------------------------------------
 * Delete a colormap
 * --------------------------------------------------------------------------
 */

colmap4f::~colmap4f( void )
{
delete [] m_list;
delete [] m_flags;
}

/* --------------------------------------------------------------------------
 * Duplicate a colormap
 * --------------------------------------------------------------------------
 */

colmap4f *colmap4f::duplicate( void )
{
colmap4f *cnew;
int cn;

cnew = new colmap4f;

for ( cn = 0; cn < m_num; cn++ )
	{
	cnew->m_list[cn] = m_list[cn]; 
	cnew->m_flags[cn] = m_flags[cn];
	}
 
cnew->m_num = m_num;

return( cnew );
}

/* --------------------------------------------------------------------------
 * Copy a color to an entire range of colors
 * --------------------------------------------------------------------------
 */

void colmap4f::setrange( int cdst, int cnum, int csrc )
{
col4f ctemp;
int cn, cpos;

if ( csrc < 0 || csrc >= m_max ||/* Sanity check */
 	cdst < 0 || cdst >= m_max )
	{
	return;
	}

if ( cdst + cnum >= m_max )/* Another check */
	{	
	cnum = m_max - cdst;
	}

ctemp = m_list[csrc];/* Get the color */
cpos= cdst; 

for ( cn = 0; cn < cnum; cn++, cpos++ ) /* Copy color (if not locked) */
	{
	if ( !(m_flags[cpos] & CMAP_LOCKED ) )
		{
		m_list[cpos] = ctemp;
		}
	}
}

/* ---------------------------------------------------------------------------
 * Interpolate between a pair of colors to a generate a blended range
 * ---------------------------------------------------------------------------
 */

void colmap4f::blend( int cdst, int cnum,
int cstart, int cfinish )
{
col4f ctmpst, ctmpfin;/* Temporary copies */
int cn, cpos;

if ( cdst < 0 || (cdst + cnum >= m_max) ||/* Sanity check */
 cstart< 0 || cstart>= m_max ||
 cfinish < 0 || cfinish >= m_max )
	{
	return;
	}

ctmpst = m_list[cstart]; /* Temporary copies */
ctmpfin = m_list[cfinish];

cpos = cdst;

for ( cn = 0; cn < cnum; cn++, cpos++ ) /* Interpolate color */
	{
	if ( !(m_flags[cpos] & CMAP_LOCKED ) )
		{
		m_list[cpos].blend( ctmpst, ctmpfin, (float) cn / cnum );
		}
	}
}

/* --------------------------------------------------------------------------
 * Swap between two sets of colors 
 *
 * A swap will only be performed if both colors are unlocked
 * --------------------------------------------------------------------------
 */

void colmap4f::swap( int cdst, int csrc, int cnum )
{
int cn, cdpos, cspos;
col4f ctemp, *csptr, *cdptr;

if ( cdst < 0 || cdst + cnum >= m_max ||/* Sanity check */
 csrc < 0 || csrc + cnum >= m_max )
	{
	return;
	}

if ( ( (csrc+cnum-1 >= cdst) && (csrc < cdst)) || /* Swap ranges must not*/
 ( (cdst+cnum-1 >= csrc) && (cdst < csrc)) )/* intersect */
	{
	return;
	}

csptr = m_list + csrc;/* Swap pointers */
cdptr = m_list + cdst;

cspos = csrc;
cdpos = cdst;

for ( cn = 0; cn < cnum; cn++, cspos++, cdpos++, csptr++, cdptr++ )
	{
	if ( !(m_flags[cspos] & CMAP_LOCKED) && 
 		!(m_flags[cdpos] & CMAP_LOCKED) )
		{
 		ctemp= *csptr;
		*csptr= *cdptr;
		*cdptr=ctemp;
		}
	}
}

/* --------------------------------------------------------------------------
 * Copy two sets of colors
 * --------------------------------------------------------------------------
 */

void colmap4f::copy( int cdst, int csrc, int cnum )
{
int cn, cspos, cdpos;
col4f *csptr, *cdptr;

if ( cdst < 0 || cdst + cnum >= m_max ||/* Sanity check */
 csrc < 0 || csrc + cnum >= m_max ) 
	{
	return;
	}

if ( csrc > cdst )
	{
	cspos = csrc;
	cdpos = cdst;

	csptr = m_list + csrc;
	cdptr = m_list + cdst;

	for ( cn = 0; cn < cnum; cn++, cspos++, cdpos++, csptr++, cdptr++ )
		{
		if ( !(m_flags[cdpos] & CMAP_LOCKED ) )
			{
			*cdptr = *csptr;
			}
		}
	}
else
	{
	cspos = csrc + cnum - 1;
	cdpos = cdst + cnum - 1;

	csptr = m_list + csrc;
	cdptr = m_list + cdst;
 
	for ( cn = cnum-1; cn > 0; cn--, cspos--, cdpos--, csptr--, cdptr-- )
		{
		if ( !(m_flags[cdpos] & CMAP_LOCKED ) )
			{
			*cdptr = *csptr;
			}
		}
	}
}

/* -------------------------------------------------------------------------- 
 * Negate a range of colors
 * --------------------------------------------------------------------------
 */
 
void colmap4f::negate( int cdst, int csrc, int cnum, int channels )
{
int cn, cspos, cdpos;
col4f *csptr, *cdptr;

if ( cdst < 0 || cdst+cnum >= m_max ||
 csrc < 0 || csrc+cnum >= m_max )
	{
	return;
	}

csptr = m_list + csrc;
cdptr = m_list + cdst;
 
cspos = csrc;
cdpos = cdst;

for ( cn = 0; cn < cnum; cn++, cspos++, cdpos++, csptr++, cdptr++ )
	{
	if ( !(m_flags[cdpos] & CMAP_LOCKED ) )
		{
		cdptr->negate( *csptr, channels );
		}
	}
}

/* --------------------------------------------------------------------------
 * Rotate a range of colors upwards
 *
 * Color[N] = Color[N+1]
 * --------------------------------------------------------------------------
 */

void colmap4f::rotateup( int cdst, int cnum )
{
int cn, cpos; 
col4f ctemp;

if ( cdst < 0 || cdst+cnum >= m_max )
	{
	return;
	}

cpos = cdst;

ctemp = m_list[cpos];

for ( cn = 0; cn < cnum-1; cn++, cpos++ )
	{
	if ( !(m_flags[cpos] & CMAP_LOCKED) )
		{
		m_list[cpos] = m_list[cpos+1];
		}
	}

m_list[cdst+cnum-1] = ctemp;
}

/* --------------------------------------------------------------------------
 * Rotate a range of colors downwards
 * --------------------------------------------------------------------------
 */

void colmap4f::rotatedown( int cdst, int cnum )
{
int cn, cpos;
col4f ctemp;

if ( cdst < 0 || cdst+cnum >= m_max )
	{
	return;
	}

cpos = cdst;

ctemp = m_list[cdst+cnum-1];

for ( cn = cnum-1; cn >= 0; cn--, cpos-- )
	{
	if ( !(m_flags[cpos] & CMAP_LOCKED) )
		{
		m_list[cpos] = m_list[cpos-1];
		}
	}

m_list[cdst] = ctemp;
}

/* --------------------------------------------------------------------------
 * Set a range of flags
 * --------------------------------------------------------------------------
 */

void colmap4f::setflags(int cdst, int cnum, int flags )
{
int cpos = cdst;

for (int cn = 0; cn < cnum; cn++, cpos++ )
	{
	m_flags[cpos] |= flags;
	}
}

/* --------------------------------------------------------------------------
 * Clear a range of flags
 * --------------------------------------------------------------------------
 */

void colmap4f::clearflags( int cdst, int cnum, int flags )
{
int cn, cpos;

cpos = cdst;

flags = ~flags;

for ( cn = 0; cn < cnum; cn++, cpos++ )
	{
	m_flags[cpos] &= flags;
	}
}

/* --------------------------------------------------------------------------
 * Load in a range of colors
 * --------------------------------------------------------------------------
 */

void colmap4f::loadrange( int cdst, int cnum, col4f *clist )
{
int cn, cpos;

if ( cdst < 0 || cdst+cnum >= m_max )/* Sanity check */
	{
	return;
	}

cpos = cdst;

for ( cn = 0; cn < cnum; cn++, cpos++ )
	{
	m_list[cpos] = clist[cn];
	}
}

/* --------------------------------------------------------------------------
 * Set the default colors for a colormap
 *
 * 0..15 = VGA colors(16)
 *
 * 16-47 = Rainbow (16)
 *
 * Black->White(32)
 * Black->Red->White (32)
 * Black->Yellow->White(32)
 * Black->Green->White (32)
 * Black->Aqua->White(32)
 * Black->Blue->White(32)
 * Black->Magenta->White (32)| 32 x 6 = 192 | 
 * 
 * --------------------------------------------------------------------------
 */

static float colors_vga[16][4] =
{
{ 0.0, 0.0, 0.0, 1.0 },/*0 = Black */
{ 0.5, 0.0, 0.0, 1.0 },/*1 = Red */
{ 0.5, 0.5, 0.0, 1.0 },/*2 = Brown */
{ 0.0, 0.5, 0.0, 1.0 },/*3 = Green */
{ 0.0, 0.5, 0.5, 1.0 },/*4 = Dark-Cyan */
{ 0.0, 0.0, 0.5, 1.0 },/*5 = Blue*/
{ 0.5, 0.0, 0.5, 1.0 },/*6 = Magenta */
{ 0.5, 0.5, 0.5, 1.0 },/*7 = Dark-Gray */
{ 0.75, 0.75, 0.75, 1.0 }, /*8 = Light-Gray */
{ 1.0, 0.0, 0.0, 1.0 },/*9 = Red*/
{ 1.0, 1.0, 0.0, 1.0 },/* 10 = Yellow */
{ 0.0, 1.0, 0.0, 1.0 },/* 11 = Green*/
{ 0.0, 1.0, 1.0, 1.0 },/* 12 = Cyan */
{ 0.0, 0.0, 1.0, 1.0 },/* 13 = Blue */
{ 1.0, 0.0, 1.0, 1.0 },/* 14 = Magenta */
{ 1.0, 1.0, 1.0, 1.0 } /* 15 = White */
};

void colmap4f::blendrange( int start, col4f ca, col4f cb, int cn )
{
int pn;

for ( pn = 0; pn < cn; pn++ )
	{
	m_list[start+pn].blend( ca, cb, (float) pn / (cn-1) );
	}
}

void colmap4f::init( void )
{
int cn, cpos;

if ( m_max < 256 )
	{
	return;
	}

cpos = 1;

for ( cn = 1; cn < 32; cn++, cpos++ )
	{
	m_list[cpos].sethue( (float) (cn-1) * 6.0f / 31.0f );
	}

for ( cn = 0; cn< 32; cn++, cpos++ )
	{
	m_list[cpos].setmono( (float) cn / 32.0f );
	}

for ( cn = 0; cn < 6; cn++ )
	{
	blendrange(64+cn*32, col4f( colors_vga[9+cn]), col4f( colors_vga[0]),16 );
	blendrange(80+cn*32, col4f( colors_vga[15]), col4f( colors_vga[9+cn]), 16 );
	}
}

/* --------------------------------------------------------------------------
 * Multiply the color entries by a 3x3 matrix
 * --------------------------------------------------------------------------
 */
/*
void colmap4f::multmatrix3f( int cdst, int csrc,
int cnum, RTmatrix3f cmat )
{
col4f *csptr, *cdptr;
int cn;

if ( cdst < 0 || cdst+cnum >= m_max )
return;

csptr = m_list + csrc;
cdptr = m_list + cdst;

for ( cn = 0; cn < cnum; cn++ ) 
cdptr->multmatrix3f( csptr, cmat );
}
 */
/* --------------------------------------------------------------------------
 * Translate the color entries by a fixed amount
 * --------------------------------------------------------------------------
 */

void colmap4f::translate( int cdst, int /* csrc */, int cnum, col4f &ctrans )
{
if ( cdst < 0 || cdst+cnum >= m_max ) /* Sanity check */
	{
	return;
	}

col4f *cdptr = m_list + cdst;
 
for (int cn = 0; cn < cnum; cn++, cdptr++ )
	{
	cdptr[cn] += ctrans;

	cdptr[cn].clamp();
	}
}

/* --------------------------------------------------------------------------
 * Scale the color entries by a fixed amount
 * --------------------------------------------------------------------------
 */

void colmap4f::scale( int cdst, int csrc, int cnum, col4f &cscale )
{
int cn;
col4f *cdptr, *csptr;

if ( cdst < 0 || cdst+cnum >= m_max )/* Sanity check */
	{
	return;
	}

cdptr = m_list + cdst;
csptr = m_list + csrc;
 
for ( cn = 0; cn < cnum; cn++, csptr++ )
	{
	cdptr[cn] = *csptr * cscale;
	cdptr[cn].clamp();
	}
}

int colmap4f::findnearest( col4f &col )
{
int cbest, cn;
float cdist, bdist;

bdist = m_list[0].distlinear( col );
cbest = 0;

for ( cn = 1; cn < m_num; cn++)
	{
	cdist = m_list[cn].distlinear( col );

	if ( cdist < bdist )
		{
		bdist = cdist;
		cbest = cn;
		}
	}

return( cbest );
}
