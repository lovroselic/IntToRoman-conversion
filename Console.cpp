#include <iostream>
#include <vector>
#include "Console.h"

void printArray(int* data, int length) {
	int* p = data;
	for (int x = 0; x < length; x++) {
		std::cout << p << " --> cell[" << x << "]\t= " << *p << std::endl;
		p++;
	}
	std::cout << std::endl;
}

void printVector(std::vector<int>& vct) {
	for (int v : vct) {
		std::cout << v << std::endl;
	}
}