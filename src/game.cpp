#include "game.h"

#include <iostream>
#include "dimensions.h"
#include "path.h"
#include "screen.h"
#include "screen_object.h"


game::game()
		: scoped_sdl()
		, screen_(dimensions(640,480))
		, player_(point(50,50),screen_)
	{}

namespace {

class frame_regulator {
public:
	frame_regulator(unsigned interval)
			: frame_num_(0)
			, interval_(interval)
		{}

	bool time_for_next_frame()
	{
		bool result;
		unsigned new_frame_num = SDL_GetTicks()/interval_;
		result = (frame_num_ < new_frame_num);
		frame_num_ = new_frame_num;
		return result;
	}

private:
	unsigned frame_num_;
	unsigned interval_;
};

} //end anonymous namespace

void game::play()
{
	frame_regulator fr(16);

	//event loop
	for(;;)
	{
		//process an event
		SDL_Event ev;
		if(SDL_PollEvent(&ev))
		{
			if(ev.type==SDL_QUIT)
				return;
			else if(ev.type==SDL_KEYDOWN)
				if(ev.key.keysym.sym==SDLK_SPACE)
					player_.on_jump();
		}

		//possibly process a frame
		if(fr.time_for_next_frame())
		{
			//update state
			player_.on_frame();

			//output
			screen_.draw();
		} //end process a frame
	} //end event loop
}


#if 0
{
	screen_->insert(screen_object(0,0));
	screen_object& player = **screen_->begin();

	platform hard_code[] = {
		{50,50,100,50}
		, {50,100,100,100}
	};
	std::set<platform> platforms;
	platforms.insert(hard_code,hard_code+sizeof(hard_code)/sizeof(platform));

	std::queue<int> frame_ticks;
	int interval = frame_interval();
	std::stringstream caption;

	Uint8* keyboard;

	for(Uint32 prev_ticks = 0; ; )
	{
		for(SDL_Event ev; SDL_PollEvent(&ev); )
		{
			switch(ev.type)
			{
			case SDL_QUIT:
				return;
			case SDL_KEYUP:
				switch(ev.key.keysym.sym)
				{
				case SDLK_SPACE:
					if(!keyboard[SDLK_DOWN])
						player.on_jump(platforms);
					break;
				}
				break;
			}
			break; //experimental -- delete this line if you want
		}

		Uint32 ticks = SDL_GetTicks();
		if(prev_ticks/interval == ticks/interval)
			continue;
		prev_ticks = ticks;
		frame_ticks.push(ticks);
		while(frame_ticks.size() > 10)
			frame_ticks.pop();
		interval = frame_interval();
		if(frame_ticks.size() >= 2)
		{
			int frame_rate = 1000*(frame_ticks.size()-1)/(frame_ticks.back()-frame_ticks.front());
			caption.str(std::string());
			caption << frame_rate;
			SDL_WM_SetCaption(caption.str().c_str(),NULL);
		}

		keyboard = SDL_GetKeyState(NULL);
		player.on_frame(keyboard,platforms);

		screen_->draw();
	}
}
#endif
