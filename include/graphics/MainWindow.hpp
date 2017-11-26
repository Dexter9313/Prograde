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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sys/time.h>
#include <vector>

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>

#include "Camera.hpp"
#include "LauncherWindow.hpp"
#include "SkyboxGenerator.hpp"
#include "Utils.hpp"
//#include "shaders/FarCelestialBodyShader.hpp"
#include "drawers/CelestialBodyDrawer.hpp"
#include "drawers/OrbitalSystemDrawer.hpp"
#include "physics/SimulationTime.hpp"
#include "math/constants.hpp"

class MainWindow : public Urho3D::Application
{
	URHO3D_OBJECT(MainWindow, Urho3D::Application);

  public:
	MainWindow(Urho3D::Context* context,
	           LauncherWindow::LauncherReturned const& initFromLauncher);
	virtual void Setup();
	virtual void Start();
	virtual void Stop();
	void update(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
	~MainWindow();

	void onEvent(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData)
	{
		if(eventType == Urho3D::E_KEYDOWN)
		{
			unsigned int key = eventData[Urho3D::KeyDown::P_KEY].GetUInt();
			if(key == Urho3D::KEY_ESCAPE)
				engine_->Exit();
			else if(key == Urho3D::KEY_TAB)
			{
				bodyTracked++;
				std::vector<CelestialBody*> bodies(
				    orbitalSystem->getAllCelestialBodiesPointers());
				if(bodyTracked == bodies.size())
					bodyTracked = 0;
				cam->setTarget(bodies[bodyTracked]);
			}
			else if(key == Urho3D::KEY_R)
			{
				float timeCoeff(clock.getTimeCoeff());
				if(timeCoeff >= 10)
					timeCoeff /= 10;
				clock.setTimeCoeff(timeCoeff);
			}
			else if(key == Urho3D::KEY_T)
			{
				float timeCoeff(clock.getTimeCoeff());
				if(timeCoeff <= 100000)
					timeCoeff *= 10;
				clock.setTimeCoeff(timeCoeff);
			}
			/*else if(event.EventType == irr::EET_GUI_EVENT)
			{
			    if(event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
			    {
			        if(event.GUIEvent.Caller->getID() == 101)
			        {
			            device->closeDevice();
			            return true;
			        }
			    }
			}*/
		}
	}

  private:
	Camera* cam;
	unsigned int bodyTracked;

	OrbitalSystem* orbitalSystem;
	OrbitalSystemDrawer* systemDrawer;
	Urho3D::Scene* systemScene;
	Urho3D::Text* debugText;

	SimulationTime clock;

	static std::string timeToStr(UniversalTime uT);
	static void computeDayMonth(unsigned int* day, unsigned int* month,
	                            bool bissextile);
};

#endif // MAINWINDOW_HPP
