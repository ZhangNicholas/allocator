// #include <cassert>
// #include <cstdlib>
#include <iostream>
// #include <string>
// #include <cstddef>?
// #include <algorithm>

#include <vector>
#include <map>
#include"myAllocator.hpp"

int main(int argc, char const* argv[])
{
	auto v = std::vector<int, logging_allocator<int>>{};
	v.reserve(6);
	for (int i = 0; i < 6; ++i) {
		std::cout << "vector size = " << v.size() << std::endl;
		v.emplace_back(i);
		std::cout << std::endl;
	}

	// std::cout << "\n\n\n\nAfter creation\n\n\n\n" << std::endl;
	// auto v2 = v;

	auto m = std::map<
		int,
		float,
		std::less<int>,
		logging_allocator<
		std::pair<
		const int, float
		>
		>
	>{};

	for (int i = 0; i < 1; ++i) {
		m[i] = static_cast<float>(i);
	}
}