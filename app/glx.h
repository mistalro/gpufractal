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

#ifndef _FRACTALGLX_H_
#define _FRACTALGLX_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <assert.h>

#define GL_GLEXT_PROTOTYPES
#define GLX_GLXEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define ASSERT(X)   assert((X))
#define ASSERTGL()  assert(glGetError() == GL_NO_ERROR)

// --------------------------------------------------------------------------
// GLX Window
// --------------------------------------------------------------------------

class CGLXWindow
{
public:
Display   *m_dpy;	// Display
Window     m_win;	// Window
GLXContext m_ctx;	// Context
GLuint     m_width;	// Visible width
GLuint     m_height;	// Visible height

CGLXWindow(void)
	{
	m_dpy = NULL;
	}

CGLXWindow(GLuint xpos, GLuint ypos, GLuint prefwidth, GLuint prefheight, bool borderless, bool fullscreen)
	{
	OpenWindow(xpos, ypos, prefwidth, prefheight, borderless, fullscreen);
	}

void OpenWindow(GLuint xpos, GLuint ypos, GLuint prefwidth, GLuint prefheight, bool borderless, bool fullscreen );

void InitExtensions(void);

inline void MakeCurrent(void)
	{
	glXMakeCurrent(m_dpy, m_win, m_ctx);
	}

inline void SwapBuffers(void)
	{
	glXSwapBuffers(m_dpy, m_win);
	}
};

#endif	// _FRACTALGLX_H_
