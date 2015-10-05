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

void *process_serverthread(void *pdata);

// --------------------------------------------------------------------------
// Process user commands
// --------------------------------------------------------------------------

static const int mask = \
        StructureNotifyMask | ExposureMask | \
        KeyPressMask | KeyReleaseMask | \
        ButtonPressMask | ButtonReleaseMask | \
        PointerMotionMask | EnterWindowMask | LeaveWindowMask;

// --------------------------------------------------------------------------
// Use a separate thread to keep the server separate from the client
// --------------------------------------------------------------------------

void *process_serverthread(void *pdata)
{
while (false == g_sysparams.GetExitFlag() )
        {
	int result;

	// In this section, attempt to open a server while there is no open
	// connection
	if (g_sysparams.m_server.m_serverstate == SERVER_CLOSED)
		{
		cout << getpid() << " - Server state closed, attempting to open" << endl;

		result = g_sysparams.m_server.open_server();

		}
	
	if (result == SOCKET_SUCCESS)
		{
		if (g_verbose)
               		{
                	cout << getpid() << " - Server: listening at port " << g_sysparams.m_server.m_port << endl;
                	}

	        result = g_sysparams.m_server.open_serverconnection(); 

        	if (g_verbose)
               		{
                	cout << getpid() << " - Server: received connection request " << g_sysparams.m_server.m_port << endl;
                	}
		}
	else
		{
		exit(0);
		}

	// Define this here to avoid unnecessary constructor initialisation
	CFractalParameters params;	// Where parameters are unpacked to
	CFractalParameters newparams;	// New calculated set of parameters

	// Temporary buffer
	FRbyte *pbuf = new FRbyte[params.m_maxmessagesize];	

	// While the server remains opn
	if (g_sysparams.m_server.m_serverstate == SERVER_OPEN)
		{
		if (g_verbose)
			{
			cout << getpid() << " - Server state open = " << g_sysparams.m_server.m_port << endl;
			}

        	for (bool endconnection = false; endconnection == false; )
               		{
                	// Decode the message into params
			// For parameter requests, this will include the
			// return port and address
			// Returns flag indicating message was received
			// as well as whether the connection was dropped
                	int ncount = g_sysparams.ReceiveParameters(params, pbuf, params.m_maxmessagesize, endconnection);

			if (ncount > 0)	// Received a message
				{
				CWindowParameters *winp = g_sysparams.m_windowlist.GetWindow(params.m_windowto);

				// Received request for calculated parameters?
				switch (params.m_msgtype)
					{
					case MSG_PING: // Send ping
						if (g_verbose)
							{
							cout << getpid() << " - Server - Received ping" << endl;
							}
						g_sysparams.SendPingReply(params);
						break;

					case MSG_PINGREPLY: // Receive ping
						if (g_verbose)
							{
							cout << getpid() <<  " - Server - Received ping reply from" << params.m_windowfrom << endl;
							}
						break;

					case MSG_REQPARAM: // Receive request from window
						if (g_verbose)
							{
							cout << getpid() << " - Received request for parameters" << endl;
							}

						// Get parameters from window
						if (winp != NULL)
							{
							cout << getpid() << " - Readin parameters from window" << endl;
							winp->getparameters(newparams);
               						g_sysparams.SendRequestReply(newparams, params );
							}
						break;

					case MSG_REQPARAMREPLY: // Received request reply
						if (g_verbose)
							{
							cout << getpid() << " - Received reply for request for parameters" << endl;
							}

                				// Set windows to new parameters
						if (winp != NULL)
							{
							winp->setparameters(params, true);
							}
						break;
			
					case MSG_PARAMS: // Received new parameters
/*
						if (g_verbose)
							{
							cout << getpid() << " - Received parameters" << endl;
							}
*/

                				// Set windows to new parameters
						if (winp != NULL)
							{
							winp->setparameters(params, false);
        						winp->calculate_viewport();
							}
						break;

					case MSG_TERMINATE:	// Kill server
						if (g_verbose)
							{
							cout << getpid() << " - Server -Received terminate command" << endl;
							}

						g_sysparams.SetExitFlag();
						break;

					case MSG_QUERYWINDOWSIZE:
                                                if (g_verbose)
                                                        {
                                                        cout << getpid() << " - Received request for window size" << endl;
                                                        }

                                                // Get parameters from window
                                                if (winp != NULL)
                                                        {
                                                        cout << getpid() << " - Reading parameters from window" << endl;
							newparams.m_windowwidth = winp->m_glxwindow.m_width;
							newparams.m_windowheight = winp->m_glxwindow.m_height;
							cout << "Window size = " << newparams.m_windowwidth << "|" << newparams.m_windowheight << endl;

							g_sysparams.SendQueryWindowSizeReply(newparams, params);
                                                        }
						break;

					case MSG_QUERYWINDOWSIZEREPLY:
                                                if (g_verbose)
                                                        {
                                                        cout << getpid() << " - Received reply for request for window size" << endl;
                                                        }

						// Save the width/height and aspect ratio
                                                if (winp != NULL)
                                                        {
							cout << "Window " << params.m_windowfrom << " has dimensions " << params.m_windowwidth << " | " << params.m_windowheight << endl;
                                                        }

						break;

					default:
						if (g_verbose)
							{
							cout << getpid() << " Unknown message" << endl;
							}
						break;
					}
                        	}
			}

		if (g_verbose)
			{
			cout << getpid() << "- Server: Connection closed" << endl;
			}
		}

	delete [] pbuf;
	}

if (g_sysparams.m_server.m_serverstate == SERVER_OPEN)
	{
	if (g_verbose)
		{
		cout << getpid() << " - Server: closing down" << g_sysparams.m_server.m_port << endl;
		}

        g_sysparams.m_server.close_server();
        }

return NULL;
}
