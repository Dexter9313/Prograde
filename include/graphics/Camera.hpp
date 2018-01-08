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

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>
#include <vector>

#include "../physics/CelestialBody.hpp"
#include "Utils.hpp"

// stays in the center of the scene, drawers know it
class Camera : public Urho3D::Object
{
	URHO3D_OBJECT(Camera, Urho3D::Object);

  public:
	Camera(Urho3D::Context* context, Urho3D::Scene* scene);
	void setTarget(CelestialBody* target)
	{
		this->target = target;
		camDist      = target->getParameters().radius * 100;
	};
	void update(UniversalTime uT);
	Vector3 getAbsolutePosition() const { return absolutePosition; };
	void onEvent(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
	Urho3D::Node* getNode() { return camNode; };
  private:
	Urho3D::Node* camNode;

	double camDist;
	float camAngleXZ;
	float camAngleXY;

	Vector3 absolutePosition;

	bool mouseIsPressed;
	bool mouseEventHandled;

	CelestialBody* target;
};

#endif // CAMERA_HPP
