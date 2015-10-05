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

#include <pthread.h>
#include <signal.h>

using namespace std;

// --------------------------------------------------------------------------
// Process user commands
// --------------------------------------------------------------------------

static const int mask = \
        StructureNotifyMask | ExposureMask | \
        KeyPressMask | KeyReleaseMask | \
        ButtonPressMask | ButtonReleaseMask | \
        PointerMotionMask | EnterWindowMask | LeaveWindowMask;

// --------------------------------------------------------------------------
// This function handles user input from the window system and sends them
// out as network messages when necessary.
// --------------------------------------------------------------------------

void *process_clientthread( void *pdata )
{
// Initialisation of all windows
for ( auto it :g_sysparams.m_windowlist )
        {
	it->mutex_lock();
        it->m_glxwindow.MakeCurrent();
        it->calculate_viewport();
        it->init_context();
	it->mutex_unlock();
        }

// Begin replay mode if necessary
if ( g_sysparams.m_replaymode )
        {
	for ( auto it : g_sysparams.m_windowlist )
		{
        	it->start_replay(0.0, (float) g_sysparams.m_savelist.size() );
		}
        }

// Run the main application loop until exit requested
while ( false == g_sysparams.GetExitFlag() )
        {
        XEvent event;

        // Process all window input and resize events
        for ( auto it : g_sysparams.m_windowlist )
                {
                if (XCheckMaskEvent( it->m_glxwindow.m_dpy, mask, &event ))
                        {
			it->mutex_lock();
                        it->process_event(event);
			it->mutex_unlock();
                        }
		}

	// For each window, update animations, resizing texture if necessary
	// computing and display the image
        // Process automatic animated actions here because these operate
	// independent of user input
        for ( auto it : g_sysparams.m_windowlist )
                {
		it->mutex_lock();
                it->process_action();
                it->m_glxwindow.MakeCurrent();
                it->resize_context( it->m_parameters.m_texwidth, it->m_parameters.m_texheight);
                it->compute_gpu();
                it->calculate_viewport();
                it->display();               
		it->mutex_unlock();
		}

        // If client mode is active then send parameters to remote peers
        if ( g_sysparams.m_clientmode )
                {
		g_sysparams.OpenServers(); // Open if not already open

		for (auto it : g_sysparams.m_windowlist )
			{
			it->mutex_lock();
               		g_sysparams.SendParameters( it->m_parameters, it->m_windowid, 0 );
			it->mutex_unlock();
			}
                }

        for ( auto it : g_sysparams.m_windowlist )
                {
                it->swapbuffers();
		}
        }

// At end of application, close all clients
if ( g_sysparams.m_clientmode )
        {
	g_sysparams.CloseServers();
        }

return NULL;
}
