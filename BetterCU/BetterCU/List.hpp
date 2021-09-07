#pragma once

#include "Array.h"

namespace CommonUtilities
{
	template<typename T>
	class List
	{
	public:
		List(const int& aGrowthSize = 10, const bool& aSafeMode = true)
		{
			myGrowthSize = aGrowthSize;
			mySafeMode = aSafeMode;
			myCapacity = aGrowthSize;
			mySize = 0;

			myElements = new T[myGrowthSize];
		}

		List(const List& anArray)
		{
			myGrowthSize = anArray.myGrowthSize;
			mySafeMode = anArray.mySafeMode;
			myCapacity = anArray.myCapacity;
			mySize = anArray.mySize;

			myElements = new T[myCapacity];

			if (mySafeMode)
			{
				for (int i = 0; i < mySize; ++i)
				{
					myElements[i] = anArray.myElements[i];
				}
			}
			else
			{
				memcpy(myElements, anArray.myElements, sizeof(T) * mySize);
			}
		}

		template <int size>
		List(const Array<T, size>& anArray, const int& aGrowthSize = 10, const bool& aSafeMode = true)
		{
			myGrowthSize = aGrowthSize;
			mySafeMode = aSafeMode;
			mySize = 0;
			myCapacity = myGrowthSize;
			myElements = new T[myGrowthSize];

			GrowToSize(anArray.Size());

			if (aSafeMode)
			{
				for (int i = 0; i < anArray.Size(); ++i)
				{
					myElements[i] = anArray.Data()[i];
				}
			}
			else
			{
				memcpy(myElements, anArray.Data(), sizeof(T) * anArray.Size());
			}

			mySize = size;
		}

		List(const std::initializer_list<T>& someElements)
		{
			myGrowthSize = 10;
			mySafeMode = true;
			mySize = 0;
			myCapacity = myGrowthSize;
			myElements = new T[myCapacity];

			GrowToSize(someElements.size());

			int i = 0;
			for (T element : someElements)
			{
				myElements[i] = element;
				++i;
			}

			mySize = someElements.size();
		}

		virtual ~List()
		{
			delete[] myElements;
		}

		int Size() const
		{
			return mySize;
		}

		int Capacity() const
		{
			return myCapacity;
		}

		void SetGrowthSize(const int& aSize)
		{
			myGrowthSize = aSize;
		}

		void SetSafeMode(const bool& aSafeMode)
		{
			mySafeMode = aSafeMode;
		}

		bool Contains(const T& anElement) const
		{
			for (int i = 0; i < mySize; ++i)
			{
				if (myElements[i] == anElement)
				{
					return true;
				}
			}

			return false;
		}

		bool Empty() const
		{
			return mySize == 0;
		}

		void Add(const T& anElement)
		{
			if (mySize == myCapacity)
			{
				Grow();
			}

			myElements[mySize] = anElement;
			++mySize;
		}

		void AddRange(const List& aRange)
		{
			GrowToSize(mySize + aRange.mySize);

			if (mySafeMode)
			{
				for (int i = 0; i < aRange.mySize; ++i)
				{
					myElements[i + mySize] = aRange.myElements[i];
				}
			}
			else
			{
				memcpy(myElements + mySize, aRange.myElements, sizeof(T) * aRange.mySize);
			}

			mySize += aRange.mySize;
		}

		template<int size>
		void AddRange(const Array<T, size>& aRange)
		{
			GrowToSize(mySize + aRange.Size());
			
			if (mySafeMode)
			{
				for (int i = 0; i < size; ++i)
				{
					myElements[i + mySize] = aRange.Data()[i];
				}
			}
			else
			{
				memcpy(myElements + mySize, aRange.Data(), sizeof(T) * size);
			}

			mySize += size;
		}

		void Insert(const T& anElement, const int& anIndex)
		{
			assert(anIndex < mySize  && anIndex >= 0 && "Index out of range.");

			GrowToSize(mySize + 1);

			if (mySafeMode)
			{
				for (int i = mySize; i > anIndex; --i)
				{
					myElements[i] = myElements[i - 1];
				}
			}
			else
			{
				memcpy(myElements + anIndex + 1, myElements + anIndex, sizeof(T) * (mySize - anIndex));
			}
			myElements[anIndex] = anElement;
			++mySize;
		}

		void InsertRange(const List& aRange, const int& anIndex)
		{
			assert(anIndex < mySize && anIndex >= 0 && "Index out of range.");

			GrowToSize(mySize + aRange.mySize);

			if (mySafeMode)
			{
				for (int i = mySize + aRange.mySize; i > anIndex + aRange.mySize - 1; --i)
				{
					myElements[i] = myElements[i - aRange.mySize];
				}

				for (int i = 0; i < aRange.mySize; ++i)
				{
					myElements[i + anIndex] = aRange.myElements[i];
				}
			}
			else
			{
				memcpy(myElements + anIndex + aRange.mySize, myElements + anIndex, sizeof(T) * (mySize - anIndex));
				memcpy(myElements + anIndex, aRange.myElements, sizeof(T) * aRange.mySize);
			}

			mySize += aRange.mySize;
		}

		template<int size>
		void InsertRange(const Array<T, size>& aRange, const int& anIndex)
		{
			assert(anIndex < mySize && anIndex >= 0 && "Index out of range.");

			GrowToSize(mySize + aRange.Size());

			if (mySafeMode)
			{
				for (int i = mySize + size; i > anIndex + size - 1; --i)
				{
					myElements[i] = myElements[i - size];
				}

				for (int i = 0; i < size; ++i)
				{
					myElements[i + anIndex] = aRange.Data()[i];
				}
			}
			else
			{
				memcpy(myElements + anIndex + size, myElements + anIndex, sizeof(T) * (mySize - anIndex));
				memcpy(myElements + anIndex, aRange.Data(), sizeof(T) * size);
			}

			mySize += size;
		}

		void RemoveAt(const int& anIndex)
		{
			assert(anIndex < mySize && anIndex >= 0 && "Index out of range.");

			if (mySafeMode)
			{
				for (int i = anIndex; i < mySize - 1; ++i)
				{
					myElements[i] = myElements[i + 1];
				}
			}
			else
			{
				memcpy(myElements + anIndex, myElements + anIndex + 1, sizeof(T) * ((mySize - 1) - anIndex));
			}
			--mySize;
		}

		void RemoveRange(const int& anIndex, const int& aCount)
		{
			assert(anIndex + aCount < mySize && anIndex >= 0 && "Index out of range.");

			if (mySafeMode)
			{
				for (int i = anIndex + aCount; i < mySize; ++i)
				{
					myElements[i - aCount] = myElements[i];
				}
			}
			else
			{
				memcpy(myElements + anIndex, myElements + anIndex + aCount, sizeof(T) * (mySize - anIndex - aCount));
			}

			mySize -= aCount;
		}

		void Remove(const T& anElement)
		{
			for (int i = 0; i < mySize; ++i)
			{
				if (myElements[i] == anElement)
				{
					RemoveAt(i);
					return;
				}
			}

			assert(false && "Element does not exist in range.");
		}

		void Clear()
		{
			delete[] myElements;
			myCapacity = myGrowthSize;
			myElements = new T[myCapacity];
			mySize = 0;
		}

		const T& operator[] (const int& anIndex) const
		{
			assert(anIndex < mySize&& anIndex >= 0 && "Index out of range.");
			return myElements[anIndex];
		}

		T& operator[](const int& anIndex)
		{
			assert(anIndex < mySize&& anIndex >= 0 && "Index out of range.");
			return myElements[anIndex];
		}

		bool operator== (const List& aList) const
		{
			if (aList.mySize != mySize)
				return false;

			for (int i = 0; i < mySize; ++i)
			{
				if (myElements[i] != aList.myElements[i])
				{
					return false;
				}
			}

			return true;
		}

		bool operator!=(const List& aList) const
		{
			return !(*this == aList);
		}

		List& operator= (const List& aList)
		{
			myCapacity = aList.myCapacity;

			delete[] myElements;
			myElements = new T[myCapacity];
			mySafeMode = aList.mySafeMode;

			if (mySafeMode)
			{
				for (int i = 0; i < aList.mySize; ++i)
				{
					myElements[i] = aList.myElements[i];
				}
			}
			else
			{
				memcpy(myElements, aList.myElements, sizeof(T) * aList.mySize);
			}

			mySize = aList.mySize;
			return *this;
		}

		template <int size>
		List& operator=(const Array<T, size>& anArray)
		{
			GrowToSize(size);

			if (mySafeMode)
			{
				for (int i = 0; i < anArray.Size(); ++i)
				{
					myElements[i] = anArray.Data()[i];
				}
			}
			else
			{
				memcpy(myElements, anArray.Data(), sizeof(T) * anArray.Size());
			}
			mySize = anArray.Size();
			return *this;
		}

		T* begin()
		{
			return myElements;
		}

		inline const T* begin() const
		{
			return myElements;
		}

		T* end()
		{
			return myElements[mySize];
		}

		inline const T* end() const
		{
			return myElements[mySize];
		}

	private:
		void Grow()
		{
			myCapacity += myGrowthSize;
			T* newElements = new T[myCapacity];

			if (mySafeMode)
			{
				for (int i = 0; i < mySize; ++i)
				{
					newElements[i] = myElements[i];
				}
			}
			else
			{
				memcpy(newElements, myElements, (sizeof(T) * mySize));
			}

			delete[] myElements;
			myElements = newElements;
		}

		void GrowToSize(const int& aSize)
		{
			while (myCapacity < aSize)
			{
				Grow();
			}
		}

		T* myElements;
		int mySize;
		int myCapacity;
		int myGrowthSize;
		
		bool mySafeMode;
	};
	
}

namespace CU = CommonUtilities;