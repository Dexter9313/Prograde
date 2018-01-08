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

#ifndef CELESTIALBODYDRAWER_HPP
#define CELESTIALBODYDRAWER_HPP

#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Technique.h>

#include "../Utils.hpp"
#include "../../physics/CelestialBody.hpp"
#include "Drawer.hpp"
//#include "../shaders/FarCelestialBodyShader.hpp"

class CelestialBodyDrawer : public Drawer
{
  public:
	CelestialBodyDrawer(Urho3D::Scene* scene, CelestialBody const* drawnBody);
	virtual void updateMesh(UniversalTime uT,
	                        Vector3 const& cameraPos) override;
	CelestialBody const* getDrawnBody() const { return drawnBody; };
	void setCenterPosition(float centerPosition)
	{
		this->centerPosition = centerPosition;
	};

  private:
	CelestialBody const* drawnBody;
	float centerPosition;
	int shaderParametersId;
};

#endif // CELESTIALBODYDRAWER_HPP
