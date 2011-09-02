#include "animation.h"

#include "data.h"
#include "foreach.h"

animation::animation(data const& d)
		: seq_()
{
	init(d);
}

animation::animation(char const* filename)
		: seq_()
{
	init(filename);
}

animation::animation(std::string const& filename)
		: seq_()
{
	init(filename);
}

void animation::draw(screen_t& s, point const& pos) const
{
	//img_.draw(s,pos);
}

/*private*/
void animation::init(data const& d)
{
	foreach(data::all_children_const_iterator::value_type const& seq_data, d.all_children())
		seq_[seq_data.first] = sequence(*seq_data.second);
}

/*private*/
void animation::init(char const* filename)
{
	init(data(filename).child("animation"));
}

/*private*/
void animation::init(std::string const& filename)
{
	init(filename.c_str());
}

//===================
//animation::sequence
animation::sequence::sequence(data const& d)
		: frames_()
{
	size_t counter = 0;
	foreach(data const& frame_data, d.child_range("frame"))
		frames_[counter++] = frame(frame_data);
}

//==========================
//animation::sequence::frame
animation::sequence::frame::frame(data const& d)
		: img(d["image"])
		, dur(d.int_value("duration"))
	{}
