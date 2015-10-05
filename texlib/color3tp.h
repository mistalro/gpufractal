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
class col3d
  {
public:
 double m_red;
  double m_green;
  double m_blue;
  
  /* Function prototypes */

   col3d() { m_red = m_green = m_blue = 0.0; };

   col3d( col3D red, col3D green, col3D blue )
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
   
  col3d operator * ( const col3D fcal ) { return col3d( m_red * fcal, m_green * fcal, m_blue * fcal ); };
  col3d operator / ( const col3D fcal ) { return col3d( m_red / fcal, m_green / fcal, m_blue / fcal ); };

   void operator += ( col3d &ca )
           { m_red += ca.m_red; m_green += ca.m_green; m_blue += ca.m_blue;  };
        
   void operator -= ( col3d &ca )
           { m_red -= ca.m_red; m_green -= ca.m_green; m_blue -= ca.m_blue;  };
  
   void operator *= ( col3d &ca )
           { m_red *= ca.m_red; m_green *= ca.m_green; m_blue *= ca.m_blue;  };
                
   void operator /= ( col3d &ca )
           { m_red /= ca.m_red; m_green /= ca.m_green; m_blue /= ca.m_blue;  };
        
   void operator *= (col3D scale )
           { m_red *= scale; m_green *= scale; m_blue *= scale; };
        
   void operator /= (col3D scale )
           { m_red /= scale; m_green /= scale; m_blue /= scale; };

   friend col3d operator * ( const col3d &ca, col3D scale )
        { return col3d( ca.m_red  * scale, ca.m_green * scale,
                           ca.m_blue * scale ); };

   friend col3d operator * ( col3D scale, const col3d &ca )
        { return col3d( ca.m_red  * scale, ca.m_green * scale,
                           ca.m_blue * scale ); };

   friend col3d operator / ( const col3d &ca, col3D scale )
        { return col3d( ca.m_red  * scale, ca.m_green * scale,
                           ca.m_blue * scale ); };

   friend col3d operator / ( col3D scale, const col3d &ca )
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

  };

