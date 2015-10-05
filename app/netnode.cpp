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

// ===========================================================================
// CLIENT SIDE
// ===========================================================================

void CNetworkNode::getipaddr()
{
char strhostname[128];
gethostname(strhostname, 128);

struct hostent *hostid = gethostbyname( strhostname );

if (hostid != NULL)
	{
        m_ipaddr = *((in_addr *) *hostid->h_addr_list);
        }
}

void CNetworkNode::setnonblocking(int fd)
{
int flags;

/* If they have O_NONBLOCK, use the Posix way to do it */

#if defined(O_NONBLOCK)
/* O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5 */
if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
	{
	flags = 0;
	}

fcntl(m_socketactive, F_SETFL, flags | O_NONBLOCK);
#else
/* Otherwise, use the old way of doing it */
flags = 1;
return ioctl(fd, FIOBIO, &flags);
#endif
}

void CNetworkNode::setnonblocking(void)
{
setnonblocking(m_socketlisten);
setnonblocking(m_socketactive);
}

// ---------------------------------------------------------------------------
// Open the client
// ---------------------------------------------------------------------------

int CNetworkNode::open_client(void)
{
struct sockaddr_in serv_addr;
struct hostent *server;

if (m_clientstate == CLIENT_OPEN)
	{
	return SOCKET_OPEN_ALREADY;
	}

// ----- Create a socket ----------------------------------------------------

m_socketactive = socket(AF_INET, SOCK_STREAM, 0);

if (m_socketactive < 0)
        {
	m_socketactive = -1;

	return SOCKET_OPENING_SOCKET;
        }

// ----- Find the server address --------------------------------------------

server = gethostbyname(m_hostname.data() );

if (server == NULL)
        {
	close(m_socketactive);	
	m_socketactive = -1;
	return SOCKET_NO_HOST;
        }

bzero((char *) &serv_addr, sizeof(serv_addr));

serv_addr.sin_family = AF_INET;

bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

serv_addr.sin_port = htons(m_port);

// ----- Connect the socket to the server -----------------------------------

errno = 0;
if (connect(m_socketactive,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
	return SOCKET_CONNECTING;
        }

m_clientstate = CLIENT_OPEN;

return SOCKET_SUCCESS;
}

// ===========================================================================
// SERVER SIDE
// ===========================================================================

// ---------------------------------------------------------------------------
// Open a server
// ---------------------------------------------------------------------------

int CNetworkNode::open_server( void )
{
struct sockaddr_in serv_addr;

if (m_serverstate != SERVER_CLOSED)
	{
	return SOCKET_OPEN_ALREADY;
	}

// ----- Create a passive listening socket --------------------------------

m_socketlisten = socket(AF_INET, SOCK_STREAM, 0);

if (m_socketlisten < 0)
        {
	return SOCKET_OPENING_SOCKET;
        }

bzero((char *) &serv_addr, sizeof(serv_addr));

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(m_port);

if (bind(m_socketlisten, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        {
	return SOCKET_BINDING;
        }

if ( listen(m_socketlisten, 5) < 0)
	{
	return SOCKET_LISTEN;
	}

m_serverstate = SERVER_OPEN;

setnonblocking(m_socketlisten);

return SOCKET_SUCCESS;
}

// --------------------------------------------------------------------------
// Open a new connection
// --------------------------------------------------------------------------

int CNetworkNode::open_serverconnection(void)
{
// ----- Create a general purpose socket for communication ------------------
sockaddr_storage recvaddr;
socklen_t recvlen;

memset(&recvaddr,0, sizeof(recvaddr) );

m_socketactive = accept(m_socketlisten, (struct sockaddr *) &recvaddr, &recvlen);

if (m_socketactive < 0)
        {
	return SOCKET_ACCEPT;
        }

return SOCKET_SUCCESS;
}

// --------------------------------------------------------------------------
// Perform a match with a port and an address
//
// What about localhost and 127.0.0.1
/*
Creating ping packet
Client is open
Sending ping to |127.0.0.1|8081|
Received ping
Sending ping reply
Trying to match to 127.0.1.1|8080
Tmatch 127.0.0.1|8080
*/
//
// Problem: We've received a message from 127.0.1.1
//
// But we only know 127.0.0.1
//
// Is 127.0.1.1 us?
// --------------------------------------------------------------------------

typedef enum
{
MATCH_NONE    = 0x00,
MATCH_ADDRESS = 0x01,
MATCH_PORT    = 0x04
} NetMatchBits;

bool match_hostentry(struct hostent *pnode, in_addr &addr)
{
char **chptr = pnode->h_addr_list;      // Try the address list

while (*chptr != NULL)
        {
        struct in_addr *paddr = (struct in_addr *) *chptr;

        if (memcmp(paddr, &addr, sizeof(struct in_addr)) == 0)
                {
                return true;
                }

        chptr++;
        }

return false;
}

bool CNetworkNode::match( in_addr &addr, int port)
{
// Get remote host entries
struct hostent *pnode = gethostbyname( m_hostname.data() ); // 127.0.0.1

if (g_verbose)
	{
	cout << "Trying to match to " << inet_ntoa( addr) << "|" << port << endl;
	}

if (pnode == NULL || m_port != port)
	{
	return false;	// No hostname entry or matching port
	}

char buf[128];
gethostname( buf, 128);
struct hostent *phost = gethostbyname( buf);
// Need to determine whether remote host is actually local host
int localmatch = match_hostentry(phost, addr);

if (localmatch && ((m_hostname == "localhost") || (m_hostname == "127.0.0.1")))
	{
	return true;
	}

return match_hostentry( pnode, addr);
}

