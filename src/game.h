#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <cassert>
#include <set>
#include <boost/shared_ptr.hpp>
#include <SDL/SDL.h>
#include "inanimate.h"
#include "keyboard.h"
#include "platform.h"
#include "player.h"
#include "scoped_sdl.h"
#include "scoped_ttf.h"
#include "screen.h"

class game
		: private scoped_sdl
//		, private scoped_ttf
{
public:
	game();

	void play();

private:
	void load_level(data const&);

	screen screen_;
	keyboard keyb_;
	player player_;
	std::set<platform,platform_comparator> plats_;
	std::set<boost::shared_ptr<inanimate> > inanimates_;
};

#endif //GAME_H_INCLUDED
