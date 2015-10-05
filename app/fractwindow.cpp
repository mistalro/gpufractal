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

#include "fractals.h"

using namespace std;

// --------------------------------------------------------------------------
// Take a screenshot of the current contents of the texture and
// save it in the selected buffer
// --------------------------------------------------------------------------

void CWindowParameters::savescreen(char *buffer)
{
CTexture tex;
// Get the texture and read the contents into a buffer
tex.Allocate( m_parameters.m_texwidth, m_parameters.m_texheight, TEX_RGB);

glBindTexture(GL_TEXTURE_2D, m_texdst);
glGenerateTextureMipmap(m_texdst);
glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.m_pdata);

// Write the texture
tex.TextureWriteFile(buffer);
}

// --------------------------------------------------------------------------
// Take a screenshot of the current contents of the texture
// and save them as a new file
// --------------------------------------------------------------------------

void CWindowParameters::savescreen(void)
{
CTexture tex;
int idx = 0;
char buffer[64];

// Find a filepath that doesn't exist
for (bool done = false; done != true; )
	{
	sprintf( buffer, "screen%04d.tga", idx);
	
	int result = access( buffer, F_OK);

	if (result == -1)
		{
		done = true;
		}
	else
		{
		idx++;	
		}
	}

savescreen( buffer);
}

// --------------------------------------------------------------------------
// Perform a complex save screen where the selected number of subframes are
// generated and saved
// --------------------------------------------------------------------------

void CWindowParameters::savesuperscreen(unsigned int subx, unsigned int suby)
{
CNetworkNode node;
char buffer[64];

// These are the widths and height of the subtiles
float fdx = 1.0f / (float) (1 << (subx-1));
float fdy = 1.0f / (float) (1 << (suby-1));

node.m_width  = fdx*2.0f;
node.m_height = fdy*2.0f; 

// Save
CFractalParameters saveparams;

saveparams = m_parameters;

// Prepare to run prints
m_glxwindow.MakeCurrent();

// Generate the frames
for (unsigned int iyp = 0; iyp < suby; iyp++)
	{
	for (unsigned int ixp = 0; ixp < subx; ixp++)
		{	
		node.m_offx = fdx * ( ixp * 2.0f - 3.0f);
		node.m_offy = fdy * ( iyp * 2.0f - 3.0f);
		
		m_parameters = saveparams;

		m_parameters.CalculateCentrePoint(saveparams, node, saveparams.m_xwidth, saveparams.m_ywidth);
 
		compute_gpu();
		
		sprintf(buffer, "frame%04dx%04d.tga", iyp, ixp);

		savescreen(buffer);
		}
	}

// Restore parameters
m_parameters = saveparams;

compute_gpu();
}

// --------------------------------------------------------------------------
// Convert the X-windows event into the relevant change of the current
// window parameters
// --------------------------------------------------------------------------

void CWindowParameters::process_event(XEvent &event)
{
switch( event.type )
	{
	case EnterNotify:
		m_inside = true;
		break;

	case LeaveNotify:
		m_inside = false;
		break;

	case MotionNotify:
		if (m_inside)
			{
			m_dx = event.xmotion.x - m_lastx;
			m_dy = event.xmotion.y - m_lasty;

			m_lastx = event.xmotion.x;
			m_lasty = event.xmotion.y;
			}
		break;

	case KeyPress:  // XKeyEvent xkey
		switch (event.xkey.keycode)
			{
			case 25: // [W] Write default
				{
				bool result = m_parameters.WriteFile( "default.frac");
				if (false == result)
					{
					cout << "Error: Could not write default parameters file" << endl;
					}
				}
				break;

			case 27: // [R] Read default
				{
				bool result = m_parameters.ReadFile( "default.frac");

				if (false == result)
					{
					cout << "Error: Could not read default parameters file" << endl;
					}

				m_parameters.m_changebits |= CHANGEBIT_ALL;
				}
				break;

			case 67: // [F1] Save texture
				savescreen();
				break;
			
			case 68: // [F2] Save super-texture
				savesuperscreen(2,2);
				break;

			case 69: // [F3] Save super-texture
				savesuperscreen(4,4);
				break;

			case 70: // [F4] Save super-texture
				savesuperscreen(8,8);
				break;

			// Enable/Disable server updates

			case 71: // [F5] Enable/Disable server updates
				m_acceptupdates = not m_acceptupdates;
				break;

                        case 74: // [F8]
                                g_sysparams.SendRequest();
                                break;

                        case 75: // [F9]
                                g_sysparams.SendPing();
                                break;

			case 76: // [F10]
				g_sysparams.SendQueryWindowSize();
				break;

                        case 96: // [F12]
                                g_sysparams.SetExitFlag();
                                break;

			case 115: // [END]
				if (m_ctrlleft && m_ctrlright)
					{
					g_sysparams.SendTerminate();
					}					
				break;

			// Display 
			case 31: // [I] Display parameters in ASCII
				m_parameters.DisplayAscii();
				break;

			case 33: // [P]
				if (g_sysparams.m_savelist.size() >= 2)
					{
					start_replay(0.0f, (float) g_sysparams.m_savelist.size());
					}
				break;
	
			case 9: // [ESC]
				stop_replay();
				break;

			case 34: // [
				m_parameters.m_minclamp = -10.0f;
				m_parameters.m_changebits |= CHANGEBIT_MINCLAMP;
				break;

			case 35: // ]
				m_parameters.m_minclamp = 0.0f;
				m_parameters.m_changebits |= CHANGEBIT_MINCLAMP;
				break;

			// Color cycling
	                case 104:
				m_parameters.m_autocycle = 0;
				m_parameters.m_changebits |= CHANGEBIT_AUTOCYCLE;
                        	break;

			case 82:
				m_parameters.m_autocycle += 1;
				m_parameters.m_changebits |= CHANGEBIT_AUTOCYCLE;
				break;

			case 86:
				m_parameters.m_autocycle -= 1;
				m_parameters.m_changebits |= CHANGEBIT_AUTOCYCLE;
				break;

			// Advanced editing

			case 37: // [Control left]
				m_ctrlleft = true;
				break;

			case 105: // [Control right]
				m_ctrlright = true;
				break;

                	case 111:
                        	m_arrowup = true;
                        	break;

                	case 116:
                        	m_arrowdown = true;
                        	break;

                	case 113:
                        	m_arrowleft = true;
                        	break;

                	case 114:
                        	m_arrowright = true;
                        	break;

			case 40: // Clear [D]
				cout << "Savelist (clearing)\n";

				if (m_ctrlleft && m_ctrlright)
					{
					g_sysparams.m_savelist.clear();
					}
				break;

			case 58: // Save the list [M]
				g_sysparams.m_savelist.WriteFile( "savedlist.frac");
				break;

			case 38: // Add a location [A]
				if (m_ctrlleft)
					{
					CFractalParameters *pnew = new CFractalParameters;
					*pnew = m_parameters;
					g_sysparams.m_savelist.push_back( *pnew);
					}

				g_sysparams.m_savelist.WriteFile( "savedlist.frac");
				break;

			case 26: // Delete last location [E]
				if (m_ctrlright)
					{
					g_sysparams.m_savelist.erase( g_sysparams.m_savelist.begin() +g_sysparams.m_savelist.size() -1 );
					}
				break;

			// Set the power mode

			case 44:	// [K]
				m_parameters.m_modepower = MANDELBROT_P2;
				m_parameters.m_changebits |= CHANGEBIT_POWER;
				break;

			case 45:	// [L]
				m_parameters.m_modepower = MANDELBROT_P3;
				m_parameters.m_changebits |= CHANGEBIT_POWER;
				break;

			case 46:	// [M]
				m_parameters.m_modepower = MANDELBROT_PN;
				m_parameters.m_changebits |= CHANGEBIT_POWER;
				break;

			case 51:	// [\]
				m_parameters.m_modeinvert = not m_parameters.m_modeinvert;
				m_parameters.m_changebits |= CHANGEBIT_MODEINVERT;
				break;

			// Keyboard rotation
			case 52:	// [X]
				m_keyrotatecw = true;
				break;

			case 53:	// [Z]
				m_keyrotateccw = true;
				break;

			// Keyboard zooming
			case 54:	// [C]
				m_zoomin = true;		
				break;

			case 55:	// [V]
				m_zoomout = true;
				break;

			// Banding
			case 56:
				if (m_parameters.m_banding > 1.0f)
					{
					m_parameters.m_banding -= 1.0f;
					m_parameters.m_changebits |= CHANGEBIT_BANDING;
					}
				break;
	
			case 57:
				if (m_parameters.m_banding < 128.0f)
					{
					m_parameters.m_banding += 1.0f;
					m_parameters.m_changebits |= CHANGEBIT_BANDING;
					}
				break;

			// Shift keys
                	case 50:
                        	m_shiftleft = true;
                       		break;

                	case 62:
                        	m_shiftright = true;
                        	break;

			// Smoothing mode
			case 39: // [S]
				m_parameters.m_modesmooth = not m_parameters.m_modesmooth;
				m_parameters.m_changebits |= CHANGEBIT_MODESMOOTH;
				break;

			// Panic button
			case 65: // [Space]
				if (m_ctrlright)
					{
					m_parameters.Reset();
					ResetKeys();
					m_parameters.m_changebits = CHANGEBIT_ALL;
					}
				break;

			// Mipmapping
			case 41: // [F]
				m_parameters.m_makemipmaps = not m_parameters.m_makemipmaps;
				m_parameters.m_changebits |= CHANGEBIT_MAKEMIPMAPS;
				break;

			// Texture size
			case 60:
				if (m_parameters.m_texwidth < (int)m_texmax &&
				    m_parameters.m_texheight < (int)m_texmax)
					{
					resize_context( m_parameters.m_texwidth << 1,
							m_parameters.m_texheight << 1 );
					m_parameters.m_changebits |= CHANGEBIT_ALL;
					}
				break;

			case 59:		
				if (m_parameters.m_texwidth > 128 &&
				    m_parameters.m_texheight > 128)
					{
					resize_context( m_parameters.m_texwidth >> 1,
							m_parameters.m_texheight >> 1 );
					m_parameters.m_changebits |= CHANGEBIT_ALL;
					}
				break;
				
			default:
				break;
			}

		// Iterations amd texture palette
		if (event.xkey.keycode >= 10 && event.xkey.keycode <= 19)
			{
			if ( m_ctrlleft )
				{
				m_parameters.m_texpalette = event.xkey.keycode - 10;
				m_parameters.m_changebits |= CHANGEBIT_TEXPALETTE;
				}
			else
				{
				int power = event.xkey.keycode - 10;

				m_parameters.m_maxiter = 1 << (power+4);
				m_parameters.m_changebits |= CHANGEBIT_MAXITER;
				}
			}

		if (g_sysparams.m_echomode)
			{
			cout << "KeyPress " << event.xkey.keycode << endl;
			}
		break;

	case KeyRelease: // XKeyEvent xkey
		switch (event.xkey.keycode)
		{
                case 37: // [Control left]
			m_ctrlleft = false;
			break;

		case 105: // [Control right]
			m_ctrlright = false;
			break;

		case 111:
			m_arrowup = false;
			break;
		
		case 116:
			m_arrowdown = false;
			break;

		case 113:
			m_arrowleft = false;
			break;

		case 114:
			m_arrowright = false;
			break;

		// Keyboard rotation
		case 52:	// [Z]
			m_keyrotatecw = false;
			break;

		case 53:	// [X]
			m_keyrotateccw = false;
			break;

		// Shift keys

		case 50:
			m_shiftleft = false;	
			break;

		case 62:
			m_shiftright = false;
			break;

	        // Keyboard zooming

                case 54:	// [C]
                        m_zoomin = false;
                        break;

                case 55:	// [V]
                        m_zoomout = false;
                        break;

		default:
			break;
		}

		if (g_sysparams.m_echomode)
			{
			cout << "KeyRelease " << event.xkey.keycode << endl;
			}
	break;

	case ButtonPress:	// XButtonEvent xbutton
		if (m_inside)
			switch(event.xbutton.button)
				{
				case Button1: // Left
					m_left = true;
					break;

				case Button2: // Middle:
					m_middle = true;
					break;

				case Button3: // Right
					m_right = true;
					break;

				// Jogwheel
				case Button4:
					m_wheelup = true;
					break;

				case Button5:
					m_wheeldown = true;
					break;

				default:
					break;
				}

		m_dx = m_dy = 0;	// Stop sliding when button is pressed
		break;

	case ButtonRelease:     // XButtonEvent xbutton
		switch(event.xbutton.button)
			{
			case Button1:
				m_left = false;
				break;

			case Button2:
				m_middle = false;
				break;

			case Button3:
				m_right = false;
				break;

			// Jogwheel
			case Button4:
				m_wheelup = false;
				break;

			case Button5:
				m_wheeldown = false;
				break;

			default:
				break;
			}
		break;

	case ConfigureNotify:
		// Handle resize events
		m_glxwindow.m_width = event.xconfigure.width;
		m_glxwindow.m_height = event.xconfigure.height;

		calculate_viewport();
		break;

	default:
		break;
	}
}

// --------------------------------------------------------------------------
// Depending on the action, modify the fractal parameters in a particular
// way. This might be moving the centre point, rotating the axis, zooming
// in or out, or any other parameter.
//
// If "replay" mode is active, then calculate the parameters from
// interpolating between frames and then return
// --------------------------------------------------------------------------

void CWindowParameters::process_action(void)
{
if (m_replay)
	{
	update_replay();

 	g_sysparams.m_savelist.CalculateFrame( m_parameters, m_replaypos );

	return;
	}

if (m_left)
	{
	float fsa, fca;

        sincosf( m_parameters.m_angle, &fsa, &fca );

        float fdx = (float) m_dx;
        float fdy = (float) m_dy;

        float frx = fca * fdx - fsa * fdy;
        float fry = fsa * fdx + fca * fdy;

        m_parameters.m_xcen -= frx * m_parameters.m_xwidth * 0.0005f;
        m_parameters.m_ycen -= fry * m_parameters.m_ywidth * 0.0005f;

	m_parameters.m_changebits |= CHANGEBIT_XCEN|CHANGEBIT_YCEN;
        }

if (m_keyrotatecw)
        {
	if (m_shiftleft)
		{
    		m_parameters.m_angle += M_PI * 0.001f;
		}
	else
		{
    		m_parameters.m_angle += M_PI * 0.0001f;
		}

	m_parameters.m_changebits |= CHANGEBIT_ANGLE;
        }

if (m_keyrotateccw)
        {
	if (m_shiftleft)
		{
    		m_parameters.m_angle -= M_PI * 0.001f;
		}
	else
		{
    		m_parameters.m_angle -= M_PI * 0.0001f;
		}

	m_parameters.m_changebits |= CHANGEBIT_ANGLE;
        }

if (m_wheelup)
        {
        if (m_right)
		{
		m_parameters.m_angle += M_PI / 30.0f;
		m_parameters.m_changebits |= CHANGEBIT_ANGLE;
                }
        else
        if (m_middle)
                {
                m_parameters.m_power += 0.05f;
		m_parameters.m_changebits |= CHANGEBIT_POWER;
                }
        else
                {
                m_parameters.m_xwidth *= 0.95f;
                m_parameters.m_ywidth *= 0.95f;
		m_parameters.m_changebits |= CHANGEBIT_XWIDTH|CHANGEBIT_YWIDTH;
                }
        }

if (m_zoomin)
	{
	if (m_shiftleft)		
		{
        	m_parameters.m_xwidth *= 0.99f;
        	m_parameters.m_ywidth *= 0.99f;
		m_parameters.m_changebits |= CHANGEBIT_XWIDTH|CHANGEBIT_YWIDTH;
		}
	else
		{
        	m_parameters.m_xwidth *= 0.999f;
        	m_parameters.m_ywidth *= 0.999f;
		m_parameters.m_changebits |= CHANGEBIT_XWIDTH|CHANGEBIT_YWIDTH;
		}
	}

if (m_wheeldown)
        {
        if (m_right)
                {
                m_parameters.m_angle -= M_PI / 30.0f;
		m_parameters.m_changebits |= CHANGEBIT_ANGLE;
                }
        else
        if (m_middle)
                {
                m_parameters.m_power -= 0.05f;
                }
        else
                {
		// Don't go beyond level of precision
		if (m_parameters.m_xwidth < 350.0f &&
		    m_parameters.m_ywidth < 350.0f )	
			{
                	m_parameters.m_xwidth *= 1.05f;
                	m_parameters.m_ywidth *= 1.05f;
			m_parameters.m_changebits |= CHANGEBIT_XWIDTH|CHANGEBIT_YWIDTH;
			}
                }
        }

if (m_zoomout)
	{
	// Don't go beyond level of precision
	if (m_parameters.m_xwidth < 350.0f &&
	    m_parameters.m_ywidth < 350.0f )	
		{
		if (m_shiftleft)
			{
       			m_parameters.m_xwidth *= 1.01f;
        		m_parameters.m_ywidth *= 1.01f;
			}
		else
			{
       			m_parameters.m_xwidth *= 1.001f;
        		m_parameters.m_ywidth *= 1.001f;
			}

		m_parameters.m_changebits |= CHANGEBIT_XWIDTH|CHANGEBIT_YWIDTH;
		}
	}

if (m_arrowleft |m_arrowright |m_arrowup|m_arrowdown)
	{
        float fsa, fca;

        sincosf( m_parameters.m_angle, &fsa, &fca );

	float fdx = 0.0f;
	float fdy = 0.0f;

	// Allow keypresses to be combined together to get diagonal movement
	if (m_arrowleft == true)		
		{
		fdx -= 1.0f;
		}

	if (m_arrowright == true)
		{
		fdx += 1.0f;
		}

	if (m_arrowup == true)
		{
		fdy -= 1.0f;
		}

	if (m_arrowdown == true)
		{ 
		fdy += 1.0f;
		}

	// Use "accelerated" mode if the left shift button is pressed
	if (m_shiftleft)
		{
		fdx *= 10.0f;
		fdy *= 10.0f;
		}

        float frx = fca * fdx - fsa * fdy;
        float fry = fsa * fdx + fca * fdy;

        m_parameters.m_xcen += frx * m_parameters.m_xwidth * 0.0005f;
        m_parameters.m_ycen += fry * m_parameters.m_ywidth * 0.0005f;

	m_parameters.m_changebits |= CHANGEBIT_XCEN|CHANGEBIT_YCEN;
	}

if (m_parameters.m_autocycle != 0)
	{
	// Delta is total number of elapsed nanoseconds 
	long int delta = m_timer.getvalue64();

	// Convert autocycle value to milliseconds
	m_parameters.m_cycleoffset = (delta * m_parameters.m_autocycle) / 100000000;
	}
else
	{
	m_parameters.m_cycleoffset = 0;
	}
}

// ==========================================================================
// DISPLAY AND PROCESSING FUNCTIONS
// ==========================================================================

// --------------------------------------------------------------------------
// Use the vertex/fragment shaders to draw a quad that fills the screen
// --------------------------------------------------------------------------

void CWindowParameters::display(void)
{
// ----- Update the display ------------------------------------------------

if (m_parameters.m_makemipmaps)
	{
	glGenerateTextureMipmap(m_texdst);
	ASSERTGL();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
else
	{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

glUseProgram(m_rendershader);
ASSERTGL();

glViewport(0, 0, m_glxwindow.m_width, m_glxwindow.m_height);
ASSERTGL();

glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
ASSERTGL();
}

// --------------------------------------------------------------------------
// Initialise display
// --------------------------------------------------------------------------

void CWindowParameters::init_context(void)
{
// ----- Create the geometry -----
init_geometry();

GLint size;
glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
ASSERTGL();

m_texmax = size;

// ----- Create the destination texture -----
m_texdst = create_texture(g_sysparams.m_texwidth, g_sysparams.m_texheight);

// ----- Create the transfer textures ------

init_texturepalette();

// ----- Create the two shaders -----

m_rendershader = init_rendershader();
ASSERTGL();

m_computeshader = init_computeshader();
ASSERTGL();
}

void CWindowParameters::resize_context(unsigned int sizex,unsigned int sizey)
{
if ((sizex == m_txsize) && (sizey == m_tysize) && (m_texdst > 0))
	{
	return;
	}

if (m_texdst > 0)
	{
	delete_texture(m_texdst);
	}

m_texdst = create_texture(sizex, sizey);

m_txsize = sizex;
m_tysize = sizey;

m_parameters.m_texwidth = sizex;
m_parameters.m_texheight = sizey;

compute_gpu();
}

// --------------------------------------------------------------------------
// Create a simple set of transfer textures
// --------------------------------------------------------------------------

static const char str_rainbow[] = "palettes/rainbow.bmp";
static const char str_mono[]    = "palettes/mono.bmp";

void CWindowParameters::load_texture(const string &strname)
{
CTexture *pnew;
int result;

pnew = new CTexture;
result = pnew->TextureReadFile(strname.data() );

if (result == false)
	{
	cout << "Error: Could not load texture |" << strname << "|" << endl;
	exit(0);
	}

int texsrc = create_texture_image(*pnew);
ASSERTGL();

m_textable.push_back(texsrc);
m_teximages.push_back(pnew);
}

void CWindowParameters::make_sawtooth(int sr,int sg, int sb, int fr, int fg, int fb)
{
CTexture *pnew;

pnew = new CTexture;

pnew->Allocate(1024,1, TEX_RGB);

GLubyte *pdst = pnew->m_pdata;

for (int idx = 0; idx < 512; idx++)
	{
	*pdst++ = (sr*(511-idx) + fr *(idx))/512;	
	*pdst++ = (sg*(511-idx) + fg *(idx))/512;	
	*pdst++ = (sb*(511-idx) + fb *(idx))/512;	
	}

for (int idx = 0; idx < 512; idx++)
	{
	*pdst++ = (fr*(511-idx) + sr *(idx))/512;	
	*pdst++ = (fg*(511-idx) + sg *(idx))/512;	
	*pdst++ = (fb*(511-idx) + sb *(idx))/512;	
	}

int texsrc = create_texture_image(*pnew);
ASSERTGL();

m_textable.push_back(texsrc);
m_teximages.push_back(pnew);
}

void CWindowParameters::make_lineargradient(int sr,int sg, int sb, int fr, int fg, int fb)
{
CTexture *pnew;

pnew = new CTexture;

pnew->Allocate(512,1, TEX_RGB);

GLubyte *pdst = pnew->m_pdata;

*pdst++ = 0;
*pdst++ = 0;
*pdst++ = 0;

for (int idx = 1; idx < 512; idx++)
        {
        *pdst++ = (sr*(511-idx) + fr *(idx))/512;
        *pdst++ = (sg*(511-idx) + fg *(idx))/512;
        *pdst++ = (sb*(511-idx) + fb *(idx))/512;
        }

int texsrc = create_texture_image(*pnew);
ASSERTGL();

m_textable.push_back(texsrc);
m_teximages.push_back(pnew);
}

void CWindowParameters::make_sinewave( int sr, int sg, int sb, int fr, int fg, int fb)
{
CTexture *pnew;

pnew = new CTexture;

pnew->Allocate(1024,1, TEX_RGB);

GLubyte *pdst = pnew->m_pdata;

for (int idx = 0; idx < 1024; idx++)
        {
	float fparam = (float) idx * 16.0f * M_PI * 2.0f / 1023.0f;
	float sval = 1.0f-(cosf(fparam) * 0.5f + 0.5f);
	float snval = 1.0f - sval;
	
	*pdst++ = (int) (sval * (float) sr + snval *(float) fr);
	*pdst++ = (int) (sval * (float) sg + snval *(float) fg);
	*pdst++ = (int) (sval * (float) sb + snval *(float) fb);
        }

int texsrc = create_texture_image(*pnew);
ASSERTGL();

assert(texsrc >= 1);

m_textable.push_back(texsrc);
m_teximages.push_back(pnew);
}

void CWindowParameters::init_texturepalette(void)
{
make_lineargradient( 0, 0,  0, 0, 255, 127 );	// Dark blue [1]
make_lineargradient( 0, 0,  0, 0, 127, 255 );	// Light blue [2]
make_lineargradient( 0, 0,  0, 255, 127, 0 );	// Mint-Green [3]
make_lineargradient( 0, 0,  0, 127, 255, 0 );	// Orange [4]
make_lineargradient( 0, 0,  0, 255, 0, 127 );	// Lime-Green [5]
make_lineargradient( 0, 0,  0, 127, 0, 255 );	// Purplish [6]

make_lineargradient( 16, 0, 32, 255, 192, 0 );  // Purple -> Gold
load_texture(str_rainbow);
load_texture(str_mono);

make_sinewave( 255,255,255,0,0,0 );		// Stripy sinewave

if (g_sysparams.m_textransfer.size() > 0)
        {
	load_texture(g_sysparams.m_textransfer);
        }
}

// ==========================================================================
// TEXTURE
// ==========================================================================

GLuint CWindowParameters::create_texture(GLuint width, GLuint height)
{
glActiveTexture(GL_TEXTURE0);
ASSERTGL();

GLuint texid;
glGenTextures(1, &texid);
ASSERTGL();
assert(texid != 0 );

glBindTexture(GL_TEXTURE_2D, texid);
ASSERTGL();

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
ASSERTGL();

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
ASSERTGL();

glTexImage2D(GL_TEXTURE_2D, 0, TEX_INTERNALFORMAT, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
ASSERTGL();

return texid;
}

void CWindowParameters::delete_texture(GLuint texid)
{
glBindTexture(GL_TEXTURE_2D,0);
glDeleteTextures(1, &texid);
ASSERTGL();
}

#define MAX(X,Y)   ((X>Y) ? (X) : (Y))

GLuint CWindowParameters::create_texture_image(CTexture &tex)
{
GLuint texHandle;

glGenTextures(1, &texHandle);
ASSERTGL();

glActiveTexture(GL_TEXTURE0);
ASSERTGL();

glBindTexture(GL_TEXTURE_1D, texHandle);
ASSERTGL();

glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
ASSERTGL();

glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
ASSERTGL();

float *pfbuf = new float[tex.m_width*tex.m_height*4];

int num = MAX(tex.m_width, tex.m_height);

for (int idx = 0; idx < num; idx++)
	{
	pfbuf[idx*4]   = (float) tex.m_pdata[idx*3] / 255.0f;
	pfbuf[idx*4+1] = (float) tex.m_pdata[idx*3+1] / 255.0f;
	pfbuf[idx*4+2] = (float) tex.m_pdata[idx*3+2] / 255.0f;
	pfbuf[idx*4+3] = 1.0f;
	}

glTexImage1D(GL_TEXTURE_1D, 0, TEX_INTERNALFORMAT, num, 0, GL_RGBA, GL_FLOAT, pfbuf);
ASSERTGL();

delete [] pfbuf;

return texHandle;
}

// ==========================================================================
// RENDER SHADER
// ==========================================================================

const char *vpSrc[] =
{
"#version 430\n"
"in vec2 pos;\n"
"out vec2 texCoord;\n"
"void main()\n"
"{\n"
"texCoord = pos*0.5f + 0.5f;\n"
"gl_Position = vec4(pos.x, -pos.y, 0.0, 1.0);\n"
"}"
};

const char *fpSrc[] =
{
"#version 430\n"
"uniform sampler2D srcTex;\n"
"in vec2 texCoord;\n"
"out vec4 color;\n"
"void main() {\n"
"vec4 texcol = texture(srcTex, texCoord);\n"
"color = texcol;\n"
"}"
};

static const std::string str_vertex = "vertex";
static const std::string str_fragment= "fragment";

// --------------------------------------------------------------------------
// Initialize the render shader
// --------------------------------------------------------------------------

GLuint CWindowParameters::init_rendershader(void)
{
// ----- Vertex shader -----

GLuint vp = compile_shaderunit(GL_VERTEX_SHADER, vpSrc, str_vertex);

// ----- Fragment shader -----

GLuint fp = compile_shaderunit(GL_FRAGMENT_SHADER, fpSrc, str_fragment);

// ----- Program ------

GLuint progid = glCreateProgram();
ASSERTGL();

glAttachShader(progid, vp);
ASSERTGL();

glAttachShader(progid, fp);
ASSERTGL();

glBindFragDataLocation(progid, 0, "color");
ASSERTGL();

glLinkProgram(progid);
ASSERTGL();

GLint rvalue;

glGetProgramiv(progid, GL_LINK_STATUS, &rvalue);
ASSERTGL();

if (!rvalue) 
	{
        cerr << "Error in linking sp" << endl;
        exit(32);
    	}  	 

glUseProgram(progid);
ASSERTGL();

glUniform1i(glGetUniformLocation(progid, "srcTex"), 0);
ASSERTGL();

GLint posPtr = glGetAttribLocation(progid, "pos");
ASSERTGL();
ASSERT(posPtr >= 0);

glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
ASSERTGL();

glEnableVertexAttribArray(posPtr);
ASSERTGL();

return progid;
}

// --------------------------------------------------------------------------
// Initialise the geometry - simply a four vertex quad
// --------------------------------------------------------------------------

void CWindowParameters::init_geometry(void)
{
GLuint vertArray;
glGenVertexArrays(1, &vertArray);
ASSERTGL();

glBindVertexArray(vertArray);
ASSERTGL();

GLuint posBuf;
glGenBuffers(1, &posBuf);
ASSERTGL();

glBindBuffer(GL_ARRAY_BUFFER, posBuf);
ASSERTGL();

static float data[] = 
	{
	-1.0f,  1.0f,
	-1.0f, -1.0f,
 	 1.0f,  1.0f,
	 1.0f, -1.0f
	};

glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8, data, GL_STREAM_DRAW);
ASSERTGL();
}
