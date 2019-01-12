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

#include "math/Vector3.hpp"
//#include <gtest/gtest.h>

/*TEST(Vector3Test, DefaultVector3IsNull)
{
	Vector3 defaultVec;
	ASSERT_TRUE(defaultVec[0] == 0 && defaultVec[1] == 0 && defaultVec[2] == 0);
}

TEST(Vector3Test, ConstructedVector3TakesCoordinates)
{
	float x(24.420942f), y(-54.586468f), z(545.189f);

	Vector3 constructedVec(x, y, z);
	ASSERT_TRUE(constructedVec[0] == x && constructedVec[1] == y
	            && constructedVec[2] == z);
}

TEST(Vector3Test, CopiedVector3IsCopiedCorrectly)
{
	float x(24.420942f), y(-54.586468f), z(545.189f);

	Vector3 copiedVector3(x, y, z);
	Vector3 copy(copiedVector3);

	ASSERT_TRUE(copy[0] == copiedVector3[0] && copy[1] == copiedVector3[1]
	            && copy[2] == copiedVector3[2]);
}

TEST(Vector3Test, SettersCopyStrictlyValues)
{
	float x(24.420942f), y(-54.586468f), z(545.189f);

	Vector3 testedVec2;
	testedVec2.setXYZ(x, y, z);
	ASSERT_TRUE(testedVec2[0] == x && testedVec2[1] == y && testedVec2[2] == z);
}

TEST(Vector3Test, NullVector3HasNullLength)
{
	Vector3 nullVec(0.f, 0.f, 0.f);
	ASSERT_TRUE(nullVec.length() == 0.f);
}

TEST(Vector3Test, HomogeneousLength)
{
	float x(24.420942f), y(-54.586468f), z(545.189f);
	float a(3.145663f);

	Vector3 testedVec(x, y, z);
	float veclength(testedVec.length());
	ASSERT_FLOAT_EQ(a * veclength, (a * testedVec).length());
}

TEST(Vector3Test, LengthSubAdditivity)
{
	Vector3 v1(24.420942f, -54.586468f, 545.189f);
	Vector3 v2(2.42f, -4.566f, 45.f);

	ASSERT_LT((v1 + v2).length(), v1.length() + v2.length());
}

TEST(Vector3Test, SomeLengthExamples)
{
	float x(24.420942f), y(-54.586468f), z(545.189f);
	float expectedLength(548.45885043263f);

	Vector3 testedVec(x, y, z);
	ASSERT_FLOAT_EQ(testedVec.length(), expectedLength);
}

TEST(Vector3Test, UnitFormIsLengthOne)
{
	float x(24.420942f), y(-54.586468f), z(545.189f);

	Vector3 testedVec(x, y, z);
	ASSERT_FLOAT_EQ(testedVec.getUnitForm().length(), 1.f);
}*/
