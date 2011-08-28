#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SDL/SDL.h>
#include <set>
#include "box.h"
#ifdef BOX
	class screen_object;
#else
	#include "screen_object.h"
#endif

class screen
		: public std::set<box<screen_object> >
{
	typedef std::set<box<screen_object> > base_t;

public:
	screen();

	void blit(SDL_Surface&, int x, int y);
	void draw();

	using base_t::insert;
	using base_t::erase;

private:
	SDL_Surface* screen_;
	std::set<screen_object*> objects_;
};

#endif //SCREEN_H_INCLUDED
