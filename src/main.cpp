// #include <cassert>
// #include <cstdlib>
#include <iostream>
// #include <string>
// #include <cstddef>?
// #include <algorithm>

#include <vector>
#include <map>
#include "allocatorTraits.hpp"
//#include "loggingAllocator.hpp"

unsigned int factorial(unsigned int n)
{
	if (n == 0)
		return 1;
	return n * factorial(n - 1);
}

int main(int argc, char const* argv[])
{
	auto container_size = 10;
	std::map<int, int> m;
	auto m_custom_allocator = std::map<
		int,
		int,
		std::less<int>,
		logging_allocator<
		std::pair<
		const int, int
		>
		>
	>{};

	for (int i = 0; i < container_size; ++i) {
		m[i] = factorial(i);
	}

	for (auto& it : m) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}

	for (int i = 0; i < container_size; ++i) {
		m_custom_allocator[i] = factorial(i);
	}

	for (auto& it : m_custom_allocator) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}
	return 0;
}