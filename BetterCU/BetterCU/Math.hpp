#pragma once

#include <assert.h>

namespace CommonUtilities
{
	constexpr float PI = 3.14159265359f;
	constexpr float Deg2Rad = PI / 180.f;
	constexpr float Rad2Deg = 180.f / PI;

	template<typename T>
	T Max(const T& aFirst, const T& aSecond)
	{
		return aFirst > aSecond ? aFirst : aSecond;
	}

	template<typename T>
	T Min(const T& aFirst, const T& aSecond)
	{
		return aFirst > aSecond ? aSecond : aFirst;
	}

	template<typename T>
	T Abs(const T& aFirst)
	{
		return aFirst > 0 ? aFirst : -aFirst;
	}

	template<typename T> 
	T Clamp(const T& aMin, const T& aMax, const T& aValue)
	{
		if (aMin > aMax)
		{
			return aValue < aMax ? aMin : aValue > aMin ? aMax : aValue;
		}

		return aValue < aMin ? aMin : aValue > aMax ? aMax : aValue;
	}

	template<typename T>
	T Lerp(const T& aFirst, const T& aSecond, const float& someTime)
	{
		return (1 - someTime) * aFirst + someTime * aSecond;
	}

	template<typename T>
	T SmoothStep(const T& aFirst, const T& aSecond, T aTime)
	{
		aTime = Clamp(static_cast<T>(0.0f), static_cast<T>(1.0f), (aTime - aFirst) / (aSecond - aFirst));

		return aTime * aTime * (3 - 2 * aTime);
	}

	template<typename T>
	void Swap(T& aFirst, T& aSecond)
	{
		T first = aFirst;

		aFirst = aSecond;
		aSecond = first;
	}

	template<typename T>
	const T Round(const T& aVal)
	{
		return static_cast<T>(static_cast<int>(aVal + static_cast<T>(.5f)));
	}

	template<typename T>
	const T Mod(const T& aVal, const T& aMod)
	{
		T rest = aVal;
		while (rest >= aMod)
		{
			rest -= aMod;
		}

		return rest;
	}



	template<typename T>
	const T Ceil(const T& aVal)
	{
		if (Mod(aVal, static_cast<T>(1)) == 0)
			return aVal;

		return static_cast<T>(static_cast<int>(aVal + static_cast<T>(1)));
	}

	template<typename T>
	const T Floor(const T& aVal)
	{
		return static_cast<T>(static_cast<int>(aVal));
	}
}

namespace CU = CommonUtilities;