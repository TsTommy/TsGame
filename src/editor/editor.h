#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include "data.h"
#include "keyboard.h"
#include "platform.h"
#include "scoped_sdl.h"
#include "screen.h"
#include "screen_object.h"

class editor
		: private scoped_sdl
{
public:
	editor();
	~editor();

	void run();

private:
	void save(std::string const&);
	void load(std::string const&);
	bool command_prompt();
	void select(boost::shared_ptr<platform>);

	screen screen_;
	keyboard keyb_;
	std::string curr_plat_type_;
	std::set<boost::shared_ptr<platform> > plats_;
	std::map<std::string,vec> plat_shape_;
	std::map<boost::shared_ptr<platform>,std::string> plat_type_;
	data plat_type_data_;
	boost::shared_ptr<platform> selected_;
	screen_object left_select_;
	screen_object right_select_;
	std::string curr_filename_;
};

#endif //EDITOR_H_INCLUDED
