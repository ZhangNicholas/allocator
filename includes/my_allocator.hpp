#pragma once

#ifndef __PRETTY_FUNCTION__
#include "pretty.h"
#endif

#include <iostream>
#include <vector>
#include <map>

#define USE_PRETTY 1

template<typename T>
struct Allocator_traits {
	using value_type = T;

	Allocator_traits();

	template <typename U>
	Allocator_traits(const Allocator_traits<U>&);

	T* allocate(std::size_t n);

	void deallocate(T* p, std::size_t n);
};

template <typename T>
Allocator_traits<T>::Allocator_traits() {
}

template <typename T>
template <typename U>
Allocator_traits<T>::Allocator_traits(const Allocator_traits<U>&) {
	// should we make a copy of the rhs.m_buffer ?
	// No, we should not!
}

template <typename T>
T* Allocator_traits<T>::allocate(std::size_t n) {
#ifndef USE_PRETTY
	std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
	std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
	auto p = std::malloc(n * sizeof(T));
	if (!p)
		throw std::bad_alloc();
	return reinterpret_cast<T*>(p);
}

template <typename T>
void Allocator_traits<T>::deallocate(T* p, std::size_t n) {
#ifndef USE_PRETTY
	std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
	std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
	std::free(p);
}

template <class T, class U>
constexpr bool operator== (const Allocator_traits<T>&, const Allocator_traits<U>&) noexcept {
	return false;
}

template <class T, class U>
constexpr bool operator!= (const Allocator_traits<T>&, const Allocator_traits<U>&) noexcept {
	return true;
}