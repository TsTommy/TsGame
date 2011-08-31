#ifndef VEC_INL_H_INCLUDED
#define VEC_INL_H_INCLUDED

#include "point.h"

inline vec::vec(point const& p)
		: x(p.x)
		, y(p.y)
	{}

#endif //VEC_INL_H_INCLUDED
