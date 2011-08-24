#include "game.h"
#include "screen.h"
#include "screen_object.h"

game::game()
		: scoped_sdl()
		, screen_()
	{}

/*private*/
void game::do_event_loop()
{
	screen_object player(screen_,0,0);

	for(Uint32 prev_ticks = 0; ; )
	{
		for(SDL_Event ev; SDL_PollEvent(&ev); )
		{
			switch(ev.type)
			{
			case SDL_QUIT:
				return;
			}
		}

		Uint32 ticks = SDL_GetTicks();
		if(prev_ticks/frame_interval() == ticks/frame_interval())
			continue;
		prev_ticks = ticks;

		player.move_to(player.x()+1,player.y());

		screen_->draw();
	}
}

void game::play()
{
	do_event_loop();
}

