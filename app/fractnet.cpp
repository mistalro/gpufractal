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
#include <arpa/inet.h>

using namespace std;

// --------------------------------------------------------------------------
// Open client connections
// --------------------------------------------------------------------------

void CNetworkSettings::OpenServers(void)
{
for (auto it : m_nodelist )	// Open Clients
	{
        // Try and open connection to remote display servers
        if ((*it).m_clientstate == CLIENT_CLOSED)
		{
                (*it).open_client();
                }
	}
}

// --------------------------------------------------------------------------
// Close client connections
// --------------------------------------------------------------------------

void CNetworkSettings::CloseServers(void)
{
// Close connections to subnodes if active networking 
for (auto it : m_nodelist)	// Close clients
	{
        (*it).close_client();
        }
}

// --------------------------------------------------------------------------
// Send standard message to all servers
// --------------------------------------------------------------------------

void CNetworkSettings::SendBroadcast(const FRbyte *pbuf, int len)
{
for (auto it : m_nodelist )     // Send ping
        {
        // If connection is open, then send a message
        if ((*it).m_clientstate == CLIENT_OPEN)
                {
                (*it).write( pbuf, len);
                }
        }
}

// --------------------------------------------------------------------------
// Helper function used by client to send message to end server
// --------------------------------------------------------------------------

void CNetworkSettings::SendTerminate(void)
{
CFractalParameters params;
int len;

FRbyte *pbuf = new FRbyte[params.m_maxmessagesize];

if (NULL == pbuf)
	{
	return;
	}

params.CreateTerminate(pbuf, len);

SendBroadcast(pbuf, len);

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Helper function used by client to send ping
// --------------------------------------------------------------------------

void CNetworkSettings::SendPing(void)
{
CFractalParameters params;
int len;

FRbyte *pbuf = new FRbyte[params.m_maxmessagesize];

if (NULL == pbuf)
	{
	return;
	}

params.CreatePing(pbuf, m_server.m_port, m_server.m_ipaddr, len);

SendBroadcast(pbuf, len);

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Helper function used by client to reply to ping
// --------------------------------------------------------------------------

void CNetworkSettings::SendPingReply(CFractalParameters &replyto)
{
FRbyte *pbuf = new FRbyte[replyto.m_maxmessagesize];

if (NULL == pbuf)
	{
	return;
	}

// Swap destination and orginating window ID's
int swap             = replyto.m_windowfrom;
replyto.m_windowfrom = replyto.m_windowto;
replyto.m_windowto   = swap;

for (auto it : m_nodelist)	// Send ping reply
        {
        if (it->match( replyto.m_addr, replyto.m_port ))
                {
                int len;

		if (g_verbose)
			{
			cout << "Ping received, replying to |" << inet_ntoa(replyto.m_addr) << endl;
			}

		replyto.m_msgtype = MSG_PINGREPLY;
			
                replyto.PackData( pbuf, len);

                it->write(pbuf, len);
                }
        }

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Helper function used by client to send request
// --------------------------------------------------------------------------

void CNetworkSettings::SendRequest(void)
{
CFractalParameters params;
FRbyte *pbuf = new FRbyte[params.m_maxmessagesize];

if (NULL == pbuf)
	{
	return;
	}

int len = 0;

params.CreateRequest(pbuf, m_server.m_port, m_server.m_ipaddr, len);

SendBroadcast(pbuf, len  );

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Send the parameters to the server identified by recvadrr and port
//
// srcparam is the local settings
// param actually contains the return address:port for the query
// --------------------------------------------------------------------------

void CNetworkSettings::SendRequestReply(CFractalParameters &srcparam, CFractalParameters &replyto)
{
FRbyte *pbuf = new FRbyte[srcparam.m_maxmessagesize];

if (NULL == pbuf)	
	{
	return;
	}

// Find out which host has the originating address or name and send a reply
// Needed to resolve names like localhost vs. 127.0.0.1 vs local IP addr
//
// If we just wanted to send back to the originating client, we could
// just use the write function on the active socket
// But as we want to find the matching server address:port combination
// we have to go through each node entry in turn

for (auto it : m_nodelist)	// Send parameters request reply
	{
	if (it->match( replyto.m_addr, replyto.m_port ) == true)
		{
		int len;
		CFractalParameters params;

    		params.CalculateNodeParameters( srcparam, *it );
		params.m_msgtype = MSG_REQPARAMREPLY;
		params.PackData(pbuf,len);

		it->write(pbuf, len);
		}
	}

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Helper function used to create and send a query window size message
// --------------------------------------------------------------------------

void CNetworkSettings::SendQueryWindowSize(void)
{
CFractalParameters params;
int len;
FRbyte *pbuf = new FRbyte[params.m_maxmessagesize];

if (NULL == pbuf)
	{
	return;
	}

params.CreateQueryWindowSize(pbuf, m_server.m_port, m_server.m_ipaddr, len);

SendBroadcast(pbuf, len);

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Helper function used to send a query window size reply message
// --------------------------------------------------------------------------

void CNetworkSettings::SendQueryWindowSizeReply(CFractalParameters &srcparam,
						CFractalParameters &replyto)
{
FRbyte *pbuf = new FRbyte[srcparam.m_maxmessagesize];

if (NULL == pbuf)
        {
        return;
        }

// Find out which host has the originating address or name and send a reply
// Needed to resolve names like localhost vs. 127.0.0.1 vs local IP addr
//
// If we just wanted to send back to the originating client, we could
// just use the write function on the active socket
// But as we want to find the matching server address:port combination
// we have to go through each node entry in turn

for (auto it : m_nodelist)      // Send parameters request reply
        {
        if (it->match( replyto.m_addr, replyto.m_port ) == true)
                {
                int len;
                srcparam.m_msgtype = MSG_QUERYWINDOWSIZEREPLY;
		srcparam.m_windowfrom = replyto.m_windowto;
		srcparam.m_windowto = replyto.m_windowfrom;

		cout << "Sending width = " << srcparam.m_windowwidth << endl;
		cout << "Sending height = " << srcparam.m_windowheight << endl;

                srcparam.PackData(pbuf,len);

                it->write(pbuf, len);
                }
        }

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Helper function used by client to send parameters
// --------------------------------------------------------------------------

void CNetworkSettings::SendParameters(CFractalParameters &srcparam, int wfrom, int wto)
{
if (srcparam.m_changebits == CHANGEBIT_NONE)
        {
        return;
        }

FRbyte *pbuf = new FRbyte[srcparam.m_maxmessagesize];

if (NULL == pbuf)
	{
	return;
	}

CFractalParameters params;
int len;

for (auto it : m_nodelist )	// Send parameters
        {
        // If connection is open, then send a message
        if (it->m_clientstate == CLIENT_OPEN)
                {
	        // Calculate parameters for peer node
       	 	params.CalculateNodeParameters( srcparam, *it );
		params.m_msgtype = MSG_PARAMS;
		params.m_windowfrom = wfrom;
		params.m_windowto = wto;

        	params.PackData(pbuf, len);

                it->write( pbuf, len);
                }
        }

srcparam.m_changebits = CHANGEBIT_NONE;

delete [] pbuf;
}

// --------------------------------------------------------------------------
// Function used by server to receive parameters
// 
// The functionality 
// --------------------------------------------------------------------------

int CNetworkSettings::ReceiveParameters(CFractalParameters &params, 
		FRbyte *pbuf, int msgsize, bool &endconnection)
{
int ncount = 0;

endconnection = false;

// Receive as many commands as required
errno = 0;

int nbytes = m_server.readnonblock( pbuf, msgsize);

if (nbytes < 0) 
	{
	if ((errno != EAGAIN) && (errno != EWOULDBLOCK))
		{
		// Connection has been closed
		if (g_verbose)		
			{
			cout << "Closing connection due to error " <<  errno << endl;
			}

		endconnection = true;
		}
	}
else
if (nbytes == 0)
	{
	if (g_verbose)
		{
		cout << "Connection closed due to other end" << endl;
		}

	// Connection has been closed
	endconnection = true; 
	}
else
	{
	if (m_messagedump)
		{
       		cout << "Received: Message (" << nbytes << " bytes)" << endl;
       		}

	// Unpack the data
	params.UnpackData(pbuf, nbytes);
	ncount++;

	if (m_messagedump)
		{
        	params.HexDump(pbuf, msgsize);
		params.DisplayAscii();
                }
	}

return ncount;
}

