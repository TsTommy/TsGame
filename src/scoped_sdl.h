#ifndef SCOPED_SDL_H_INCLUDED
#define SCOPED_SDL_H_INCLUDED

#include <cassert>
#include <SDL/SDL.h>

struct scoped_sdl {
	scoped_sdl() {bool success = (SDL_Init(SDL_INIT_EVERYTHING) >= 0); assert(success);}
	~scoped_sdl() {SDL_Quit();}
};

#endif //SCOPED_SDL_H_INCLUDED
