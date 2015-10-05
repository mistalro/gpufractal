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

void  process_arguments( int argc, const char *argv[]);
void *process_serverthread(void *pdata);
void *process_clientthread(void *pdata);

// ---------------------------------------------------------------------------
// Set up threads and run application
// ---------------------------------------------------------------------------

int g_verbose = 0;		// Needed for the File IO System
CSystemParameters g_sysparams;	// Global settings

int main(int argc, const char *argv[])
{
XInitThreads();

g_sysparams.ProcessArguments(argc, argv);

// Open a window. The window is also stored in the active window list
g_sysparams.CreateSetWindow();

// Receive network messages
if (g_sysparams.m_servermode)
	{
	pthread_attr_t attrs_server;   // Attributes
	pthread_t thread_server;     // Thread A

	pthread_attr_init( &attrs_server);
	pthread_create( &thread_server, &attrs_server, &process_serverthread, NULL);
	}

process_clientthread(NULL);
}
