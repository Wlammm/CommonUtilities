#pragma once

#include <random>
#include "Math.hpp"

namespace CommonUtilities
{
	const int RandomInt(const int& aMin, const int& aMax)
	{
		return CU::Mod(rand(), (aMax - aMin + 1)) + aMin;
	}

	const float RandomRange()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	const float RandomFloat(const float& aMin, const float& aMax)
	{
		float randInt = static_cast<float>(RandomInt(static_cast<int>(aMin), static_cast<int>(aMax)));
		float randDeci = RandomRange();
		return randInt + randDeci;
	}
}

namespace CU = CommonUtilities;