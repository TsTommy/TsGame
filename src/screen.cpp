#include <cassert>

#include "foreach.h"
#include "path.h"
#include "screen.h"

screen::screen()
		: screen_(SDL_SetVideoMode(640,480,32,SDL_SWSURFACE))
{
	assert(screen_);
	SDL_Surface* loaded = SDL_LoadBMP(IMAGE("hello.bmp"));
	assert(loaded);
	images_.insert(loaded);
	SDL_BlitSurface(loaded,NULL,screen_,NULL);
	SDL_Flip(screen_);
}

screen::~screen()
{
	foreach(SDL_Surface* s, images_)
	{
		assert(s);
		SDL_FreeSurface(s);
	}
}

static SDL_Rect make_SDL_Rect(int x, int y)
{
	SDL_Rect result;
	result.x = x;
	result.y = y;
	return result;
}

void screen::blit(SDL_Surface& s, int x, int y)
{
	SDL_BlitSurface(&s,NULL,screen_,&make_SDL_Rect(x,y));
}

void screen::draw()
{
	SDL_Flip(screen_);
}

