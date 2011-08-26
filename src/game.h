#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include "box.h"
#ifdef BOX
	class screen;
#else
	#include "screen.h"
#endif

struct scoped_sdl {
	scoped_sdl() {if(SDL_Init(SDL_INIT_EVERYTHING)<0) throw 0;}
	~scoped_sdl() {SDL_Quit();}
};

class game
		: private scoped_sdl
{
public:
	game();
	void play();

private:
	void do_event_loop();
	int frame_interval() const {return 16;}

	box<screen> screen_;
};

#endif //GAME_H_INCLUDED
