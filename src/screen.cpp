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

void screen::on_frame(Uint32 curr_time)
{
	foreach(object* obj, objects_)
		obj->on_frame(curr_time);
}

void screen::draw()
{
	screen_.clear();
	int counter = 0;
	foreach(object* obj, objects_)
	{
		obj->draw(screen_);
		++counter;
		//debug
		#if 0
		if(counter >= 6)
			break;
		#endif
	}
	screen_.flip();
}
