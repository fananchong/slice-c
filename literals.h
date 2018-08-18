#pragma once

#pragma warning(push)
#pragma warning(disable:4455)

struct slice_index
{
	size_t begin, end;
};

struct slice_literals
{
	size_t begin;

	slice_index operator - (slice_literals sl) const
	{
		return { begin, sl.begin };
	}
};

constexpr slice_literals operator "" i(unsigned long long _Val)
{
	return slice_literals{ size_t(_Val) };
}

#pragma warning(pop)  