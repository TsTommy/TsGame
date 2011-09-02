#ifndef VEC_INL_H_INCLUDED
#define VEC_INL_H_INCLUDED

#include "point.h"

inline vec::vec(point const& p)
		: x(p.x)
		, y(p.y)
	{}

inline vec::operator safe_bool() const
{
	if(x==0 && y==0)
		return 0;
	else
		return &vec::safe_bool_details;
}

#endif //VEC_INL_H_INCLUDED
