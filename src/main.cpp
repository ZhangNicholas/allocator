// #include <cassert>
// #include <cstdlib>
#include <iostream>
// #include <string>
// #include <cstddef>?
// #include <algorithm>

#include <vector>
#include <map>
//#include "allocator_traits.hpp"
//#include "logging_allocator.hpp"
#include "my_allocator.hpp"


unsigned int factorial(unsigned int n) {
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
		Allocator_traits<
		std::pair<
		const int, int
		>
		>
	>{};

	for (int i = 0; i < container_size; ++i) {
		m[i] = factorial(i);
	}

	for (const auto& it : m) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}

	for (int i = 0; i < container_size; ++i) {
		m_custom_allocator[i] = factorial(i);
	}

	for (const auto& it : m_custom_allocator) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}
	return 0;
}