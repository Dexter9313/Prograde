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

#ifndef SKYBOXGENERATOR_HPP
#define SKYBOXGENERATOR_HPP

#include <array>
#include <cmath>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/Graphics/TextureCube.h>
#include <Urho3D/Resource/Image.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Node.h>
#include <Urho3D/Scene/Scene.h>

#include "../math/constants.hpp"
#include "../physics/Color.hpp"
#include "Utils.hpp"

class SkyboxGenerator
{
  public:
	SkyboxGenerator() = delete;
	static void createRandomUniformSkybox(Urho3D::Scene* scene,
	                                      unsigned int texturesSize);
	static void createRandomGalacticSkybox(Urho3D::Scene* scene,
	                                       unsigned int texturesSize);
	static void loadSkybox(Urho3D::Scene* scene, unsigned int texturesSize);
	static void loadSkyboxFromEquatorialData(Urho3D::Scene* scene,
	                                         unsigned int texturesSize,
	                                         float axialTilt);

  private:
	struct Star
	{
		std::string commonName;
		float latitude;
		float longitude;
		float properMotionLatitude;
		float properMotionLongitude;
		float magnitude;
		Urho3D::Color color;
	};

	static std::vector<Star> loadStars();
	static void sphericalToCube(double latitude, double longitude,
	                            unsigned int edgeLength, unsigned int& face,
	                            unsigned int& faceX, unsigned int& faceY,
	                            float axialTilt);

	static float lumFromMagnitude(float magnitude);
	static Color colorFromColorIndex(float ci);
	static void createSceneNode(Urho3D::Scene* scene,
	                            std::array<Urho3D::Image*, 6>& ims);
};

#endif // SKYBOXGENERATOR_HPP
