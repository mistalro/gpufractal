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

#ifndef FRACTPLAYER_H_
#define FRACTPLAYER_H_

// --------------------------------------------------------------------------
// Frame player
// --------------------------------------------------------------------------

class CFramePlayer
{
public:
bool  m_replay;         // Replay mode
bool  m_pause;          // Pause mode
float m_replaypos;      // Replay position
float m_replayrate;     // Replay rate
float m_replaymax;      // Replay maximum pos
float m_replaymin;      // Replay minimum pos
bool  m_replayloop;     // Replay on a loop

CFramePlayer(void )
        {
        m_replay = false;
        m_pause = false;
        m_replaypos = 0.0f;
        m_replayrate = 0.001f;
        m_replaymin = 0.0f;
        m_replaymax = 0.0f;
        m_replayloop = false;
        }

~CFramePlayer(void)
        {

        }

void start_replay(float fstart, float fend)
        {
        m_replay = true;
        m_replaypos = 0.0f;
        m_pause = false;
        m_replaymin = fstart;
        m_replaymax = fend;
        }

void stop_replay(void)
        {
        m_replay = false;
        }

void pause_replay(void)
        {
        m_pause = true;
        }

void update_replay(void)
        {
        if ((m_pause == false) && (m_replay == true))
                {
                if (m_replaypos >= m_replaymax)
                        {
                        if (m_replayloop)
                                {
                                m_replaypos = m_replaymin;
                                }
                        else
                                {
                                m_replay = false;
                                }
                        }
                else
                        {
                        m_replaypos += m_replayrate;
                        }
                }
        }
};

#endif	// FRACTPLAYER_H_
