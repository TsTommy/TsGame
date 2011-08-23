#include <cassert>

#include "foreach.h"
#include "screen.h"

screen::screen()
		: screen_(*SDL_SetVideoMode(640,480,32,SDL_SWSURFACE))
{
	SDL_Surface* loaded = SDL_LoadBMP("../../data/images/hello.bmp");
	assert(loaded);
	images_.insert(loaded);
	SDL_BlitSurface(loaded,NULL,&screen_,NULL);
	SDL_Flip(&screen_);
}

screen::~screen()
{
	foreach(SDL_Surface* s, images_)
	{
		assert(s);
		SDL_FreeSurface(s);
	}
}
