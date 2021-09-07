#pragma once

#include "Array.h"

namespace CommonUtilities
{
	using MatrixDefaultType = float;

	template<int rows, int columns, typename T = MatrixDefaultType>
	class Matrix
	{
	public:
		Matrix()
		{
			myElements = {};
		}

		Matrix(const Matrix& aMatrix)
		{
			myElements = aMatrix.myElements;
		}

		Matrix(const Array<Array<T, columns>, rows>& someElements)
		{
			myElements = someElements;
		}

		~Matrix() = default;

		inline static constexpr int Rows()
		{
			return rows;
		}

		inline static constexpr int Columns()
		{
			return columns;
		}

		Matrix<columns, rows, T> Transposed() const
		{
			Matrix<columns, rows, T> newMatrix = {};
			
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < columns; ++j)
				{
					newMatrix[j][i] = myElements[i, j];
				}
			}

			return newMatrix;
		}

		const T& operator()(const int& aRow, const int& aColumn) const
		{
			return myElements[aRow][aColumn];
		}

		T& operator()(const int& aRow, const int& aColumn)
		{
			return myElements[aRow][aColumn];
		}

		inline const Array<T, columns>& operator[](const int& aRow) const
		{
			return myElements[rows];
		}

		inline Array<T, columns>& operator[](const int& aRow)
		{
			return myElements[rows];
		}

		bool operator==(const Matrix& aMatrix) const
		{
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < columns; ++j)
				{
					if (myElements[i][j] != aMatrix.myElements[i][j])
					{
						return false;
					}
				}
			}

			return true;
		}

		bool operator!=(const Matrix& aMatrix) const
		{
			return !(*this == aMatrix);
		}

		void operator+=(const Matrix& aMatrix) const
		{
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < columns; ++j)
				{
					myElements[i][j] += aMatrix.elements[i][j];
				}
			}
		}

		inline Matrix operator+(const Matrix& aMatrix) const
		{
			Matrix newMatrix = aMatrix;
			newMatrix += *this;
			return newMatrix;
		}

		void operator -=(const Matrix& aMatrix)
		{
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < columns; ++j)
				{
					myElements[i][j] -= aMatrix.myElements[i][j];
				}
			}
		}

		inline Matrix operator-(const Matrix& aMatrix) const
		{
			Matrix newMatrix = aMatrix;
			newMatrix -= *this;
			return newMatrix;
		}

		template <typename N>
		void operator*=(const N& aScalar)
		{
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < columns; ++j)
				{
					myElements[i][j] *= aScalar;
				}
			}
		}

		template <typename N>
		inline Matrix operator*(const N& aScalar) const
		{
			Matrix newMatrix = *this;
			newMatrix *= aScalar;
			return newMatrix;
		}

		template<typename N>
		void operator/=(const N& aScalar)
		{
			for (size_t i{ 0 }; i < rows; ++i)
			{
				for (size_t j{ 0 }; j < columns; ++j)
				{
					myElements[i][j] /= aScalar;
				}
			}
		}

		template<typename N>
		inline Matrix operator/(const N& aScalar) const
		{
			Matrix newMatrix{ *this };
			newMatrix /= aScalar;
			return newMatrix;
		}

		template<size_t secondColumns>
		Matrix<rows, secondColumns, T> operator*(const Matrix<columns, secondColumns, T>& aMatrix) const
		{
			Matrix<rows, secondColumns, T> newMatrix{};
			for (size_t i{ 0 }; i < rows; ++i)
			{
				for (size_t j{ 0 }; j < secondColumns; ++j)
				{
					for (size_t k{ 0 }; k < columns; ++k)
					{
						newMatrix[i][j] += myElements[i][k] * aMatrix[k][j];
					}
				}
			}
			return newMatrix;
		}

		template<int size, typename T = MatrixDefaultType>
		using SquareMatrix = Matrix<size, size, T>;

		template<int size, typename T = MatrixDefaultType>
		static SquareMatrix<size, T> IdentityMatrix()
		{
			SquareMatrix<size, T> matrix{};
			for (size_t i{ 0 }; i < size; ++i)
			{
				matrix[i][i] = 1;
			}
			return matrix;
		}

		template<int size, typename T = MatrixDefaultType>
		static SquareMatrix<size, T> CreateRotationAroundX(const T& anAngleInRadians)
		{
			assert(size > 2 && size < 5 && "Rotation only works for 3x3 and 4x4 matrixes");

			SquareMatrix<size> tempMatrix;
			tempMatrix(1, 1) = cos(anAngleInRadians);
			tempMatrix(1, 2) = sin(anAngleInRadians);

			tempMatrix(2, 1) = -sin(anAngleInRadians);
			tempMatrix(2, 2) = cos(anAngleInRadians);

			return tempMatrix;
		}

		template<int size, typename T = MatrixDefaultType>
		static SquareMatrix<size, T> CreateRotationAroundY(const T& anAngleInRadians)
		{
			assert(size > 2 && size < 5 && "Rotation only works for 3x3 and 4x4 matrixes");

			SquareMatrix<size> tempMatrix;
			tempMatrix(0, 0) = cos(anAngleInRadians);
			tempMatrix(0, 2) = -sin(anAngleInRadians);

			tempMatrix(2, 0) = sin(anAngleInRadians);
			tempMatrix(2, 2) = cos(anAngleInRadians);

			return tempMatrix;
		}

		template<int size, typename T = MatrixDefaultType>
		static SquareMatrix<size, T> CreateRotationAroundZ(const T& anAngleInRadians)
		{
			assert(size > 2 && size < 5 && "Rotation only works for 3x3 and 4x4 matrixes");

			SquareMatrix<size> tempMatrix;
			tempMatrix(0, 0) = cos(anAngleInRadians);
			tempMatrix(0, 1) = sin(anAngleInRadians);

			tempMatrix(1, 0) = -sin(anAngleInRadians);
			tempMatrix(1, 1) = cos(anAngleInRadians);

			return tempMatrix;
		}

	private:
		Array<Array<T, columns>, rows> myElements;
	};

	template <typename type = MatrixDefaultType>
	using Matrix4x4 = Matrix<4, 4, type>;

	template <typename type = MatrixDefaultType>
	using Matrix3x3 = Matrix<3, 3, type>;
}

namespace CU = CommonUtilities;