#include "animation.h"
#include "path.h"

#include "screen_object.h"

screen_object::screen_object(screen* s, int x, int y)
		: screen_(s)
		, x_(x)
		, y_(y)
		, animation_(IMAGE("hello.bmp"))
{
	assert(s);
}

void screen_object::draw() const
{
	animation_->draw(*screen_,x_,y_);
}

void screen_object::move_to(int x, int y)
{
	x_ = x;
	y_ = y;
}
