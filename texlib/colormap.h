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
 * Manipulation routines for color palettes
 *
 * Author:  Michael S. A. Robb
 *
 * Date:    August 2002
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * Class definition for the colormap class
 * -------------------------------------------------------------------------- 
 */

class colmap4f
  {
public:
  int		m_max;    /* Maximum number of colors */
  int		m_num;    /* Current number of colors */
  col4f *m_list;   /* List of colors */
  int	   *m_flags;  /* List of flags */

  colmap4f();
  colmap4f( int num );

  ~colmap4f();

  colmap4f *duplicate( void );

  void zero();
  void clamp();
  void random(   col4f *cptr );
  void blend(    col4f *ca, col4f *cb, float blend );
  void maxvalue( col4f *ca, col4f *cb );

  void   expand(      int num );
  void   loadrange(   int cdst, int cnum, col4f *cptr );
  void   setrange(    int cdst, int cnum, int csrc );
  void   blend(       int cdst, int cnum, int cstart, int cfinish );
  void   translate(   int cdst, int csrc, int cnum, col4f &ctrans );
  void   scale(       int cdst, int csrc, int cnum, col4f &cscale );
 // void   multmatrix3f( int cdst, int csrc, int cnum, RTmatrix3f cmat );
 // void   multmatrix4f( int cdst, int csrc, int cnum, RTmatrix4f cmat );
  void   swap(        int cdst, int csrc, int cnum );
  void   copy(        int cdst, int csrc, int cnum );
  void   negate(      int cdst, int csrc, int cnum, int channels );
  void   rotateup(    int cdst, int cnum );
  void   rotatedown(  int cdst, int cnum );
  void   setflags(    int cdst, int cnum, int flags );
  void   clearflags(  int cdst, int cnum, int flags );
  void   init(        void );
  int    findnearest( col4f &cptr );  
  float  distlinear(  col4f &cptr );
  void   blendrange(  int start, col4f ca, col4f cb, int cn );
  };
  
#define CMAP_LOCKED      0x0001
#define CMAP_TRANSPARENT 0x0002

#define COL_CHANR  0x01
#define COL_CHANG  0x02
#define COL_CHANB  0x04
#define COL_CHANA  0x08

#define COL_CHANALL 0x0F
#define COL_CHANRGB 0x07


#define CB_MONO 0x00
#define CB_COLOR 0x01

