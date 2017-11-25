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

#ifndef ECCENTRICANOMALYSOLVER_H
#define ECCENTRICANOMALYSOLVER_H

#include <array>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_roots.h>

#include "constants.hpp"

/*! \ingroup math
 */
class EccentricAnomalySolver
{
	struct EquationParams
	{
		double meanAnomaly;
		double eccentricity;
	};

  public:
	static double solveForEllipticOrbit(double meanAnomaly,
	                                    double eccentricity);
	static double solveForParabolicOrbit(double meanAnomaly);
	static double solveForHyperbolicOrbit(double meanAnomaly,
	                                      double eccentricity);

  private:
	EccentricAnomalySolver() = delete;
	static double findRoot(gsl_function_fdf FDF, void* parameters, double x);
};

#endif // ECCENTRICANOMALYSOLVER_H
