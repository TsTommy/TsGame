#include "screen_object.h"

screen_object::screen_object(point const& pos, char const* filename)
		: pos_(pos)
		, anim_(filename)
{
}

screen_object::screen_object(point const& pos, std::string const& filename)
		: pos_(pos)
		, anim_(filename)
{
}

void screen_object::draw(screen_t& s) const
{
	anim_.draw(s,pos_);
}
