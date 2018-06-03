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
	auto cache    = GetSubsystem<Urho3D::ResourceCache>();
	auto graphics = GetSubsystem<Urho3D::Graphics>();
	uiRoot        = GetSubsystem<Urho3D::UI>()->GetRoot();
	auto style    = cache->GetResource<Urho3D::XMLFile>("UI/DefaultStyle.xml");
	uiRoot->SetDefaultStyle(style);

	auto button   = new Urho3D::Button(context_);
	auto text     = new Urho3D::Text(context_);
	auto checkbox = new Urho3D::CheckBox(context_);

	checkbox->SetName("FULLSCREEN");
	checkbox->SetSize(30, 30);
	checkbox->SetPosition(
	    (graphics->GetWidth() - checkbox->GetWidth()) / 2 - 40, 300);
	checkbox->SetStyleAuto();
	text->SetText("Fullscreen");
	text->SetPosition((graphics->GetWidth() - checkbox->GetWidth()) / 2, 300);
	text->SetStyleAuto();
	uiRoot->AddChild(checkbox);
	uiRoot->AddChild(text);

	text = new Urho3D::Text(context_);
	button->SetName("LAUNCH");
	button->SetSize(128, 56);
	button->SetPosition((graphics->GetWidth() - button->GetWidth()) / 3, 500);
	button->SetStyleAuto();
	text->SetText("Launch");
	text->SetSize(128, 56);
	text->SetPosition((graphics->GetWidth() - 10) / 3, 515);
	text->SetStyleAuto();
	uiRoot->AddChild(button);
	uiRoot->AddChild(text);

	button = new Urho3D::Button(GetContext());
	text   = new Urho3D::Text(context_);
	button->SetName("QUIT");
	button->SetSize(128, 56);
	button->SetPosition((graphics->GetWidth() - button->GetWidth()) * 2 / 3,
	                    500);
	button->SetStyleAuto(style);
	text->SetText("Quit");
	text->SetSize(128, 56);
	text->SetPosition((graphics->GetWidth() - 52) * 2 / 3, 515);
	text->SetStyleAuto();
	uiRoot->AddChild(button);
	uiRoot->AddChild(text);
}

void OnGuiEvent(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData)
{
	(void) eventType;
	(void) eventData;
}
