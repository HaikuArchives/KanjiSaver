//		Copyright © 1997–2000  Jens Kilian
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

#include <GraphicsDefs.h>

#include "RandomColor.h"
#include "RandomNumbers.h"

inline float
rgb(float q1, float q2, int hue)
{
	hue = (hue + 360) % 360;
	if (hue < 60) {
		return q1 + (q2-q1) * hue / 60.0;

	} else if (hue < 180) {
		return q2;

	} else if (hue < 240) {	
		return q1 + (q2-q1) * (240 - hue) / 60.0;
	
	} else {
		return q1;
	}
}

RandomColor::RandomColor(float minL, float maxL, float minS, float maxS,
								 int hue)
{
	if (hue < 0) {
		hue = randomInteger(360);
	} else {
		hue %= 360;
	}

	float lightness  = minL + randomFloat() * (maxL-minL);
	float saturation = minS + randomFloat() * (maxS-minS);

	// HLS to RGB conversion.  Sheer magic, don't ask me :-)
	float p2 = (lightness <= 0.5)
		? lightness * (saturation + 1.0)
		: lightness + saturation - lightness*saturation;
	float p1 = 2.0*lightness - p2;
	
	if (saturation == 0.0) {
		mColor.red =		(int)(255.0 * lightness);
		mColor.green =		(int)(255.0 * lightness);
		mColor.blue =		(int)(255.0 * lightness);
	} else {
		mColor.red =		(int)(255.0 * rgb(p1, p2, hue + 120));
		mColor.green =		(int)(255.0 * rgb(p1, p2, hue));
		mColor.blue =		(int)(255.0 * rgb(p1, p2, hue - 120));
	}
}
