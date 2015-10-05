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

#ifndef _FRACTPARAMSLIST_H_
#define _FRACTPARAMSLIST_H_

class CFractalParametersList : public CFractalParamsListIO
{
public:
// Function used to perform linear interpolation between two frames
// 
// fpos is the parametric coordinate between the two frames

void CalculateFrame(CFractalParameters &frame, float fpos )
        {
        unsigned int ipos = (int) fpos;
        float frac = fpos - (float) ipos;

        if (ipos >= size()-1)
                {
                ipos = size()-1;
                frame = at(ipos);
                }
        else
                {
                frame.Mix( at(ipos), at(ipos+1), frac);
                }
        }
};

#endif	// _FRACTPARAMSLIST_H_
