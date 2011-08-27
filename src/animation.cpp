#include <cassert>

#include "animation.h"
#include "screen.h"

animation::animation(std::string const& image_path)
		: image_(SDL_LoadBMP(image_path.c_str()))
{
	assert(image_);
}

void animation::draw(screen& s, int x, int y) const
{
	s.blit(*image_,x,y);
}
