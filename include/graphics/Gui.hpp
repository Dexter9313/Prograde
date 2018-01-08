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

#ifndef GUI_HPP
#define GUI_HPP

#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Texture2D.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Window.h>

class Gui : public Urho3D::Object
{
	URHO3D_OBJECT(Gui, Urho3D::Object);

  public:
	Gui(Urho3D::Context* context);
	void OnGuiEvent(Urho3D::StringHash eventType,
	                Urho3D::VariantMap& eventData);

  private:
	Urho3D::SharedPtr<Urho3D::UIElement> uiRoot;
};

#endif // GUI_HPP
