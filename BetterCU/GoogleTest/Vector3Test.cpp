#include "pch.h"
#include "..\BetterCU\Vector3.hpp"

TEST(Vector3, Reflect)
{

	CU::Vector3f vec = CU::Vector3f::Reflect({ 1, -1, 0}, { 0, 1, 0 });

	EXPECT_EQ(-1, vec.X());
	EXPECT_EQ(1, vec.Y());
	EXPECT_EQ(0, vec.Z());
}