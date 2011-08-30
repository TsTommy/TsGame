#include "dimensions.h"
#include "path.h"
#include "screen.h"
#include "screen_object.h"

#include "game.h"

game::game()
		: scoped_sdl()
		, screen_(dimensions(640,480))
		, player_(point(50,50),IMAGE("hello.bmp"))
	{}

void game::play()
{
	screen_.add(&player_);
	screen_.draw();
	for(;;)
		SDL_PollEvent(NULL);
}

