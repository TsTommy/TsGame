#include "screen_object.h"

screen_object::screen_object(point const& pos, char const* filename)
		: pos_(pos)
		, anim_(filename)
		, curr_anim_seq_()
{
}

screen_object::screen_object(point const& pos, std::string const& filename)
		: pos_(pos)
		, anim_(filename)
		, curr_anim_seq_()
{
}

void screen_object::draw(screen_t& s) const
{
	anim_.draw(s,pos_);
}

void screen_object::on_frame(Uint32 curr_time)
{
	anim_.on_frame(curr_time);
}

void screen_object::set_anim_mode(std::string const& anim)
{
	if(curr_anim_seq_ == anim)
		return;

	curr_anim_seq_ = anim;

	anim_.start(anim);
}

