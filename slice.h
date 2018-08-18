#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "literals.h"
#include "array.h"

template<typename T>
class slice
{
public:
	slice(std::initializer_list<T> array_)
	{
		array = slice_array<T>(array_.begin(), array_.size());
		begin = 0;
		end = array_.size();
	}

	slice operator[](const slice_index& si) const
	{
		slice s;
		if (si.begin >= si.end)
		{
			return s;
		}
		s.array = array;
		s.begin = si.begin;
		s.end = si.end;
		return s;
	}

private:
	slice() : begin(0), end(0) {}

	slice_array<T> array;
	size_t begin;
	size_t end;

	template<typename T> friend slice<T>& append(slice<T>& s, std::initializer_list<T> array_);
	template<typename T> friend slice<T>& append(slice<T>& s1, const slice<T>& s2);
	template<typename T> friend slice<T>& remove(slice<T>& s, const size_t si);
	template<typename T> friend slice<T>& remove(slice<T>& s, const size_t si_begin, const size_t si_end);
	template<typename T> friend std::ostream& operator<<(std::ostream&, const slice<T>&);
};

template<typename T>
slice<T>& append(slice<T>& s, std::initializer_list<T> array_)
{
	s.array.append(s.end, array_);
	s.end += array_.size();
	return s;
}

template<typename T>
slice<T>& append(slice<T>& s1, const slice<T>& s2)
{
	s1.array.append(s1.end, s2.array, s2.begin, s2.end);
	s1.end += s2.end - s2.begin;
	return s1;
}

template<typename T>
slice<T>& remove(slice<T>& s, const size_t si)
{
	auto index = s.begin + si;
	if (index >= s.end)
	{
		return s;
	}
	s.array.remove(index);
	s.end -= 1;
	return s;
}

template<typename T> slice<T>& remove(slice<T>& s, const size_t si_begin, const size_t si_end)
{
	static slice<T> empty;
	auto begin = s.begin + si_begin;
	auto end = (std::min)(s.begin + si_end, s.end);

	if (begin >= end)
	{
		return empty;
	}
	s.array.remove(begin, end);
	s.end -= (end - begin);
	return s;
}


template<typename T>
inline std::ostream& operator<<(std::ostream& o, const slice<T>& s)
{
	std::string out = "{";
	for (size_t i = s.begin; i < s.end; i++)
	{
		if (out.size() > 1)
		{
			out += ", ";
		}
		out += s.array[i];
	}

	out += "}";
	o << out;
	return o;
}
