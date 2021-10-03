#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CU::Vector2<T>& aVector)
{
	os << "(" << aVector.x << ", " << aVector.y << ")";
	return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CU::Vector3<T>& aVector)
{
	os << "(" << aVector.x << ", " << aVector.y << ", " << aVector.z << ")";
	return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CU::Vector4<T>& aVector)
{
	os << "(" << aVector.x << ", " << aVector.y << ", " << aVector.z << ", " << aVector.w << ")";
	return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CU::Matrix2x2<T>& aMatrix)
{
	os << "(" << aMatrix(0, 0) << ", " << aMatrix(0, 1) << 
		 "\n" << aMatrix(1, 0) << ", " aMatrix(1, 1) << ")";
	return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CU::Matrix3x3<T>& aMatrix)
{
	os << "(" << aMatrix(0, 0) << ", " << aMatrix(0, 1) << ", " << aMatrix(0, 2) << 
		 "\n" << aMatrix(1, 0) << ", " << aMatrix(1, 1) << ", " << aMatrix(1, 2) <<
		 "\n" << aMatrix(2, 0) << ", " << aMatrix(2, 1) << ", " << aMatrix(2, 2) << ")";
	return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CU::Matrix4x4<T>& aMatrix)
{
	os << "(" << aMatrix(0, 0) << ", " << aMatrix(0, 1) << ", " << aMatrix(0, 2) << ", " << aMatrix(0, 3) << 
		 "\n" << aMatrix(1, 0) << ", " << aMatrix(1, 1) << ", " << aMatrix(1, 2) << ", " << aMatrix(1, 3) << 
		 "\n" << aMatrix(2, 0) << ", " << aMatrix(2, 1) << ", " << aMatrix(2, 2) << ", " << aMatrix(2, 3) << 
		 "\n" << aMatrix(3, 0) << ", " << aMatrix(3, 1) << ", " << aMatrix(3, 2) << ", " << aMatrix(3, 3) << ")";
	return os;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CU::Quaternion<T>& aQuaternion)
{
	os << "(" << aQuaternion[0] << ", " << aQuaternion[1] << ", " << aQuaternion[2] << ", " << aQuaternion[3] << ")";
	return os;
}