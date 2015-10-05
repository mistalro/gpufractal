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

/* 
All allowed formats are a power of two; RGBA RG, R

    while disallowed formats are the RGB types 
        RGB32F          rgb32f
        RGB16F          rgb16f 

The following formats are allowed:

----------------------------------+------------------------------------------
Floating point formats            | Unsigned Normalised integer formats
----------------------------------+------------------------------------------
RGBA32F         rgba32f        OK | RGBA8     rgba8             
RGBA16F         rgba16f        OK | RGBA16    rgba16            
RG32F           rg32f          OK | R16       r16               
RG16F           rg16f          OK | RG16      rg16              
R32F            r32f           OK | RG8       rg8               
R16F            r16f           OK | R8        r8                
R11F_G11F_B10F  r11f_g11f_b10f    | RGB10_A2  rgb10_a2
----------------------------------+------------------------------------------

----------------------------------+------------------------------------------
Unsigned integers                 | Integers 
----------------------------------+------------------------------------------
RGBA32UI        rgba32ui          | RGBA32I   rgba32i
RGBA16UI        rgba16ui          | RGBA16I   rgba16i
RGBA8UI         rgba8ui           | RGBA8I    rgba8i
RG32UI          rg32ui            | RG32I     rg32i
RG16UI          rg16ui            | RG16I     rg16i
RG8UI           rg8ui             | RG8I      rg8i
R32UI           r32ui             | R32I      r32i
R16UI           r16ui             | R16I      r16i
R8UI            r8ui              | RG8I      rg8i
RGB10_A2UI      rgb10_a2uia       | 

----------------------------------+------------------------------------------
Signed normalized integers        | Signed normalized integers
----------------------------------+------------------------------------------
RGBA16_SNORM    rgba16_snorm      | RGBA8_SNORM     rgba8_snorm
RG16_SNORM      rg16_snorm        | RG8_SNORM       rg8_snorm
R8_SNORM        r8_snorm          |
----------------------------------+------------------------------------------

Each permitted format also has a compute shader layout qualifier
Thus RGBA32F has the layout qualifier "rgba32f"
*/
/*
#define TEX_INTERNALFORMAT GL_RGBA32F
#define TEX_FORMAT         GL_RGBA
#define TEX_TYPE           GL_FLOAT
#define TEX_COMPUTEFORMAT  "rgba32f"
*/
/*
#define TEX_INTERNALFORMAT GL_RGBA16F
#define TEX_FORMAT         GL_RGBA
#define TEX_TYPE           GL_HALF_FLOAT
#define TEX_COMPUTEFORMAT  "rgba16f"
*/
/*
#define TEX_INTERNALFORMAT GL_RGB32F
#define TEX_FORMAT         GL_RGB
#define TEX_TYPE           GL_FLOAT
#define TEX_COMPUTEFORMAT  "rgb32f"
*/
/*
#define TEX_INTERNALFORMAT GL_RG32F
#define TEX_FORMAT         GL_RG
#define TEX_TYPE           GL_FLOAT
#define TEX_COMPUTEFORMAT  "rg32f"
*/
/*
#define TEX_INTERNALFORMAT GL_RG16F
#define TEX_FORMAT         GL_RG
#define TEX_TYPE           GL_HALF_FLOAT
#define TEX_COMPUTEFORMAT  "rg16f"
*/
/*
#define TEX_INTERNALFORMAT GL_R32F
#define TEX_FORMAT         GL_R
#define TEX_TYPE           GL_FLOAT
#define TEX_COMPUTEFORMAT  "r32f"
*/
/*
#define TEX_INTERNALFORMAT GL_R16F              
#define TEX_FORMAT         GL_RED
#define TEX_TYPE           GL_HALF_FLOAT
#define TEX_COMPUTEFORMAT  "r16f"
*/


#define TEX_INTERNALFORMAT GL_RGBA8
#define TEX_FORMAT         GL_RGBA
#define TEX_TYPE           GL_UNSIGNED_BYTE
#define TEX_COMPUTEFORMAT  "rgba8"

/*
#define TEX_INTERNALFORMAT GL_RGBA16           
#define TEX_FORMAT         GL_RGBA
#define TEX_TYPE           GL_SHORT
#define TEX_COMPUTEFORMAT  "rgba16"
*/
/*
#define TEX_INTERNALFORMAT GL_R16               
#define TEX_FORMAT         GL_RED
#define TEX_TYPE           GL_SHORT
#define TEX_COMPUTEFORMAT  "r16"
*/
/*
#define TEX_INTERNALFORMAT GL_RG16
#define TEX_FORMAT         GL_RG
#define TEX_TYPE           GL_SHORT
#define TEX_COMPUTEFORMAT  "rg16"
*/
/*
#define TEX_INTERNALFORMAT GL_RG8
#define TEX_FORMAT         GL_RG
#define TEX_TYPE           GL_BYTE
#define TEX_COMPUTEFORMAT  "rg8"
*/
/*
#define TEX_INTERNALFORMAT GL_R8                
#define TEX_FORMAT         GL_RED
#define TEX_TYPE           GL_BYTE
#define TEX_COMPUTEFORMAT  "r8"
*/

