#include "pch.h"
#include "..\BetterCU\Vector.h"
#include "..\BetterCU\Vector3.hpp"
#include "..\BetterCU\Math.hpp"

#pragma region Vector
TEST(Vector, DefaultConstructor) {
	CU::Vector<float, 2> vector{};
	EXPECT_EQ(0.0f, vector.Element(0));

  //EXPECT_EQ(1, 1);
  //EXPECT_TRUE(true);
}

TEST(Vector, CopyConstructor)
{
	CU::Vector<float, 2> vec1;
	vec1.Element(1) = 2;

	CU::Vector<float, 2> vec{ vec1 };
	EXPECT_EQ(2, vec.Element(1));
	EXPECT_EQ(0, vec.Element(0));
}

TEST(Vector, InitializerListConstructor)
{
	CU::Vector<float, 2> vec = { 3, 2 };

	EXPECT_EQ(3, vec.Element(0));
	EXPECT_EQ(2, vec.Element(1));
}

TEST(Vector, Element)
{
	CU::Vector<float, 2> vec{ 3, 2 };

	EXPECT_EQ(3, vec.Element(0));
}

TEST(Vector, AsColumnMatrix)
{
	CU::Vector<float, 2> vec{ 3, 2 };

	CU::Matrix<2, 1> mat = vec.AsColumnMatrix();
	EXPECT_EQ(mat(0, 0), 3);
	EXPECT_EQ(mat(1, 0), 2);
}

TEST(Vector, AsRowMatrix)
{
	CU::Vector<float, 2> vec{ 2, 3 };

	CU::Matrix<1, 2> mat = vec.AsRowMatrix();
	EXPECT_EQ(mat(0, 0), 2);
	EXPECT_EQ(mat(0, 1), 3);
}

TEST(Vector, Dot)
{
	CU::Vector<float, 2> vec{ 2, 2 };
	CU::Vector<float, 2> vec1{ 3, 3 };
	EXPECT_EQ(12, vec.Dot(vec1));
}

TEST(Vector, Normalize)
{
	CU::Vector<float, 2> vec{ 2, 3 };

	CU::Vector<float, 2> normVec = vec.Normalized();

	EXPECT_EQ(1, normVec.Length());
}

TEST(Vector, Length)
{
	CU::Vector<float, 2> vec{ 2.65f, 3 };
	CU::Vector<float, 2> vec2{ -2.65f, -3 };

	EXPECT_EQ(4.f, std::floor(vec.Length()));
	EXPECT_EQ(4.f, std::floor(vec2.Length()));
}

TEST(Vector, Cast)
{
	CU::Vector<float, 2> vec{ 2, 2 };
	CU::Vector<int, 2> vecI = vec.Cast<int>();
	EXPECT_TRUE(true);
}
#pragma endregion

#pragma region Vector3

TEST(Vector3, Variables)
{
	CU::Vector3f vec{ 10, 2, 4 };

	EXPECT_EQ(10, vec.X());
	EXPECT_EQ(2, vec.Y());
	EXPECT_EQ(4, vec.Z());
}

TEST(Vector3, Cross)
{
	CU::Vector3f vec{ 1, -1, 0 };
	CU::Vector3f cross = vec.Cross({ 0, 1, 0 });

	EXPECT_EQ(0, cross.X());
	EXPECT_EQ(0, cross.Y());
	EXPECT_EQ(1, cross.Z());
}

TEST(Vector3, Reflect)
{
	CU::Vector3f vec = CU::Vector3f::Reflect({ 1, -1, 0 }, { 0, 1, 0 });

	EXPECT_EQ(1, vec.X());
	EXPECT_EQ(1, vec.Y());
	EXPECT_EQ(0, vec.Z());
}

#pragma endregion


#pragma region Math

TEST(Math, Round)
{
	EXPECT_EQ(2, CU::Round(2.3f));
	EXPECT_EQ(3, CU::Round(2.7f));
	EXPECT_EQ(2, CU::Round(2.49f));
	EXPECT_EQ(3, CU::Round(2.51f));
	EXPECT_EQ(2, CU::Round(2.0f));
	EXPECT_EQ(2, CU::Round(2.0));
	EXPECT_EQ(2, CU::Round(2.3));
}

TEST(Math, Floor)
{
	EXPECT_EQ(2, CU::Floor(2.99f));
	EXPECT_EQ(3, CU::Floor(3));
	EXPECT_EQ(1, CU::Floor(1.01));
}

TEST(Math, Ceil)
{
	EXPECT_EQ(2, CU::Ceil(1.99f));
	EXPECT_EQ(2, CU::Ceil(1.001f));
	EXPECT_EQ(1, CU::Ceil(1));
}

TEST(Math, Mod)
{
	EXPECT_EQ(0, CU::Mod(3, 1));
	EXPECT_EQ(1, CU::Mod(3.0f, 2.f));
}

#pragma endregion
