#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include <cassert>
#include <SDL/SDL.h>
#include "dimensions.h"
#include "point.h"

///wrapper class for SDL_Surface*
///DOES NOT own the underlying pointer
class surface
{
public:
	surface(SDL_Surface* p): p_(p)
		{assert(p_);}

	int width() const {return p_->w;}
	int height() const {return p_->h;}

	void blit(surface& dst, point const& p) const
	{
		SDL_Rect r;   r.x=p.x;   r.y=p.y;
		SDL_BlitSurface(p_,NULL,dst.p_,&r);
	}

	void clear()
		{SDL_FillRect(p_,&p_->clip_rect,SDL_MapRGB(p_->format,0xFF,0xFF,0xFF));}
	void make_all_black()
		{SDL_FillRect(p_,&p_->clip_rect,SDL_MapRGB(p_->format,0x0,0x0,0x0));}
	void flip()
		{SDL_Flip(p_);}
	void free()
		{SDL_FreeSurface(p_);}
	surface scale_blit(surface dst, Uint16 new_w, Uint16 new_h);

private:
	SDL_Surface* const p_;
};

#endif //SURFACE_H_INCLUDED
