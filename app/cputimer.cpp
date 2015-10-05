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
#include <time.h>

// @brief Setup the timer.
//
// @return None.
void CTimerCPU::setup(void)
{
}

// @brief Shutdown the timer.
//
// @return None.

void CTimerCPU::shutdown(void)
{
}

// @brief Start the timer.
//
// @return None.
void CTimerCPU::start(void)
{
clock_gettime(CLOCK_MONOTONIC, &m_timestart);
}

// @brief Stop the timer.
//
// @return None.
void CTimerCPU::stop(void)
{
clock_gettime(CLOCK_MONOTONIC, &m_timefinish);
}

void timespec_sub(struct timespec &finish, struct timespec &start, struct timespec &delta)
{
delta.tv_sec = finish.tv_sec - start.tv_sec;
delta.tv_nsec = finish.tv_nsec - start.tv_nsec;

if (delta.tv_nsec < 0)
	{
	delta.tv_sec -= 1;
	delta.tv_nsec += 1000000000L;
	}

if (delta.tv_nsec > 1000000000L)
	{
	delta.tv_sec += 1;
	delta.tv_nsec -= 1000000000L;
	}
}

// @brief Query the value of the timer as a 64-bit result.
//
// @return None.
long int CTimerCPU::getvalue64(void)
{
clock_gettime(CLOCK_MONOTONIC, &m_timefinish);
timespec_sub( m_timefinish, m_timestart, m_timedelta);

return m_timedelta.tv_sec * 1000000000L + m_timedelta.tv_nsec;
}

// @brief Query the value of the timer as a 32-bit result.
//
// @return None.
int CTimerCPU::getvalue(void)
{
clock_gettime(CLOCK_MONOTONIC, &m_timefinish);
timespec_sub( m_timefinish, m_timestart, m_timedelta);

return m_timedelta.tv_sec * 1000000000L + m_timedelta.tv_nsec;
}
