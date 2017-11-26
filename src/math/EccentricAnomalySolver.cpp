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

#include "math/EccentricAnomalySolver.hpp"

// If too slow, don't use boost and program it yourself
//(Newton method isn't hard at all to implement
double EccentricAnomalySolver::solveForEllipticOrbit(double meanAnomaly,
                                                     double eccentricity)
{
	double guess((eccentricity < 0.8 ? meanAnomaly : constant::pi));
	boost::uintmax_t maxit = 100;

	return boost::math::tools::newton_raphson_iterate(
	    [meanAnomaly, eccentricity](const double& eccAn) {
		    return std::make_pair(eccAn - (eccentricity * sin(eccAn))
		                              - meanAnomaly,
		                          1 - (eccentricity * cos(eccAn)));
		},
	    guess, 0.0, 2 * constant::pi, std::numeric_limits<double>::digits,
	    maxit);
}

double EccentricAnomalySolver::solveForParabolicOrbit(double meanAnomaly)
{
	// E^3+3E-6M = 0
	// Solving using Cardano method (and the fact that there will always be one
	// single real root)
	// https://fr.wikipedia.org/wiki/M%C3%A9thode_de_Cardan#Si_.CE.94_est_n.C3.A9gatif
	double p(3), q(-6 * meanAnomaly);
	double term(sqrt(q * q / 4.0 + p * p * p / 27.0));
	return cbrt(-q / 2.0 + term) + cbrt(-q / 2.0 - term);
}

double EccentricAnomalySolver::solveForHyperbolicOrbit(double meanAnomaly,
                                                       double eccentricity)
{
	double guess(constant::pi);
	boost::uintmax_t maxit = 100;

	return boost::math::tools::newton_raphson_iterate(
	    [meanAnomaly, eccentricity](const double& eccAn) {
		    return std::make_pair((eccentricity * sinh(eccAn)) - eccAn
		                              - meanAnomaly,
		                          (eccentricity * cosh(eccAn)) - 1);
		},
	    guess, 0.0, 2 * constant::pi, std::numeric_limits<double>::digits,
	    maxit);
}
