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

#ifndef KERBALSYSTEM_HPP
#define KERBALSYSTEM_HPP

#include "math/constants.hpp"

#include "../OrbitalSystem.hpp"

class KerbalSystem : public OrbitalSystem
{
  public:
	KerbalSystem();

  private:
	void createPlanets();
	void createEveSubSystem();
	void createKerbinSubSystem();
	void createDunaSubSystem();
	void createJoolSubSystem();

	float distanceMultiplier = 1.f;  // 0.0000002f;//40.f / 15000000.f;
	float radiusMultiplier = 1000.f; // 0.002f;
	float massMultiplier   = 1.f;    // 1.f / 1e17;
};

#endif // KERBALSYSTEM_HPP
