#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <cassert>
#include <set>
#include <boost/shared_ptr.hpp>
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
	std::set<boost::shared_ptr<platform> > plats_;
};

#endif //GAME_H_INCLUDED
