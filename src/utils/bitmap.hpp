#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <initializer_list>
#include <algorithm>

template <std::size_t _Num_bits, typename _Word_type = std::uint64_t>
struct bitmap
{
	using word_type = _Word_type;
	static inline constexpr auto num_bits = _Num_bits;
	static inline constexpr auto word_size = sizeof(word_type) * 8;
	static inline constexpr auto num_words = (num_bits + word_size - 1)/word_size;	

	constexpr bitmap(): store { 0u } {}
	constexpr bitmap(const bitmap& prev): bitmap(prev, std::make_index_sequence<num_words>{}) {}
	constexpr bitmap(const int (&values) [num_bits])
	: store { 0u }
	{
		for (auto i = 0u; i < num_bits; ++i)
			set (i, values[i]);
	}

	constexpr bitmap(std::initializer_list<int> values)
	:	store { 0u }
	{		
		const auto x = std::min (num_bits, values.size());
		for (auto i = 0u; i < x; ++i)
			set (i, *(values.begin() + i));
	}

	constexpr void set(std::size_t index, bool value)
	{
		index = index % num_bits;
		const auto m = word_type(1) << (index % word_size);
		if (value)
			store [index / word_size] |= m;
		else
			store [index / word_size] &= ~m;
	}

	constexpr bool get(std::size_t index) const
	{
		index = index % num_bits;
		const auto m = word_type(1) << (index % word_size);
		return !!(store [index / word_size] & m);
	}

	static constexpr auto size() { return num_bits ; }

	constexpr auto clear() 
	{
		for (auto&& cell : store) 
			cell = word_type { 0 };
	}

private:

	template <std::size_t ... I>
	constexpr bitmap(const bitmap& prev, std::index_sequence<I...>): store { prev.store[I]... } {}


	word_type store [num_words];
};