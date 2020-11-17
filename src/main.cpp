#include <vector>
#include <iostream>
#include <map>

#include "arena_allocator.h"

template <class T, std::size_t N> using A = arena_allocator<T, N>;
template <class T, std::size_t N> using Vector = std::vector<T, arena_allocator<T, N>>;
template <class Key, class T, std::size_t N> using Map =
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
	constexpr std::size_t arena_size = 1024;
	arena<arena_size> a;

	std::map<int, int> m;
	Map<int, int, arena_size> m_custom_allocator{
		A<std::map<int, int>, arena_size>(a) };

	for (int i = 0; i < container_size; ++i) {
		m_custom_allocator[i] = factorial(i);
		std::cout << sizeof(m_custom_allocator[i]) << std::endl;
	}

	for (const auto& it : m_custom_allocator) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}
}