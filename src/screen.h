#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SDL/SDL.h>
#include <set>
#include "image.h"
#include "surface.h"

class screen_object;

class screen
{
public:
	typedef screen_object object;

	screen(dimensions const&);

	void draw();

	void add(object&);
	void remove(object&);

private:
	surface screen_;
	std::set<object*> objects_;
};

#endif //SCREEN_H_INCLUDED
