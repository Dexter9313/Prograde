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

#include "../../../include/graphics/drawers/CelestialBodyDrawer.hpp"

CelestialBodyDrawer::CelestialBodyDrawer(Urho3D::Scene* scene,
                                         CelestialBody const* drawnBody)
    : Drawer(scene)
    , drawnBody(drawnBody)
{
	Urho3D::ResourceCache* cache = scene->GetSubsystem<Urho3D::ResourceCache>();
	node                         = scene->CreateChild();
	Urho3D::StaticModel* sphere  = node->CreateComponent<Urho3D::StaticModel>();
	sphere->SetModel(cache->GetResource<Urho3D::Model>(
	    "Models/Sphere.mdl")); // TODO(florian) : check true size of sphere is 1
	auto mat = new Urho3D::Material(scene->GetContext());
	mat->SetNumTechniques(1);
	mat->SetTechnique(0, cache->GetResource<Urho3D::Technique>(
	                         "Techniques/FarCelestialBody.xml"));
	mat->SetShaderParameter("BodyColor",
	                        toUrho3D(drawnBody->getParameters().color));
	sphere->SetMaterial(mat);

	// node = scene->addSphereSceneNode(this->drawnBody->getParameters().radius,
	// 64, 0, -1);
	// node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	// node->setMaterialType(FarCelestialBodyShader::getInstance()->getMaterialType());
	// this->scnMgr->getMeshManipulator()->setVertexColors(mesh->getMesh(),
	// toIrrlicht(this->drawnBody->getParameters().color));
	node->SetPosition(toUrho3D(this->drawnBody->getAbsolutePositionAtUT(0)));
	/*
	shaderParametersId =
	FarCelestialBodyShader::getInstance()->generateUniqueParametersId();
	mesh->getMaterial(0).MaterialTypeParam2 = shaderParametersId;*/
}

void CelestialBodyDrawer::updateMesh(UniversalTime uT, Vector3 const& cameraPos)
{
	Vector3 camRelPos(drawnBody->getAbsolutePositionAtUT(uT) - cameraPos);
	double camDist(camRelPos.length());
	double scale(centerPosition / camDist);
	node->SetPosition(toUrho3D(scale * camRelPos));

	double radiusScale(2 * drawnBody->getParameters().radius
	                   * scale); // sphere radius is 0.5
	if(radiusScale / centerPosition < 0.002)
	{
		radiusScale = 0.002 * centerPosition;
	}
	node->SetScale(toUrho3D(Vector3(radiusScale, radiusScale, radiusScale)));

	Vector3 bodyCenter(scale * camRelPos);
	Vector3 centralBodyCenter(-1 * scale * cameraPos);

	Urho3D::Material* mat
	    = node->GetComponent<Urho3D::StaticModel>()->GetMaterial(0);
	mat->SetShaderParameter("BodyCenter", toUrho3D(bodyCenter));
	mat->SetShaderParameter("CentralBodyCenter", toUrho3D(centralBodyCenter));
}
