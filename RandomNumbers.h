//		Copyright © 2000  Jens Kilian
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

//		Utility functions for calculating random numbers.

#ifndef RANDOMNUMBERS_H
#define RANDOMNUMBERS_H

#include <cstdlib>

// Generate a random float from [min, max).
inline float
randomFloat(const float min = 0.0f, const float max = 1.0f)
{
	return min + (max - min) * (float)rand() / ((float)RAND_MAX + 1.0f);
}

// Generate a random double from [min, max).
inline double
randomDouble(const double min = 0.0, const double max = 1.0)
{
	return min + (max - min) * (double)rand() / ((double)RAND_MAX + 1.0);
}

// Generate a random integer.
inline int
randomInteger(const int max)
{
	return (int)(randomDouble() * max);
}

#endif // RANDOMNUMBERS_H
