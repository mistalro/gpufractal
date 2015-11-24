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

#ifndef FRACTSYSTEM_H_
#define FRACTSYSTEM_H_

// --------------------------------------------------------------------------
// System parameters
// --------------------------------------------------------------------------

class CSystemParameters : public CWindowSettings,
			  public CNetworkSettings
{
public:

int    m_verbose;               // Display events
bool   m_echomode;              // Echo mode for events
bool	m_replaymode;		// Use replay mode
string m_replayfile;            // Replay file path
CFractalParametersList m_savelist; // Replay file data
CFractalParameters m_loadparameters; // Default parameters to read from file
string m_textransfer;		// Color file
bool   m_exitmode;              // Exit application flag
float  m_angledelta;		// Rotation speed for angles
float  m_transdelta;		// Translation speed
float  m_powerdelta;		// Power delta
float  m_zoomdelta;		// Zoom delta
float  m_zoomwheeldelta;	// Zoom wheel delta

CSystemParameters(void)
        {
        m_verbose = false;
        m_echomode = false;
	m_replaymode = false;
        m_replayfile = "";
        m_savelist.clear();
	m_textransfer = "";
        m_exitmode = false;
	m_angledelta = 0.0001f * M_PI;
	m_transdelta = 0.005f;
	m_zoomdelta = 0.01f;
	m_zoomwheeldelta = 0.05f;
        }

inline void SetExitFlag(void)
	{
	m_exitmode = true;
	}

inline bool GetExitFlag(void)
	{
	return m_exitmode;
	}

void DisplayHelp( int argc, const char *argv[]);
void ProcessArguments( int argc, const char *argv[]);

CWindowParameters * CreateSetWindow(void)
	{
	CWindowParameters *window = CWindowSettings::CreateWindow();

	window->setparameters( m_loadparameters, true );

	window->setkeyboardrotationdelta( m_angledelta );
	window->setkeyboardtransdelta( m_transdelta );
	window->setzoomdelta( m_zoomdelta );
	window->setzoomwheeldelta( m_zoomwheeldelta );
	window->setpowerdelta( m_powerdelta);

	return window;
	}	
};

#endif	// FRACTSYSTEM_H_
