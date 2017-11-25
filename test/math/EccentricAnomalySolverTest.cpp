#include <gsl/gsl_poly.h>
#include <gtest/gtest.h>

#include "math/EccentricAnomalySolver.hpp"
#include "math/constants.hpp"

TEST(EccentricAnomalySolverTest, EllipticZeroEccentricityEqualsSameAngle)
{
	// mA = meanAnomaly
	float mA1(0.0), mA2(constant::pi), mA3(2 * constant::pi), mA4(1.234567f);

	ASSERT_FLOAT_EQ(mA1,
	                EccentricAnomalySolver::solveForEllipticOrbit(mA1, 0.f));
	ASSERT_FLOAT_EQ(mA2,
	                EccentricAnomalySolver::solveForEllipticOrbit(mA2, 0.f));
	ASSERT_FLOAT_EQ(mA3,
	                EccentricAnomalySolver::solveForEllipticOrbit(mA3, 0.f));
	ASSERT_FLOAT_EQ(mA4,
	                EccentricAnomalySolver::solveForEllipticOrbit(mA4, 0.f));
}

TEST(EccentricAnomalySolverTest, ParabolicSolvesBarkerEquation)
{
	float mA1(0.0), mA2(constant::pi), mA3(2 * constant::pi), mA4(1.234567f);
	float s1(EccentricAnomalySolver::solveForParabolicOrbit(mA1)),
	    s2(EccentricAnomalySolver::solveForParabolicOrbit(mA2)),
	    s3(EccentricAnomalySolver::solveForParabolicOrbit(mA3)),
	    s4(EccentricAnomalySolver::solveForParabolicOrbit(mA4));

	std::array<double, 4> barkerPolynomial = {0.0 - mA1, 1.0, 0.0, 1.0 / 3.0};
	ASSERT_NEAR(0, gsl_poly_eval(barkerPolynomial.data(), 4, s1), 1e-6);
	barkerPolynomial[0] = 0.0 - mA2;
	ASSERT_NEAR(0, gsl_poly_eval(barkerPolynomial.data(), 4, s2), 1e-6);
	barkerPolynomial[0] = 0.0 - mA3;
	ASSERT_NEAR(0, gsl_poly_eval(barkerPolynomial.data(), 4, s3), 1e-6);
	barkerPolynomial[0] = 0.0 - mA4;
	ASSERT_NEAR(0, gsl_poly_eval(barkerPolynomial.data(), 4, s4), 1e-6);
}
