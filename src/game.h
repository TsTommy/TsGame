#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "debug.h"
#ifdef DEBUG
	class screen;
#else
	#include "screen.h"
#endif

class game
{
public:
	game();
	void play();

private:
	box<screen> screen_;
};

#endif //GAME_H_INCLUDED
