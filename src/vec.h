#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#include <cmath>
#include <cstdlib>

class point;

class vec
{
private:
	typedef void (vec::*safe_bool)();

public:
	vec() {}
	vec(double arg_x, double arg_y): x(arg_x), y(arg_y) {}
	vec(point const& p);

	operator safe_bool() const;

	vec& operator+=(vec const& v) {x+=v.x; y+=v.y; return *this;}
	vec& operator-=(vec const& v) {x-=v.x; y-=v.y; return *this;}
	vec operator*=(double s) {x*=s; y*=s; return *this;}
	vec operator/=(double s) {x/=s; y/=s; return *this;}
	vec operator+(vec const& v) const {return vec(*this)+=v;}
	vec operator-(vec const& v) const {return vec(*this)-=v;}
	vec operator*(double s) const {return vec(*this)*=s;}
	vec operator/(double s) const {return vec(*this)/=s;}
	vec operator-() const {return vec(-x,-y);}
	bool operator==(vec const& v) const {return x==v.x && y==v.y;}
	bool operator!=(vec const& v) const {return x!=v.x || y!=v.y;}

	///returns the length of this vector
	double mag() const {return sqrt(x*x+y*y);}
	///returns the dot product of *this and v
	double dot(vec const& v) const {return x*v.x+y*v.y;}
	///returns the magnitude of the projection of *this onto v
	double proj_mag(vec const& v) const {return this->dot(v)/v.mag();}
	///returns a unit vector with the same direction as *this
	vec normalized() const {return *this/mag();}
	///returns the projection of *this onto v as a vector
	vec project(vec const& v) const 
	{
		vec const result = v.normalized() *= proj_mag(v);
		return result;
	}

	double x;
	double y;

private:
	void safe_bool_details() {exit(1);}
};

struct vec_comparator {
	bool operator()(vec const& a, vec const& b) const {return a.y<b.y || (a.y==b.y && a.x<b.x);}
};

#include "vec-inl.h"

#endif //VEC_H_INCLUDED
