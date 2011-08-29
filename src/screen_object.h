#ifndef SCREEN_OBJECT_H_INCLUDED
#define SCREEN_OBJECT_H_INCLUDED

#include "box.h"
#include "tag.h"

template<typename Tag = normal_tag>
class screen_object
{
public:
	void draw();

private:
};

template<>
class screen_object<stub_tag>
{
public:
	screen_object();
	void draw();

	size_t draw_count();

private:
	size_t counter_;
};

#endif //SCREEN_OBJECT_H_INCLUDED
