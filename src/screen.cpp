#include "foreach.h"
#include "image.h"
#include "screen_object.h"

#include "screen.h"

template<typename Tag>
screen<Tag>::screen()
		: screen_()
		, objects_()
	{}

template<typename Tag>
void screen<Tag>::draw()
{
	foreach(object* obj, objects_)
		obj->draw();
}

template<typename Tag>
void screen<Tag>::add(object& obj)
{
	objects_.insert(&obj);
}

template<typename Tag>
void screen<Tag>::remove(object& obj)
{
	objects_.erase(&obj);
}

template screen<normal_tag>;
template screen<isolated_tag>;
