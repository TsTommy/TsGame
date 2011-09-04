#include "editor.h"

#include <fstream>
#include <boost/lexical_cast.hpp>
#include "data.h"
#include "dimensions.h"
#include "foreach.h"
#include "frame_rate_tracker.h"
#include "frame_regulator.h"
#include "path.h"

editor::editor()
		: scoped_sdl()
		, screen_(dimensions(800,600),dimensions(3000,1000))
		, curr_plat_type_()
		, plats_()
		, plat_shape_()
		, plat_type_()
		, plat_type_data_(PATH("data/platforms.data"))
		, selected_()
		, left_select_(point(-100,-100),ANIMATION("editor/left_select.data"))
		, right_select_(point(-100,-100),ANIMATION("editor/right_select.data"))
		, curr_filename_()

{
	//construct
	screen_.add(left_select_);
	screen_.add(right_select_);

	//auto-load
	load("temp");
}

editor::~editor()
{
	//auto-save
	save("temp");

	//destruct
	screen_.remove(left_select_);
	screen_.remove(right_select_);
}

void editor::save(std::string const& arg)
{
	std::string filename = LEVEL(arg+".data");
	std::ofstream file(filename.c_str());
	if(file)
	{
		file <<"platform_types {"<< data(PATH("data/platforms.data")) <<"}";
		foreach(boost::shared_ptr<platform> const& plat, plats_)
			file <<"platform { type = \""<< plat_type_[plat] <<"\""
					<<"x = \""<< plat->left_pt().x <<"\" y = \""
					<< plat->left_pt().y <<"\"}";
	}
	else //failed to open file
		std::cout << "Failed to open "+filename+" for writing.\n";
}

void editor::load(std::string const& arg)
{
	std::string filename = LEVEL(arg+".data");
	std::ifstream file(filename.c_str());
	if(file)
	{
		//auto-save old data
		if(arg!="temp") //don't overwrite it if that's what we are loading, though!
			save("temp");

		//clear old data
		select(boost::shared_ptr<platform>());
		plats_.clear();
		plat_type_.clear();

		//load new data
		{
			data d(file);

			std::map<std::string,vec> shape;
			foreach(data::all_children_const_iterator::value_type type_data, d.child("platform_types").all_children())
				shape[type_data.first] = vec(type_data.second->double_value("x"),type_data.second->double_value("y"));

			foreach(data const& plat_data, d.child_range("platform"))
			{
				std::string type = plat_data["type"];
				vec pos = vec(plat_data.double_value("x"),plat_data.double_value("y"));
				boost::shared_ptr<platform> to_insert(new platform(pos,shape[type],ANIMATION(type+".data"),screen_));
				plats_.insert(to_insert);
				plat_type_[to_insert] = type;
			}
		}
	}
	else
		std::cout <<"Failed to open "+filename+" for reading.\n";
}

//returns whether to quit
bool editor::command_prompt()
{
	for(;;)
	{
		std::cout << "\n"
				<< "Type 'help' for help.\n"
				<< "$ ";

		std::string input;
		std::getline(std::cin,input);

		//process command
		if(input == "help")
			std::cout << "Command list:\n"
					<< "  equip <T> - Sets <T> as the current type of platform to place\n"
					<< "  save      - Saves the current level\n"
					<< "  save <L>  - Saves the current level as '<L>.data'\n"
					<< "  load <L>  - Loads level data from '<L>.data'\n"
					<< "  quit      - Quit. The current data will be auto-saved in 'temp.data'\n"
					<< "  return    - continue working in the level editor\n"
					<< "  help      - get help\n";
		else if(input == "return")
		{
			std::cout << "RIGHT NOW, DO NOT TYPE."; //intentional lack of "\n"
			break;
		}
		else if(input == "equip")
			std::cout << "What type of platform would you like to equip?\n";
		else if(input.size() >= 6
				&& std::equal(input.begin(),input.begin()+6,"equip "))
		{
			std::string plat_type(input.begin()+6,input.end());
			if(plat_type_data_.has_child(plat_type))
			{
				curr_plat_type_ = plat_type;
				plat_shape_[plat_type] = vec(plat_type_data_.child(plat_type).double_value("x"),plat_type_data_.child(plat_type).double_value("y"));
				std::cout << "Success.\n";
			}
			else //unrecognized platform type
				std::cout <<"Sorry, I don't know of a '"<< plat_type <<"' type of platform.\n";
		}
		else if(input == "save")
		{
			if(curr_filename_.empty())
				std::cout << "What would you like to name your level?\n";
			else
			{
				save(curr_filename_);
				std::cout <<"Success.\n";
			}
		}
		else if(input.size() >= 5
				&& std::equal(input.begin(),input.begin()+5,"save "))
		{
			std::string argument(input.begin()+5,input.end());
			save(argument);
			curr_filename_ = argument;
			std::cout << "Success.\n";
		}
		else if(input == "load")
			std::cout << "What data would you like to load?\n";
		else if(input.size() >= 5
				&& std::equal(input.begin(),input.begin()+5,"load "))
		{
			std::string argument(input.begin()+5,input.end());
			load(argument);
			curr_filename_ = argument;
			screen_.draw();
			std::cout << "Success.\n";
		}
		else if(input == "quit")
		{
			save("temp"); //auto-save old data
			return true;
		}
		else if(input.empty())
			{}
		else
			std::cout << "Unrecognized command: '"+input+"'\n";

		//flush the event queue, ignoring all events
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
			{}
	}

	//flush the event queue, ignoring all events
	SDL_Event ev;
	while(SDL_PollEvent(&ev))
		{}

	return false;
}

void editor::select(boost::shared_ptr<platform> to_select)
{
	selected_ = to_select;
	if(to_select)
	{
		left_select_.move_to(point(to_select->left_pt()));
		right_select_.move_to(point(to_select->right_pt()));
	}
	else
	{
		left_select_.move_to(point(-100,-100));
		right_select_.move_to(point(-100,-100));
	}
}

void editor::run()
{
	std::cout << "Instructions:\n"
			<< "(1)  Press enter IN THE OTHER WINDOW to activate the command prompt\n"
			<< "     in THIS window.\n"
			<< "(2)  Type 'help'.\n"
			<< "(3)  Type 'equip flat'.\n"
			<< "(4)  Type 'return' and switch back to the editor window.\n"
			<< "(5)  Use the arrow keys to scroll around.\n"
			<< "(6)  Right click in the level editor to place the platform.\n"
			<< "(7)  Left click near the left end point of a platform to select it.\n"
			<< "(8)  Press Delete to delete the selected platform.\n"
			<< "(9)  Press enter and switch back to the command prompt.\n"
			<< "(10) Type 'save blah' to save the level in a file called 'blah.data'.\n"
			<< "(11) Type 'load blah' to load 'blah.data'. The current level data will be\n"
			<< "     automatically saved as 'temp.data'.\n"
			<< "(12) Type 'quit' to quit. The current level data will be automatically saved\n"
			<< "     as 'temp.data'.\n"
			<< "\n"
			<< "RIGHT NOW, DO NOT TYPE."; //intentional lack of "\n"

	frame_regulator fr(16);
	frame_rate_tracker frt;

	for(;;)
	{
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
		{
			if(ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if(ev.button.button == SDL_BUTTON_LEFT)
				{
					if(!plats_.empty())
					{
						vec mouse(ev.button.x+screen_.camera().x,ev.button.y+screen_.camera().y);
						boost::shared_ptr<platform> to_select = *plats_.begin();
						foreach(boost::shared_ptr<platform> const& plat, plats_)
							if((plat->left_pt()-mouse).mag() < (to_select->left_pt()-mouse).mag())
								to_select = plat;
						select(to_select);
					}
				}
				else if(ev.button.button == SDL_BUTTON_RIGHT)
				{
					if(!curr_plat_type_.empty())
					{
						point mouse_p(ev.button.x+screen_.camera().x,ev.button.y+screen_.camera().y);
						mouse_p.x = mouse_p.x - mouse_p.x%20;
						mouse_p.y = mouse_p.y - mouse_p.y%20;
						vec mouse = mouse_p;
						boost::shared_ptr<platform> new_plat(new platform(mouse,plat_shape_[curr_plat_type_],ANIMATION(curr_plat_type_+".data"),screen_));
						plats_.insert(new_plat);
						select(new_plat);
						plat_type_[new_plat] = curr_plat_type_;
					}
				}
			}
			else if(ev.type == SDL_KEYDOWN)
			{
				if(ev.key.keysym.sym == SDLK_DELETE)
				{
					plats_.erase(selected_);
					plat_type_.erase(selected_);
					select(boost::shared_ptr<platform>());
				}
				if(ev.key.keysym.sym == SDLK_RETURN)
					if(command_prompt()) //returns whether to quit
						return; //quit
			}
			else if(ev.type == SDL_QUIT)
				return;
		}

		if(fr.time_for_next_frame())
		{
			//track frame rate
			frt.on_frame(fr.time());

			//move camera
			{
				int const SPEED = 20;
				point camera = screen_.camera();
				if(keyb_[SDLK_LEFT])
					camera.x -= SPEED;
				if(keyb_[SDLK_RIGHT])
					camera.x += SPEED;
				if(keyb_[SDLK_UP])
					camera.y -= SPEED;
				if(keyb_[SDLK_DOWN])
					camera.y += SPEED;
				screen_.move_camera(camera);
			}

			//output
			screen_.draw();
			SDL_WM_SetCaption(boost::lexical_cast<std::string>(frt.frame_rate()).c_str(),NULL);
		}
	}
}

