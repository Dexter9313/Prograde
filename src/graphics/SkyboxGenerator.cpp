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

#include "graphics/SkyboxGenerator.hpp"

// http://mathworld.wolfram.com/SpherePointPicking.html
void SkyboxGenerator::createRandomUniformSkybox(Urho3D::Scene* scene,
                                                unsigned int texturesSize)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distributionLong(0.0,
	                                                        2 * constant::pi);
	std::uniform_real_distribution<double> distributionLat(-1.0, 1.0);
	// close enough distributions
	std::exponential_distribution<double> distributionMag(1);
	std::uniform_real_distribution<double> distributionCI(-0.33, 1.4);

	std::array<Urho3D::Image*, 6> ims
	    = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	for(auto& im : ims)
	{
		im = new Urho3D::Image(scene->GetContext());
		im->SetSize(texturesSize, texturesSize, 4);
	}

	unsigned int face(0), x(0), y(0);

	for(unsigned int i(0); i < 120000; ++i)
	{
		sphericalToCube(acos(distributionLat(generator)) - (constant::pi / 2.0),
		                distributionLong(generator), texturesSize, face, x, y,
		                0.f);
		float mag(-1.0 * distributionMag(generator) + 10);
		float lum(lumFromMagnitude(mag));
		Urho3D::Color baseColor(
		    toUrho3D(colorFromColorIndex(distributionCI(generator))));
		ims[face]->SetPixel(x, y, Urho3D::Color(lum * baseColor.r_,
		                                        lum * baseColor.g_,
		                                        lum * baseColor.b_, 255));
	}

	createSceneNode(scene, ims);
}

void SkyboxGenerator::createRandomGalacticSkybox(Urho3D::Scene* scene,
                                                 unsigned int texturesSize)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distributionLong(0.0,
	                                                        2 * constant::pi);
	std::normal_distribution<double> distributionLat(0, 0.5);
	// close enough distributions
	std::exponential_distribution<double> distributionMag(1);
	std::uniform_real_distribution<double> distributionCI(-0.33, 1.4);

	std::array<Urho3D::Image*, 6> ims
	    = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	for(auto& im : ims)
	{
		im = new Urho3D::Image(scene->GetContext());
		im->SetSize(texturesSize, texturesSize, 4);
	}

	unsigned int face(0), x(0), y(0);

	for(unsigned int i(0); i < 120000; ++i)
	{
		sphericalToCube(acos(distributionLat(generator)) - (constant::pi / 2.0),
		                distributionLong(generator), texturesSize, face, x, y,
		                0.f);
		float mag(-1.0 * distributionMag(generator) + 10);
		float lum(lumFromMagnitude(mag));
		Urho3D::Color baseColor(
		    toUrho3D(colorFromColorIndex(distributionCI(generator))));
		ims[face]->SetPixel(x, y, Urho3D::Color(lum * baseColor.r_,
		                                        lum * baseColor.g_,
		                                        lum * baseColor.b_, 255));
	}

	createSceneNode(scene, ims);
}

void SkyboxGenerator::loadSkybox(Urho3D::Scene* scene,
                                 unsigned int texturesSize)
{
	loadSkyboxFromEquatorialData(scene, texturesSize, 0.f);
}

void SkyboxGenerator::loadSkyboxFromEquatorialData(Urho3D::Scene* scene,
                                                   unsigned int texturesSize,
                                                   float axialTilt)
{
	std::array<Urho3D::Image*, 6> ims
	    = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	for(auto& im : ims)
	{
		im = new Urho3D::Image(scene->GetContext());
		im->SetSize(texturesSize, texturesSize, 4);
	}

	std::vector<Star> stars = loadStars();

	unsigned int face(0), x(0), y(0);

	for(Star star : stars)
	{
		sphericalToCube(star.latitude, star.longitude, texturesSize, face, x, y,
		                axialTilt);
		ims[face]->SetPixel(x, y, star.color);
	}

	createSceneNode(scene, ims);
}

std::vector<SkyboxGenerator::Star> SkyboxGenerator::loadStars()
{
	std::vector<Star> result;

	std::ifstream ifs("data/physics/hygdata_v3_min.csv", std::ifstream::in);
	std::string buffer;

	getline(ifs, buffer);

	while(getline(ifs, buffer) != nullptr)
	{
		std::string::size_type currentPos(0);
		std::string::size_type nextPos(0);
		// NAME
		currentPos       = nextPos;
		nextPos          = buffer.find(',', nextPos);
		std::string name = buffer.substr(currentPos, nextPos - currentPos);

		// MAGNITUDE
		++nextPos;
		currentPos = nextPos;
		nextPos    = buffer.find(',', nextPos);
		float mag
		    = atof(buffer.substr(currentPos, nextPos - currentPos).c_str());

		// COLOR INDEX
		++nextPos;
		currentPos = nextPos;
		nextPos    = buffer.find(',', nextPos);
		float ci
		    = atof(buffer.substr(currentPos, nextPos - currentPos).c_str());

		// RIGHT ASCENSION RAD
		++nextPos;
		currentPos = nextPos;
		nextPos    = buffer.find(',', nextPos);
		float rarad
		    = atof(buffer.substr(currentPos, nextPos - currentPos).c_str());

		// DECLINATION RAD
		++nextPos;
		currentPos = nextPos;
		nextPos    = buffer.find(',', nextPos);
		float decrad
		    = atof(buffer.substr(currentPos, nextPos - currentPos).c_str());

		++nextPos;
		currentPos = nextPos;
		(void) currentPos; // value not used yet
		nextPos = buffer.find(',', nextPos);
		++nextPos;
		currentPos = nextPos;
		(void) currentPos; // value not used yet
		nextPos = buffer.find(',', nextPos);

		// CONSTELLATION
		++nextPos;
		currentPos = nextPos;
		nextPos    = buffer.find('\r', nextPos);

		if(static_cast<int>(nextPos) == -1)
		{
			nextPos = buffer.find('\n', currentPos);
		}

		std::string constellation
		    = buffer.substr(currentPos, nextPos - currentPos);

		if(mag > -10)
		{
			result.push_back(Star());
			int i = result.size() - 1;

			result[i].commonName            = "";
			result[i].latitude              = decrad;
			result[i].longitude             = rarad;
			result[i].properMotionLatitude  = 0.f;
			result[i].properMotionLongitude = 0.f;

			result[i].magnitude = mag;

			float lum(lumFromMagnitude(mag));

			Urho3D::Color baseColor(toUrho3D(colorFromColorIndex(ci)));
			result[i].color
			    = Urho3D::Color(lum * baseColor.r_, lum * baseColor.g_,
			                    lum * baseColor.b_, 255);
		}
	}

	ifs.close();

	return result;
}

// ims[0] : y (pixs X:latitude[pi/4->-pi/4] Y:longitude[-3*pi/4->-pi/4])
// ims[1] : -y (pixs X:latitude[pi/4->-pi/4] Y:longitude[pi/4->3*pi/4])
// ims[2] : x (pixs X:latitude[pi/4->-pi/4] Y:longitude[-pi/4->pi/4])
// ims[3] : -x (pixs X:latitude[-pi/4->pi/4] Y:longitude[-3*pi/4->3*pi/4])
// ims[4] : -z (pixs X:x+->x- Y:y-->y+)
// ims[5] : z (pixs X:x-->x+ Y:y-->y+)
// https://stackoverflow.com/questions/2656899/mapping-a-sphere-to-a-cube
void SkyboxGenerator::sphericalToCube(double latitude, double longitude,
                                      unsigned int edgeLength,
                                      unsigned int& face, unsigned int& faceX,
                                      unsigned int& faceY, float axialTilt)
{
	double cosLat(cos(latitude)), cosLong(cos(longitude));
	double sinLat(sin(latitude)), sinLong(sin(longitude));

	double x(cosLat * cosLong), y(-cosLat * sinLong), z(sinLat);

	// Conversion from equatorial to ecliptic
	if(axialTilt != 0.f)
	{
		double tmpY(y), tmpZ(z);
		y = cos(axialTilt) * tmpY - sin(axialTilt) * tmpZ;
		z = sin(axialTilt) * tmpY + cos(axialTilt) * tmpZ;
	}

	double fx(fabs(x)), fy(fabs(y)), fz(fabs(z));

	// facesDist from POV in pixels
	double facesDist
	    = edgeLength / 2.f; // we know there is a pi/4 angle between center of
	                        // face and edge from POV, thus that faceDist =
	                        // edgeLength/(2*tan(pi/4)) and tan(pi/4) = 1

	if(fy >= fx && fy >= fz)
	{
		// scaling (x,y,z) so that it touches the face and projecting on x;z
		x *= facesDist / fy;
		z *= facesDist / fy;

		// transform to face coordinates
		if(y > 0)
		{
			face  = 0;
			faceX = edgeLength / 2.f - x;
			faceY = edgeLength / 2.f + z;
		}
		else
		{
			face  = 1;
			faceX = edgeLength / 2.f - x;
			faceY = edgeLength / 2.f - z;
		}
	}
	else if(fx >= fy && fx >= fz)
	{
		// scaling (x,y,z) so that it touches the face and projecting on y;z
		y *= facesDist / fx;
		z *= facesDist / fx;

		// transform to face coordinates
		if(x > 0)
		{
			face  = 2;
			faceX = edgeLength / 2.f + z;
			faceY = edgeLength / 2.f - y;
		}
		else
		{
			face  = 3;
			faceX = edgeLength / 2.f - z;
			faceY = edgeLength / 2.f - y;
		}
	}
	else
	{
		// scaling (x,y,z) so that it touches the face and projecting on x;y
		x *= facesDist / fz;
		y *= facesDist / fz;

		// transform to face coordinates
		if(z > 0)
		{
			face  = 5;
			faceX = edgeLength / 2.f - x;
			faceY = edgeLength / 2.f + y;
		}
		else
		{
			face  = 4;
			faceX = edgeLength / 2.f + x;
			faceY = edgeLength / 2.f + y;
		}
	}
}

float SkyboxGenerator::lumFromMagnitude(float magnitude)
{
	// return magnitude < 3 ? 3 - magnitude : 0;
	return pow(10, (-1.44f - magnitude) / 9.f);
}

Color SkyboxGenerator::colorFromColorIndex(float ci)
{
	// https://stackoverflow.com/questions/21977786/star-b-v-color-index-to-apparent-rgb-color
	float t = 4600 * ((1.f / ((0.92f * ci) + 1.7f))
	                  + (1.f / ((0.92f * ci) + 0.62f)));

	float x = 0.f, y = 0.f, X, Y, Z, r, g, b;

	if(t >= 1667 && t <= 4000)
	{
		x = ((-0.2661239 * pow(10, 9)) / (t * t * t))
		    + ((-0.2343580 * pow(10, 6)) / (t * t))
		    + ((0.8776956 * pow(10, 3)) / t) + 0.179910;
	}
	else if(t > 4000 && t <= 25000)
	{
		x = ((-3.0258469 * pow(10, 9)) / (t * t * t))
		    + ((2.1070379 * pow(10, 6)) / (t * t))
		    + ((0.2226347 * pow(10, 3)) / t) + 0.240390;
	}

	if(t >= 1667 && t <= 2222)
	{
		y = -1.1063814 * x * x * x - 1.34811020 * x * x + 2.18555832 * x
		    - 0.20219683;
	}
	else if(t > 2222 && t <= 4000)
	{
		y = -0.9549476 * x * x * x - 1.37418593 * x * x + 2.09137015 * x
		    - 0.16748867;
	}
	else if(t > 4000 && t <= 25000)
	{
		y = 3.0817580 * x * x * x - 5.87338670 * x * x + 3.75112997 * x
		    - 0.37001483;
	}

	Y = (y == 0.f) ? 0.f : 1.f;
	X = (y == 0.f) ? 0.f : x / y;
	Z = (y == 0.f) ? 0.f : (1.f - x - y) / y;

	r = 3.240479 * X - 1.537150 * Y - 0.498535 * Z;
	g = -0.969256 * X + 1.875992 * Y + 0.041556 * Z;
	b = 0.055648 * X - 0.204043 * Y + 1.057311 * Z;

	return Color(255, 255 * r, 255 * g, 255 * b);
}

void SkyboxGenerator::createSceneNode(Urho3D::Scene* scene,
                                      std::array<Urho3D::Image*, 6>& ims)
{
	Urho3D::ResourceCache* cache = scene->GetSubsystem<Urho3D::ResourceCache>();
	Urho3D::Node* skyNode        = scene->CreateChild("Sky");
	Urho3D::Skybox* skybox       = skyNode->CreateComponent<Urho3D::Skybox>();
	skybox->SetModel(cache->GetResource<Urho3D::Model>("Models/Box.mdl"));

	auto tex = new Urho3D::TextureCube(scene->GetContext());
	tex->SetFilterMode(Urho3D::TextureFilterMode::FILTER_ANISOTROPIC);
	tex->SetNumLevels(1);
	tex->SetSize(ims[0]->GetWidth(), Urho3D::Graphics::GetRGBAFormat(),
	             Urho3D::TEXTURE_STATIC);

	tex->SetData(Urho3D::FACE_POSITIVE_X, ims[3]);
	tex->SetData(Urho3D::FACE_NEGATIVE_X, ims[2]);
	tex->SetData(Urho3D::FACE_NEGATIVE_Z, ims[4]);
	tex->SetData(Urho3D::FACE_POSITIVE_Z, ims[5]);
	tex->SetData(Urho3D::FACE_POSITIVE_Y, ims[0]);
	tex->SetData(Urho3D::FACE_NEGATIVE_Y, ims[1]);

	cache->AddManualResource(tex);

	skybox->SetMaterial(
	    cache->GetResource<Urho3D::Material>("Materials/Skybox.xml"));
	Urho3D::Material* mat = skybox->GetMaterial(0);
	mat->SetTexture(Urho3D::TU_DIFFUSE, tex);

	for(auto& im : ims)
	{
		delete im;
	}
}
