#pragma once

#include <limits>

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
	closeEnough(T x, T y, T threshold = 0.0000001)
{
	return std::abs(x - y) < threshold || std::abs(x - y) < std::numeric_limits<T>::min();
}