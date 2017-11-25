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

#ifndef SIMULATIONTIME_HPP
#define SIMULATIONTIME_HPP

#include <chrono>

#include "UniversalTime.hpp"

typedef std::chrono::steady_clock stdclock;

class SimulationTime
{
  public:
	SimulationTime(UniversalTime startingUt = 0.f);
	UniversalTime getCurrentUt() const
	{
		return currentUt;
	};
	void setTimeCoeff(float timeCoeff) { this->timeCoeff = timeCoeff; };
	float getTimeCoeff() const { return timeCoeff; };
	float getCurrentFPS() const { return currentFPS; };
	void setTargetFPS(float targetFPS) { this->targetFPS = targetFPS; };
	float getTargetFPS() const { return targetFPS; };
	void resetAtEpoch();
	void update();
	bool drawableFrame();

  private:
	stdclock::time_point lastTime;
	UniversalTime currentUt;
	float timeCoeff;

	stdclock::time_point lastFrameTime;
	float currentFPS;
	float targetFPS;
	bool drawFrame;
};

#endif // SIMULATIONTIME_HPP
