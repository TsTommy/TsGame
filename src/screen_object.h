#ifndef SCREEN_OBJECT_H_INCLUDED
#define SCREEN_OBJECT_H_INCLUDED

#include "animation.h"
#include "point.h"
#include "surface.h"

class screen_object
{
public:
	typedef animation::screen_t screen_t;
	screen_object(point const& pos, char const* filename);
	screen_object(point const& pos, std::string const& filename);

	void draw(screen_t&) const;

private:
	point pos_;
	animation anim_;
};

#endif //SCREEN_OBJECT_H_INCLUDED
