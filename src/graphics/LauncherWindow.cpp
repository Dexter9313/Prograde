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

#include "graphics/LauncherWindow.hpp"
#include <iostream>

LauncherWindow::LauncherWindow(Urho3D::Context* context)
    : Urho3D::Application(context)
{
}

void LauncherWindow::Setup()
{
	// Modify engine startup parameters
	engineParameters_["WindowTitle"] = "Prograde Launcher";
	engineParameters_["LogName"]
	    = GetSubsystem<Urho3D::FileSystem>()->GetAppPreferencesDir("urho3d",
	                                                               "logs")
	      + GetTypeName() + ".log";
	engineParameters_["FullScreen"]      = false;
	engineParameters_["Headless"]        = false;
	engineParameters_["Sound"]           = false;
	engineParameters_["WindowResizable"] = false;
	engineParameters_["WindowWidth"]     = 800;
	engineParameters_["WindowHeight"]    = 600;
	engineParameters_["ResourcePaths"]
	    = "data/urho3d/Data;data/urho3d/CoreData";

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

void LauncherWindow::Start()
{
	GetSubsystem<Urho3D::Input>()->SetMouseVisible(true);
	gui = new Gui(context_);

	SubscribeToEvent(Urho3D::E_UIMOUSECLICK,
	                 URHO3D_HANDLER(LauncherWindow, onEvent));

	returned.launch     = false;
	returned.fullscreen = false;
	// returned.utStart = 16*365.25*24*3600 - 71*24*3600;
	returned.utStart = 1443394800 - 946728000;
	// limit before we stop representing milliseconds (we have plenty of time !)
	// we can consider 100000 years to be our safe upper limit for epoch user
	// input (there's theorically 185000 years left before we see problems)
	// returned.utStart = 280000.0*365.25*24.0*3600.0;
	// test age of the universe, normally only precise to 100 seconds, but it's
	// a bit sloppy (yeah I know...;) )
	// returned.utStart = 13500000000.0*365.25*24.0*3600.0;
	// returned.orbitalSystem = new SolarSystem();
	// returned.utStart = 0;
	returned.orbitalSystem = new SolarSystem();
	// returned.orbitalSystem = new KerbalSystem();
	/*
	    float au(20), sunMass(4.75177), satAu(3000);
	    Orbit::Parameters orbitalParams;
	    CelestialBody::Parameters physicalParams;
	    orbitalParams.meanAnomalyAtEpoch = 0;

	    //X
	    orbitalParams.inclination = 0.f;
	    orbitalParams.ascendingNodeLongitude = 0.f;
	    orbitalParams.periapsisArgument = 0.f;
	    orbitalParams.eccentricity = 0;
	    orbitalParams.semiMajorAxis = 0.4*au;
	    orbitalParams.meanAnomalyAtEpoch = 0.f;
	    returned.orbits.push_back(Orbit(sunMass, orbitalParams));
	    returned.radii.push_back(1);
	    returned.colors.push_back(irr::video::SColor(255, 255, 0, 0));
	    //Y
	    orbitalParams.inclination = 0.f;
	    orbitalParams.ascendingNodeLongitude = 0.f;
	    orbitalParams.periapsisArgument = 0.f;
	    orbitalParams.eccentricity = 0.f;
	    orbitalParams.semiMajorAxis = 0.4*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI*90.f/180.f;
	    returned.orbits.push_back(Orbit(sunMass, orbitalParams));
	    returned.radii.push_back(1);
	    returned.colors.push_back(irr::video::SColor(255, 0, 255, 0));
	    //Z
	    orbitalParams.inclination = M_PI * 90 / 180.f;
	    orbitalParams.ascendingNodeLongitude = 0.f;
	    orbitalParams.periapsisArgument = 0.f;
	    orbitalParams.eccentricity = 0.f;
	    orbitalParams.semiMajorAxis = 0.4*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI*90.f/180.f;
	    returned.orbits.push_back(Orbit(sunMass, orbitalParams));
	    returned.radii.push_back(1);
	    returned.colors.push_back(irr::video::SColor(255, 0, 0, 255));


	    //mercury
	    orbitalParams.inclination = M_PI * 7.005 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 48.331 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*29.124/180.f;
	    orbitalParams.eccentricity = 0.205630;
	    orbitalParams.semiMajorAxis = 0.387098*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 174.8 / 180.f;
	    physicalParams.radius = 1;
	    physicalParams.color = Color(100, 100, 100);
	    returned.bodies.push_back(new CelestialBody(sunMass, orbitalParams,
	   physicalParams));


	    //venus
	    orbitalParams.inclination = M_PI * 3.4 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 76.7 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*55.2/180.f;
	    orbitalParams.eccentricity = 0.0068;
	    orbitalParams.semiMajorAxis = 0.723*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 50.115 / 180.f;
	    physicalParams.radius = 1.5;
	    physicalParams.color = Color(255, 255, 204);
	    returned.bodies.push_back(new CelestialBody(sunMass, orbitalParams,
	   physicalParams));

	    //earth
	    orbitalParams.inclination = M_PI * 0.f / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * -11.3 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*114.2/180.f;
	    orbitalParams.eccentricity = 0.017;
	    orbitalParams.semiMajorAxis = au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 358.6 / 180.f;
	    physicalParams.radius = 1.5;
	    physicalParams.color = Color(0, 204, 255);
	    physicalParams.mass = 2.86627;
	    CelestialBody* earth = new CelestialBody(sunMass, orbitalParams,
	   physicalParams);

	    //moon
	    orbitalParams.inclination = M_PI * 5.145 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * -11.3 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*114.2/180.f;
	    orbitalParams.eccentricity = 0.0549;
	    orbitalParams.semiMajorAxis = 0.00257*satAu;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 358.6 / 180.f;
	    physicalParams.radius = 0.3;
	    physicalParams.color = Color(100, 100, 100);
	    CelestialBody* moon = earth->createChild(orbitalParams, physicalParams);
	    returned.bodies.push_back(moon);
	    returned.bodies.push_back(earth);

	    //mars
	    orbitalParams.inclination = M_PI * 1.85 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 49.562 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*286.537/180.f;
	    orbitalParams.eccentricity = 0.0935;
	    orbitalParams.semiMajorAxis = 1.52*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 19.36 / 180.f;
	    physicalParams.radius = 1.2;
	    physicalParams.color = Color(204, 102, 51);
	    physicalParams.mass = 2;
	    CelestialBody* mars = new CelestialBody(sunMass, orbitalParams,
	   physicalParams);

	    //phobos
	    orbitalParams.inclination = M_PI * 26.04 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 0 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*0/180.f;
	    orbitalParams.eccentricity = 0.0151;
	    orbitalParams.semiMajorAxis = 0.00057*satAu;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 358.6 / 180.f;
	    physicalParams.radius = 0.2;
	    physicalParams.color = Color(100, 100, 100);
	    CelestialBody* phobos = mars->createChild(orbitalParams,
	   physicalParams);
	    returned.bodies.push_back(phobos);
	    //deimos
	    orbitalParams.inclination = M_PI * 27.58 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 0 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*0/180.f;
	    orbitalParams.eccentricity = 0.00033;
	    orbitalParams.semiMajorAxis = 0.00207*satAu;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 358.6 / 180.f;
	    physicalParams.radius = 0.1;
	    physicalParams.color = Color(170, 150, 150);
	    CelestialBody* deimos = mars->createChild(orbitalParams,
	   physicalParams);
	    returned.bodies.push_back(deimos);
	    returned.bodies.push_back(mars);

	    //jupiter
	    orbitalParams.inclination = M_PI * 1.305 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 100.492 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*275.066/180.f;
	    orbitalParams.eccentricity = 0.049;
	    orbitalParams.semiMajorAxis = 5.2*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 18.818 / 180.f;
	    physicalParams.radius = 2.8;
	    physicalParams.color = Color(255, 204, 102);
	    returned.bodies.push_back(new CelestialBody(sunMass, orbitalParams,
	   physicalParams));

	    //saturn
	    orbitalParams.inclination = M_PI * 2.485 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 113.6 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*336/180.f;
	    orbitalParams.eccentricity = 0.056;
	    orbitalParams.semiMajorAxis = 9.58*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 320.35 / 180.f;
	    physicalParams.radius = 2.5;
	    physicalParams.color = Color(255, 204, 80);
	    returned.bodies.push_back(new CelestialBody(sunMass, orbitalParams,
	   physicalParams));

	    //uranus
	    orbitalParams.inclination = M_PI * 0.773 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 74 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*97/180.f;
	    orbitalParams.eccentricity = 0.047;
	    orbitalParams.semiMajorAxis = 19.2*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 142.24 / 180.f;
	    physicalParams.radius = 2.2;
	    physicalParams.color = Color(180, 180, 255);
	    returned.bodies.push_back(new CelestialBody(sunMass, orbitalParams,
	   physicalParams));

	    //neptune
	    orbitalParams.inclination = M_PI * 1.768 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI *131.8 / 180.f;
	    orbitalParams.periapsisArgument = M_PI*273.2/180.f;
	    orbitalParams.eccentricity = 0.0087;
	    orbitalParams.semiMajorAxis = 30*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 259.89 / 180.f;
	    physicalParams.radius = 2.2;
	    physicalParams.color = Color(80, 51, 255);
	    returned.bodies.push_back(new CelestialBody(sunMass, orbitalParams,
	   physicalParams));

	    //pluton
	    orbitalParams.inclination = M_PI * 17.09 / 180.f;
	    orbitalParams.ascendingNodeLongitude = M_PI * 110.38 / 180.f;
	    orbitalParams.periapsisArgument = M_PI * 112.6 / 180.f;
	    orbitalParams.eccentricity = 0.2502;
	    orbitalParams.semiMajorAxis = 39.45*au;
	    orbitalParams.meanAnomalyAtEpoch = M_PI * 14.85 / 180.f;
	    physicalParams.radius = 0.4;
	    physicalParams.color = Color(178, 145, 67);
	    returned.bodies.push_back(new CelestialBody(sunMass, orbitalParams,
	   physicalParams));
	    */
}

void LauncherWindow::Stop()
{
	engine_->DumpResources(true);
}

LauncherWindow::~LauncherWindow()
{
	delete gui;
}
