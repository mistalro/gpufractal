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

#ifndef _FRACTGUI_H_
#define _FRACTGUI_H_

// --------------------------------------------------------------------------
// Window parameters for each GLX context
// --------------------------------------------------------------------------

class CWindowState
{
public:
bool m_inside;		// Pointer is inside window
bool m_left;		// Left button is pressed
bool m_middle;		// Middle button is pressed
bool m_right;		// Right button is pressed
bool m_wheelup;		// Wheel rotation up
bool m_wheeldown;	// Wheel rotation down
bool m_keyrotatecw;	// Keyboard rotation CW
bool m_keyrotateccw;	// Keyboard rotation CCW
bool m_zoomin;		// Zoom-in button presed
bool m_zoomout;		// Zoom-out button pressed
bool m_ctrlleft;	// Ctrl-Left is pressed
bool m_ctrlright;	// Ctrl-Right is pressed
bool m_shiftleft;	// Shift-Left is pressed
bool m_shiftright;	// Shift-Right is pressed
bool m_arrowleft;	// Left arrow is pressed
bool m_arrowright;	// Right arrow is pressed
bool m_arrowup;		// Up arrow is pressed
bool m_arrowdown;	// Down arrow is pressed
int  m_dx;		// Delta X
int  m_dy;		// Delta Y
int  m_lastx;		// Last X
int  m_lasty;		// Last Y

CWindowState(void)
        {
        Init();
        }

void Init(void)
        {
        m_inside = false;
        m_left = false;
        m_middle = false;
        m_right = false;
        m_wheelup = false;
        m_wheeldown = false;
        m_keyrotatecw = false;
        m_keyrotateccw = false;
	m_zoomin = false;
	m_zoomout = false;
        m_ctrlleft = false;
        m_ctrlright = false;
	m_shiftleft = false;
	m_shiftright = false;
        m_dx = 0;
        m_dy = 0;
        m_lastx = 0;
        m_lasty = 0;
	m_arrowleft = 0;
	m_arrowright = 0;
	m_arrowup = 0;
	m_arrowdown = 0;
        }

void ResetKeys(void)
	{
  	m_zoomin = false;
        m_zoomout = false;
        m_ctrlleft = false;
        m_ctrlright = false;
        m_shiftleft = false;
        m_shiftright = false;
	m_keyrotatecw = false;
        m_keyrotateccw = false;
	m_arrowleft = 0;
	m_arrowright = 0;
	m_arrowup = 0;
	m_arrowdown = 0;
	}

};

// --------------------------------------------------------------------------
// Utility function for compiling shader
// --------------------------------------------------------------------------

class CShaderUtils
{
public:
GLuint compile_shaderunit(GLuint type, const char **src, const std::string &strname);
};

// --------------------------------------------------------------------------
// Compute shader
// --------------------------------------------------------------------------

class CWindowCompute : virtual public CShaderUtils
{
public:
CFractalParameters m_parameters;	// Current parameters
GLuint 	           m_computeshader;	// Compute shader
vector <CTexture *> m_teximages;	// Transfer texture
vector <GLuint>    m_textable;		// Source textures
GLuint             m_texdst;		// Destination texture
GLuint             m_txsize;		// Actual texture size in X
GLuint		   m_tysize;		// Actual texture size in Y
GLuint		   m_texmax;		// Maximum size of texture

CWindowCompute(void)
	{
	m_computeshader = 0;
	m_txsize = 0;	
	m_tysize = 0;
	m_texdst = 0;
	m_texmax = 0;
	}

GLuint init_computeshader(void);
void setparameters_computeshader(GLuint progHandle, CFractalParameters &parameters);
void compute_gpu(void);
};

// --------------------------------------------------------------------------
// Window parameters
// --------------------------------------------------------------------------

class CWindowParameters : public CWindowState, 
			  public CFramePlayer, 
			  public CWindowCompute,
			  virtual public CShaderUtils
{
public:
CGLXWindow         m_glxwindow;		// GLX window
GLuint 	           m_rendershader;	// Render shader
GLuint             m_windowid;      	// Window ID number

pthread_mutexattr_t m_mutexattr;	// Mutex attributes
pthread_mutex_t	   m_mutex;		// Mutex for editing parameters
CTimerCPU	   m_timer;		// Timer for color cycling
bool		   m_acceptupdates;	// Accept server updates
float              m_angledelta;	// Delta for rotations
float              m_angledeltafast;	// Delta for rotations (fast)
float              m_transdelta;	// Delta for translation
float		   m_transdeltafast;    // Delta for translations (fast)
float		   m_powerdelta;	// Delta for power term
float		   m_zoomwheelin;	// Delta for zooming in (mouse wheel)
float		   m_zoomwheelout;	// Delta for zooming out (mouse wheel)
float		   m_maxzoomout;	// Maximum zoom out
float		   m_zoomoutdelta;		// Zoom out
float		   m_zoomoutdeltafast;	// Zoom out fast
float		   m_zoomindelta;		// Zoom in
float              m_zoomindeltafast;	// Zoom in fast

float		   m_maxbanding;        // Maximum color banding
float		   m_minbanding;        // Minimum color banding
int		   m_mintexsize;	// Minimum texture size

CWindowParameters(void) 
	{
	m_rendershader = 0;
	m_windowid = 0;
	m_acceptupdates = true;
	m_angledelta = M_PI * 0.0001f;
	m_angledeltafast = m_angledelta * 10.0f;

	m_transdelta = 0.0005f;
	m_transdeltafast = m_transdelta * 10.0f;

	m_powerdelta = 0.05f;
	m_zoomwheelin = 0.95f;
	m_zoomwheelout = 1.05f;
	m_maxzoomout = 350.0f;
	m_zoomoutdelta = 1.01f;
	m_zoomoutdeltafast = 1.001f;
	m_zoomindelta = 0.999f;
	m_zoomindeltafast = 0.99f;

	m_maxbanding = 128.0f;
	m_minbanding = 1.0f;
	m_mintexsize = 128;

	pthread_mutexattr_init( &m_mutexattr);
	pthread_mutex_init( &m_mutex, &m_mutexattr);

	m_timer.start();
	}

void mutex_lock(void)
	{
	pthread_mutex_lock( &m_mutex);
	}

void mutex_unlock(void)
	{
	pthread_mutex_unlock( &m_mutex);
	}

// Initialisation
void init_context(void);
void init_geometry(void);
void init_texturepalette(void);

void resize_context(unsigned int sizex, unsigned int sizey);

void load_texture(const string &strname );
GLuint create_texture(GLuint width, GLuint height);
void delete_texture(GLuint texid);

GLuint create_texture_image(CTexture &tex);
void make_lineargradient(int sr, int sg, int sb, int fr, int fg, int fb);
void make_sawtooth(int sr, int sg, int sb, int fr, int fg, int fb);
void make_sinewave( int sr, int sg, int sb, int fr, int fg, int fb);

// Event processing
void process_event(XEvent &event);
void process_action(void);

// Render shader
GLuint init_rendershader(void);
void display(void);

inline void swapbuffers(void)
	{
	m_glxwindow.SwapBuffers();	
	}

inline void calculate_viewport(void)
	{
	m_parameters.m_ywidth = m_parameters.m_xwidth * (float) m_glxwindow.m_height / (float) m_glxwindow.m_width;
	}

inline void setparameters(CFractalParameters &params, bool force)
	{
	if (true == m_acceptupdates || force)
		{
		mutex_lock();
		m_parameters = params;
		mutex_unlock();
		}
	}

inline void getparameters(CFractalParameters &params)
	{
	mutex_lock();
	params = m_parameters;
	mutex_unlock();
	}

void savescreen(void);
void savescreen(char *buffer);

void savesuperscreen(unsigned int subx, unsigned int suby);

inline void setkeyboardrotationdelta( float frotation )
        {
        m_angledelta = frotation;
	m_angledeltafast = frotation * 10.0f;
        }

inline void setkeyboardtransdelta( float ftrans )
	{
	m_transdelta = ftrans;
	m_transdeltafast = ftrans * 10.0f;
	}

inline void setpowerdelta( float fdelta)	
	{
	m_powerdelta = fdelta;
	}

inline void setzoomdelta(float fzoomfactor)
	{
	m_zoomindelta      = 1.0f - fzoomfactor * 0.1f;
	m_zoomindeltafast  = 1.0f - fzoomfactor;
	m_zoomoutdelta     = 1.0f + fzoomfactor * 0.1f;
	m_zoomoutdeltafast = 1.0f + fzoomfactor;
	}

inline void setzoomwheeldelta(float fwheeldelta)
	{
        m_zoomwheelin = 1.0f - fwheeldelta;
        m_zoomwheelout = 1.0f + fwheeldelta;
	}
};

// --------------------------------------------------------------------------
// Maintain a list of windows
// --------------------------------------------------------------------------

class CWindowParametersList : public vector <CWindowParameters *>
{
public:
CWindowParameters *CreateWindow(GLuint xpos, GLuint ypos, GLuint prefwidth, GLuint prefheight, bool borderless, bool fullscreen)
        {
        CWindowParameters *pnew = new CWindowParameters;

        pnew->m_glxwindow.OpenWindow(xpos, ypos, prefwidth, prefheight, borderless, fullscreen);
	pnew->m_windowid = size();

        push_back(pnew);

	return pnew;
	}

inline bool ValidWindow( unsigned int windowid )
	{
	return windowid < size();
	}

inline CWindowParameters *GetWindow(unsigned int windowid )
	{
	CWindowParameters *winp;

	if ( windowid < size() )
		{
		winp = at(windowid);
		}
	else
		{		
		winp = NULL;
		}
	
	return winp;
	}

inline void GetWindowDimensions(unsigned int windowid, int &width, int &height)
	{
	CWindowParameters *winp = GetWindow(windowid);
	
	if (NULL != winp)
		{
		width = winp->m_glxwindow.m_width;
		height = winp->m_glxwindow.m_height;
		}
	else
		{
		width = height = 0;
		}	
	}
};

// --------------------------------------------------------------------------
// Default parameters for all windows
// --------------------------------------------------------------------------

class CWindowSettings
{
public:
int m_texwidth;                 // Preferred texture width
int m_texheight;                // Preferred texture height
int m_winposx;                  // Window position on screen X coordinate
int m_winposy;                  // Window position on screen Y coordinate
int m_winwidth;                 // Preferred window width 
int m_winheight;                // Preferred window height
bool m_borderless;              // Window borderless
bool    m_fullscreenmode;       // Full screen mode
CWindowParametersList m_windowlist;       // List of windows

CWindowSettings(void)
        {
        m_texwidth = 512;
        m_texheight = 512;
        m_winposx = 0;
        m_winposy = 0;
        m_winwidth = 512;
        m_winheight = 512;
        m_borderless = false;
        }

inline CWindowParameters * CreateWindow( void)
        {
        return m_windowlist.CreateWindow( m_winposx, m_winposy, m_winwidth, m_winheight, m_borderless, m_fullscreenmode);
        }

inline void GetWindowDimensions(unsigned int windowid, int &width, int &height)
	{
	return m_windowlist.GetWindowDimensions(windowid, width, height);
	}
};

#endif // _FRACTGUI_H_
