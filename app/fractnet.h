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

#ifndef _FRACTNET_H_
#define _FRACTNET_H_

// --------------------------------------------------------------------------
// Network node list - no extra functions required
// --------------------------------------------------------------------------

class CNetworkNodeList : public CNetNodeEntryListIO
{
public:

};

// --------------------------------------------------------------------------
// Define the network settings for this application
// --------------------------------------------------------------------------

class CNetworkSettings
{
public:
bool   m_servermode;            // Network server mode
bool   m_clientmode;            // Use network mode
string m_nodelistfile;          // Network node specification file
CNetworkNodeList m_nodelist;    // List of network nodes for sending
CNetworkNode m_server;          // Server to handle requests and updates
bool    m_messagedump;          // Dump raw messages

CNetworkSettings(void)
        {
	m_messagedump = false;
        m_servermode = false;
        m_clientmode = false;

        m_nodelistfile = "";
        m_nodelist.clear();
        }

// Client functions
void OpenServers(void);
void CloseServers(void);

void SendBroadcast(const FRbyte *pbuf, int len);

void SendPing(void);
void SendRequest( void );
void SendTerminate(void);

void SendParameters(CFractalParameters &srcparam, int wfrom, int wto);
void SendQueryWindowSize(void);

void SendQueryWindowSizeReply(CFractalParameters &srcparam,
                              CFractalParameters &replyto);

// Server functions
int ReceiveParameters(CFractalParameters &params,
                FRbyte *pbuf, int msgsize, bool &endconnection);

void SendPingReply(CFractalParameters &reply);
void SendRequestReply(CFractalParameters &srcparam, CFractalParameters &replyto);
};

#endif	// _FRACTNET_H_
