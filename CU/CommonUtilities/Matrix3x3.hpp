#pragma once
#include "Vector.hpp"
#include "Matrix4x4.hpp"
#include <assert.h>
#include <math.h>

namespace CommonUtilities
{
	template <class T>
	class Matrix3x3
	{
	public:
		// Creates the identity matrix.
		Matrix3x3<T>();
		// Copy Constructor.
		Matrix3x3<T>(const Matrix3x3<T>& aMatrix);
		// Copies the top left 3x3 part of the Matrix4x4.
		Matrix3x3<T>(const Matrix4x4<T>& aMatrix);
		// () operator for accessing element (row, column) for read/write or read, respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix);
		void operator+=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix);
		void operator-=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix);
		void operator*=(const Matrix3x3<T>& aMatrix);
		void operator=(const Matrix3x3<T>& aMatrix);
		// Static functions for creating rotation matrices.
		static Matrix3x3<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundZ(T aAngleInRadians);
		// Static function for creating a transpose of a matrix.
		static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose);
	private:
		CU::Vector3<T> myRow1;
		CU::Vector3<T> myRow2;
		CU::Vector3<T> myRow3;
	};

	template<class T>
	inline Matrix3x3<T>::Matrix3x3()
	{
		myRow1.x = 1;
		myRow2.x = 0;
		myRow3.x = 0;

		myRow1.y = 0;
		myRow2.y = 1;
		myRow3.y = 0;

		myRow1.z = 0;
		myRow2.z = 0;
		myRow3.z = 1;
	}
	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
	{
		*this = aMatrix;
	}
	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		myRow1.x = aMatrix(1, 1);
		myRow1.y = aMatrix(1, 2);
		myRow1.z = aMatrix(1, 3);

		myRow2.x = aMatrix(2, 1);
		myRow2.y = aMatrix(2, 2);
		myRow2.z = aMatrix(2, 3);

		myRow3.x = aMatrix(3, 1);
		myRow3.y = aMatrix(3, 2);
		myRow3.z = aMatrix(3, 3);
	}
	template<class T>
	inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		switch (aRow)
		{
		case 1:
			switch (aColumn)
			{
			case 1:
				return myRow1.x;
				break;
			case 2:
				return myRow1.y;
				break;
			case 3:
				return myRow1.z;
				break;
			default:
				assert(aColumn < 4 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		case 2:
			switch (aColumn)
			{
			case 1:
				return myRow2.x;
				break;
			case 2:
				return myRow2.y;
				break;
			case 3:
				return myRow2.z;
				break;
			default:
				assert(aColumn < 4 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		case 3:
			switch (aColumn)
			{
			case 1:
				return myRow3.x;
				break;
			case 2:
				return myRow3.y;
				break;
			case 3:
				return myRow3.z;
				break;
			default:
				assert(aColumn < 4 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		default:
			assert(aRow < 4 && aRow > 0 && "Out of bounds.");
			break;
		}
	}
	template<class T>
	inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		switch (aRow)
		{
		case 1:
			switch (aColumn)
			{
			case 1:
				return myRow1.x;
				break;
			case 2:
				return myRow1.y;
				break;
			case 3:
				return myRow1.z;
				break;
			default:
				assert(aColumn < 4 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		case 2:
			switch (aColumn)
			{
			case 1:
				return myRow2.x;
				break;
			case 2:
				return myRow2.y;
				break;
			case 3:
				return myRow2.z;
				break;
			default:
				assert(aColumn < 4 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		case 3:
			switch (aColumn)
			{
			case 1:
				return myRow3.x;
				break;
			case 2:
				return myRow3.y;
				break;
			case 3:
				return myRow3.z;
				break;
			default:
				assert(aColumn < 4 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		default:
			assert(aRow < 4 && aRow > 0 && "Out of bounds.");
			break;
		}
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix3x3<T> tempMatrix;
		tempMatrix.myRow2.y = cos(aAngleInRadians);
		tempMatrix.myRow2.z = sin(aAngleInRadians);

		tempMatrix.myRow3.y = -sin(aAngleInRadians);
		tempMatrix.myRow3.z = cos(aAngleInRadians);

		return tempMatrix;
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix3x3<T> tempMatrix;
		tempMatrix.myRow1.x = cos(aAngleInRadians);
		tempMatrix.myRow1.z = -sin(aAngleInRadians);

		tempMatrix.myRow3.x = sin(aAngleInRadians);
		tempMatrix.myRow3.z = cos(aAngleInRadians);

		return tempMatrix;
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix3x3<T> tempMatrix;
		tempMatrix.myRow1.x = cos(aAngleInRadians);
		tempMatrix.myRow1.y = sin(aAngleInRadians);

		tempMatrix.myRow2.x = -sin(aAngleInRadians);
		tempMatrix.myRow2.y = cos(aAngleInRadians);

		return tempMatrix;
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMatrixToTranspose)
	{
		Vector3<T> column1(aMatrixToTranspose.myRow1.x, aMatrixToTranspose.myRow2.x, aMatrixToTranspose.myRow3.x);
		Vector3<T> column2(aMatrixToTranspose.myRow1.y, aMatrixToTranspose.myRow2.y, aMatrixToTranspose.myRow3.y);
		Vector3<T> column3(aMatrixToTranspose.myRow1.z, aMatrixToTranspose.myRow2.z, aMatrixToTranspose.myRow3.z);

		Matrix3x3<T> tempMatrix;
		tempMatrix.myRow1 = column1;
		tempMatrix.myRow2 = column2;
		tempMatrix.myRow3 = column3;
		return tempMatrix;
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> tempMatrix;
		tempMatrix.myRow1 = this->myRow1 + aMatrix.myRow1;
		tempMatrix.myRow2 = this->myRow2 + aMatrix.myRow2;
		tempMatrix.myRow3 = this->myRow3 + aMatrix.myRow3;
		return tempMatrix;
	}
	template<class T>
	inline void Matrix3x3<T>::operator+=(const Matrix3x3<T>& aMatrix)
	{
		this->myRow1 += aMatrix.myRow1;
		this->myRow2 += aMatrix.myRow2;
		this->myRow3 += aMatrix.myRow3;
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> tempMatrix;
		tempMatrix.myRow1 = this->myRow1 - aMatrix.myRow1;
		tempMatrix.myRow2 = this->myRow2 - aMatrix.myRow2;
		tempMatrix.myRow3 = this->myRow3 - aMatrix.myRow3;
		return tempMatrix;
	}
	template<class T>
	inline void Matrix3x3<T>::operator-=(const Matrix3x3<T>& aMatrix)
	{
		this->myRow1 -= aMatrix.myRow1;
		this->myRow2 -= aMatrix.myRow2;
		this->myRow3 -= aMatrix.myRow3;
	}
	template<class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& aMatrix)
	{
		Vector3<T> column1(aMatrix.myRow1.x, aMatrix.myRow2.x, aMatrix.myRow3.x);
		Vector3<T> column2(aMatrix.myRow1.y, aMatrix.myRow2.y, aMatrix.myRow3.y);
		Vector3<T> column3(aMatrix.myRow1.z, aMatrix.myRow2.z, aMatrix.myRow3.z);
		Matrix3x3<T> tempMatrix;
		tempMatrix.myRow1.x = myRow1.Dot(column1);
		tempMatrix.myRow1.y = myRow1.Dot(column2);
		tempMatrix.myRow1.z = myRow1.Dot(column3);

		tempMatrix.myRow2.x = myRow2.Dot(column1);
		tempMatrix.myRow2.y = myRow2.Dot(column2);
		tempMatrix.myRow2.z = myRow2.Dot(column3);

		tempMatrix.myRow3.x = myRow3.Dot(column1);
		tempMatrix.myRow3.y = myRow3.Dot(column2);
		tempMatrix.myRow3.z = myRow3.Dot(column3);

		return tempMatrix;
	}
	template<class T>
	inline void Matrix3x3<T>::operator*=(const Matrix3x3<T>& aMatrix)
	{
		*this = (*this) * aMatrix;
	}
	template<class T>
	inline void Matrix3x3<T>::operator=(const Matrix3x3<T>& aMatrix)
	{
		myRow1 = aMatrix.myRow1;
		myRow2 = aMatrix.myRow2;
		myRow3 = aMatrix.myRow3;
	}
	template<class T>
	inline bool operator==(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		if (aMatrix0(1, 1) == aMatrix1(1, 1) && aMatrix0(1, 2) == aMatrix1(1, 2) && aMatrix0(1, 3) == aMatrix1(1, 3) &&
			aMatrix0(2, 1) == aMatrix1(2, 1) && aMatrix0(2, 2) == aMatrix1(2, 2) && aMatrix0(2, 3) == aMatrix1(2, 3) &&
			aMatrix0(3, 1) == aMatrix1(3, 1) && aMatrix0(3, 2) == aMatrix1(3, 2) && aMatrix0(3, 3) == aMatrix1(3, 3))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	template<class T>
	inline Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
	{
		Vector3<T> column1(aMatrix(1, 1), aMatrix(2, 1), aMatrix(3, 1));
		Vector3<T> column2(aMatrix(1, 2), aMatrix(2, 2), aMatrix(3, 2));
		Vector3<T> column3(aMatrix(1, 3), aMatrix(2, 3), aMatrix(3, 3));

		return Vector3<T>(aVector.Dot(column1), aVector.Dot(column2), aVector.Dot(column3));
	}
}