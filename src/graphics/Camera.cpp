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

#include "graphics/Camera.hpp"

Camera::Camera(Urho3D::Context* context, Urho3D::Scene* scene)
    : Urho3D::Object(context)
    , camDist(100)
    , camAngleXZ(0)
    , camAngleXY(0)
    , mouseIsPressed(false)
    , mouseEventHandled(false)
    , target(nullptr)
{
	camNode             = scene->CreateChild("Camera");
	Urho3D::Camera* cam = camNode->CreateComponent<Urho3D::Camera>();
	(void) cam;
	camNode->SetPosition(Urho3D::Vector3(0, 0, 0));
	camNode->LookAt(Urho3D::Vector3(1, 0, 0), Urho3D::Vector3(0, 0, 1));

	SubscribeToEvent(Urho3D::E_MOUSEBUTTONUP, URHO3D_HANDLER(Camera, onEvent));
	SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN,
	                 URHO3D_HANDLER(Camera, onEvent));
	SubscribeToEvent(Urho3D::E_MOUSEMOVE, URHO3D_HANDLER(Camera, onEvent));
	SubscribeToEvent(Urho3D::E_MOUSEWHEEL, URHO3D_HANDLER(Camera, onEvent));
}

void Camera::update(UniversalTime uT)
{
	Vector3 camRelPos(camDist + target->getParameters().radius, 0, 0);
	camRelPos.rotateAlongY(camAngleXZ);
	camRelPos.rotateAlongZ(camAngleXY);

	absolutePosition     = target->getAbsolutePositionAtUT(uT) + camRelPos;
	Vector3 targetVector = (-1 * camRelPos);
	camNode->LookAt(toUrho3D(targetVector), Urho3D::Vector3(0, 0, 1));

	mouseEventHandled = false;
}

void Camera::onEvent(Urho3D::StringHash eventType,
                     Urho3D::VariantMap& eventData)
{
	if(eventType == Urho3D::E_MOUSEBUTTONDOWN
	   && eventData[Urho3D::MouseButtonDown::P_BUTTON].GetInt()
	          == Urho3D::MOUSEB_RIGHT)
	{
		mouseIsPressed = true;
		GetSubsystem<Urho3D::Input>()->SetMouseVisible(false);
	}
	else if(eventType == Urho3D::E_MOUSEWHEEL)
	{
		if(eventData[Urho3D::MouseWheel::P_WHEEL].GetInt() > 0)
		{
			camDist /= 1.2f;
		}
		else if(eventData[Urho3D::MouseWheel::P_WHEEL].GetInt() < 0)
		{
			camDist *= 1.2f;
		}
	}
	else if(eventType == Urho3D::E_MOUSEBUTTONUP
	        && eventData[Urho3D::MouseButtonUp::P_BUTTON].GetInt()
	               == Urho3D::MOUSEB_RIGHT)
	{
		mouseIsPressed = false;
		GetSubsystem<Urho3D::Input>()->SetMouseVisible(true);
	}
	else if(eventType == Urho3D::E_MOUSEMOVE)
	{
		if(!mouseIsPressed || mouseEventHandled)
		{
			return;
		}

		camAngleXZ -= eventData[Urho3D::MouseMove::P_DY].GetInt() / 500.f;
		camAngleXY -= eventData[Urho3D::MouseMove::P_DX].GetInt() / 500.f;
		if(camAngleXZ <= -1.5)
		{
			camAngleXZ = -1.5;
		}
		if(camAngleXZ >= 1.5)
		{
			camAngleXZ = 1.5;
		}

		mouseEventHandled = true;
	}
}
