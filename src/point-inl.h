#ifndef POINT_INL_H_INCLUDED
#define POINT_INL_H_INCLUDED

#include "vec.h"

inline point::point(vec const& v)
		: x(static_cast<int>(v.x))
		, y(static_cast<int>(v.y))
	{}

#endif //POINT_INL_H_INCLUDED
