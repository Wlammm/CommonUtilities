#pragma once

#include <assert.h>
#include <initializer_list>

namespace CommonUtilities
{
	template<typename T, int size>
	class Array
	{
	public:
		Array();
		Array(const Array<T, size>& anArray);		
		Array(const std::initializer_list<T>& someElements);
		~Array();

		void Fill(const T& anElement);
		bool Contains(const T& anElement) const;
		T* Data() const;

		static constexpr int Size();
		static constexpr bool Empty();

		T& operator[](const int& anIndex);
		const T& operator[](const int& anIndex) const;
		bool operator==(const Array<T, size>& anArray) const;
		bool operator!=(const Array<T, size>& anArray) const;
		Array<T, size>& operator=(const Array<T, size> anArray);

		T* begin();
		T* end();

		const T* begin() const;
		const T* end() const;

	private:
		T* myElements;
	};

	template<typename T, int size>
	inline Array<T, size>::Array()
	{
		myElements = new T[size];
	}

	template<typename T, int size>
	inline Array<T, size>::Array(const Array<T, size>& anArray)
	{
		myElements = new T[size];

		for (int i = 0; i < size; ++i)
		{
			myElements[i] = anArray.myElements[i];
		}
	}

	template<typename T, int size>
	inline Array<T, size>::Array(const std::initializer_list<T>& someElements)
	{
		assert(someElements.size() <= size && "Too many elements in initialized list");

		myElements = new T[size];

		int i = 0; 
		for (T element : someElements)
		{
			myElements[i] = element;
			++i;
		}
	}
	
	template<typename T, int size>
	inline Array<T, size>::~Array()
	{
		delete[] myElements;
	}
	template<typename T, int size>
	inline void Array<T, size>::Fill(const T& anElement)
	{
		for (int i = 0; i < size; ++i)
		{
			myElements[i] = anElement;
		}
	}
	template<typename T, int size>
	inline bool Array<T, size>::Contains(const T& anElement) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (myElements[i] == anElement)
			{
				return true;
			}
		}

		return false;
	}
	template<typename T, int size>
	inline T* Array<T, size>::Data() const
	{
		return myElements;
	}
	template<typename T, int size>
	inline constexpr int Array<T, size>::Size()
	{
		return size;
	}
	template<typename T, int size>
	inline constexpr bool Array<T, size>::Empty()
	{
		return size == 0;
	}
	template<typename T, int size>
	inline T& Array<T, size>::operator[](const int& anIndex)
	{
		assert(anIndex < size && "Index out of range.");

		return myElements[anIndex];
	}

	template<typename T, int size>
	inline const T& Array<T, size>::operator[](const int& anIndex) const
	{
		assert(anIndex < size && "Index out of range.");

		return myElements[anIndex];
	}

	template<typename T, int size>
	inline bool Array<T, size>::operator==(const Array<T, size>& anArray) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (myElements[i] != anArray.myElements[i])
			{
				return false;
			}
		}
		return true;
	}
	template<typename T, int size>
	inline bool Array<T, size>::operator!=(const Array<T, size>& anArray) const
	{
		return !(*this == anArray);
	}
	template<typename T, int size>
	inline Array<T, size>& Array<T, size>::operator=(const Array<T, size> anArray)
	{
		for (int i = 0; i < size; ++i)
		{
			myElements[i] = anArray.myElements[i];
		}

		return *this;
	}
	template<typename T, int size>
	inline T* Array<T, size>::begin()
	{
		return myElements;
	}
	template<typename T, int size>
	inline T* Array<T, size>::end()
	{
		return myElements[size];
	}
	template<typename T, int size>
	inline const T* Array<T, size>::begin() const
	{
		return myElements;
	}
	template<typename T, int size>
	inline const T* Array<T, size>::end() const
	{
		return myElements[size];
	}
}

namespace CU = CommonUtilities;