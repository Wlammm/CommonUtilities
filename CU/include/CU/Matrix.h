#ifndef CU_MATRIX_H
#define CU_MATRIX_H

#include "Array.h"

namespace cu
{
    using MatrixDefaultType = float;

    template<size_t rows, size_t columns, typename T = MatrixDefaultType>
    class Matrix
    {
    private:
        Array<Array<T, columns>, rows> elements;

    public:
        #pragma region Constructors
        Matrix() :
            elements{}
        {}

        Matrix(const Matrix& matrix) :
            elements{ matrix.elements }
        {}

        Matrix(const Array<Array<T, columns>, rows>& elements) :
            elements{ elements }
        {}
        #pragma endregion

        ~Matrix() = default;

        inline static constexpr size_t Rows()
        {
            return rows;
        }

        inline static constexpr size_t Columns()
        {
            return columns;
        }

        Matrix<columns, rows, T> Transposed() const
        {
            Matrix<columns, rows, T> newMatrix{};
            for (size_t i{ 0 }; i < rows; ++i)
            {
                for (size_t j{ 0 }; j < columns; ++j)
                {
                    newMatrix[j][i] = elements[i][j];
                }
            }
            return newMatrix;
        }

        #pragma region Operators
        inline Array<T, columns>& operator[](const size_t& row)
        {
            return elements[row];
        }

        inline const Array<T, columns>& operator[](const size_t& row) const
        {
            return elements[row];
        }

        bool operator==(const Matrix& matrix) const
        {
            for (size_t i{ 0 }; i < rows; ++i)
            {
                for (size_t j{ 0 }; j < columns; ++j)
                {
                    if (elements[i][j] != matrix.elements[i][j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        bool operator!=(const Matrix& matrix) const
        {
            return !(*this == matrix);
        }

        void operator+=(const Matrix& matrix)
        {
            for (size_t i{ 0 }; i < rows; ++i)
            {
                for (size_t j{ 0 }; j < columns; ++j)
                {
                    elements[i][j] += matrix.elements[i][j];
                }
            }
        }

        inline Matrix operator+(const Matrix& matrix) const
        {
            Matrix newMatrix{ matrix };
            newMatrix += *this;
            return newMatrix;
        }

        void operator-=(const Matrix& matrix)
        {
            for (size_t i{ 0 }; i < rows; ++i)
            {
                for (size_t j{ 0 }; j < columns; ++j)
                {
                    elements[i][j] -= matrix.elements[i][j];
                }
            }
        }

        inline Matrix operator-(const Matrix& matrix) const
        {
            Matrix newMatrix{ matrix };
            newMatrix -= *this;
            return newMatrix;
        }

        template<typename N>
        void operator*=(const N& scalar)
        {
            for (size_t i{ 0 }; i < rows; ++i)
            {
                for (size_t j{ 0 }; j < columns; ++j)
                {
                    elements[i][j] *= scalar;
                }
            }
        }

        template<typename N>
        inline Matrix operator*(const N& scalar) const
        {
            Matrix newMatrix{ *this };
            newMatrix *= scalar;
            return newMatrix;
        }

        template<typename N>
        void operator/=(const N& scalar)
        {
            for (size_t i{ 0 }; i < rows; ++i)
            {
                for (size_t j{ 0 }; j < columns; ++j)
                {
                    elements[i][j] /= scalar;
                }
            }
        }

        template<typename N>
        inline Matrix operator/(const N& scalar) const
        {
            Matrix newMatrix{ *this };
            newMatrix /= scalar;
            return newMatrix;
        }

        template<size_t secondColumns>
        Matrix<rows, secondColumns, T> operator*(const Matrix<columns, secondColumns, T> & matrix) const
        {
            Matrix<rows, secondColumns, T> newMatrix{};
            for (size_t i{ 0 }; i < rows; ++i)
            {
                for (size_t j{ 0 }; j < secondColumns; ++j)
                {
                    for (size_t k{ 0 }; k < columns; ++k)
                    {
                        newMatrix[i][j] += elements[i][k] * matrix[k][j];
                    }
                }
            }
            return newMatrix;
        }
        #pragma endregion
    };

    #pragma region Aliases
    template<size_t size, typename T = MatrixDefaultType>
    using SquareMatrix = Matrix<size, size, T>;

    using Matrix4x4 = SquareMatrix<4>;
    using Matrix3x3 = SquareMatrix<3>;
    using Matrix2x2 = SquareMatrix<2>;
    #pragma endregion

    // Creates an identity matrix of specified size.
    template<size_t size, typename T = MatrixDefaultType>
    static SquareMatrix<size, T> IdentityMatrix()
    {
        SquareMatrix<size, T> matrix{};
        for (size_t i{ 0 }; i < size; ++i)
        {
            matrix[i][i] = 1;
        }
        return matrix;
    }
}

#endif