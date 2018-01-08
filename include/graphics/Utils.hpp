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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <Urho3D/Math/Color.h>
#include <Urho3D/Math/Vector3.h>

#include "../math/Vector3.hpp"
#include "../physics/Color.hpp"

Urho3D::Vector3 toUrho3D(Vector3 const& vector);
Vector3 fromUrho3D(Urho3D::Vector3 const& vector);
Urho3D::Color toUrho3D(Color const& color);
Color fromUrho3D(Urho3D::Color const& color);

#endif // UTILS_HPP
