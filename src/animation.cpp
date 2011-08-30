#include "animation.h"

animation::animation(char const* filename)
		: img_(filename)
	{}

animation::animation(std::string const& filename)
		: img_(filename)
	{}

void animation::draw(screen_t& s, point const& pos) const
{
	img_.draw(s,pos);
}