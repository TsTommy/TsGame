#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

class point;

class vec
{
public:
	vec(double arg_x, double arg_y): x(arg_x), y(arg_y) {}
	vec(point const& p);

	vec& operator+=(vec const& v) {x+=v.x; y+=v.y; return *this;}
	vec& operator-=(vec const& v) {x-=v.x; y-=v.y; return *this;}
	vec operator*=(double s) {x*=s; y*=s; return *this;}
	vec operator+(vec const& v) const {return vec(*this)+=v;}
	vec operator-(vec const& v) const {return vec(*this)-=v;}
	vec operator*(double s) {return vec(*this)*=s;}

	double x;
	double y;
};

#include "vec-inl.h"

#endif //VEC_H_INCLUDED
