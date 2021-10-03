#ifndef CU_MAP_H
#define CU_MAP_H

#include "Pair.h"
#include "GrowingArray.h"

namespace cu
{
	template<typename KeyT, typename ValueT>
	class Map
	{
	private:
		using KeyValuePair = Pair<KeyT, ValueT>;

		GrowingArray<KeyValuePair> elements;

		Pair<bool, KeyValuePair*> FindValue(const KeyT& key)
		{
			for (size_t i{ 0 }; i < elements.Size(); ++i)
			{
				if (elements[i].First() == key)
				{
					return { true, &elements[i] };
				}
			}
			return { false, 0 };
		}

		const Pair<bool, const KeyValuePair*> FindValue(const KeyT& key) const
		{
			for (size_t i{ 0 }; i < elements.Size(); ++i)
			{
				if (elements[i].First() == key)
				{
					return { true, &elements[i] };
				}
			}
			return { false, 0 };
		}

	public:
		Map(const size_t& growthSize = 10, const bool safeMode = true) :
			elements{ growthSize, safeMode }
		{}

		template<size_t size>
		Map(const cu::Array<KeyValuePair, size>& keyValuePairs) :
			elements{ keyValuePairs }
		{}

		Map(const cu::GrowingArray<KeyValuePair>& keyValuePairs) :
			elements{ keyValuePairs }
		{}

		~Map() = default;

		// Sets the value at a specified key.
		void SetValue(const KeyT& key, const ValueT& value)
		{
			const Pair<bool, KeyValuePair*> valueData{ FindValue(key) };
			if (valueData.First())
			{
				valueData.Second()->Second() = value;
			}
			else
			{
				elements.Add({ key, value });
			}
		}

		// Gets the element at a specified key, and throws an error if there is none.
		ValueT& At(const KeyT& key)
		{
			const Pair<bool, KeyValuePair*> valueData{ FindValue(key) };
			if (valueData.First())
			{
				return valueData.Second()->Second();
			}
			else
			{
				throw std::invalid_argument{ "No value at target key." };
			}
		}

		// Gets the element at a specified key.
		const ValueT& At(const KeyT& key) const
		{
			const Pair<bool, KeyValuePair*> valueData{ FindValue(key) };
			if (valueData.First())
			{
				return valueData.Second()->Second();
			}
			else
			{
				throw std::invalid_argument{ "No value at target key." };
			}
		}

		// Checks if a specified key has a value associated with it.
		bool KeyHasValue(const KeyT& key)
		{
			return FindValue().First();
		}

		// Removes the element at a specified key if the key has an associated value.
		void RemoveAt(const KeyT& key)
		{
			for (size_t i{ 0 }; i < elements.Size(); ++i)
			{
				if (elements[i].First() == key)
				{
					elements.RemoveAt(i);
					break;
				}
			}
		}

		ValueT& operator[](const KeyT& key)
		{
			const Pair<bool, KeyValuePair*> valueData{ FindValue(key) };
			if (valueData.First())
			{
				return valueData.Second()->Second();
			}
			else
			{
				elements.Add({ key, ValueT{} });
				return elements[elements.Size() - 1].Second();
			}
		}

		const ValueT& operator[](const KeyT& key) const
		{
			return FindValue(key).Second()->Second();
		}

		#pragma region Iterators
		inline KeyValuePair* begin()
		{
			return elements.begin();
		}

		inline const KeyValuePair* begin() const
		{
			return elements.begin();
		}

		inline KeyValuePair* end()
		{
			return elements.end();
		}

		inline const KeyValuePair* end() const
		{
			return elements.end();
		}
		#pragma endregion
	};
}

#endif