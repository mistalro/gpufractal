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
#ifndef _GEO_CPUTIMER_H_
#define _GEO_CPUTIMER_H_

#include <sys/time.h>

class CTimerCPU
{
struct timespec m_timestart;
struct timespec m_timefinish;
struct timespec m_timedelta;

public:
CTimerCPU(void)
	{
	init();
	}

void init(void)
	{
	};

void setup(void);
void shutdown(void);
void start(void);
void stop(void);
long int getvalue64(void);
int getvalue(void);
};

#endif	// _GEO_CPUTUMER_H_
