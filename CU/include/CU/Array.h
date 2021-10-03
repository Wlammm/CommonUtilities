#ifndef CU_ARRAY_H
#define CU_ARRAY_H

#include <initializer_list>
#include <stdexcept>

namespace cu
{
	template<typename T, size_t size>
	class Array
	{
	private:
		T* elements;

		// Validates index to prevent out of range access.
		inline static void ValidateIndex(const size_t& index)
		{
			if (index >= size)
			{
				throw std::out_of_range{ "Index is out of range." };
			}
		}

	public:
		#pragma region Constructors
		Array() :
			elements{ new T[size]{} }
		{}

		Array(const Array& array) :
			elements{ new T[size] }
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				elements[i] = array.elements[i];
			}
		}

		Array(const std::initializer_list<T>& elements) :
			elements{ new T[size] }
		{
			if (elements.size() != size)
			{
				throw std::invalid_argument((elements.size() < size) ? "Too few elements in initializer list" : "Too many elements in initializer list");
			}
			size_t i{ 0 };
			for (T element : elements)
			{
				this->elements[i] = element;
				++i;
			}
		}
		#pragma endregion

		virtual ~Array()
		{
			delete[] elements;
		}

		// Fills the array with the specified element.
		void Fill(const T& element)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				elements[i] = element;
			}
		}

		// Checks if the array contains the specified element.
		bool Contains(const T& element) const
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				if (elements[i] == element)
				{
					return true;
				}
			}
			return false;
		}

		// Gets a pointer to the data stored in the array.
		T* Data()
		{
			return elements;
		}

		// Gets a pointer to the data stored in the array.
		const T* Data() const
		{
			return elements;
		}

		#pragma region Static
		// The size of the array.
		inline static constexpr size_t Size()
		{
			return size;
		}

		// Checks if the array is empty (has no elements).
		inline static constexpr bool Empty()
		{
			return size == 0;
		}
		#pragma endregion

		#pragma region Operators
		inline T& operator[](const size_t& index)
		{
			ValidateIndex(index);
			return elements[index];
		}

		inline const T& operator[](const size_t& index) const
		{
			ValidateIndex(index);
			return elements[index];
		}

		bool operator==(const Array& array) const
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				if (elements[i] != array.elements[i])
				{
					return false;
				}
			}
			return true;
		}

		inline bool operator!=(const Array& array) const
		{
			return !(*this == array);
		}

		Array& operator=(const Array& array)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				elements[i] = array.elements[i];
			}
			return *this;
		}
		#pragma endregion

		#pragma region Iterators
		inline T* begin()
		{
			return elements;
		}

		inline const T* begin() const
		{
			return elements;
		}

		inline T* end()
		{
			return &elements[size];
		}

		inline const T* end() const
		{
			return &elements[size];
		}
		#pragma endregion
	};
}

#endif