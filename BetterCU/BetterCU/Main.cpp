#include <iostream>
#include <conio.h>
#include "Math.hpp"
#include <math.h>
#include <chrono>
#include "Vector3.hpp"

int main()
{
	CU::Vector3f vec = { 0, 0, 0 };
	CU::Vector3f vec1 = { 1, 1, 1 };
	
	CU::Vector3f lerped = CU::Vector3f::SmoothStep(vec, vec1, 0.8f);

	std::cout << "X: " << lerped.X() << " Y: " << lerped.Y() << " Z: " << lerped.Z();

	_getch();
	return 0;
}