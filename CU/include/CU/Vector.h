#ifndef CU_VECTOR_H
#define CU_VECTOR_H

#include "Array.h"
#include "Matrix.h"

namespace cu
{
	template<typename T, size_t size>
	class Vector : protected Array<T, size>
	{
	public:
		Vector() :
			Array<T, size>{}
		{}

		Vector(const Vector& vector) :
			Array<T, size>{ vector }
		{}

		Vector(const std::initializer_list<T>& elements) :
			Array<T, size>{ elements }
		{}

		~Vector() = default;

		inline T& Element(const size_t& index)
		{
			if (index >= size)
			{
				throw std::out_of_range{ "Index is out of range." };
			}
			return (*this)[index];
		}

		inline const T& Element(const size_t& index) const
		{
			if (index >= size)
			{
				throw std::out_of_range{ "Index is out of range." };
			}
			return (*this)[index];
		}

		// Represents the vector as a column matrix.
		inline Matrix<size, 1, T> AsColumnMatrix()
		{
			Matrix<size, 1, T> matrix{};
			for (size_t i{ 0 }; i < size; ++i)
			{
				matrix[i][0] = (*this)[i];
			}
			return matrix;
		}

		// Represents the vector as a row matrix.
		inline Matrix<1, size, T> AsRowMatrix()
		{
			Matrix<1, size, T> matrix{};
			for (size_t i{ 0 }; i < size; ++i)
			{
				matrix[0][i] = (*this)[i];
			}
			return matrix;
		}

		// Calculates the dot product of this vector and another vector.
		T Dot(const Vector& vector)
		{
			T dotProduct{};
			for (size_t i{ 0 }; i < size; ++i)
			{
				dotProduct += (*this)[i] * vector[i];
			}
			return dotProduct;
		}

		#pragma region Operators
		void operator+=(const Vector& vector)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				(*this)[i] += vector[i];
			}
		}

		inline Vector operator+(const Vector& vector)
		{
			Vector resultVector{ vector };
			resultVector += *this;
			return resultVector;
		}

		void operator-=(const Vector& vector)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				(*this)[i] -= vector[i];
			}
		}

		inline Vector operator-(const Vector& vector)
		{
			Vector resultVector{ vector };
			resultVector -= *this;
			return resultVector;
		}

		template<typename N>
		void operator*=(const N& scalar)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				(*this)[i] *= scalar;
			}
		}

		template<typename N>
		inline Vector operator*(const N& scalar)
		{
			Vector resultVector{ *this };
			resultVector *= scalar;
			return resultVector;
		}

		template<typename N>
		void operator/=(const N& scalar)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				(*this)[i] /= scalar;
			}
		}

		template<typename N>
		inline Vector operator/(const N& scalar)
		{
			Vector resultVector{ *this };
			resultVector /= scalar;
			return resultVector;
		}
		#pragma endregion
	};

	// Calculates the length of a vector.
	template<typename N = float, typename T, size_t size>
	N Length(const Vector<T, size>& vector)
	{
		N sum{};
		for (size_t i{ 0 }; i < size; ++i)
		{
			sum += pow(vector.Element(i), 2);
		}
		return sqrt(sum);
	}

	// Calculates a normalized (length 1) version of a vector.
	template<typename T, size_t size>
	Vector<T, size> Normalized(const Vector<T, size>& vector)
	{
		return vector / Length<T>(vector);
	}
}

#endif