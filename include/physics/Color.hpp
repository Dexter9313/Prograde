/*
    Copyright (C) 2015 Florian Cabot

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
  public:
	Color();
	Color(unsigned int r, unsigned int g, unsigned int b);
	Color(unsigned int alpha, unsigned int r, unsigned int g, unsigned int b);

	unsigned int alpha;
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

#endif // COLOR_HPP
