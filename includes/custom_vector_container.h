#pragma once
#include <iostream>
#include <string>
#include <vector>

template <
	class T,
	class A = std::allocator<T>
>

struct It {
	std::vector<T, A>& vec_;
	std::size_t pointer_;

	It(std::vector<T, A>& vec) : vec_{ vec }, pointer_{ 0 } {}

	It(std::vector<T, A>& vec, std::size_t size) : vec_{ vec }, pointer_{ size } {}

	bool operator!=(const It<T, A>& other) const {
		return !(*this == other);
	}

	bool operator==(const It<T, A>& other) const {
		return pointer_ == other.pointer_;
	}

	It& operator++() {
		++pointer_;
		return *this;
	}

	T& operator*() const {
		return vec_.at(pointer_);
	}
};

template<
	class T,
	class Allocator = std::allocator<T>
>
struct CustomVector {
	std::vector<T, Allocator> vec_;

	CustomVector() {
		std::vector<T, std::allocator<T>> vec_;
	};

	CustomVector(Allocator al) : vec_{ al } {
	};

	void push_back(T item) {
		vec_.push_back(item);
	};

	It<T, Allocator> begin() {
		return It<T, Allocator>(vec_);
	}

	It<T, Allocator> end() {
		return It<T, Allocator>(vec_, vec_.size());
	}
};