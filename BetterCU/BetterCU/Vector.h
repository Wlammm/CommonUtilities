#pragma once

#include "Array.h"
#include "Matrix.hpp"

namespace CommonUtilities
{
	template<typename T, int size>
	class Vector : protected Array<T, size>
	{
	public:
		Vector()
			: Array<T, size>{}
		{ 
			for (int i = 0; i < size; ++i)
			{
				(*this)[i] = 0;
			}
		}

		Vector(const Vector& aVector) :
			Array<T, size>{ aVector }
		{}

		Vector(const Array<T, size>& anArray)
			: Array<T, size>{ anArray } 
		{}

		Vector(const std::initializer_list<T>& someElements) :
			Array<T, size>{ someElements }
		{}

		~Vector() = default;

		inline T& Element(const int& anIndex)
		{
			assert(anIndex < size&& anIndex >= 0 && "Index out of range.");

			return (*this)[anIndex];
		}

		inline const T& Element(const int& anIndex) const
		{
			assert(anIndex < size&& anIndex >= 0 && "Index out of range.");

			return (*this)[anIndex];
		}

		inline Matrix<size, 1, T> AsColumnMatrix()
		{
			Matrix<size, 1, T> matrix{};
			for (int i = 0; i < size; ++i)
			{
				matrix[i][0] = (*this)[i];
			}
			return matrix;
		}

		inline Matrix<1, size, T> AsRowMatrix()
		{
			Matrix<1, size, T> matrix{};
			for (int i = 0; i < size; ++i)
			{
				matrix[0][i] = (*this)[i];
			}
			return matrix;
		}

		T Dot(const Vector& aVector) const
		{
			T dotProduct;
			for (int i = 0; i < size; ++i)
			{
				dotProduct += (*this)[i] * aVector[i];
			}
			return dotProduct;
		}

		void operator +=(const Vector& aVector)
		{
			for (int i = 0; i < size; ++i)
			{
				(*this)[i] += aVector[i];
			}
		}

		inline Vector operator+(const Vector& aVector)
		{
			Vector resultVector = aVector;
			resultVector += *this;
			return resultVector;
		}

		void operator-=(const Vector& aVector)
		{
			for (int i = 0; i < size; ++i)
			{
				(*this)[i] -= aVector[i];
			}
		}

		inline Vector operator-(const Vector& aVector)
		{
			Vector resultVector = aVector;
			resultVector -= *this;
			return resultVector;
		}

		template <typename T>
		void operator*=(const T& aScalar)
		{
			for (int i = 0; i < size; ++i)
			{
				(*this)[i] *= aScalar;
			}
		}

		template<typename T>
		inline Vector operator*(const T& aScalar)
		{
			Vector resultVector = *this;
			resultVector *= aScalar;
			return resultVector;
		}

		template<typename T>
		void operator/=(const T& aScalar)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				(*this)[i] /= aScalar;
			}
		}

		template<typename T>
		inline Vector operator/(const T& aScalar)
		{
			Vector resultVector{ *this };
			resultVector /= aScalar;
			return resultVector;
		}

		float Length()
		{
			float sum;
			for (int i = 0; i < size; ++i)
			{
				sum += pow(Element(i), 2);
			}
			return sqrt(sum);
		}

		Vector<T, size> Normalized()
		{
			return (*this) / Length();
		}

		template<typename T>
		Vector<T, size> Cast()
		{
			Array<T, size> values;
			
			for (int i = 0; i < size; ++i)
			{
				values[i] = static_cast<T>(Element(i));
			}

			return Vector<T, size>{ values };
		}

		// Matrix multiplication.
	};
}

namespace CU = CommonUtilities;