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

#include "graphics/Gui.hpp"

Gui::Gui(Urho3D::Context* context)
    : Urho3D::Object(context)
{
	Urho3D::ResourceCache* cache = GetSubsystem<Urho3D::ResourceCache>();
	Urho3D::Graphics* graphics   = GetSubsystem<Urho3D::Graphics>();
	uiRoot                       = GetSubsystem<Urho3D::UI>()->GetRoot();
	Urho3D::XMLFile* style
	    = cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml");
	uiRoot->SetDefaultStyle(style);

	auto button = new Urho3D::Button(context_);
	auto text   = new Urho3D::Text(context_);
	button->SetName("LAUNCH");
	button->SetSize(128, 128);
	button->SetPosition((graphics->GetWidth() - button->GetWidth()) / 2, 200);
	button->SetStyleAuto();
	text->SetText("Launch");
	text->SetSize(128, 128);
	text->SetPosition((graphics->GetWidth() - button->GetWidth()) / 2, 200);
	text->SetStyleAuto();
	uiRoot->AddChild(button);
	uiRoot->AddChild(text);

	button = new Urho3D::Button(GetContext());
	text   = new Urho3D::Text(context_);
	button->SetName("QUIT");
	button->SetSize(128, 128);
	button->SetPosition((graphics->GetWidth() - button->GetWidth()) / 2, 400);
	button->SetStyleAuto(style);
	text->SetText("Quit");
	text->SetSize(128, 128);
	text->SetPosition((graphics->GetWidth() - button->GetWidth()) / 2, 400);
	text->SetStyleAuto();
	uiRoot->AddChild(button);
	uiRoot->AddChild(text);
}

void OnGuiEvent(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData)
{
	(void) eventType;
	(void) eventData;
}
