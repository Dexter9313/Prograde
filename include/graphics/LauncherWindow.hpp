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

#ifndef LAUNCHERWINDOW_HPP
#define LAUNCHERWINDOW_HPP

#include <Urho3D/Engine/Application.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/UI/UIEvents.h>
#include <vector>

#include "../physics/OrbitalSystem.hpp"
#include "../physics/default-orbitalsystems/KerbalSystem.hpp"
#include "../physics/default-orbitalsystems/SolarSystem.hpp"
#include "Gui.hpp"

class LauncherWindow : public Urho3D::Application
{
	URHO3D_OBJECT(LauncherWindow, Urho3D::Application);

  public:
	struct LauncherReturned
	{
		bool launch;
		bool fullscreen;
		UniversalTime utStart;
		OrbitalSystem* orbitalSystem;
	};

	LauncherWindow(Urho3D::Context* context);
	virtual void Setup();
	virtual void Start();
	virtual void Stop();
	~LauncherWindow();

	void onEvent(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData)
	{
		if(eventType == Urho3D::E_UIMOUSECLICK)
		{
			Urho3D::UIElement* ptr
			    = (Urho3D::UIElement*)
			          eventData[Urho3D::UIMouseClick::P_ELEMENT]
			              .GetPtr();
			if(!ptr)
				return;
			Urho3D::String name = ptr->GetName();
			if(name == "LAUNCH")
			{
				returned.launch = true;
				engine_->Exit();
			}
			else if(name == "QUIT")
			{
				returned.launch = false;
				engine_->Exit();
			}
			else if(name == "FULLSCREEN")
			{
				returned.fullscreen = !returned.fullscreen;
			}
		}
	}

	LauncherReturned returned;

  private:
	Gui* gui;
};

#endif // LAUNCHERWINDOW_HPP
