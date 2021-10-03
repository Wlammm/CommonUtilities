#include <iostream>
#include <conio.h>
#include "Math.hpp"
#include <math.h>
#include <chrono>
#include "Vector3.hpp"
#include <vector>
#include "Random.hpp"
#include <thread>
#include "List.hpp"

int main()
{
	CU::List<float> list;
	list.Add(3);
	list.Add(2);
	list.Add(6);

	std::vector<float> list2;
	list2.push_back(2);
	list2.push_back(2);
	list2.push_back(2);

	_getch();
	return 0;
}