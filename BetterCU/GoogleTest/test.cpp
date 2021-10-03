#include "pch.h"
#include "..\BetterCU\Vector.h"
#include "..\BetterCU\Vector3.hpp"
#include "..\BetterCU\Math.hpp"
#include "..\BetterCU\Vector2.hpp"
#include "Matrix.hpp"

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

TEST(Vector3, EqualsOperator)
{
	CU::Vector3f vec = { 1, 2, 3 };

	CU::Vector3f vec1 = vec;
	EXPECT_TRUE(true);
}

#pragma endregion

#pragma region Vector2

TEST(Vector2, EqualsOperator)
{
	CU::Vector2f vec = { 2, 2 };
	const CU::Vector2f& vec1 = vec;

	CU::Vector2f vec2 = vec1;
	EXPECT_TRUE(true);
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

#pragma region Matrix

TEST(Matrix, DefaultConstructor)
{
	CU::Matrix<3, 3> matrix;

	EXPECT_EQ(0, matrix(0, 0));
	EXPECT_EQ(0, matrix(1, 0));
	EXPECT_EQ(0, matrix(2, 0));
	EXPECT_EQ(0, matrix(0, 1));
	EXPECT_EQ(0, matrix(0, 2));
}

TEST(Matrix, CopyConstructor)
{
	CU::Matrix3x3<float> matrix;
	matrix(2, 2) = 3;

	CU::Matrix3x3<float> mat1{ matrix };
	CU::Matrix3x3<float> mat2 = matrix;

	EXPECT_EQ(mat1(2, 2), 3);
	EXPECT_EQ(mat1(0, 0), 0);
	EXPECT_EQ(mat2(0, 0), 0);
	EXPECT_EQ(mat2(2, 2), 3);
}

TEST(Matrix, ArrayConstructor)
{
	CU::Array<CU::Array<float, 3>, 3> ar;
	ar[0][2] = 2;

	CU::Matrix3x3<float> mat{ ar };

	CU::Matrix3x3<float> mat1 = ar;

	EXPECT_EQ(mat(0, 2), 2);
	EXPECT_EQ(mat1(0, 2), 2);
}

TEST(Matrix, Rows)
{
	CU::Matrix3x3<float> mat;

	EXPECT_EQ(3, mat.Rows());
}

TEST(Matrix, Columns)
{
	CU::Matrix3x3<float> mat;

	EXPECT_EQ(3, mat.Columns());
}

TEST(Matrix, Transpose)
{
	CU::Matrix3x3<float> mat;
	mat(0, 0) = 1;
	mat(0, 1) = 1;
	mat(0, 2) = 1;
	CU::Matrix3x3<float> transposed = mat.Transposed();

	EXPECT_EQ(1, transposed(0, 0));
	EXPECT_EQ(1, transposed(1, 0));
	EXPECT_EQ(1, transposed(2, 0));
}

TEST(Matrix, ParenthesisOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 1;

	EXPECT_EQ(1, mat(1, 1));
	ASSERT_DEATH(mat(4, 0), "");
	ASSERT_DEATH(mat(0, 4), "");
	ASSERT_DEATH(mat(0, -1), "");
	ASSERT_DEATH(mat(-1, 0), "");
}

TEST(Matrix, BracketOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 1;

	CU::Array<float, 3> ar = mat[1];
	EXPECT_EQ(ar[1], 1);
}

TEST(Matrix, DoubleEqualsOperator)
{
	CU::Matrix3x3<float> mat;
	mat(2, 2) = 2;
	mat(1, 1) = 1;

	CU::Matrix3x3<float> mat2;
	mat2(2, 2) = 2;
	mat2(1, 1) = 1;

	EXPECT_TRUE(mat == mat2);

	mat2(0, 0) = 1;

	EXPECT_FALSE(mat == mat2);
}

TEST(Matrix, NotEqualsOperator)
{
	CU::Matrix3x3<float> mat;
	mat(2, 2) = 2;
	CU::Matrix3x3<float> mat2;

	EXPECT_TRUE(mat != mat2);

	mat2(2, 2) = 2;
	EXPECT_FALSE(mat != mat2);
}

TEST(Matrix, AddToOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 2;

	CU::Matrix3x3<float> mat2;
	mat2(2, 1) = 2;

	mat += mat2;
	EXPECT_EQ(mat(2, 1), 2);

	EXPECT_EQ(mat(1, 1), 2);

	mat2(1, 1) = 3;
	mat += mat2;
	EXPECT_EQ(mat(1, 1), 5);
}

TEST(Matrix, RemoveFromOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 2;
	CU::Matrix3x3<float> mat2;
	mat2(1, 1) = 1;

	mat -= mat2;
	EXPECT_EQ(mat(1, 1), 1);
}

TEST(Matrix, RemoveOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 2;
	CU::Matrix3x3<float> mat2;
	mat2(1, 1) = 1;

	CU::Matrix3x3<float> newMat = mat - mat2;
	EXPECT_EQ(newMat(1, 1), 1);
}

TEST(Matrix, MultiplyToOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 2;

	mat *= 3;
	EXPECT_EQ(mat(1, 1), 6);
}

TEST(Matrix, MultiplyOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 2;

	CU::Matrix3x3<float> mat2 = mat * 3;

	EXPECT_EQ(mat2(1, 1), 6);
}

TEST(Matrix, DivideFromOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 6;

	mat /= 2;

	EXPECT_EQ(mat(1, 1), 3);
}

TEST(Matrix, DivideOperator)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 6;

	auto mat2 = mat / 2;

	EXPECT_EQ(mat2(1, 1), 3);
}

TEST(Matrix, MultiplyMatrixOperator)
{
	CU::Matrix3x3<float> mat;
	mat(2, 2) = 3;

	CU::Matrix3x3<float> mat2;
	mat2(2, 2) = 2;

	auto mat3 = mat * mat2;

	EXPECT_EQ(mat3(0, 0), 0);
	EXPECT_EQ(mat3(0, 1), 0);
	EXPECT_EQ(mat3(0, 2), 0);
	EXPECT_EQ(mat3(1, 0), 0);
	EXPECT_EQ(mat3(1, 1), 0);
	EXPECT_EQ(mat3(1, 2), 0);
	EXPECT_EQ(mat3(2, 0), 0);
	EXPECT_EQ(mat3(2, 1), 0);
	EXPECT_EQ(mat3(2, 2), 6);
}

TEST(Matrix, IdentityMatrix)
{
	CU::Matrix3x3<float> mat;
	auto mat1 = CU::Matrix3x3<float>::IdentityMatrix();

	EXPECT_EQ(mat1(0, 0), 1);
	EXPECT_EQ(mat1(1, 1), 1);
	EXPECT_EQ(mat1(2, 2), 1);
	EXPECT_EQ(mat1(0, 1), 0);

	CU::Matrix<10, 10, float> mat10;
	auto mat11 = CU::Matrix<10, 10, float>::IdentityMatrix();
	EXPECT_EQ(mat11(0, 0), 1);
	EXPECT_EQ(mat11(1, 1), 1);
	EXPECT_EQ(mat11(2, 2), 1);
	EXPECT_EQ(mat11(3, 3), 1);
	EXPECT_EQ(mat11(4, 4), 1);
	EXPECT_EQ(mat11(5, 5), 1);
	EXPECT_EQ(mat11(6, 6), 1);
	EXPECT_EQ(mat11(7, 7), 1);
	EXPECT_EQ(mat11(8, 8), 1);
	EXPECT_EQ(mat11(9, 9), 1);
	EXPECT_EQ(mat11(0, 1), 0);
	EXPECT_EQ(mat11(9, 8), 0);
}

TEST(Matrix, RotationAroundX)
{
	CU::Matrix3x3<float> mat;
	mat(1, 1) = 1;

	mat = mat * CU::Matrix<3, 3, float>::CreateRotationAroundX(3.14f);
	EXPECT_TRUE(true);
}



#pragma endregion