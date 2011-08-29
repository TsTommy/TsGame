#include "tag.h"

#include "screen_object.h"

template<typename Tag>
void screen_object<Tag>::draw()
{
}

//stub definitions
screen_object<stub_tag>::screen_object()
		: counter_(0)
	{}

void screen_object<stub_tag>::draw()
{
	++counter_;
}

size_t screen_object<stub_tag>::draw_count()
{
	return counter_;
}

template screen_object<normal_tag>;
template screen_object<isolated_tag>;
