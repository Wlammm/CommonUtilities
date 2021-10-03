#pragma once
#include "Vector.h"
#include <assert.h>
#include <math.h>

namespace CommonUtilities
{
	template <class T>
	class Matrix4x4
	{
	public:
		// Creates the identity matrix.
		Matrix4x4<T>();
		// Copy Constructor.
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix);
		// () operator for accessing element (row, column) for read/write or read, respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix);
		void operator+=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix);
		void operator-=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix);
		void operator*=(const Matrix4x4<T>& aMatrix);
		void operator=(const Matrix4x4<T>& aMatrix);
		// Static functions for creating rotation matrices.
		static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians);
		// Static function for creating a transpose of a matrix.
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);
		// Assumes aTransform is made up of nothing but rotations and translations.
		static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aTransform);

	private:
		Vector4<T> myRow1;
		Vector4<T> myRow2;
		Vector4<T> myRow3;
		Vector4<T> myRow4;
	};
	template<class T>
	inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
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
			case 4:
				return myRow1.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
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
			case 4:
				return myRow2.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
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
			case 4:
				return myRow3.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		case 4:
			switch (aColumn)
			{
			case 1:
				return myRow4.x;
				break;
			case 2:
				return myRow4.y;
				break;
			case 3:
				return myRow4.z;
				break;
			case 4:
				return myRow4.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		default:
			assert(aRow < 5 && aRow > 0 && "Out of bounds.");
			break;
		}
	}
	template<class T>
	inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
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
			case 4:
				return myRow1.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
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
			case 4:
				return myRow2.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
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
			case 4:
				return myRow3.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		case 4:
			switch (aColumn)
			{
			case 1:
				return myRow4.x;
				break;
			case 2:
				return myRow4.y;
				break;
			case 3:
				return myRow4.z;
				break;
			case 4:
				return myRow4.w;
				break;
			default:
				assert(aColumn < 5 && aColumn > 0 && "Out of bounds.");
				break;
			}
			break;
		default:
			assert(aRow < 5 && aRow > 0 && "Out of bounds.");
			break;
		}
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix4x4<T> tempMatrix;
		tempMatrix.myRow2.y = cos(aAngleInRadians);
		tempMatrix.myRow2.z = sin(aAngleInRadians);

		tempMatrix.myRow3.y = -sin(aAngleInRadians);
		tempMatrix.myRow3.z = cos(aAngleInRadians);

		return tempMatrix;
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix4x4<T> tempMatrix;
		tempMatrix.myRow1.x = cos(aAngleInRadians);
		tempMatrix.myRow1.z = -sin(aAngleInRadians);

		tempMatrix.myRow3.x = sin(aAngleInRadians);
		tempMatrix.myRow3.z = cos(aAngleInRadians);

		return tempMatrix;
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix4x4<T> tempMatrix;
		tempMatrix.myRow1.x = cos(aAngleInRadians);
		tempMatrix.myRow1.y = sin(aAngleInRadians);

		tempMatrix.myRow2.x = -sin(aAngleInRadians);
		tempMatrix.myRow2.y = cos(aAngleInRadians);

		return tempMatrix;
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMatrixToTranspose)
	{
		Vector4<T> column1(aMatrixToTranspose.myRow1.x, aMatrixToTranspose.myRow2.x, aMatrixToTranspose.myRow3.x, aMatrixToTranspose.myRow4.x);
		Vector4<T> column2(aMatrixToTranspose.myRow1.y, aMatrixToTranspose.myRow2.y, aMatrixToTranspose.myRow3.y, aMatrixToTranspose.myRow4.y);
		Vector4<T> column3(aMatrixToTranspose.myRow1.z, aMatrixToTranspose.myRow2.z, aMatrixToTranspose.myRow3.z, aMatrixToTranspose.myRow4.z);
		Vector4<T> column4(aMatrixToTranspose.myRow1.w, aMatrixToTranspose.myRow2.w, aMatrixToTranspose.myRow3.w, aMatrixToTranspose.myRow4.w);

		Matrix4x4<T> tempMatrix;
		tempMatrix.myRow1 = column1;
		tempMatrix.myRow2 = column2;
		tempMatrix.myRow3 = column3;
		tempMatrix.myRow4 = column4;
		return tempMatrix;
	}

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
	{
		Matrix4x4 tempMatrix = Transpose(aTransform);

		Vector4<T> translation;
		translation.x = -aTransform(4, 1);
		translation.y = -aTransform(4, 2);
		translation.z = -aTransform(4, 3);
		translation.w = 0;

		tempMatrix(1, 4) = 0;
		tempMatrix(2, 4) = 0;
		tempMatrix(3, 4) = 0;
		tempMatrix(4, 4) = 1;

		translation = translation * tempMatrix;

		Matrix4x4 returnMatrix;
		returnMatrix.myRow1 = tempMatrix.myRow1;
		returnMatrix.myRow2 = tempMatrix.myRow2;
		returnMatrix.myRow3 = tempMatrix.myRow3;
		returnMatrix.myRow4 = translation;
		returnMatrix(1, 4) = aTransform(1, 4);
		returnMatrix(2, 4) = aTransform(2, 4);
		returnMatrix(3, 4) = aTransform(3, 4);
		returnMatrix(4, 4) = aTransform(4, 4);

		return returnMatrix;
	}



	template<class T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		myRow1.x = 1;
		myRow2.x = 0;
		myRow3.x = 0;
		myRow4.x = 0;

		myRow1.y = 0;
		myRow2.y = 1;
		myRow3.y = 0;
		myRow4.y = 0;

		myRow1.z = 0;
		myRow2.z = 0;
		myRow3.z = 1;
		myRow4.z = 0;

		myRow1.w = 0;
		myRow2.w = 0;
		myRow3.w = 0;
		myRow4.w = 1;
	}
	template<class T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		*this = aMatrix;
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> tempMatrix;
		tempMatrix.myRow1 = this->myRow1 + aMatrix.myRow1;
		tempMatrix.myRow2 = this->myRow2 + aMatrix.myRow2;
		tempMatrix.myRow3 = this->myRow3 + aMatrix.myRow3;
		tempMatrix.myRow4 = this->myRow4 + aMatrix.myRow4;
		return tempMatrix;
	}
	template<class T>
	inline void Matrix4x4<T>::operator+=(const Matrix4x4<T>& aMatrix)
	{
		*this = (*this) + aMatrix;
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> tempMatrix;
		tempMatrix.myRow1 = this->myRow1 - aMatrix.myRow1;
		tempMatrix.myRow2 = this->myRow2 - aMatrix.myRow2;
		tempMatrix.myRow3 = this->myRow3 - aMatrix.myRow3;
		tempMatrix.myRow4 = this->myRow4 - aMatrix.myRow4;
		return tempMatrix;
	}
	template<class T>
	inline void Matrix4x4<T>::operator-=(const Matrix4x4<T>& aMatrix)
	{
		*this = (*this) - aMatrix;
	}
	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& aMatrix)
	{
		Vector4<T> column1(aMatrix.myRow1.x, aMatrix.myRow2.x, aMatrix.myRow3.x, aMatrix.myRow4.x);
		Vector4<T> column2(aMatrix.myRow1.y, aMatrix.myRow2.y, aMatrix.myRow3.y, aMatrix.myRow4.y);
		Vector4<T> column3(aMatrix.myRow1.z, aMatrix.myRow2.z, aMatrix.myRow3.z, aMatrix.myRow4.z);
		Vector4<T> column4(aMatrix.myRow1.w, aMatrix.myRow2.w, aMatrix.myRow3.w, aMatrix.myRow4.w);
		Matrix4x4<T> tempMatrix;
		tempMatrix.myRow1.x = myRow1.Dot(column1);
		tempMatrix.myRow1.y = myRow1.Dot(column2);
		tempMatrix.myRow1.z = myRow1.Dot(column3);
		tempMatrix.myRow1.w = myRow1.Dot(column4);

		tempMatrix.myRow2.x = myRow2.Dot(column1);
		tempMatrix.myRow2.y = myRow2.Dot(column2);
		tempMatrix.myRow2.z = myRow2.Dot(column3);
		tempMatrix.myRow2.w = myRow2.Dot(column4);

		tempMatrix.myRow3.x = myRow3.Dot(column1);
		tempMatrix.myRow3.y = myRow3.Dot(column2);
		tempMatrix.myRow3.z = myRow3.Dot(column3);
		tempMatrix.myRow3.w = myRow3.Dot(column4);

		tempMatrix.myRow4.x = myRow4.Dot(column1);
		tempMatrix.myRow4.y = myRow4.Dot(column2);
		tempMatrix.myRow4.z = myRow4.Dot(column3);
		tempMatrix.myRow4.w = myRow4.Dot(column4);

		return tempMatrix;
	}
	template<class T>
	inline void Matrix4x4<T>::operator*=(const Matrix4x4<T>& aMatrix)
	{
		*this = (*this) * aMatrix;
	}
	template<class T>
	inline void Matrix4x4<T>::operator=(const Matrix4x4<T>& aMatrix)
	{
		myRow1 = aMatrix.myRow1;
		myRow2 = aMatrix.myRow2;
		myRow3 = aMatrix.myRow3;
		myRow4 = aMatrix.myRow4;
	}
	template<class T>
	inline bool operator==(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		if (aMatrix0(1, 1) == aMatrix1(1, 1) && aMatrix0(1, 2) == aMatrix1(1, 2) && aMatrix0(1, 3) == aMatrix1(1, 3) && aMatrix0(1, 4) == aMatrix1(1, 4) &&
			aMatrix0(2, 1) == aMatrix1(2, 1) && aMatrix0(2, 2) == aMatrix1(2, 2) && aMatrix0(2, 3) == aMatrix1(2, 3) && aMatrix0(2, 4) == aMatrix1(2, 4) &&
			aMatrix0(3, 1) == aMatrix1(3, 1) && aMatrix0(3, 2) == aMatrix1(3, 2) && aMatrix0(3, 3) == aMatrix1(3, 3) && aMatrix0(3, 4) == aMatrix0(3, 4) &&
			aMatrix0(4, 1) == aMatrix1(4, 1) && aMatrix0(4, 2) == aMatrix1(4, 2) && aMatrix0(4, 3) == aMatrix1(4, 3) && aMatrix0(4, 4) == aMatrix0(4, 4))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	template<class T>
	inline Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		Vector4<T> column1(aMatrix(1, 1), aMatrix(2, 1), aMatrix(3, 1), aMatrix(4, 1));
		Vector4<T> column2(aMatrix(1, 2), aMatrix(2, 2), aMatrix(3, 2), aMatrix(4, 2));
		Vector4<T> column3(aMatrix(1, 3), aMatrix(2, 3), aMatrix(3, 3), aMatrix(4, 3));
		Vector4<T> column4(aMatrix(1, 4), aMatrix(2, 4), aMatrix(3, 4), aMatrix(4, 4));

		return Vector4<T>(aVector.Dot(column1), aVector.Dot(column2), aVector.Dot(column3), aVector.Dot(column4));
	}
}