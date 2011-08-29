#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SDL/SDL.h>
#include <set>

#include "image.box"
#include "screen_object.fwd"
#include "tag.h"

template<typename Tag = normal_tag>
class screen
{
public:
	typedef screen_object<typename Tag::neighbor_tag> object;

	screen();

	void draw();

	void add(object& x);
	void remove(object& x);

private:
	box<image<typename Tag::neighbor_tag> > screen_;
	std::set<object*> objects_;
};

#endif //SCREEN_H_INCLUDED
