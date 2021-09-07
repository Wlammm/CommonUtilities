#include <iostream>
#include <conio.h>
#include "Array.h"
#include "List.hpp"
#include "Vector2.hpp"

int main()
{
	CU::Vector<float, 2> vector;

	std::cout << vector.Element(0) << std::endl;

	_getch();
	return 0;
}