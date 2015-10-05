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
 * File:    texcolor.h
 * Purpose: Manipulation routines for color data types
 *
 * Author:  Michael S. A. Robb
 *
 * Date:    August 2002
 * --------------------------------------------------------------------------
 */

#include <math.h>
// Avoid problems with Windows NT

#undef TEX_MINSHORT			
#undef TEX_MAXSHORT

#define TEX_MINSHORT 0
#define TEX_MAXSHORT 65535

#define TEX_MINLONG  0
#define TEX_MAXLONG  2147483647

typedef unsigned char  TEXBYTE;
typedef unsigned short TEXSHORT;
typedef long           TEXLONG;
typedef unsigned long  TEXULONG;

class col2b
	{
public:
    TEXBYTE m_mono;
	TEXBYTE m_alpha;

	col2b( int alpha, int mono )
		{	
        m_alpha = alpha; 
        m_mono  = mono; 
        };

	col2b() { m_alpha = 0; m_mono = 0; };

	~col2b() {};

	bool operator == (const col2b &ca )
		{ return( (m_alpha == ca.m_alpha) && (m_mono == ca.m_mono) ); };

	bool operator != (const col2b &ca )
		{ return( (m_alpha != ca.m_alpha) || (m_mono != ca.m_mono) ); };

	void minimum( col2b &ca, col2b &cb )
		{
		m_alpha = (ca.m_alpha < cb.m_alpha ) ? (ca.m_alpha) : (cb.m_alpha);
		m_mono  = (ca.m_mono  < cb.m_mono  ) ? (ca.m_mono)  : (cb.m_mono);
		};

	void maximum( col2b &ca, col2b &cb )
		{
		m_alpha = (ca.m_alpha > cb.m_alpha ) ? (ca.m_alpha) : (cb.m_alpha);
		m_mono  = (ca.m_mono  > cb.m_mono  ) ? (ca.m_mono)  : (cb.m_mono);
		};
	
	void minimum( col2b &ca )
		{
		m_alpha = (ca.m_alpha < m_alpha ) ? (ca.m_alpha) : m_alpha;
		m_mono  = (ca.m_mono  < m_mono  ) ? (ca.m_mono) : m_mono ;
		};

	void maximum( col2b &ca )
		{
		m_alpha = (ca.m_alpha > m_alpha ) ? (ca.m_alpha) : m_alpha;
		m_mono  = (ca.m_mono  > m_mono  ) ? (ca.m_mono) : m_mono;
		};

	void setmax( void )
		{
        m_alpha = 255; 
        m_mono =  255; 
        };

	void setmin( void )
		{ 
        m_alpha = 0; 
        m_mono =  0; 
        };
		
	};

class col2s
	{
public:
	TEXSHORT m_mono;
	TEXSHORT m_alpha;

	col2s( int mono, int alpha )
		{	m_mono = mono; m_alpha = alpha; };

	col2s() { m_mono = 0; m_alpha = 0; };

	~col2s() {};

	bool operator == (const col2s &ca )
		{ return( (m_mono == ca.m_mono) && (m_alpha == ca.m_alpha) ); };

	bool operator != (const col2s &ca )
		{ return( (m_mono != ca.m_mono) || (m_alpha != ca.m_alpha) ); };

	void minimum( col2s &ca, col2s &cb )
		{
		m_mono = (ca.m_mono < cb.m_mono ) ? (ca.m_mono) : (cb.m_mono);
		m_alpha  = (ca.m_alpha  < cb.m_alpha  ) ? (ca.m_alpha)  : (cb.m_alpha);
		};

	void maximum( col2s &ca, col2s &cb )
		{
		m_mono = (ca.m_mono > cb.m_mono ) ? (ca.m_mono) : (cb.m_mono);
		m_alpha  = (ca.m_alpha  > cb.m_alpha  ) ? (ca.m_alpha)  : (cb.m_alpha);
		};
	
	void minimum( col2s &ca )
		{
		m_mono = (ca.m_mono < m_mono ) ? (ca.m_mono) : m_mono;
		m_alpha  = (ca.m_alpha  < m_alpha  ) ? (ca.m_alpha) : m_alpha ;
		};

	void maximum( col2s &ca )
		{
		m_mono = (ca.m_mono > m_mono ) ? (ca.m_mono) : m_mono;
		m_alpha  = (ca.m_alpha  > m_alpha  ) ? (ca.m_alpha) : m_alpha;
		};

	void setmax( void )
		{ m_mono = TEX_MAXSHORT; m_alpha = TEX_MAXSHORT; };

	void setmin( void )
		{ m_mono = TEX_MINSHORT; m_alpha = TEX_MINSHORT; };
		
	};

class col1f
        {
public:
        float m_mono;
        float m_alpha;

        col1f( float mono )
                { m_mono = mono; };

        col1f() { m_mono = 0; };

        ~col1f() {};

        bool operator == (const col1f &ca )
                { return( (m_mono == ca.m_mono) ); };

        bool operator != (const col1f &ca )
                { return( (m_mono != ca.m_mono) ); };

        void minimum( col1f &ca, col1f &cb )                 
		{
                m_mono = (ca.m_mono < cb.m_mono ) ? (ca.m_mono) : (cb.m_mono);
                };

        void maximum( col1f &ca, col1f &cb )
                {
                m_mono = (ca.m_mono > cb.m_mono ) ? (ca.m_mono) : (cb.m_mono);
                };

        void minimum( col1f &ca )
                {
                m_mono = (ca.m_mono < m_mono ) ? (ca.m_mono) : m_mono;
                };

        void maximum( col1f &ca )
                {
                m_mono = (ca.m_mono > m_mono ) ? (ca.m_mono) : m_mono;
                };

        void setmax( void )
                { m_mono = 1000.0f; };

        void setmin( void )
                { m_mono = -1000.0f; };
        };

class col2f
	{
public:
	float m_mono;
	float m_alpha;

	col2f( float mono, float alpha )
		{	m_mono = mono; m_alpha = alpha; };

	col2f() { m_mono = 0; m_alpha = 0; };

	~col2f() {};

	bool operator == (const col2f &ca )
		{ return( (m_mono == ca.m_mono) && (m_alpha == ca.m_alpha) ); };

	bool operator != (const col2f &ca )
		{ return( (m_mono != ca.m_mono) || (m_alpha != ca.m_alpha) ); };

	void minimum( col2f &ca, col2f &cb )
		{
		m_mono = (ca.m_mono < cb.m_mono ) ? (ca.m_mono) : (cb.m_mono);
		m_alpha  = (ca.m_alpha  < cb.m_alpha  ) ? (ca.m_alpha)  : (cb.m_alpha);
		};

	void maximum( col2f &ca, col2f &cb )
		{
		m_mono = (ca.m_mono > cb.m_mono ) ? (ca.m_mono) : (cb.m_mono);
		m_alpha  = (ca.m_alpha  > cb.m_alpha  ) ? (ca.m_alpha)  : (cb.m_alpha);
		};
	
	void minimum( col2f &ca )
		{
		m_mono = (ca.m_mono < m_mono ) ? (ca.m_mono) : m_mono;
		m_alpha  = (ca.m_alpha  < m_alpha  ) ? (ca.m_alpha) : m_alpha ;
		};

	void maximum( col2f &ca )
		{
		m_mono = (ca.m_mono > m_mono ) ? (ca.m_mono) : m_mono;
		m_alpha  = (ca.m_alpha  > m_alpha  ) ? (ca.m_alpha) : m_alpha;
		};

	void setmax( void )
		{ m_mono = 1000.0f; m_alpha = 1000.0f; };

	void setmin( void )
		{ m_mono = -1000.0f; m_alpha = -1000.0f; };
		
	};

class col3b
	{
public:
	TEXBYTE m_red;
	TEXBYTE m_green;
	TEXBYTE m_blue;

	/* Function prototypes */

	col3b( int red, int green, int blue ) 
		{ m_red = red; m_green = green; m_blue = blue; };

	col3b() { m_red = m_green = m_blue = 0; };
	~col3b() {};

	bool operator == (const col3b &ca )
		{ return( (m_red == ca.m_red) && (m_green == ca.m_green) && (m_blue == ca.m_blue) ); };

	bool operator != (const col3b &ca )
		{ return( (m_red != ca.m_red) || (m_green != ca.m_green) || (m_blue != ca.m_blue) ); };

	void minimum( col3b &ca, col3b &cb )
		{
		m_red   = (ca.m_red   < cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
		m_green = (ca.m_green < cb.m_green ) ? (ca.m_green) : (cb.m_green);
		m_blue  = (ca.m_blue  < cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
		};

	void maximum( col3b &ca, col3b &cb )
		{
		m_red   = (ca.m_red   > cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
		m_green = (ca.m_green > cb.m_green ) ? (ca.m_green) : (cb.m_green);
		m_blue  = (ca.m_blue  > cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
		};

	void minimum( col3b &ca )
		{
		m_red   = (ca.m_red   < m_red   ) ? (ca.m_red)   : m_red;
		m_green = (ca.m_green < m_green ) ? (ca.m_green) : m_green;
		m_blue  = (ca.m_blue  < m_blue  ) ? (ca.m_blue)  : m_blue; 
		};

	void maximum( col3b &ca )
		{
		m_red   = (ca.m_red   > m_red   ) ? (ca.m_red)   : m_red;
		m_green = (ca.m_green > m_green ) ? (ca.m_green) : m_green;
		m_blue  = (ca.m_blue  > m_blue  ) ? (ca.m_blue)  : m_blue;
		};

	void setmin( void )
		{ m_red = m_green = m_blue = 0;	};

	void setmax( void )
		{ m_red = m_green = m_blue = 255; };
	};

class col3s
  {
public:
  TEXSHORT m_red;
  TEXSHORT m_green;
  TEXSHORT m_blue;

  /* Function prototypes */

   col3s() { m_red = m_green = m_blue = 0; };

   col3s( SHORT red, SHORT green, SHORT blue ) 
	{
	m_red = red;
	m_green = green;	
	m_blue = blue;
	};

  ~col3s() {};

  void minimum( col3s &ca, col3s &cb )
	{
	m_red   = (ca.m_red   < cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green < cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  < cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	};

  void maximum( col3s &ca, col3s &cb )
	{
	m_red   = (ca.m_red   > cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green > cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  > cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	};

  void minimum( col3s &ca )
 	{
	m_red   = (ca.m_red   < m_red   ) ? (ca.m_red)   : m_red;
	m_green = (ca.m_green < m_green ) ? (ca.m_green) : m_green;
	m_blue  = (ca.m_blue  < m_blue  ) ? (ca.m_blue)  : m_blue; 
	};

  void maximum( col3s &ca )
	{
	m_red   = (ca.m_red   > m_red   ) ? (ca.m_red) : m_red;
	m_green = (ca.m_green > m_green ) ? (ca.m_green) : m_green;
	m_blue  = (ca.m_blue  > m_blue  ) ? (ca.m_blue) : m_blue;
	};

  void setmin( void )
		{ m_red = m_green = m_blue = TEX_MINSHORT; };

  void setmax( void )
		{ m_red = m_green = m_blue =  TEX_MAXSHORT; };
  };

// --------------------------------------------------------------------------
// col3l
// --------------------------------------------------------------------------

class col3l
  {
public:
  TEXLONG m_red;
  TEXLONG m_green;
  TEXLONG m_blue;

  /* Function prototypes */

   col3l() { m_red = m_green = m_blue = 0; };

   col3l( SHORT red, SHORT green, SHORT blue )
        {
        m_red = red;
        m_green = green;
        m_blue = blue;
        };

  col3l( const col3l &ca )
	{
	m_red   = ca.m_red;
	m_green = ca.m_green;
	m_blue  = ca.m_blue;
	}

  col3l( col3b &ca )
	{
	m_red   = ca.m_red;
	m_green = ca.m_green;
	m_blue  = ca.m_blue;
	}

  col3l( const col3b &ca )
	{
	m_red   = ca.m_red;
	m_green = ca.m_green;
	m_blue  = ca.m_blue;
	}

  ~col3l() {};
	
  col3l operator + ( col3l &ca )
	{
	col3l result;

	result = *this;
	result += ca;

	return( result );
	}

  col3l operator - ( col3l &ca )
	{
	col3l result;

	result = *this;
	result -= ca;

	return( result );
	}

  col3l operator * ( col3l &ca )
	{
	col3l result;

	result = *this;
	result *= ca;

	return( result);
	}

  col3l operator / ( col3l &ca )
	{
	col3l result;

	result = *this;
	result /= ca;

	return( result );
	}

  col3l operator * ( int scale )
	{
	col3l result;

	result = *this;
	result *= scale;

	return( result );
	}

  col3l operator * ( unsigned int scale )
	{
	col3l result;

	result = *this;
	result *= scale;

	return( result );
	}

  col3l operator / ( int scale )
	{
	col3l result;

	result = *this;
	result /= scale;

	return( result );
	}

  col3l operator / ( unsigned int scale )
	{
	col3l result;

	result = *this;

	return( result /= scale );
	}

  col3l operator += ( int scale )
	{
	m_red   += scale;
	m_green += scale;
	m_blue  += scale;

	return( *this);
	}

  col3l operator += ( unsigned int scale )
	{
	m_red   += scale;
	m_green += scale;
	m_blue  += scale;

	return( *this);
	}

  col3l operator -= ( int scale )
	{
	m_red   -= scale;
	m_green -= scale;
	m_blue  -= scale;

	return( *this);
	}

  col3l operator -= ( unsigned int scale )
	{
	m_red   -= scale;
	m_green -= scale;
	m_blue  -= scale;

	return( *this);
	}

  col3l operator *= ( int scale )
	{
	m_red   *= scale;
	m_green *= scale;
	m_blue  *= scale;

	return( *this);
	}

  col3l operator *= ( unsigned int scale )
	{
	m_red   *= scale;
	m_green *= scale;
	m_blue  *= scale;

	return( *this);
	}

  col3l operator /= ( int scale )
	{
	m_red   /= scale;
	m_green /= scale;
	m_blue  /= scale;

	return( *this);
	}

  col3l operator /= ( unsigned int scale )
	{
	m_red   /= scale;
	m_green /= scale;
	m_blue  /= scale;

	return( *this);
	}

  col3l operator += ( const col3l &ca )
	{
	m_red   += ca.m_red;
	m_green += ca.m_green;
	m_blue  += ca.m_blue;

	return( *this );
	}

  col3l operator += ( const col3b &ca )
        {
        m_red   += ca.m_red;
        m_green += ca.m_green;
        m_blue  += ca.m_blue;

        return( *this );
        }

  col3l operator -= ( const col3l &ca )
	{
	m_red   -= ca.m_red;
	m_green -= ca.m_green;
	m_blue  -= ca.m_blue;

	return( *this );
	}

  col3l operator -= ( const col3b &ca )
        {
        m_red   -= ca.m_red;
        m_green -= ca.m_green;
        m_blue  -= ca.m_blue;

        return( *this );
        }

  col3l operator *= ( const col3l &ca )
	{
	m_red   *= ca.m_red;
	m_green *= ca.m_green;
	m_blue  *= ca.m_blue;

	return( *this );
	}

  col3l operator *= ( const col3b &ca )
	{
	m_red   *= ca.m_red;
	m_green *= ca.m_green;
	m_blue  *= ca.m_blue;

	return( *this );
	}

  col3l operator /= ( const col3l &ca )
	{
	m_red   /= ca.m_red;
	m_green /= ca.m_green;
	m_blue  /= ca.m_blue;

	return( *this );
	}

  col3l operator /= ( const col3b &ca )
	{
	m_red   /= ca.m_red;
	m_green /= ca.m_green;
	m_blue  /= ca.m_blue;

	return( *this );
	}

  col3l & operator = ( col3b &ca )
	{
	m_red   = ca.m_red;
	m_green = ca.m_green;
	m_blue  = ca.m_blue;

	return( *this );
	}

  void zero( void )
	{
	m_red = m_green = m_blue = 0L;
	}

  void minimum( col3l &ca, col3l &cb )
        {
        m_red   = (ca.m_red   < cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
        m_green = (ca.m_green < cb.m_green ) ? (ca.m_green) : (cb.m_green);
        m_blue  = (ca.m_blue  < cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
        };

  void maximum( col3l &ca, col3l &cb )
        {
        m_red   = (ca.m_red   > cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
        m_green = (ca.m_green > cb.m_green ) ? (ca.m_green) : (cb.m_green);
        m_blue  = (ca.m_blue  > cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
        };

  void minimum( col3l &ca )
        {
        m_red   = (ca.m_red   < m_red   ) ? (ca.m_red)   : m_red;
        m_green = (ca.m_green < m_green ) ? (ca.m_green) : m_green;
        m_blue  = (ca.m_blue  < m_blue  ) ? (ca.m_blue)  : m_blue;
        };

  void maximum( col3l &ca )
        {
        m_red   = (ca.m_red   > m_red   ) ? (ca.m_red) : m_red;
        m_green = (ca.m_green > m_green ) ? (ca.m_green) : m_green;
        m_blue  = (ca.m_blue  > m_blue  ) ? (ca.m_blue) : m_blue;
        };

  void setmin( void )
                { m_red = m_green = m_blue = TEX_MINLONG; };

  void setmax( void )
                { m_red = m_green = m_blue =  TEX_MAXLONG; };

  void toc3b( col3b &cdst )
	{
	cdst.m_red   = m_red;
	cdst.m_green = m_green;
	cdst.m_blue  = m_blue;
	}

  void fromc3b( col3b &csrc )
	{
	m_red   = csrc.m_red;
	m_green = csrc.m_green;
	m_blue  = csrc.m_blue;
	}
  };

class col3f
  {
public:
  float m_red;
  float m_green;
  float m_blue;

  /* Function prototypes */

   col3f() { m_red = m_green = m_blue = 0.0f; };

   col3f( float red, float green, float blue ) 
	{
	m_red = red;
	m_green = green;	
	m_blue = blue;
	};

  ~col3f() {};  
  col3f operator + ( const col3f &ca ) { return col3f( m_red + ca.m_red, m_green + ca.m_green, m_blue + ca.m_blue); };
  col3f operator - ( const col3f &ca ) { return col3f( m_red - ca.m_red, m_green - ca.m_green, m_blue - ca.m_blue); };
  col3f operator * ( const col3f &ca ) { return col3f( m_red * ca.m_red, m_green * ca.m_green, m_blue * ca.m_blue); };
  col3f operator / ( const col3f &ca ) { return col3f( m_red / ca.m_red, m_green / ca.m_green, m_blue / ca.m_blue); };

  col3f operator * ( const float fcal ) { return col3f( m_red * fcal, m_green * fcal, m_blue * fcal ); };
  col3f operator / ( const float fcal ) { return col3f( m_red / fcal, m_green / fcal, m_blue / fcal ); };

   void operator += ( col3f &ca )
           { m_red += ca.m_red; m_green += ca.m_green; m_blue += ca.m_blue;  };

   void operator -= ( col3f &ca )
           { m_red -= ca.m_red; m_green -= ca.m_green; m_blue -= ca.m_blue;  };

   void operator *= ( col3f &ca )
           { m_red *= ca.m_red; m_green *= ca.m_green; m_blue *= ca.m_blue;  };

   void operator /= ( col3f &ca )
           { m_red /= ca.m_red; m_green /= ca.m_green; m_blue /= ca.m_blue;  };

   void operator *= (float scale )
           { m_red *= scale; m_green *= scale; m_blue *= scale; };

   void operator /= (float scale )
           { m_red /= scale; m_green /= scale; m_blue /= scale; };

   friend col3f operator * ( const col3f &ca, float scale ) 
	{ return col3f( ca.m_red  * scale, ca.m_green * scale, 
			   ca.m_blue * scale ); };

   friend col3f operator * ( float scale, const col3f &ca ) 
	{ return col3f( ca.m_red  * scale, ca.m_green * scale, 
			   ca.m_blue * scale ); };

   friend col3f operator / ( const col3f &ca, float scale ) 
	{ return col3f( ca.m_red  * scale, ca.m_green * scale, 
			   ca.m_blue * scale ); };

   friend col3f operator / ( float scale, const col3f &ca ) 
	{ return col3f( ca.m_red  * scale, ca.m_green * scale, 
			   ca.m_blue * scale ); };

  void minimum( col3f &ca, col3f &cb )
	{
	m_red   = (ca.m_red   < cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green < cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  < cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	};

  void maximum( col3f &ca, col3f &cb )
	{
	m_red   = (ca.m_red   > cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green > cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  > cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	};

  void minimum( col3f &ca )
 	{
	m_red   = (ca.m_red   < m_red   ) ? (ca.m_red) : m_red;
	m_green = (ca.m_green < m_green ) ? (ca.m_green) : m_green;
	m_blue  = (ca.m_blue  < m_blue  ) ? (ca.m_blue) : m_blue; 
	};

  void maximum( col3f &ca )
	{
	m_red   = (ca.m_red   > m_red   ) ? (ca.m_red)   : m_red;
	m_green = (ca.m_green > m_green ) ? (ca.m_green) : m_green;
	m_blue  = (ca.m_blue  > m_blue  ) ? (ca.m_blue)  : m_blue;
	};

  void setmin( void )
		{ m_red = m_green = m_blue = -1000.0f; };

  void setmax( void )
		{ m_red = m_green = m_blue = 1000.0f; };

  void fromc3b( col3b &ca )
	{
	m_red   = ca.m_red   / 255.0f;
	m_green = ca.m_green / 255.0f;
	m_blue  = ca.m_blue  / 255.0f;
	}

   void toc3b(   col3b &ca )
	{
	ca.m_red   = (int)(m_red   * 255.0f );
	ca.m_green = (int)(m_green * 255.0f );
	ca.m_blue  = (int)(m_blue  * 255.0f );
	}

   void pow( float fpow )
	{
	m_red   = powf( m_red,   fpow );
	m_green = powf( m_green, fpow );
	m_blue  = powf( m_blue,  fpow );
	}

   void pow( col3f &color )
	{
	m_red   = powf( m_red,   color.m_red   );
	m_green = powf( m_green, color.m_green );
	m_blue  = powf( m_blue,  color.m_blue  );
	}
  };

class col3d
  {
public:
 double m_red;
  double m_green;
  double m_blue;
  
  /* Function prototypes */

   col3d() { m_red = m_green = m_blue = 0.0; };

   col3d( double red, double green, double blue )
        {               
        m_red = red;
        m_green = green;
        m_blue = blue;
        };              
 
  ~col3d() {};
  col3d operator + ( const col3d &ca ) { return col3d( m_red + ca.m_red, m_green + ca.m_green, m_blue + ca.m_blue); };
  col3d operator - ( const col3d &ca ) { return col3d( m_red - ca.m_red, m_green - ca.m_green, m_blue - ca.m_blue); };
  col3d operator * ( const col3d &ca ) { return col3d( m_red * ca.m_red, m_green * ca.m_green, m_blue * ca.m_blue); };
  col3d operator / ( const col3d &ca ) { return col3d( m_red / ca.m_red, m_green / ca.m_green, m_blue / ca.m_blue); };
   
  col3d operator * ( const double fcal ) { return col3d( m_red * fcal, m_green * fcal, m_blue * fcal ); };
  col3d operator / ( const double fcal ) { return col3d( m_red / fcal, m_green / fcal, m_blue / fcal ); };

   void operator += ( col3d &ca )
           { m_red += ca.m_red; m_green += ca.m_green; m_blue += ca.m_blue;  };
        
   void operator -= ( col3d &ca )
           { m_red -= ca.m_red; m_green -= ca.m_green; m_blue -= ca.m_blue;  };
  
   void operator *= ( col3d &ca )
           { m_red *= ca.m_red; m_green *= ca.m_green; m_blue *= ca.m_blue;  };
                
   void operator /= ( col3d &ca )
           { m_red /= ca.m_red; m_green /= ca.m_green; m_blue /= ca.m_blue;  };
        
   void operator *= (double scale )
           { m_red *= scale; m_green *= scale; m_blue *= scale; };
        
   void operator /= (double scale )
           { m_red /= scale; m_green /= scale; m_blue /= scale; };

   friend col3d operator * ( const col3d &ca, double scale )
        { return col3d( ca.m_red  * scale, ca.m_green * scale,
                           ca.m_blue * scale ); };

   friend col3d operator * ( double scale, const col3d &ca )
        { return col3d( ca.m_red  * scale, ca.m_green * scale,
                           ca.m_blue * scale ); };

   friend col3d operator / ( const col3d &ca, double scale )
        { return col3d( ca.m_red  * scale, ca.m_green * scale,
                           ca.m_blue * scale ); };

   friend col3d operator / ( double scale, const col3d &ca )
        { return col3d( ca.m_red  * scale, ca.m_green * scale,
                           ca.m_blue * scale ); };

  void minimum( col3d &ca, col3d &cb )
        {
        m_red   = (ca.m_red   < cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
        m_green = (ca.m_green < cb.m_green ) ? (ca.m_green) : (cb.m_green);
        m_blue  = (ca.m_blue  < cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
        };

  void maximum( col3d &ca, col3d &cb )
        {
        m_red   = (ca.m_red   > cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
        m_green = (ca.m_green > cb.m_green ) ? (ca.m_green) : (cb.m_green);
        m_blue  = (ca.m_blue  > cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
        };

  void minimum( col3d &ca )
        {
        m_red   = (ca.m_red   < m_red   ) ? (ca.m_red) : m_red;
        m_green = (ca.m_green < m_green ) ? (ca.m_green) : m_green;
        m_blue  = (ca.m_blue  < m_blue  ) ? (ca.m_blue) : m_blue;
        };

  void maximum( col3d &ca )
        {
        m_red   = (ca.m_red   > m_red   ) ? (ca.m_red)   : m_red;
        m_green = (ca.m_green > m_green ) ? (ca.m_green) : m_green;
        m_blue  = (ca.m_blue  > m_blue  ) ? (ca.m_blue)  : m_blue;
        };

  void setmin( void )
                { m_red = m_green = m_blue = -1000.0; };

  void setmax( void )
                { m_red = m_green = m_blue = 1000.0; };

  void fromc3b( col3b &ca )
        {
        m_red   = ca.m_red   / 255.0;
        m_green = ca.m_green / 255.0;
        m_blue  = ca.m_blue  / 255.0;
        }

   void toc3b(   col3b &ca )
        {
        ca.m_red   = (int)(m_red   * 255.0 );
        ca.m_green = (int)(m_green * 255.0 );
        ca.m_blue  = (int)(m_blue  * 255.0 );
        }

   void pow( double fpow )
        {
        m_red   = ::pow( m_red,   fpow );
        m_green = ::pow( m_green, fpow );
        m_blue  = ::pow( m_blue,  fpow );
        }
   
   void pow( col3d &color )
        {
        m_red   = ::pow( m_red,   color.m_red   );
        m_green = ::pow( m_green, color.m_green );
        m_blue  = ::pow( m_blue,  color.m_blue  );
        }

  };


class col4b
  {
public:
  TEXBYTE m_red;
  TEXBYTE m_green;
  TEXBYTE m_blue;
  TEXBYTE m_alpha;

  /* Function prototypes */

	col4b( int red, int green, int blue )
			{ m_red = red; m_green = green; m_blue = blue; m_alpha = 255; };

	col4b( int red, int green, int blue, int alpha )
			{ m_red = red; m_green = green; m_blue = blue; m_alpha = alpha; };

   col4b() { m_red = m_green = m_blue = m_alpha = 0; };
  ~col4b() {};  

 void operator += (const col4b &ca )
   { m_red += ca.m_red; m_green += ca.m_green; m_blue += ca.m_blue; m_alpha += ca.m_alpha; };

 void operator -= (const col4b &ca )
   { m_red -= ca.m_red; m_green -= ca.m_green; m_blue -= ca.m_blue; m_alpha -= ca.m_alpha; };

 bool operator == (const col4b &ca )
	{ return( (m_red == ca.m_red) && (m_green == ca.m_green) && (m_blue == ca.m_blue) && (m_alpha == ca.m_alpha ) ); };

  bool operator != (const col4b &ca )
	{ return( (m_red != ca.m_red) || (m_green != ca.m_green) || (m_blue != ca.m_blue) || (m_alpha != ca.m_alpha ) ); };

  col3b GetColor3b( void )
		{
		return( col3b( m_red, m_green, m_blue ) );
		}

  void minimum( col4b &ca, col4b &cb )
	{
	m_red   = (ca.m_red   < cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green < cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  < cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	};

  void maximum( col4b &ca, col4b &cb )
	{
	m_red   = (ca.m_red   > cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green > cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  > cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	};

  void minimum( col4b &ca )
	{
	m_red   = (ca.m_red   < m_red   ) ? (ca.m_red)   : (m_red);
	m_green = (ca.m_green < m_green ) ? (ca.m_green) : (m_green);
	m_blue  = (ca.m_blue  < m_blue  ) ? (ca.m_blue)  : (m_blue);
	};

  void maximum( col4b &ca )
	{
	m_red   = (ca.m_red   > m_red   ) ? (ca.m_red)   : (m_red);
	m_green = (ca.m_green > m_green ) ? (ca.m_green) : (m_green);
	m_blue  = (ca.m_blue  > m_blue  ) ? (ca.m_blue)  : (m_blue);
	};

  void setmin( void )
	{ m_red = m_green = m_blue = m_alpha = 0; };

  void setmax( void )
	{ m_red = m_green = m_blue = m_alpha = 255; };


  void zero( void )
  	{
  	m_red = m_green = m_blue = m_alpha = 0;
  	}

  int nonzero( void )
  	{
  	return( m_red != 0 || m_green != 0 || m_blue != 0 );
  	}

  int iszero( void )
  	{
  	return( (m_red == 0) && (m_green == 0) && (m_blue == 0) );
  	}
  };

class col4s
  {
public:
  TEXSHORT m_red;
  TEXSHORT m_green;
  TEXSHORT m_blue;
  TEXSHORT m_alpha;

  /* Function prototypes */

   col4s() { m_red = m_green = m_blue = m_alpha = 0; };

   col4s( SHORT red, SHORT green, SHORT blue, SHORT alpha )
		{
		m_red   = red;
		m_green = green;
		m_blue  = blue;
		m_alpha = alpha;
		};

  ~col4s() {};   
  };

class col4f
  {
public:
  float m_red;    /* Red   */
  float m_green;  /* Green */
  float m_blue;   /* Blue  */
  float m_alpha;  /* Alpha */

  /* Function prototypes */

   col4f( void ) { m_red = m_green = m_blue = m_alpha = 0.0f; };

	col4f( float fval )
		{	
		m_red = m_green = m_blue = m_alpha = fval;
		}

   col4f( float red, float green, float blue, float alpha ) 
     { m_red = red; m_green = green; m_blue = blue; m_alpha = alpha; };

   col4f( const col3f &col, const float falpha )
	{
	m_red   = col.m_red;
	m_green = col.m_green;
	m_blue  = col.m_blue;
	m_alpha = falpha;
	}

   col4f( float *cols )
	{ 
	m_red = cols[0]; 
	m_green = cols[1]; 
	m_blue = cols[2]; 
	m_alpha = cols[3]; 
	};

    col4f( col3f &cval )
	{
	m_red = cval.m_red; 
	m_green = cval.m_green; 
	m_blue = cval.m_blue; 
	m_alpha = 1.0f; 
	};
     
  void tohls( float *pcolhls );
  void fromhls( float *pcolhls );

  ~col4f() {};   

	col4f & operator = ( float fval ) 
	{ 
	m_red = m_green = m_blue = m_alpha = fval; 

	return( *this );
	};

	
  col4f operator + ( const col4f &ca ) 
	{ return col4f( m_red + ca.m_red, m_green + ca.m_green, m_blue + ca.m_blue, m_alpha+ca.m_alpha ); };

  col4f operator - ( void ) 
	{ return col4f( -m_red, -m_green, -m_blue, -m_alpha ); };

  col4f operator - ( const col4f &ca ) { return col4f( m_red - ca.m_red, m_green - ca.m_green, m_blue - ca.m_blue, m_alpha+ca.m_alpha ); };

  col4f operator * ( const col4f &ca ) { return col4f( m_red * ca.m_red, m_green * ca.m_green, m_blue * ca.m_blue, m_alpha+ca.m_alpha ); };

  col4f operator / ( const col4f &ca ) { return col4f( m_red / ca.m_red, m_green / ca.m_green, m_blue / ca.m_blue, m_alpha+ca.m_alpha ); };

  col4f operator * ( const float fcal ) { return col4f( m_red * fcal, m_green * fcal, m_blue * fcal, m_alpha * fcal ); };

  col4f operator / ( const float fcal ) { return col4f( m_red / fcal, m_green / fcal, m_blue / fcal, m_alpha / fcal ); };

void operator += ( const col3f &ca )
	{ m_red += ca.m_red; m_green += ca.m_green; m_blue += ca.m_blue; };

void operator -= ( const col3f &ca )
	{ m_red -= ca.m_red; m_green -= ca.m_green; m_blue -= ca.m_blue; };

void operator *= ( const col3f &ca )
           { m_red *= ca.m_red; m_green *= ca.m_green; m_blue *= ca.m_blue; };

void operator /= ( const col3f &ca )
           { m_red /= ca.m_red; m_green /= ca.m_green; m_blue /= ca.m_blue; };

void operator += ( const col4f &ca )
           { m_red += ca.m_red; m_green += ca.m_green; m_blue += ca.m_blue; m_alpha += ca.m_alpha; };

void operator -= ( const col4f &ca )
           { m_red -= ca.m_red; m_green -= ca.m_green; m_blue -= ca.m_blue; m_alpha -= ca.m_alpha; };

void operator *= ( const col4f &ca )
           { m_red *= ca.m_red; m_green *= ca.m_green; m_blue *= ca.m_blue; m_alpha *= ca.m_alpha; };

void operator /= ( const col4f &ca )
           { m_red /= ca.m_red; m_green /= ca.m_green; m_blue /= ca.m_blue; m_alpha /= ca.m_alpha; };

/*
   void operator += ( const col4f &ca )
           { m_red += ca.m_red; m_green += ca.m_green; m_blue += ca.m_blue; m_alpha += ca.m_alpha; };

   void operator -= ( const col4f &ca )
           { m_red -= ca.m_red; m_green -= ca.m_green; m_blue -= ca.m_blue; m_alpha -= ca.m_alpha; };

   void operator *= ( const col4f &ca )
           { m_red *= ca.m_red; m_green *= ca.m_green; m_blue *= ca.m_blue; m_alpha *= ca.m_alpha; };

   void operator /= ( const col4f &ca )
           { m_red /= ca.m_red; m_green /= ca.m_green; m_blue /= ca.m_blue; m_alpha /= ca.m_alpha; };
*/
   void operator *= (float scale )
           { m_red *= scale; m_green *= scale; m_blue *= scale; };

   void operator /= (float scale )
           { m_red /= scale; m_green /= scale; m_blue /= scale; };

   col4f & operator = ( const col3b &ca )
			{
			m_red   = (float) ca.m_red   / 255.0f;
			m_green = (float) ca.m_green / 255.0f;
			m_blue  = (float) ca.m_blue  / 255.0f;

			return (*this );
			};

	void operator = ( const col3s &ca )
			{
			m_red   = (float) ca.m_red   / 65535.0f;
			m_green = (float) ca.m_green / 65535.0f;
			m_blue  = (float) ca.m_blue  / 65535.0f;
			}	

	void operator = ( const col2b &ca )
			{
			m_red   = (float) ca.m_mono / 255.0f;
			m_green = (float) ca.m_alpha / 255.0f;
			m_blue  = 0.0f;
			m_alpha = 1.0f;
			}

	void operator = ( const col2s &ca )
			{
			m_red 	= (float) ca.m_mono / 65535.0;
			m_green = (float) ca.m_alpha / 65535.0;
			m_blue  = 0.0f;
			m_alpha = 1.0f;
			}

	void operator = ( const col2f &ca )
			{
			m_red   = ca.m_mono;
			m_green = ca.m_alpha;
			m_blue  = 0.0f;
			m_alpha = 1.0f;
			}

	void operator = ( const col3f &ca )
			{
			m_red   = ca.m_red;
			m_green = ca.m_green;
			m_blue  = ca.m_blue;
			m_alpha = 1.0f;
			}

	void operator = ( const col4b &ca )
			{
			m_red   = (float) ca.m_red   / 255.0f;
			m_green = (float) ca.m_green / 255.0f;
			m_blue  = (float) ca.m_blue  / 255.0f;
			m_alpha = (float) ca.m_alpha / 255.0f;
			};

	void operator = ( const col4s &ca )
			{
			m_red = (float) ca.m_red   / 255.0f;
			m_green = (float) ca.m_green / 255.0f;
			m_blue  = (float) ca.m_blue  / 255.0f;
			m_alpha = (float) ca.m_alpha / 255.0f;
			};

	col4f &operator = ( const col4f &ca )
			{
			m_red   = ca.m_red;
			m_green = ca.m_green;
			m_blue  = ca.m_blue;
			m_alpha = ca.m_alpha;

			return( *this );
			};

	col4f &operator = ( col4f &ca )
			{
			m_red   = ca.m_red;
			m_green = ca.m_green;
			m_blue  = ca.m_blue;
			m_alpha = ca.m_alpha;

			return( *this );
			};

	void setvalue( float fr, float fg, float fb, float fa )
		{
		m_red = fr;
		m_green = fg;
		m_blue = fb;
		m_alpha = fa;
		}

	col3b GetColor3b( void )
		{
		return( col3b( (int)( m_red   * 255.0f),
				  (int)( m_green * 255.0f),
				  (int)( m_blue  * 255.0f) ) );
		}

	col3f GetColor3f( void )
		{
		return( col3f( m_red, m_green, m_blue ) );
		}


	col3s GetColor3s( void )
		{
		return( col3s( (int)( m_red   * TEX_MAXSHORT ),
				  (int)( m_green * TEX_MAXSHORT ),
				  (int)( m_blue  * TEX_MAXSHORT ) ) );
		}

	col4b GetColor4b( void )
		{
		return( col4b( (int)( m_red   * 255.0f),
				  (int)( m_green * 255.0f), 
                                  (int)( m_blue  * 255.0f),
				  (int)( m_alpha * 255.0f) ) );
		}

	col4s GetColor4s( void )
		{
		return( col4s( (int)( m_red   * TEX_MAXSHORT),
				  (int)( m_green * TEX_MAXSHORT), 
                                  (int)( m_blue  * TEX_MAXSHORT),
				  (int)( m_alpha * TEX_MAXSHORT) ) );
		}
/*
   friend col4f operator * ( col3f &ca, float scale ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, 1.0f ); };

   friend col4f operator * ( float scale, col3f &ca ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, 1.0f ); };

   friend col4f operator / ( col3f &ca, float scale ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, 1.0f ); };

   friend col4f operator / ( float scale, col3f &ca ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, 1.0f ); };
*/

   friend col4f operator * ( const col4f &ca, float scale ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, ca.m_alpha ); };

   friend col4f operator * ( float scale, const col4f &ca ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, ca.m_alpha ); };

   friend col4f operator / ( const col4f &ca, float scale ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, ca.m_alpha ); };

   friend col4f operator / ( float scale, const col4f &ca ) { return col4f( ca.m_red * scale, ca.m_green * scale, ca.m_blue * scale, ca.m_alpha ); };


  void minimum( col4f &ca, col4f &cb )
	{
	m_red   = (ca.m_red   < cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green < cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  < cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	m_alpha  = (ca.m_alpha  < cb.m_alpha  ) ? (ca.m_alpha) : (cb.m_alpha);
	};

  void maximum( col4f &ca, col4f &cb )
	{
	m_red   = (ca.m_red   > cb.m_red   ) ? (ca.m_red)   : (cb.m_red);
	m_green = (ca.m_green > cb.m_green ) ? (ca.m_green) : (cb.m_green);
	m_blue  = (ca.m_blue  > cb.m_blue  ) ? (ca.m_blue)  : (cb.m_blue);
	m_alpha = (ca.m_alpha  > cb.m_alpha  ) ? (ca.m_alpha) : (cb.m_alpha);
	};

  void minimum( col4f &ca )
	{
	m_red   = (ca.m_red   < m_red   ) ? (ca.m_red)   : (m_red);
	m_green = (ca.m_green < m_green ) ? (ca.m_green) : (m_green);
	m_blue  = (ca.m_blue  < m_blue  ) ? (ca.m_blue)  : (m_blue);
	m_alpha = (ca.m_alpha < m_alpha  ) ? (ca.m_alpha) : (m_alpha);
	};

  void maximum( col4f &ca )
	{
	m_red   = (ca.m_red   > m_red   ) ? (ca.m_red)   : (m_red);
	m_green = (ca.m_green > m_green ) ? (ca.m_green) : (m_green);
	m_blue  = (ca.m_blue  > m_blue  ) ? (ca.m_blue)  : (m_blue);
	m_alpha = (ca.m_alpha  > m_alpha  ) ? (ca.m_alpha) : (m_alpha);
	};

   void setmin( void )
		{ m_red = m_green = m_blue = m_alpha = -1000.0f; };

   void setmax( void )
		{ m_red = m_green = m_blue = m_alpha = 1000.0f; };

   float length( void ) { return( (float)sqrt( m_red * m_red + m_green * m_green + m_blue * m_blue ) ); }

   float distance( col4f *ca) { return (*this - *ca).length(); };

   void linear( col3f &ca, col3f &cb, float val ) 
		{ *this = (1.0f - val) * ca + val * cb; };

   void linear( col4f &ca, col4f &cb, float val ) 
		{ *this = (1.0f - val) * ca + val * cb; };

   void zero( void ) { m_red = m_green = m_blue = m_alpha = 0.0f; };
   void clamp( void );
   void random( void );
   void blend(   col4f &ca, col4f &cb, float blend );
  // void maxpair( col4f &ca, col4f &cb );
   void maxvalue( col4f &ca );
   float distlinear( col4f &ca ) {
		return( (float) fabs( m_red   - ca.m_red ) +
			    (float) fabs( m_green - ca.m_green ) +
			    (float) fabs( m_blue  - ca.m_blue  ) ); };

   void blendrange( col4f *ca, col4f *cb, int cnum );
   void setmono( float mono );
   void sethue( float hue );

   void negate( col4f &ca, int hue );

   float dot(    col4f &ca )
		{  return( ( m_red * ca.m_red ) +
          ( m_green * ca.m_green ) + 
          ( m_blue  * ca.m_blue  ) ); };

   col4f & pow( float fpow )
        {
        m_red   = powf( m_red,   fpow );
        m_green = powf( m_green, fpow );
        m_blue  = powf( m_blue,  fpow );
        m_alpha = powf( m_alpha, fpow );

	return *this;
        }

   col4f & pow( col4f &color )
        {
        m_red   = powf( m_red,   color.m_red   );
        m_green = powf( m_green, color.m_green );
        m_blue  = powf( m_blue,  color.m_blue  );
        m_alpha = powf( m_alpha, color.m_alpha );

	return *this;
        }

 
   void fromc4b( col4b &ca ) 
   { 
  	 m_red   = ca.m_red   / 255.0f; 
	 m_green = ca.m_green / 255.0f; 
     	m_blue  = ca.m_blue  / 255.0f;
     	m_alpha = ca.m_alpha / 255.0f;
	};

   void toc4b(   col4b &ca )
	{
	ca.m_red   = (int)( m_red   * 255.0f );
	ca.m_green = (int)( m_green * 255.0f ); 
	ca.m_blue  = (int)( m_blue  * 255.0f );
	ca.m_alpha = (int)( m_alpha * 255.0f );
	};

   void fromc3b( col3b &ca )
	{
	m_red   = ca.m_red   / 255.0f;
	m_green = ca.m_green / 255.0f;
	m_blue  = ca.m_blue  / 255.0f;
	m_alpha = 1.0f;
	}

   void toc3b(   col3b &ca )
	{
	ca.m_red   = (int)(m_red   * 255.0f );
	ca.m_green = (int)(m_green * 255.0f );
	ca.m_blue  = (int)(m_blue  * 255.0f );
	}

   void fromc1f( col1f &ca )
	{
	m_red   = ca.m_mono;
	m_green = ca.m_mono;
	m_blue  = ca.m_mono;
	m_alpha = 1.0f;	
	}

   void fromc2f( col2f &ca )
	{
	m_red   = ca.m_mono;
	m_green = ca.m_alpha;
	m_blue  = 0.0f;
	m_alpha = 1.0f;	
	}

   void fromc3f( col3f &ca )
	{
	m_red   = ca.m_red;
	m_green = ca.m_green;
	m_blue  = ca.m_blue;
	m_alpha = 1.0f;
	}

   void toc1f( col1f &ca )
	{
	ca.m_mono = m_red;
	}

   void toc2f( col2f &ca )
	{
	ca.m_mono = m_red;
	ca.m_alpha = m_alpha;
	};

   void toc3f( col3f &ca )
	{
	ca.m_red   = m_red;
	ca.m_green = m_green;
	ca.m_blue  = m_blue;	
	}

   void normalize( void )
	{
	float fmag = this->dot( *this );

	m_red /= fmag;
	m_green /= fmag;
	m_blue /= fmag;
	}

   void writefile( FILE *file );
   void readfile(  FILE *file );

   void writebuf( char *buf );
   void readbuf(  char *buf );
  };

class col4d
  {
public:
  double m_red;    /* Red   */
  double m_green;  /* Green */
  double m_blue;   /* Blue  */
  double m_alpha;  /* Alpha */

  /* Function prototypes */
  };

class col3i
{
public:
int m_red;
int m_green;
int m_blue;
};

class col4i
{
public:
int m_red;
int m_green;
int m_blue;
int m_alpha;
};
