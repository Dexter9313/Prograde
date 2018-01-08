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

#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>

#include "../../math/Vector3.hpp"
#include "../../physics/UniversalTime.hpp"

class Drawer
{
  public:
	Drawer(Urho3D::Scene* scene)
	    : scene(scene){};
	virtual void updateMesh(UniversalTime uT, Vector3 const& cameraPos) = 0;
	virtual ~Drawer(){};

  protected:
	Urho3D::Scene* scene;
	Urho3D::Node* node;
};

#endif // DRAWER_HPP
