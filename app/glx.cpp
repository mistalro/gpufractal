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

#include "glx.h"

Display *m_dpy;
Window m_win;
GLXContext m_ctx;

// --------------------------------------------------------------------------
// Initialize GLX
// --------------------------------------------------------------------------

static int visual_attr[] =
	{

	GLX_X_RENDERABLE, True,
	GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
	GLX_RENDER_TYPE,   GLX_RGBA_BIT,
	GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
/*
	GLX_RED_SIZE,      8,
	GLX_GREEN_SIZE,    8,
	GLX_BLUE_SIZE,     8,
	GLX_ALPHA_SIZE,    8,
*/
	GLX_DEPTH_SIZE,    24,
	GLX_STENCIL_SIZE,  8,
	GLX_DOUBLEBUFFER,  True,
/*
	GLX_SAMPLE_BUFFERS, 1,
	GLX_SAMPLES,        4,
*/
	None
	};

static int attr[] =
        {
        GLX_RGBA,
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        GLX_DOUBLEBUFFER,
        None
        };

void CGLXWindow::OpenWindow(GLuint xpos, GLuint ypos, GLuint prefwidth, GLuint prefheight, bool borderless, bool fullscreen)
{
if (!(m_dpy = XOpenDisplay(NULL)))
        {
        cerr << "Couldn't open X11 display" << endl;
        exit(10);
        }

int scrnum = DefaultScreen(m_dpy);
Window root = RootWindow(m_dpy, scrnum);

int elemc;
GLXFBConfig *fbcfg = glXChooseFBConfig(m_dpy, scrnum, visual_attr, &elemc);

if (!fbcfg)
        {
        cerr << "Couldn't get FB configs" << endl;
        exit(11);
        }

XVisualInfo *visinfo = glXChooseVisual(m_dpy, scrnum, attr);

if (!visinfo)
        {
        cerr << "Couldn't get a visual" << endl;
        exit(12);
        }

// Window parameters
XSetWindowAttributes swa;

swa.colormap = XCreateColormap(m_dpy, root, visinfo->visual, AllocNone);
swa.border_pixel = 0;
swa.background_pixel = 0;

swa.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | EnterWindowMask | LeaveWindowMask;

swa.border_pixel = 0;

unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask; 

if (fullscreen)
        {
        XWindowAttributes winattr;

        Window win = DefaultRootWindow( m_dpy);
        XGetWindowAttributes(m_dpy, win, &winattr);

        prefwidth = winattr.width;
        prefheight = winattr.height;
        }

if (borderless)
	{
	swa.override_redirect = true;
	mask |= CWOverrideRedirect;
	}

m_win = XCreateWindow(m_dpy, root, xpos, ypos, prefwidth, prefheight, 0,
        visinfo->depth, InputOutput, visinfo->visual, mask, &swa);

// OpenGL version 4.3, forward compatible core profile
int gl3attr[] =
        {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 3,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
        };

m_ctx = glXCreateContextAttribsARB(m_dpy, fbcfg[0], NULL, true, gl3attr);

if (!m_ctx)
        {
        cerr << "Couldn't create an OpenGL context" << endl;
        exit(13);
        }

XFree(visinfo);

// Setting the window name
XTextProperty windowName;
windowName.value = (unsigned char *) "OpenGL compute shader demo";
windowName.encoding = XA_STRING;
windowName.format = 8;
windowName.nitems = strlen((char *) windowName.value);

XSetWMName(m_dpy, m_win, &windowName);

XMapWindow(m_dpy, m_win);
glXMakeCurrent(m_dpy, m_win, m_ctx);

m_width = prefwidth;
m_height = prefheight;

if (fullscreen)
	{
	XGrabKeyboard(m_dpy, m_win, true, GrabModeAsync, GrabModeAsync, CurrentTime);
	}

glViewport(0, 0, m_width, m_height);
ASSERTGL();
}

// --------------------------------------------------------------------------
// Initialize errors
// --------------------------------------------------------------------------

void CGLXWindow::InitExtensions(void)
{
std::cout << "OpenGL" << std::endl;
std::cout << "Vendor " << glGetString(GL_VENDOR) << std::endl;
std::cout << "Renderer " << glGetString(GL_RENDERER) << std::endl;
std::cout << "Version " << glGetString(GL_VERSION) << std::endl;
std::cout << "Shader " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

// Finding the compute shader extension
int extCount;
glGetIntegerv(GL_NUM_EXTENSIONS, &extCount);
bool found = false;

for (int i = 0; i < extCount; ++i)
        {
        if (!strcmp((const char*)glGetStringi(GL_EXTENSIONS, i), "GL_ARB_compute_shader"))
                {
                std::cout << "Extension \"GL_ARB_compute_shader\" found" << std::endl;
                found = true;
                break;
                }

        if (!found)
                {
                std::cout<< "Extension \"GL_ARB_compute_shader\" not found\n" << std::endl;
                exit(15);
                }
        }
}
