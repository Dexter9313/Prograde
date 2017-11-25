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

#ifndef ORBITALSYSTEMDRAWER_HPP
#define ORBITALSYSTEMDRAWER_HPP

#include <Urho3D/Graphics/BillboardSet.h>
#include <Urho3D/Graphics/Technique.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Math/Vector2.h>
#include <Urho3D/Resource/Image.h>

#include "../../physics/OrbitalSystem.hpp"
#include "../Utils.hpp"
#include "CelestialBodyDrawer.hpp"

// TODO rethink Drawer (mesh attribute)
class OrbitalSystemDrawer : public Drawer
{
  public:
	OrbitalSystemDrawer(Urho3D::Scene* scene, OrbitalSystem const* drawnSystem);
	virtual void updateMesh(UniversalTime uT,
	                        Vector3 const& cameraPos) override;
	~OrbitalSystemDrawer();

  private:
	OrbitalSystem const* drawnSystem;
	std::vector<CelestialBodyDrawer*> bodyDrawers;

	std::map<double, CelestialBodyDrawer*> sortedDrawers;
	double camDist;

	double billboardOriginalEdgeSize;
};

#endif // ORBITALSYSTEMDRAWER_HPP
