#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <string>
#include <SDL/SDL.h>

#include "box.h"
#ifdef BOX
#else
#endif

class screen;

class animation
{
public:
	animation(std::string const& image_path);
	void draw(screen&, int x, int y) const;

private:
	SDL_Surface* image_;
};

#endif //ANIMATION_H_INCLUDED
