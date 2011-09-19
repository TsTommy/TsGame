#include "inanimate.h"

#include <set>
#include "foreach.h"
#include "platform.h"
#include "screen.h"

inanimate::inanimate(vec pos, double mass, char const* filename, screen& s)
		: pos_(pos)
		, veloc_(0,0)
		, mass_(mass)
		, body_(point(pos_),filename)
		, screen_(s)
{
	s.add(body_);
}

inanimate::inanimate(vec pos, double mass, std::string const& filename, screen& s)
		: pos_(pos)
		, veloc_(0,0)
		, mass_(mass)
		, body_(point(pos_),filename)
		, screen_(s)
{
	s.add(body_);
}

static inline vec approach(vec const& val, vec const& target, vec const& speed)
{
	if(val.x == 5)
		int debug = 0;

	if(val.x > target.x-speed.x)
	{
		if(val.x > target.x+speed.x)
			return val-speed;
		else return val + (target-val).project(speed);
	}
	else
	{
		return val+speed;
	}
}

static int const frame_interval = 16;

void inanimate::on_frame(std::set<platform,platform_comparator> const& plats)
{
	//accelerate
	{
		//x
		vec const x_axis = (is_on_floor()? standing_on_->direction().normalized(): vec(1,0));
		vec const GROUND_ACCEL(frame_interval*frame_interval/256.0,0);
		vec const AIR_ACCEL(0,0);
		vec const ACCEL = (is_on_floor()? GROUND_ACCEL: AIR_ACCEL);
		vec const accel = ACCEL.project(x_axis);
		vec const old_veloc = veloc_;

		veloc_ = approach(veloc_,vec(0,0),accel);

		//y
//		if(!is_on_floor())
//		{
			double const TERMINAL_VEL = frame_interval*40.0/16.0;
			veloc_.y += frame_interval*frame_interval*(1-(veloc_.y/TERMINAL_VEL))/256.0;
//		}
	}

	//walked off a platform?
	if(standing_on_)
	{
		if(standing_on_->is_right_of(pos_))
			standing_on_ = standing_on_->left_neighbor();
		else if(standing_on_->is_left_of(pos_))
			standing_on_ = standing_on_->right_neighbor();
	}

	//fell onto a platform?
	vec new_veloc = veloc_;
	foreach(platform const& plat, plats)
	{
		bool altered = false;
		platform const* next_plat = plat.alter_trajectory(pos_,veloc_,new_veloc,altered);
		if(altered)
		{
			standing_on_ = &plat;
			while(next_plat)
			{
				platform const* next_next_plat = next_plat->alter_trajectory(pos_,veloc_,new_veloc,altered);
				if(altered)
					standing_on_ = next_plat;
				else
					break;

				next_plat = next_next_plat;
			}
			break;
		}
	}

	//move
	pos_ += veloc_;
	veloc_ = new_veloc;

	//debug
	if(pos_.x < 0)
	{
		pos_.x = 0;
		veloc_.x = 0;
	}
}
