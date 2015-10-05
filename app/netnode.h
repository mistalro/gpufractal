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

// ---------------------------------------------------------------------------
// Common network functions for server and client
// ---------------------------------------------------------------------------

#ifndef NETWORK_NODE_H_
#define NETWORK_NODE_H_

using namespace std;

// --------------------------------------------------------------------------
// Result code for socket operations
// --------------------------------------------------------------------------

typedef enum
{
SOCKET_SUCCESS = 1,
SOCKET_OPENING_SOCKET = -1,
SOCKET_NO_HOST = -2,
SOCKET_CONNECTING = -3,
SOCKET_BINDING = -4,
SOCKET_ACCEPT = -5,
SOCKET_LISTEN = -6,
SOCKET_OPEN_ALREADY = -7
} SocketErrors;

// --------------------------------------------------------------------------
// State of client and server ends
// --------------------------------------------------------------------------

typedef enum
{
CLIENT_CLOSED,
CLIENT_OPEN,
SERVER_CLOSED,
SERVER_OPEN
} SocketSendState;

// --------------------------------------------------------------------------
// Bundle up all the socket communication into a single class object
// --------------------------------------------------------------------------

class CNetworkNode : public CNodeDataIO
{
public:
int    m_clientstate;		// Client state (open or closed)
int    m_serverstate;		// Server state (open or closed)
int    m_socketlisten;		// Server (listening socket)
int    m_socketactive;		// Server/Client (active socket)
in_addr m_ipaddr;		// Local address

CNetworkNode(void)
        {
	m_serverstate = SERVER_CLOSED;	// Closed at start 
	m_clientstate = CLIENT_CLOSED;	// Closed at start
        m_hostname = "localhost";	// Use localhost as default
        m_port = 8080;			// Default port
	m_socketlisten = 0;		// Listening socket
	m_socketactive = 0;		// Active socket

	getipaddr();
        }

void getipaddr(void);

int open_client();

inline void close_client(void)
	{
	if (CLIENT_OPEN == m_clientstate)
		{
		close(m_socketactive);
		m_clientstate = CLIENT_CLOSED;
		}
	}

int open_server(void);
int open_serverconnection(void);

inline void close_server(void)
	{
	if (SERVER_OPEN == m_serverstate)
		{
		close(m_socketactive);
		close(m_socketlisten);
		
		cout << "Closing server" << endl;

		m_serverstate = SERVER_CLOSED;
		}
	}

inline void write( const FRbyte *pdata, int len)
	{
	// Equivalent to write, but without any signals 
	errno = 0;
 	int result = ::send( m_socketactive, (char *)pdata, len, MSG_NOSIGNAL);

	// Remote end has been disconnected
	if ((-1 == result) && (EPIPE  == errno))
		{
		// Mark client as closed
		m_clientstate = CLIENT_CLOSED;
		}
	}

inline int read( FRbyte *pbuf, int max)
	{
	return ::read( m_socketactive, pbuf, max);
	}

inline int readnonblock( FRbyte *pbuf, int max)
	{
        struct sockaddr src_addr;
        socklen_t addr_len;

	return ::recvfrom(m_socketactive, pbuf, max, MSG_DONTWAIT, &src_addr, &addr_len);
	}

void setnonblocking(int fd);
void setnonblocking(void);

bool match(in_addr &addr, int port);
};

#endif // NETWORK_NODE_H_
