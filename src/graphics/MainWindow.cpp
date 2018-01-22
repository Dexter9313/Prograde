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

#include "graphics/MainWindow.hpp"

MainWindow::MainWindow(Urho3D::Context* context,
                       LauncherWindow::LauncherReturned const& initFromLauncher)
    : Urho3D::Application(context)
    , bodyTracked(0)
    , orbitalSystem(initFromLauncher.orbitalSystem)
    , clock(initFromLauncher.utStart)
{
}

void MainWindow::Setup()
{
	// Modify engine startup parameters
	engineParameters_["WindowTitle"] = "Prograde";
	engineParameters_["LogName"]
	    = GetSubsystem<Urho3D::FileSystem>()->GetAppPreferencesDir("urho3d",
	                                                               "logs")
	      + GetTypeName() + ".log";
	engineParameters_["Fullscreen"]   = true;
	engineParameters_["Borderless"]   = false;
	engineParameters_["Headless"]     = false;
	engineParameters_["WindowWidth"]  = 1920;
	engineParameters_["WindowHeight"] = 1080;
	engineParameters_["VSync"]        = false;
	engineParameters_["ResourcePaths"]
	    = "data/urho3d/Data;data/urho3d/CoreData";
	engineParameters_["Multisample"] = 16;

	// Construct a search path to find the resource prefix with two entries:
	// The first entry is an empty path which will be substituted with
	// program/bin directory -- this entry is for binary when it is still in
	// build tree
	// The second and third entries are possible relative paths from the
	// installed program/bin directory to the asset directory -- these entries
	// are for binary when it is in the Urho3D SDK installation location
	if(!engineParameters_.Contains("ResourcePrefixPaths"))
	{
		engineParameters_["ResourcePrefixPaths"]
		    = ";../share/Resources;../share/Urho3D/Resources";
	}
}

void MainWindow::Start()
{
	SubscribeToEvent(Urho3D::E_KEYDOWN, URHO3D_HANDLER(MainWindow, onEvent));
	SubscribeToEvent(Urho3D::E_UPDATE, URHO3D_HANDLER(MainWindow, update));
	GetSubsystem<Urho3D::Input>()->SetMouseVisible(true);

	systemScene = new Urho3D::Scene(context_);
	systemScene->CreateComponent<Urho3D::Octree>();
	SkyboxGenerator::loadSkyboxFromEquatorialData(
	    systemScene, 1500, 23.4392811 * constant::pi / 180.f);
	// SkyboxGenerator::loadSkybox(systemScene, 1024);
	// SkyboxGenerator::createRandomUniformSkybox(systemScene, 1024);
	// SkyboxGenerator::createRandomGalacticSkybox(systemScene, 1024);

	systemDrawer = new OrbitalSystemDrawer(systemScene, orbitalSystem);

	cam = new Camera(context_, systemScene);
	cam->setTarget(orbitalSystem->getAllCelestialBodiesPointers()[0]);

	auto renderer = GetSubsystem<Urho3D::Renderer>();

	// Set up a viewport to the Renderer subsystem so that the 3D scene can be
	// seen. We need to define the scene and the camera
	// at minimum. Additionally we could configure the viewport screen size and
	// the rendering path (eg. forward / deferred) to
	// use, but now we just use full screen and default render path configured
	// in the engine command line options
	auto viewport(new Urho3D::Viewport(
	    context_, systemScene, cam->getNode()->GetComponent<Urho3D::Camera>()));
	renderer->SetViewport(0, viewport);

	auto cache                = GetSubsystem<Urho3D::ResourceCache>();
	Urho3D::UIElement* uiRoot = GetSubsystem<Urho3D::UI>()->GetRoot();
	auto style = cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml");
	uiRoot->SetDefaultStyle(style);

	debugText = new Urho3D::Text(context_);
	debugText->SetText("Hello World");
	debugText->SetSize(100, 100);
	debugText->SetPosition(20, 20);
	debugText->SetStyleAuto();
	uiRoot->AddChild(debugText);

	/*env->addButton(core::rect<s32>(10,240,110,240 + 32), 0, 101,
	                    L"Quit", L"Exits Program");*/
}

#include <iostream>
#include <sstream>
void MainWindow::update(Urho3D::StringHash eventType,
                        Urho3D::VariantMap& eventData)
{
	(void) eventType;
	(void) eventData;
	clock.update();
	if(!clock.drawableFrame())
	{
		return;
	}

	std::stringstream stream;
	stream.precision(2);
	stream << clock.getCurrentFPS() << " FPS" << std::endl;
	stream << "Targeting : "
	       << orbitalSystem->getAllCelestialBodiesNames()[bodyTracked]
	       << std::endl;
	stream.precision(10);
	stream << "Distance : "
	       << (cam->getAbsolutePosition()
	           - orbitalSystem->getAllCelestialBodiesPointers()[bodyTracked]
	                 ->getAbsolutePositionAtUT(clock.getCurrentUt()))
	                  .length()
	              - orbitalSystem->getAllCelestialBodiesPointers()[bodyTracked]
	                    ->getParameters()
	                    .radius
	       << std::endl;
	stream.precision(4);
	stream << "UT = " << timeToStr(clock.getCurrentUt()) << std::endl;
	stream.precision(300);
	stream << " Raw UT = " << floor(clock.getCurrentUt() * 10) / 10
	       << std::endl;
	stream.precision(8);
	stream << "x" << clock.getTimeCoeff();
	debugText->SetText(stream.str().c_str());

	cam->update(clock.getCurrentUt());

	systemDrawer->updateMesh(clock.getCurrentUt(), cam->getAbsolutePosition());
}

void MainWindow::Stop()
{
	engine_->DumpResources(true);
}

MainWindow::~MainWindow()
{
	delete cam;

	delete systemDrawer;
	delete orbitalSystem;

	delete debugText;
}

#include <cmath>
std::string MainWindow::timeToStr(UniversalTime uT)
{
	UniversalTime uT2 = floor(uT);
	auto time(uT2.convert_to<int64_t>());
	unsigned int sec, min, hour, day, month(0), year(1999);
	sec = time % 60;
	time -= sec;
	min = (time / 60) % 60;
	time -= min * 60;
	hour = (12 + (time / 3600)) % 24;
	time -= hour * 3600;
	day = time / (24 * 3600);

	int daytmp(day);

	while(daytmp >= 0)
	{
		year++;
		daytmp -= 365;

		if(daytmp < 0)
		{
			daytmp += 365;
			break;
		}

		year++;
		daytmp -= 365;

		if(daytmp < 0)
		{
			daytmp += 365;
			break;
		}

		year++;
		daytmp -= 365;

		if(daytmp < 0)
		{
			daytmp += 365;
			break;
		}

		year++;
		daytmp -= 366;

		if(daytmp < 0)
		{
			daytmp += 366;
			break;
		}
	}

	day = daytmp;

	computeDayMonth(&day, &month, (year % 4) == 0);

	std::stringstream stream;
	stream << day << " "
	       << " " << month << " " << year << " " << hour << ":" << min << ":"
	       << sec;
	return stream.str();
}

void MainWindow::computeDayMonth(unsigned int* day, unsigned int* month,
                                 bool bissextile)
{
	if(*day < 31)
	{
		*day += 1;
		*month = 1;
		return;
	}

	*day -= 31;

	if((*day < 28 && !bissextile) || (*day < 29 && bissextile))
	{
		*day += 1;
		*month = 2;
		return;
	}

	*day -= bissextile ? 29 : 28;

	if(*day < 31)
	{
		*day += 1;
		*month = 3;
		return;
	}

	*day -= 31;

	if(*day < 30)
	{
		*day += 1;
		*month = 4;
		return;
	}

	*day -= 30;

	if(*day < 31)
	{
		*day += 1;
		*month = 5;
		return;
	}

	*day -= 31;

	if(*day < 30)
	{
		*day += 1;
		*month = 6;
		return;
	}

	*day -= 30;

	if(*day < 31)
	{
		*day += 1;
		*month = 7;
		return;
	}

	*day -= 31;

	if(*day < 31)
	{
		*day += 1;
		*month = 8;
		return;
	}

	*day -= 31;

	if(*day < 30)
	{
		*day += 1;
		*month = 9;
		return;
	}

	*day -= 30;

	if(*day < 31)
	{
		*day += 1;
		*month = 10;
		return;
	}

	*day -= 31;

	if(*day < 30)
	{
		*day += 1;
		*month = 11;
		return;
	}

	*day -= 30;

	if(*day < 31)
	{
		*day += 1;
		*month = 12;
		return;
	}
}
