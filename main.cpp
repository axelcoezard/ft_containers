#include <iostream>
#include <string>
#include <deque>

#ifdef STD
	//#include <map>
	//#include <stack>
	#include <vector>
	namespace ft = std;
#else
	//#include "map.hpp"
	//#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
#define COUNT (MAX_RAM / (int)sizeof(int))


int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<int> vector_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_int.push_back(i);
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_int[idx] = 5;
	}
	ft::vector<int>().swap(vector_int);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_int.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	return (0);
}
