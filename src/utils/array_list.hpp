#pragma once

#include <cstdint>
#include <cstddef>
#include <cassert>
#include <initializer_list>

template <typename _Value_type, std::size_t _Max_size>
struct array_list
{
	using value_type = _Value_type;
	
	constexpr array_list()
	: _size	{ 0u },
		_data { } 
	{}

	constexpr array_list(const array_list& prev)
	: _size { prev._size }		
	{
		for (auto i = 0u; i < prev._size; ++i)
			_data[i] = prev._data[i];
	}

	constexpr array_list(std::initializer_list<value_type> values)
	: _size { values.size() }		
	{
		auto to_copy = std::min(values.size(), capacity());
		for (auto i = 0u; i < to_copy; ++i)
			_data[i] = *(values.begin() + i);
	}

	constexpr auto&& operator [] (std::size_t i) const
	{
		assert(i < _size);
		return _data[i];
	}

	constexpr auto&& operator [] (std::size_t i) 
	{
		assert(i < _size);
		return _data[i];
	}

	constexpr void push(value_type v) 
	{
		assert(_size < capacity());
		_data[_size++] = std::move(v);				
	}

	constexpr void pop()
	{
		assert(_size > 0);
		--_size;
	}

	constexpr void clear()
	{
		_size = 0;
	}

	constexpr auto size() const 
	{
		return _size;
	}

	constexpr auto empty() const
	{
		return size () == 0;
	}

	static constexpr auto capacity () 
	{
		return _Max_size;
	}

	constexpr void swap (array_list& rhs)
	{
		auto to_swap = std::max(size(), rhs.size());
		for (auto i = 0u; i < to_swap; ++i)
			std::swap(_data[i], rhs._data[i]);
		std::swap(_size, rhs._size);
	}

private:
	std::size_t _size { 0u };
	value_type _data [_Max_size] { };
};
