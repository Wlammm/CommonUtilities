#ifndef CU_GROWINGARRAY_H
#define CU_GROWINGARRAY_H

#include "Array.h"

namespace cu
{
	template<typename T>
	class GrowingArray
	{
	private:
		T* elements;
		size_t size;
		size_t capacity;

		size_t growthSize;
		bool safeMode;

		// The array grows to be able to hold sizeNeeded more elements.
		void Grow(const size_t& sizeNeeded)
		{
			// The first part of the growth calculation works only since growthSize has integer type.
			const size_t growth{ (sizeNeeded / growthSize) * growthSize + growthSize };

			capacity += growth;
			T* newElements{ new T[capacity] };

			// Copies all elements into the new array.
			if (safeMode)
			{
				for (size_t i{ 0 }; i < size; ++i)
				{
					newElements[i] = elements[i];
				}
			}
			else
			{
				memcpy(newElements, elements, sizeof(T) * size);
			}

			delete[] elements;
			elements = newElements;
		}

		// Validates the size for element insertion. If the size it too small for the elements, the array grows.
		inline void ValidateSize(const size_t& insertionCount)
		{
			if (size + insertionCount - 1 >= capacity)
			{
				Grow(insertionCount - (capacity - size));
			}
		}

		// Validates index to prevent out of range access.
		inline void ValidateIndex(const size_t& index) const
		{
			if (index >= size)
			{
				throw std::out_of_range{ "Index is out of range." };
			}
		}

	public:
		#pragma region Constructors
		GrowingArray(const size_t& growthSize = 10, const bool& safeMode = true) :
			growthSize{ growthSize },
			elements{ new T[growthSize] },
			capacity{ growthSize },
			safeMode{ safeMode },
			size{ 0 }
		{}

		GrowingArray(const GrowingArray& array) :
			growthSize{ array.growthSize },
			elements{ new T[array.capacity] },
			capacity{ array.capacity },
			safeMode{ array.safeMode },
			size{ array.size }
		{
			if (safeMode)
			{
				for (size_t i{ 0 }; i < array.size; ++i)
				{
					elements[i] = array.elements[i];
				}
			}
			else
			{
				memcpy(elements, array.elements, sizeof(T) * array.size);
			}
		}

		template<size_t size>
		GrowingArray(const Array<T, size>& array, const size_t& growthSize = 10, const bool& safeMode = true) :
			growthSize{ growthSize },
			elements{ new T[growthSize] },
			capacity{ growthSize },
			safeMode{ safeMode },
			size{ 0 }
		{
			ValidateSize(size);

			if (safeMode)
			{
				for (size_t i{ 0 }; i < array.Size(); ++i)
				{
					elements[i] = array.Data()[i];
				}
			}
			else
			{
				memcpy(elements, array.Data(), sizeof(T) * array.Size());
			}
			this->size = size;
		}

		GrowingArray(const std::initializer_list<T>& elements) :
			GrowingArray{}
		{
			ValidateSize(elements.size());

			size_t i{ 0 };
			for (T element : elements)
			{
				this->elements[i] = element;
				++i;
			}
			this->size = elements.size();
		}
		#pragma endregion

		virtual ~GrowingArray()
		{
			delete[] elements;
		}

		inline size_t Size() const
		{
			return size;
		}

		inline size_t Capacity() const
		{
			return capacity;
		}

		// Sets the size with which the array grows once it is filled up.
		inline void SetGrowthSize(const size_t& size)
		{
			growthSize = size;
		}

		// Tells the growing array whether to use safe mode (less optimized but safer).
		inline void SetSafeMode(const bool& value)
		{
			safeMode = value;
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

		// Checks if the array is empty.
		bool Empty() const
		{
			return size == 0;
		}

		#pragma region Element management
		// Adds an element at the end of the array.
		void Add(const T& element)
		{
			ValidateSize(1);
			elements[size] = element;
			++size;
		}

		// Adds a range of elements at the end of the array.
		void AddRange(const GrowingArray& range)
		{
			ValidateSize(range.size);
			if (safeMode)
			{
				for (size_t i{ 0 }; i < range.size; ++i)
				{
					elements[i + size] = range.elements[i];
				}
			}
			else
			{
				memcpy(elements + size, range.elements, sizeof(T) * range.size);
			}
			size += range.size;
		}

		// Adds a range of elements at the end of the array.
		template<size_t size>
		void AddRange(const Array<T, size>& range)
		{
			ValidateSize(size);
			if (safeMode)
			{
				for (size_t i{ 0 }; i < size; ++i)
				{
					elements[i + this->size] = range.Data()[i];
				}
			}
			else
			{
				memcpy(elements + this->size, range.Data(), sizeof(T) * size);
			}
			this->size += size;
		}

		// Inserts an element at the specified index.
		void Insert(const T& element, const size_t& index)
		{
			if (index > size)
			{
				throw std::out_of_range{ "Index is out of range." };
			}
			ValidateSize(1);

			if (safeMode)
			{
				for (size_t i{ size }; i > index; --i)
				{
					elements[i] = elements[i - 1];
				}
			}
			else
			{
				memcpy(elements + index + 1, elements + index, sizeof(T) * (size - index));
			}
			elements[index] = element;
			++size;
		}

		// Inserts a range at the specified index.
		void InsertRange(const GrowingArray& range, const size_t& index)
		{
			if (index > size)
			{
				throw std::out_of_range{ "Index is out of range." };
			}
			ValidateSize(range.size);

			if (safeMode)
			{
				for (size_t i{ size + range.size }; i > index + range.size - 1; --i)
				{
					elements[i] = elements[i - range.size];
				}
				for (size_t i{ 0 }; i < range.size; ++i)
				{
					elements[i + index] = range.elements[i];
				}
			}
			else
			{
				memcpy(elements + index + range.size, elements + index, sizeof(T) * (size - index));
				memcpy(elements + index, range.elements, sizeof(T) * range.size);
			}
			size += range.size;
		}

		// Inserts a range at the specified index.
		template<size_t size>
		void InsertRange(const Array<T, size>& range, const size_t& index)
		{
			if (index > this->size)
			{
				throw std::out_of_range{ "Index is out of range." };
			}
			ValidateSize(size);

			if (safeMode)
			{
				for (size_t i{ this->size + size }; i > index + size - 1; --i)
				{
					elements[i] = elements[i - size];
				}
				for (size_t i{ 0 }; i < size; ++i)
				{
					elements[i + index] = range.Data()[i];
				}
			}
			else
			{
				memcpy(elements + index + size, elements + index, sizeof(T) * (this->size - index));
				memcpy(elements + index, range.Data(), sizeof(T) * size);
			}
			this->size += size;
		}

		// Removes an element at the specified index.
		void RemoveAt(const size_t& index)
		{
			ValidateIndex(index);

			if (safeMode)
			{
				for (size_t i{ index }; i < size - 1; ++i)
				{
					elements[i] = elements[i + 1];
				}
			}
			else
			{
				memcpy(elements + index, elements + index + 1, sizeof(T) * ((size - 1) - index));
			}
			--size;
		}

		// Removes a range of elements at the specified index.
		void RemoveRange(const size_t& index, const size_t& count)
		{
			if (index + count > size)
			{
				throw std::out_of_range{ "Target range is out of range." };
			}

			if (safeMode)
			{
				for (size_t i{ index + count }; i < size; ++i)
				{
					elements[i - count] = elements[i];
				}
			}
			else
			{
				memcpy(elements + index, elements + index + count, sizeof(T) * (size - index - count));
			}
			size -= count;
		}

		// Removes the first occurance of the specified element, and returns whether the element was found.
		bool Remove(const T& element)
		{
			for (size_t i{ 0 }; i < size; ++i)
			{
				if (elements[i] == element)
				{
					RemoveAt(i);
					return true;
				}
			}
			return false;
		}

		// Clears the array and resets its capacity.
		void Clear()
		{
			delete[] elements;
			capacity = growthSize;
			elements = new T[capacity];
			size = 0;
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

		bool operator==(const GrowingArray& array) const
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

		inline bool operator!=(const GrowingArray& array) const
		{
			return !(*this == array);
		}

		GrowingArray& operator=(const GrowingArray& array)
		{
			capacity = array.capacity;
			elements = new T[capacity];
			safeMode = array.safeMode;

			if (safeMode)
			{
				for (size_t i{ 0 }; i < array.size; ++i)
				{
					elements[i] = array.elements[i];
				}
			}
			else
			{
				memcpy(elements, array.elements, sizeof(T) * array.size);
			}
			size = array.size;
			return *this;
		}

		template<size_t size>
		GrowingArray& operator=(const Array<T, size>& array)
		{
			if (size > this->size)
			{
				ValidateSize(array.Size() - this->size);
			}

			if (safeMode)
			{
				for (size_t i{ 0 }; i < array.Size(); ++i)
				{
					elements[i] = array.Data()[i];
				}
			}
			else
			{
				memcpy(elements, array.Data(), sizeof(T) * array.Size());
			}
			this->size = array.Size();
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