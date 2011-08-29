#include "image.h"

template<typename Tag>
image<Tag>::image()
	{}

template<typename Tag>
void image<Tag>::draw()
	{}

//stub definition
image<stub_tag>::image()
	{}

void image<stub_tag>::draw()
{
	++counter_;
}

size_t image<stub_tag>::draw_count()
{
	return counter_;
}

template image<normal_tag>;
template image<isolated_tag>;