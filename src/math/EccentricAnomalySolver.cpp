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

// If too slow, don't use GSL and program it yourself
//(Newton method isn't hard at all to implement
double EccentricAnomalySolver::solveForEllipticOrbit(double meanAnomaly,
                                                     double eccentricity)
{
	// Setting up parameters
	EquationParams params = {meanAnomaly, eccentricity};

	// Setting up function
	gsl_function_fdf FDF;

	FDF.f = [](double x, void* params) {
		EquationParams* p = static_cast<EquationParams*>(params);
		double meanAnomaly(p->meanAnomaly);
		double eccentricity(p->eccentricity);
		return x - (eccentricity * sin(x)) - meanAnomaly;
	};

	FDF.df = [](double x, void* params) {
		EquationParams* p = static_cast<EquationParams*>(params);
		double eccentricity(p->eccentricity);
		return 1 - (eccentricity * cos(x));
	};

	FDF.fdf = [](double x, void* params, double* y, double* dy) {
		EquationParams* p = static_cast<EquationParams*>(params);
		double meanAnomaly(p->meanAnomaly);
		double eccentricity(p->eccentricity);

		*y  = x - (eccentricity * sin(x)) - meanAnomaly;
		*dy = 1 - (eccentricity * cos(x));
	};

	FDF.params = &params;
	double x((eccentricity < 0.8 ? meanAnomaly : constant::pi));

	return findRoot(FDF, &params, x);
}

double EccentricAnomalySolver::solveForParabolicOrbit(double meanAnomaly)
{
	double x0, x1, x2;
	gsl_poly_solve_cubic(0.0, 3.0, -3.0 * meanAnomaly, &x0, &x1, &x2);
	return x0;
}

double EccentricAnomalySolver::solveForHyperbolicOrbit(double meanAnomaly,
                                                       double eccentricity)
{
	// Setting up parameters
	EquationParams params = {meanAnomaly, eccentricity};

	// Setting up function
	gsl_function_fdf FDF;

	FDF.f = [](double x, void* params) {
		EquationParams* p = static_cast<EquationParams*>(params);
		double meanAnomaly(p->meanAnomaly);
		double eccentricity(p->eccentricity);
		return (eccentricity * sinh(x)) - x - meanAnomaly;
	};

	FDF.df = [](double x, void* params) {
		EquationParams* p = static_cast<EquationParams*>(params);
		double eccentricity(p->eccentricity);
		return (eccentricity * cosh(x)) - 1;
	};

	FDF.fdf = [](double x, void* params, double* y, double* dy) {
		EquationParams* p = static_cast<EquationParams*>(params);
		double meanAnomaly(p->meanAnomaly);
		double eccentricity(p->eccentricity);

		*y  = (eccentricity * sinh(x)) - x - meanAnomaly;
		*dy = (eccentricity * cosh(x)) - 1;
	};

	FDF.params = &params;
	double x((eccentricity < 0.8 ? meanAnomaly : constant::pi));

	return findRoot(FDF, &params, x);
}

double EccentricAnomalySolver::findRoot(gsl_function_fdf FDF, void* parameters,
                                        double x)
{
	// Settings up parameters
	EquationParams* params = static_cast<EquationParams*>(parameters);

	// Solver Init
	int status;
	unsigned int currentIter(0);
	const unsigned int maxIter(100);

	gsl_root_fdfsolver* solver(
	    gsl_root_fdfsolver_alloc(gsl_root_fdfsolver_newton));
	gsl_root_fdfsolver_set(solver, &FDF, x);

	// Iterate
	do
	{
		currentIter++;
		gsl_root_fdfsolver_iterate(solver);
		x      = gsl_root_fdfsolver_root(solver);
		status = gsl_root_test_residual(FDF.f(x, &params), 1e-15);
	} while(status == GSL_CONTINUE && currentIter < maxIter);

	// Solver Freeing
	gsl_root_fdfsolver_free(solver);

	return x;
}
