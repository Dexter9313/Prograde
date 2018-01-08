/*
    Copyright (C) 2018 Florian Cabot <florian.cabot@hotmail.fr>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "graphics/Utils.hpp"

Urho3D::Vector3 toUrho3D(Vector3 const& vector)
{
	return Urho3D::Vector3(vector[0], -1 * vector[1], vector[2]);
}

Vector3 fromUrho3D(Urho3D::Vector3 const& vector)
{
	return Vector3(vector.x_, -1 * vector.y_, vector.z_);
}

Urho3D::Color toUrho3D(Color const& color)
{
	return Urho3D::Color(color.r / 255.f, color.g / 255.f, color.b / 255.f,
	                     color.alpha / 255.f);
}

Color fromUrho3D(Urho3D::Color const& color)
{
	return Color(255 * color.a_, 255 * color.r_, 255 * color.g_,
	             255 * color.b_);
}
