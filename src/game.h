#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <cassert>
#include <SDL/SDL.h>
#include "keyboard.h"
#include "player.h"
#include "screen.h"

struct scoped_sdl {
	scoped_sdl() {bool success = (SDL_Init(SDL_INIT_EVERYTHING) >= 0); assert(success);}
	~scoped_sdl() {SDL_Quit();}
};

class game
		: private scoped_sdl
{
public:
	game();

	void play();

private:
	screen screen_;
	keyboard keyb_;
	player player_;
};

#endif //GAME_H_INCLUDED
