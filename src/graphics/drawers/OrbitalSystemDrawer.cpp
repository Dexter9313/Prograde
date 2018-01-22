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
#include "../../../include/graphics/drawers/OrbitalSystemDrawer.hpp"

OrbitalSystemDrawer::OrbitalSystemDrawer(Urho3D::Scene* scene,
                                         OrbitalSystem const* drawnSystem)
    : Drawer(scene)
    , drawnSystem(drawnSystem)
{
	auto cache = scene->GetSubsystem<Urho3D::ResourceCache>();

	node           = scene->CreateChild("Sun");
	auto billboard = node->CreateComponent<Urho3D::BillboardSet>();
	billboard->SetNumBillboards(1);
	billboard->SetSorted(true);

	auto mat = new Urho3D::Material(scene->GetContext());
	auto tex = cache->GetResource<Urho3D::Texture2D>("Textures/star.png");
	mat->SetTexture(Urho3D::TU_DIFFUSE, tex);
	mat->SetNumTechniques(1);
	mat->SetTechnique(0, cache->GetResource<Urho3D::Technique>(
	                         "Techniques/DiffUnlitAlpha.xml"));
	billboard->SetMaterial(mat);
	node->GetComponent<Urho3D::BillboardSet>()->GetBillboard(0)->enabled_
	    = true;

	billboardOriginalEdgeSize = drawnSystem->getCentralRadius() * 512.0 / 30.0;

	for(CelestialBody* body :
	    this->drawnSystem->getAllCelestialBodiesPointers())
	{
		bodyDrawers.push_back(new CelestialBodyDrawer(scene, body));
	}
}

void OrbitalSystemDrawer::updateMesh(UniversalTime uT, Vector3 const& cameraPos)
{
	camDist = cameraPos.length();

	sortedDrawers.clear();
	for(CelestialBodyDrawer* bodyDrawer : bodyDrawers)
	{
		sortedDrawers[(bodyDrawer->getDrawnBody()->getAbsolutePositionAtUT(uT)
		               - cameraPos)
		                  .length()]
		    = bodyDrawer;
		bodyDrawer->updateMesh(uT, cameraPos);
	}
	bool centralBodyDrawn(false);

	float centerPosition(100);
	float increment(250 / (sortedDrawers.size() + 1));

	for(std::pair<double, CelestialBodyDrawer*> drawerPair : sortedDrawers)
	{
		if(drawerPair.first > camDist && !centralBodyDrawn)
		{
			double scale(centerPosition / camDist);
			node->SetPosition(toUrho3D(-1 * scale * cameraPos));
			if((scale * drawnSystem->getCentralRadius()) / centerPosition
			   < 0.0007)
			{
				scale
				    = 0.0007 * centerPosition / drawnSystem->getCentralRadius();
			}
			node->GetComponent<Urho3D::BillboardSet>()->GetBillboard(0)->size_
			    = Urho3D::Vector2(billboardOriginalEdgeSize * scale,
			                      billboardOriginalEdgeSize * scale);
			node->GetComponent<Urho3D::BillboardSet>()->Commit();
			centralBodyDrawn = true;
			centerPosition += increment;
		}
		drawerPair.second->setCenterPosition(centerPosition);
		drawerPair.second->updateMesh(uT, cameraPos);
		centerPosition += increment;
	}
}

OrbitalSystemDrawer::~OrbitalSystemDrawer()
{
	for(CelestialBodyDrawer* bodyDrawer : bodyDrawers)
	{
		delete bodyDrawer;
	}
}
