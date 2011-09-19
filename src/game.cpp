#include "game.h"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include "data.h"
#include "dimensions.h"
#include "foreach.h"
#include "frame_rate_tracker.h"
#include "frame_regulator.h"
#include "path.h"
#include "platform.h"
#include "screen.h"
#include "screen_object.h"


game::game()
		: scoped_sdl()
//		, scoped_ttf()
		, screen_(dimensions(800,600),dimensions(3000,1000))
		, keyb_()
		, player_(point(50,50),screen_)
		, plats_()
	{}

static inline point toward(point const& src, point const& dst)
{
	int x = src.x + ((dst.x-400)-src.x)/10;
	int y = src.y + ((dst.y-500)-src.y)/10;
	return point(x,y);
}

/*private*/
void game::load_platforms(data const& d)
{
	std::map<std::string,vec> shape;
	std::map<vec,platform*,vec_comparator> left_pt;
	std::map<vec,platform*,vec_comparator> right_pt;
	foreach(data::all_children_const_iterator::value_type type_data, d.child("platform_types").all_children())
		shape[type_data.first] = vec(type_data.second->double_value("x"),type_data.second->double_value("y"));

	foreach(data const& plat_data, d.child_range("platform"))
	{
		std::string type = plat_data["type"];
		vec pos = vec(plat_data.double_value("x"),plat_data.double_value("y"));
		if(left_pt.find(pos) != left_pt.end()
				|| right_pt.find(pos+shape[type]) != right_pt.end())
			throw "illegal platform overlap";
		std::pair<std::set<platform,platform_comparator>::iterator,bool> info = plats_.insert(platform(pos,shape[type],ANIMATION(type+".data"),screen_));
		if(!info.second)
			throw "set insertion failure";
		platform* new_plat = &*info.first;
		left_pt[pos] = right_pt[pos+shape[type]] = new_plat;
		if(left_pt.find(pos+shape[type]) != left_pt.end())
		{
			new_plat->set_right_neighbor(left_pt[pos+shape[type]]);
			left_pt[pos+shape[type]]->set_left_neighbor(new_plat);
		}

		if(right_pt.find(pos) != right_pt.end())
		{
			new_plat->set_left_neighbor(right_pt[pos]);
			right_pt[pos]->set_right_neighbor(new_plat);
		}
	}

	//debug
	#if 0
	for(int i = 0; i<300; ++i)
		plats_.insert(platform(vec(300,700),vec(400,700),ANIMATION("flat.data"),screen_));
	#endif
}

void game::play()
{
	//instructions in console window
	std::cout << "Arrow keys to move.\n"
			<< "Hold shift to run.\n"
			<< "Press spacebar to jump.\n";

	load_platforms(data(PATH("data/level.data")));

	frame_regulator fr(16);
	frame_rate_tracker frt;

	//event loop
	for(;;)
	{
		//process an event
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
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

		//possibly process a frame
		if(fr.time_for_next_frame())
		{
			frt.on_frame(fr.time());

			//update state
			player_.on_frame(keyb_,plats_);
			screen_.on_frame(fr.time());

			//bounds check
			if(player_.pos().y > screen_.size().h+1000)
				return;

			//output
			screen_.move_camera(toward(screen_.camera(),point(player_.camera_point())));
			screen_.draw();
			SDL_WM_SetCaption(boost::lexical_cast<std::string>(frt.frame_rate()).c_str(),NULL);
		}
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
