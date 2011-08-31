#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class vec;

class point
{
public:
	point(int arg_x, int arg_y): x(arg_x), y(arg_y) {}
	explicit point(vec const& v);

	int x, y;
};

#include "point-inl.h"

#endif //POINT_H_INCLUDED
