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
// Header file used to provide the definition of the texture class
// 
// Author: Michael S. A. Robb
//
// Date:   19th August 2002
//
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Useful constants
// --------------------------------------------------------------------------

#define TEX_NONE       0x00     // No match found 

#define TEX_MONO       0x0001     // Texture has a monochrome palette 
#define TEX_RGB3       0x0002     // Truecolor RGB format         
#define TEX_PALETTE    0x0004     // Texture has a color palette  
#define TEX_ALPHA      0x0008     // Pixels have alpha channel       
#define TEX_DUAL       0x0010     // Dual format 

#define TEX_8BIT       0x0100    // 8  bit components
#define TEX_16BIT      0x0200    // 16 bit components         
#define TEX_32BIT      0x0400    // 32 bit components   
#define TEX_FLOAT      0x0800    // Floating-point components 

#define TEX_SIGNED     0x1000   // Data values are signed, otherwise unsigned
#define TEX_COMPRESSED 0x2000   // Compressed texture
#define TEX_COMPLEXFLAG 0x4000	// Complex data

//#define TEX_BUMPMAP    0x4000   // Texture is a bump-map (OpenGL flag)

#define TEX_MODEMASK   0x0FFF

#define TEX_BITSIZES   (TEX_8BIT|TEX_16BIT|TEX_32BIT|TEX_FLOAT)

#define TEX_MONO8     (TEX_MONO | TEX_8BIT )
#define TEX_MONOA8    (TEX_MONO | TEX_8BIT  | TEX_ALPHA )
#define TEX_MONO16    (TEX_MONO | TEX_16BIT )
#define TEX_MONOA16   (TEX_MONO | TEX_16BIT | TEX_ALPHA )
#define TEX_MONOFLOAT (TEX_MONO | TEX_32BIT              | TEX_FLOAT)
#define TEX_MONOFLOAT32 (TEX_MONO | TEX_32BIT              | TEX_FLOAT)
#define TEX_MONOAFLOAT (TEX_MONO | TEX_32BIT | TEX_ALPHA | TEX_FLOAT )
#define TEX_MONOAFLOAT32 (TEX_MONO | TEX_32BIT | TEX_ALPHA | TEX_FLOAT )

#define TEX_MONOCOMPLEX32 (TEX_MONO | TEX_32BIT | TEX_FLOAT | TEX_COMPLEXFLAG)
#define TEX_MONOACOMPLEX32 (TEX_MONO | TEX_32BIT | TEX_FLOAT | TEX_ALPHA | TEX_COMPLEXFLAG)

#define TEX_RGB       (TEX_RGB3  | TEX_8BIT )
#define TEX_RGBA      (TEX_RGB3  | TEX_8BIT  | TEX_ALPHA)
#define TEX_RGB16     (TEX_RGB3  | TEX_16BIT )
#define TEX_RGBA16    (TEX_RGB3  | TEX_16BIT | TEX_ALPHA)
#define TEX_RGBFLOAT  (TEX_RGB3  | TEX_32BIT |             TEX_FLOAT )
#define TEX_RGBAFLOAT (TEX_RGB3  | TEX_32BIT | TEX_ALPHA | TEX_FLOAT )

#define TEX_RGBFLOAT32  (TEX_RGB3  | TEX_32BIT |             TEX_FLOAT )
#define TEX_RGBAFLOAT32 (TEX_RGB3  | TEX_32BIT | TEX_ALPHA | TEX_FLOAT )
#define TEX_RGBCOMPLEX32 (TEX_RGB3 | TEX_32BIT |             TEX_FLOAT | TEX_COMPLEXFLAG )

#define TEX_DUAL8      (TEX_DUAL | TEX_8BIT )
#define TEX_DUAL16     (TEX_DUAL | TEX_16BIT )
#define TEX_DUALFLOAT  (TEX_DUAL | TEX_32BIT |             TEX_FLOAT )

#define TEX_PALETTE16 (TEX_PALETTE| TEX_16BIT)
#define TEX_HILO16    (TEX_HILO | TEX_16BIT)

// --------------------------------------------------------------------------
// Constants used to define the texture channels
// --------------------------------------------------------------------------

#define TEX_CHANNELRED   0x000	// Red 
#define TEX_CHANNELGREEN 0x001	// Green
#define TEX_CHANNELBLUE  0x002  // Blue
#define TEX_CHANNELALPHA 0x003  // Alpha
#define TEX_CHANNELMONO  0x000  // Monochrome

#define TEX_LOCALSCALE          0x0000 // Scale components individually
#define TEX_GLOBALSCALE         0x0001 // Scale components globally

#define TEX_VERBOSE             0x0001 // Verbose
#define TEX_SAVEIMAGES          0x0002 // Save images of Gabor frequency
#define TEX_EXTREMEVERBOSE      0x0004 // Extremely verbose
#define TEX_RAWFILTER           0x0008 // Keep raw filter data
#define TEX_SAVEFILTERS         0x0010 // Save image domain filter images
#define TEX_SAVESPECTRAL        0x0020 // Save frequency domain filter images

// --------------------------------------------------------------------------
// Volume data
// --------------------------------------------------------------------------

#define VOLUME_8BIT       0x0000
#define VOLUME_16BITLSB   0x0001
#define VOLUME_16BITMSB   0x0002
#define VOLUME_32BITLSB   0x0003
#define VOLUME_32BITMSB   0x0004
#define VOLUME_32BITFLOAT 0x0005

// --------------------------------------------------------------------------
// Utility functions
// --------------------------------------------------------------------------

ULONG readbytemsb(  FILE *fp );
ULONG readshortmsb( FILE *fp );
ULONG readlongmsb(  FILE *fp );
ULONG readbytelsb(  FILE *fp );
ULONG readshortlsb( FILE *fp );
ULONG readlonglsb(  FILE *fp );

void  writebytemsb(  FILE *fp, ULONG val );
void  writeshortmsb( FILE *fp, ULONG val );
void  writelongmsb(  FILE *fp, ULONG val );
void  writebytelsb(  FILE *fp, ULONG val );
void  writeshortlsb( FILE *fp, ULONG val );
void  writelonglsb(  FILE *fp, ULONG val );

// --------------------------------------------------------------------------
// The texture class
// --------------------------------------------------------------------------

class CTexture
{
public: 
CTextureName m_name;       // Name of texture
int	     m_width;      // Width of the texture in pixels
int	     m_height;     // Height of the texture in pixels
int	     m_area;	   // Total area in pixels
int	     m_size;       // Total size of texture in bytes
int	     m_type;	   // Type of texture
int	     m_compsize;   // Size of pixel components in bytes
int	     m_pixelsize;  // Size of pixels in bytes
int          m_nelements;  // Number of components in each pixel
int	     m_pitch;      // Width of each row in bytes
TEXBYTE     *m_pdata;      // Pointer to data
colmap4f *m_pcolormap;  // Pointer to colormap data
int	     m_textureid;  // ID number of the texture (OpenGL)
int          m_userflags;  // User flags
// Function prototypes 

// ----- Constructor and  destructor -----------------------------------------
 
CTexture( void )
	{
	Init();
	}

CTexture( int width, int  height, int ctype )
	{
	Init();
	Allocate( width, height, ctype );
	}

~CTexture()
	{
	Deallocate();
	}

void Init( void )
	{
	m_name[0] = '\0';
	m_width = 0;
	m_height = 0;
	m_area = 0;
	m_size = 0;
	m_type = 0;
	m_compsize = 0;
	m_pixelsize = 0;
	m_nelements = 0;
	m_pitch = 0;
	m_pdata = NULL;
	m_pcolormap = NULL;
	m_textureid = 0;
	m_userflags = 0;
	}

int  TextureIsFloat( void ) { return( (m_type & TEX_FLOAT) == TEX_FLOAT); };
int  TextureIsByte(  void ) { return( (m_type & TEX_8BIT)  == TEX_8BIT ); };
int  TextureIsShort( void ) { return( (m_type & TEX_16BIT) == TEX_16BIT); };

// ----- Operators ----------------------------------------------------------

int SortCompare( const CTexture &texture )
        {
        return( m_area - texture.m_area );
        };
bool operator < ( const CTexture &texture )
        { return ( m_area < texture.m_area );  };

bool operator > ( const CTexture &texture )
        { return ( m_area > texture.m_area ); };

void Display( void ) { };

// ----- Debug function -----------------------------------------------------

void TextureDumpStatistics( char *pdescr );

// ----- Comparision functions ----------------------------------------------

int  TextureSameSize( CTexture &texa ) {
		return( (texa.m_width  == m_width ) &&
		    	(texa.m_height == m_height) &&
			    (texa.m_type   == m_type  ) ); };

// ----- Name manipulation functions ----------------------------------------

void TextureSetName( char *name ) { strncpy( m_name, name, MATHS_NAME_MAX ); };
char *TextureGetName( void ) { return m_name; };

// ----- Texture memory management ------------------------------------------

void Allocate( int width, int height, int ctype );
void Allocate( CTexture &texture );
void Deallocate( void );
void TextureGetSize( int ctype, int *csize, int *psize, int *nelems );
void Duplicate( CTexture &psrc );
void Copy( CTexture &psrc );
void Transfer( CTexture &psrc );
void Swap( CTexture &psrc );

// ----- File access routines -----------------------------------------------

int  TextureReadFile(      const char path[] );
int  TextureWriteFile(     const char *path );
int  TextureReadtga(       const char *path );
int  TextureWritetga(      const char *path );
int  TextureReadbmp(       const char *path );
int  TextureWritebmp(      const char *path );
int  TextureReadtiff(      const char *path );
int  TextureWritetiff(     const char *path );

int  TextureCheckRGB( const char *path );
int  TextureCheckFloat( const char *path );

// Utilities used by file loaders
void TextureFlipv( void );
void TextureFliph( void );

void TextureFlipd( void );
void TextureFlipd_square( void );
void TextureFlipd_rectangle( void );

void TextureReadPixel( int x, int y, col4f &pixel );
void TextureWritePixel( int x, int y, col4f &pixel );

inline TEXBYTE *TextureLinear( int xpos, int ypos )
	{
	return( m_pdata + (m_width * ypos + xpos) * m_pixelsize );
	}

void TextureHalfSize( CTexture &psrc );
};
