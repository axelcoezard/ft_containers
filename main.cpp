/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:00:01 by acoezard          #+#    #+#             */
/*   Updated: 2022/04/05 17:00:04 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include <time.h>

#ifdef STD
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#include <stdlib.h>
#define COUNT 20


static void vector_tests(void)
{
	ft::vector<int> vector_int;

	for (int i = 0; i < COUNT; i++)
		vector_int.push_back(i);

	for (int i = 0; i < 2; i++)
		vector_int.pop_back();

	std::cout << "capactity: " << vector_int.capacity() << std::endl;
	std::cout << "size: " << vector_int.size() << std::endl;
	std::cout << "max size: " << vector_int.max_size() << std::endl;

	for (size_t i = 0; i < vector_int.size(); i++)
		std::cout << "[" << i << "] = " << vector_int[i] << "\n";
}

static void stack_tests(void)
{
	ft::stack<int> stack_int;

	for (int i = 0; i < COUNT; i++)
		stack_int.push(i);

	for (int i = 0; i < 2; i++)
		stack_int.pop();

	std::cout << "size: " << stack_int.size() << std::endl;

	size_t i = stack_int.size();
	while (!stack_int.empty() && i--)
	{
		std::cout << "[" << i << "] = " << stack_int.top() << "\n";
		stack_int.pop();
	}
}

static void map_tests(void)
{
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
		map_int.insert(ft::make_pair(i, i));

	std::cout << "size: " << map_int.size() << std::endl;
	std::cout << "max size: " << map_int.max_size() << std::endl;

	for (size_t i = 0; i < map_int.size(); i++)
		std::cout << "[" << i << "] = " << map_int[i] << "\n";
}

int main(void)
{
	std::cout << "====\nTests for vector\n====" << std::endl;
	vector_tests();

	std::cout << "====\nTests for stack\n====" << std::endl;
	stack_tests();

	std::cout << "====\nTests for map\n====" << std::endl;
	map_tests();

	return (0);
}
