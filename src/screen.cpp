#include <cassert>

#include "foreach.h"
#include "path.h"
#include "screen.h"
#include "screen_object.h"

screen::screen()
		: base_t()
		, screen_(SDL_SetVideoMode(640,480,32,SDL_SWSURFACE))
{
	assert(screen_);
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
	SDL_Rect temp = make_SDL_Rect(x,y);
	SDL_BlitSurface(&s,NULL,screen_,&temp);
}

void screen::draw()
{
	SDL_FillRect(screen_,&screen_->clip_rect,SDL_MapRGB(screen_->format,0xFF,0xFF,0xFF));
	foreach(screen_object* s, *this)
		s->draw(*this);
	SDL_Flip(screen_);
}

