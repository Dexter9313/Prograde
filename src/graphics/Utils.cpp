#include "graphics/Utils.hpp"

Urho3D::Vector3 toUrho3D(Vector3 const& vector)
{
	return Urho3D::Vector3(vector[0], -1 * vector[1], vector[2]);
}

Vector3 fromUrho3D(Urho3D::Vector3 const& vector)
{
	return Vector3(vector.x_, -1 * vector.y_, vector.z_);
}

Urho3D::Color toUrho3D(Color const& color)
{
	return Urho3D::Color(color.r / 255.f, color.g / 255.f, color.b / 255.f,
	                     color.alpha / 255.f);
}

Color fromUrho3D(Urho3D::Color const& color)
{
	return Color(255 * color.a_, 255 * color.r_, 255 * color.g_,
	             255 * color.b_);
}
