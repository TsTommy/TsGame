#include "animation.h"

#include "data.h"
#include "foreach.h"
#include "path.h"

animation::animation(data const& d)
		: seq_()
		, curr_seq_()
		, curr_frame_()
		, frame_start_time_()
{
	init(d);
}

animation::animation(char const* filename)
		: seq_()
		, curr_seq_()
		, curr_frame_()
		, frame_start_time_()
{
	init(filename);
}

animation::animation(std::string const& filename)
		: seq_()
		, curr_seq_()
		, curr_frame_()
		, frame_start_time_()
{
	init(filename);
}

void animation::draw(screen_t& s, point const& pos) const
{
	assert(seq_.find(curr_seq_) != seq_.end());
	sequence::frame f = seq_.find(curr_seq_)->second.frames[curr_frame_];
	f.img.draw(s,point(pos.x-f.hotspot.x,pos.y-f.hotspot.y));
}

void animation::on_frame(Uint32 curr_time)
{
	sequence& curr_seq = seq_[curr_seq_];
	while(static_cast<int>(curr_seq.frames[curr_frame_].dur) <= static_cast<int>(curr_time)-static_cast<int>(frame_start_time_))
	{
		frame_start_time_ += curr_seq.frames[curr_frame_].dur;
		if(frame_start_time_ > 1000000)
			throw 0;
		curr_frame_ = (curr_frame_+1) % curr_seq.frames.size();
	}
};

void animation::start(std::string seq)
{
	curr_seq_ = seq;
	curr_frame_ = 0;
	frame_start_time_ = SDL_GetTicks();
	if(frame_start_time_ > 1000000)
		throw 0;
	assert(seq_.find(curr_seq_) != seq_.end());
}

/*private*/
void animation::init(data const& d)
{
	foreach(data::all_children_const_iterator::value_type const& seq_data, d.all_children())
		seq_[seq_data.first] = sequence(*seq_data.second);
	start(seq_.begin()->first);
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
animation::sequence::sequence()
		: frames()
	{}

animation::sequence::sequence(data const& d)
		: frames()
{
	foreach(data const& frame_data, d.child_range("frame"))
		frames.push_back(frame(frame_data));
}

//==========================
//animation::sequence::frame
animation::sequence::frame::frame(data const& d)
		: img(IMAGE(d["image"]))
		, dur(d.int_value("duration"))
		, hotspot(d.child("hotspot").int_value("x"),d.child("hotspot").int_value("y"))
	{}
