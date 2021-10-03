#pragma once

#include <assert.h>
#include <initializer_list>

namespace CommonUtilities
{
	template <typename Type, int size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	private:
		Type myArray[size];
		CountType myCurrentSize;

	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<Type>& aInitList);
		~VectorOnStack();

		VectorOnStack& operator=(const VectorOnStack& aVectorOnStack);
		inline const Type& operator[](const CountType aIndex) const;
		inline Type& operator[](const CountType aIndex);

		inline void Add(const Type& aObject);
		inline void Insert(const CountType aIndex, const Type& aObject);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(const CountType aIndex);
		inline void Clear();

		inline CountType Size() const;
	};


	// Definition.
	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack()
	{
		myCurrentSize = 0;
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		if (UseSafeModeFlag)
		{
			this = aVectorOnStack;
		}
		else
		{
			memcpy(&this, &aVectorOnStack, sizeof(aVectorOnStack));
		}
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack(const std::initializer_list<Type>& aInitList)
	{
		myCurrentSize = 0;
			
		for (auto iter = aInitList.begin(); iter != aInitList.end(); ++iter)
		{
			myArray[myCurrentSize++] = *iter;
		}
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		myCurrentSize = 0;
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>& VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
	{
		if (UseSafeModeFlag)
		{
			this = aVectorOnStack;
		}
		else
		{
			memcpy(&this, &aVectorOnStack, sizeof(aVectorOnStack));
		}

		return *this;
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline const Type& VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType aIndex) const
	{
		assert(aIndex >= 0 && aIndex < myCurrentSize && "Out of bounds.");

		return (myArray[aIndex]);
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline Type& VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType aIndex)
	{
		assert(aIndex >= 0 && aIndex < myCurrentSize && "Out of bounds.");

		return myArray[aIndex];
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Add(const Type& aObject)
	{
		assert(myCurrentSize != size && "Out of bounds. Array is full.");

		myArray[myCurrentSize] = aObject;
		myCurrentSize++;
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Insert(const CountType aIndex, const Type& aObject)
	{
		assert(myCurrentSize != size && "Out of bounds. Array is full.");
		assert(aIndex < size&& aIndex >= 0 && "Out of bounds.");

		if (aIndex >= myCurrentSize)
		{
			myArray[aIndex] = aObject;
			myCurrentSize++;
			return;
		}

		for (CountType i = myCurrentSize; i >= aIndex; --i)
		{
			if (UseSafeModeFlag)
			{
				myArray[i] = myArray[i - 1];
			}
			else
			{
				memcpy(&myArray[i], &myArray[i - 1], sizeof(Type));
			}
		}

		myCurrentSize++;
		if (UseSafeModeFlag)
		{
			myArray[aIndex] = aObject;
		}
		else
		{
			memcpy(&myArray[aIndex], &aObject, sizeof(Type));
		}
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::RemoveCyclic(const Type& aObject)
	{
		for (int i = size - 1; i > 0; --i)
		{
			if (myArray[i] == aObject)
			{
				myArray[i] = myArray[myCurrentSize - 1];
				myCurrentSize--;
				return;
			}
		}
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(const CountType aIndex)
	{
		myArray[aIndex] = myArray[myCurrentSize - 1];
		myCurrentSize--;
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Clear()
	{
		myCurrentSize = 0;
	}

	template<typename Type, int size, typename CountType, bool UseSafeModeFlag>
	__forceinline CountType VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Size() const
	{
		return myCurrentSize;
	}
}

namespace CU = CommonUtilities;