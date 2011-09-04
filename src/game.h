#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <cassert>
#include <set>
#include <boost/shared_ptr.hpp>
#include <SDL/SDL.h>
#include "keyboard.h"
#include "platform.h"
#include "player.h"
#include "scoped_sdl.h"
#include "screen.h"

class game
		: private scoped_sdl
{
public:
	game();

	void play();

private:
	void load_platforms(data const&);

	screen screen_;
	keyboard keyb_;
	player player_;
	std::set<platform,platform_comparator> plats_;
};

#endif //GAME_H_INCLUDED
