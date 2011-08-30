#include <cassert>
#include "dimensions.h"
#include "foreach.h"
#include "screen_object.h"

#include "screen.h"

screen::screen(dimensions const& dim)
		: screen_(SDL_SetVideoMode(dim.w,dim.h,32,SDL_SWSURFACE))
		, objects_()
	{}

void screen::add(object& obj)
{
	objects_.insert(&obj);
}

void screen::remove(object& obj)
{
	objects_.erase(&obj);
}

void screen::draw()
{
	screen_.clear();
	foreach(object* obj, objects_)
		obj->draw(screen_);
	screen_.flip();
}
