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
