#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <string>
#include "image.h"

class animation
{
public:
	typedef image::screen_t screen_t;

	animation(char const* filename);
	animation(std::string const& filename);

	void draw(screen_t&, point const& pos) const;

private:
	image img_;
};

#endif //ANIMATION_H_INCLUDED
