#include "game.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "dimensions.h"
#include "frame_rate_tracker.h"
#include "path.h"
#include "screen.h"
#include "screen_object.h"


game::game()
		: scoped_sdl()
		, screen_(dimensions(800,600))
		, keyb_()
		, player_(point(50,50),screen_)
		, plats_()
	{}

namespace {

class frame_regulator {
public:
	frame_regulator(unsigned interval)
			: frame_num_(0)
			, interval_(interval)
			, curr_time_(0)
		{}

	bool time_for_next_frame()
	{
		bool result;
		curr_time_ = SDL_GetTicks();
		unsigned new_frame_num = curr_time_/interval_;
		result = (frame_num_ < new_frame_num);
		frame_num_ = new_frame_num;
		return result;
	}

	Uint32 time() const {return curr_time_;}

private:
	Uint32 curr_time_;
	unsigned frame_num_;
	unsigned interval_;
};

} //end anonymous namespace

static inline point toward(point const& src, point const& dst)
{
	int x = src.x + ((dst.x-400)-src.x)/20;
	int y = src.y + ((dst.y-500)-src.y)/20;
	return point(x,y);
}

void game::play()
{
	//instructions in console window
	std::cout << "Arrow keys to move.\n"
			<< "Hold shift to run.\n"
			<< "Press spacebar to jump.\n";

	//hard-coded platforms
	std::vector<boost::shared_ptr<platform> > temp_plats;
	boost::shared_ptr<platform> plat(new platform(vec(-100,880),vec(1600,0),ANIMATION("floor.data"),screen_));
	temp_plats.push_back(plat);
	plat.reset(new platform(vec(600,700),vec(200,0),ANIMATION("flat.data"),screen_));
	temp_plats.push_back(plat);
	plat.reset(new platform(vec(800,700),vec(200,-100),ANIMATION("slant.data"),screen_));
	temp_plats.push_back(plat);
	plat.reset(new platform(vec(1000,600),vec(200,0),ANIMATION("flat.data"),screen_));
	temp_plats.push_back(plat);
	plat.reset(new platform(vec(1500,880),vec(50,-500),ANIMATION("wall.data"),screen_));
	temp_plats.push_back(plat);
	temp_plats[0]->set_right_neighbor(&*temp_plats[4]);
	temp_plats[1]->set_right_neighbor(&*temp_plats[2]);
	temp_plats[2]->set_left_neighbor(&*temp_plats[1]);
	temp_plats[2]->set_right_neighbor(&*temp_plats[3]);
	temp_plats[3]->set_left_neighbor(&*temp_plats[2]);
	temp_plats[4]->set_left_neighbor(&*temp_plats[0]);
	plats_.insert(temp_plats.begin(),temp_plats.end());
	//debug
	#if 0
	for(int i = 0; i<300; ++i)
	{
		plat.reset(new platform(vec(300,700),vec(400,700),ANIMATION("flat.data"),screen_));
		plats_.insert(plat);
	}
	#endif

	frame_regulator fr(16);
	frame_rate_tracker frt;

	//event loop
	for(;;)
	{
		//process an event
		SDL_Event ev;
		if(SDL_PollEvent(&ev))
		{
			if(ev.type==SDL_QUIT)
				return;
			//else if(ev.type==SDL_KEYUP) //non-debug
			else if(ev.type==SDL_KEYDOWN) //debug
				if(ev.key.keysym.sym==SDLK_SPACE)
					player_.on_jump(keyb_);
//				else if(ev.key.keysym.sym==SDLK_RETURN)
//					{player_.on_frame(keyb_,plats_);   screen_.draw();}
		}

//#if 0
		//possibly process a frame
		if(fr.time_for_next_frame())
		{
			frt.on_frame(fr.time());

			//update state
			player_.on_frame(keyb_,plats_);
			screen_.on_frame(fr.time());

			//output
			screen_.move_camera(toward(screen_.camera(),point(player_.pos())));
			screen_.draw();
			SDL_WM_SetCaption(boost::lexical_cast<std::string>(frt.frame_rate()).c_str(),NULL);
		}
//#endif
	}
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
