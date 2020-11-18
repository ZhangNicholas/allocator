#include <vector>
#include <iostream>
#include <map>

#include "arena_allocator.h"
#include "custom_vector_container.h"

template <class T, std::size_t N> using CA = arena_allocator<T, N>; // custom allocator
template <class T, std::size_t N> using CACustomVector = // custom vector with custom allocator
CustomVector<T, arena_allocator<T, N>>;
template <class Key, class T, std::size_t N> using CAMap = // map with custom allocator
std::map <
	Key,
	T,
	std::less<Key>,
	arena_allocator<std::pair<const Key, T>, N>
>;

unsigned int factorial(unsigned int n) {
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

int main() {
	constexpr int container_size = 10;
	constexpr std::size_t arena_size = 1024; // bytes
	arena<arena_size> a;

	std::map<int, int> m;
	CAMap<int, int, arena_size> ca_m{
		CA<std::map<int, int>, arena_size>(a)
	};

	CustomVector<int, std::allocator<int>> vec;
	CACustomVector<int, arena_size> ca_vec{
		CA<std::vector<int>, arena_size>(a)
	};

	std::cout << "map with std::allocator" << std::endl;
	for (int i = 0; i < container_size; ++i) {
		m[i] = factorial(i);
	}
	for (const auto& it : m) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}

	std::cout << "map with custom allocator" << std::endl;
	for (int i = 0; i < container_size; ++i) {
		ca_m[i] = factorial(i);
	}
	for (const auto& it : ca_m) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}

	std::cout << "custom vector with std::allocator" << std::endl;
	for (int i = 0; i < container_size; ++i) {
		vec.push_back(i);
	}
	for (It<int> it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << std::endl;
	}

	std::cout << "custom vector with custom allocator" << std::endl;
	for (int i = 0; i < container_size; ++i) {
		ca_vec.push_back(i);
	}
	for (It<int, arena_allocator<int, arena_size>> it = ca_vec.begin(); it != ca_vec.end(); ++it) {
		std::cout << *it << std::endl;
	}
}