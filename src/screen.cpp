#include <cassert>
#include "dimensions.h"
#include "foreach.h"
#include "screen_object.h"

#include "screen.h"

screen::screen(dimensions const& camera, dimensions const& world)
		: screen_(SDL_SetVideoMode(camera.w,camera.h,32,SDL_SWSURFACE))
		, buffer_(SDL_CreateRGBSurface(SDL_SWSURFACE,world.w,world.h,32,0,0,0,0))
		, zoom_buffer_(SDL_CreateRGBSurface(SDL_SWSURFACE,world.w/4,world.h/4,32,0,0,0,0))
		, objects_()
		, camera_(0,0)
		, zoom_(1)
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
	screen_.make_all_black();
	buffer_.clear();
	int counter = 0;
	foreach(object* obj, objects_)
	{
		obj->draw(buffer_);
		++counter;
		//debug
		#if 0
		if(counter >= 6)
			break;
		#endif
	}
	if(zoom_ < 1)
	{
		buffer_.scale_blit(zoom_buffer_,zoom_buffer_.width(),zoom_buffer_.height());
		zoom_buffer_.blit(screen_,point(-camera_.x/4,-camera_.y/4));
	}
	else
	{
		buffer_.blit(screen_,point(-camera_.x,-camera_.y));
	}
	screen_.flip();
}
