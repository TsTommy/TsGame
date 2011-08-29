#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "box.h"
#include "tag.h"

template<typename Tag = normal_tag>
class image
{
public:
	image();
	void draw();

private:
};

template<>
class image<stub_tag>
{
public:
	image();
	void draw();

	size_t draw_count();

private:
	size_t counter_;
};

#endif //IMAGE_H_INCLUDED
