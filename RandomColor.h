//		Copyright © 1997  Jens Kilian
//
//		This program is free software; you can redistribute it and/or modify
//		it under the terms of the GNU General Public License as published by
//		the Free Software Foundation; either version 1, or (at your option)
//		any later version.
//
//		This program is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
//		GNU General Public License for more details.
//
//		You should have received a copy of the GNU General Public License
//		along with this program; if not, write to the Free Software
//		Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

//		Select a color of random hue, within a given range of lightness
//		and saturation.

#ifndef RANDOMCOLOR_H
#define RANDOMCOLOR_H

#include <GraphicsDefs.h>

class RandomColor {
public:
	RandomColor(float minL, float maxL, float minS, float maxS,
					int hue = -1);
	
	operator rgb_color(void) const;

private:
	rgb_color mColor;
};

inline
RandomColor::operator rgb_color(void) const
{
	return mColor;
}

#endif // RANDOMCOLOR_H
