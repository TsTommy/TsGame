#include "player.h"

#include <cmath>
#include "foreach.h"
#include "keyboard.h"
#include "path.h"
#include "platform.h"
#include "screen.h"

player::player(point const& p, screen& s)
		: body_(p,ANIMATION("player.data"))
		, pos_(p)
		, veloc_(0,0)
		, jump_strength_(0)
		, standing_on_(NULL)
		, screen_(s)
{
	s.add(body_);
	update_animation();
}

player::~player()
{
	screen_.remove(body_);
}

static int const FLOOR = 440;

/*private*/
bool player::is_on_floor() const
{
	return standing_on_ != NULL;
}

template<typename num>
static inline num approach(num val, num target, num speed)
{
	if(val > target-speed)
		return std::max(target,val-speed);
	else
		return val+speed;
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

static inline int cap(int val, int min, int max)
	{return std::max(min,std::min(val,max));}

template<typename num>
static inline bool in_range(num val, num min, num max)
	{return val>=min && val<max;}

/*private*/
void player::move_to(vec const& v)
{
	pos_ = v;
	body_.move_to(point(pos_));
}

static int const frame_interval = 16;

void player::on_frame(keyboard const& k, std::set<platform,platform_comparator> const& plats)
{
	//accelerate
	{
		//x
		vec const x_axis = (is_on_floor()? standing_on_->direction().normalized(): vec(1,0));
		vec const GROUND_ACCEL(frame_interval*frame_interval/256.0,0);
		vec const AIR_ACCEL = GROUND_ACCEL/4.0;
		vec const ACCEL = (is_on_floor()? GROUND_ACCEL: AIR_ACCEL);
		vec const accel = ACCEL.project(x_axis);
		double const SPEED = k[SDLK_LSHIFT]? frame_interval*15.0/16.0: frame_interval*5.0/16.0;
		vec const old_veloc = veloc_;
		if(k[SDLK_LEFT] == k[SDLK_RIGHT])
			veloc_ = approach(veloc_,vec(0,0),accel);
		else if(k[SDLK_LEFT])
			veloc_ = approach(veloc_,x_axis*(-SPEED),accel);
		else //(k[SDLK_RIGHT])
			veloc_ = approach(veloc_,x_axis*(SPEED),accel);
		if((veloc_-old_veloc).mag() > 1)
			int debug = 0;

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
	move_to(pos_ + veloc_);
	veloc_ = new_veloc;

	if(is_on_floor())
	{
		//calculate jump strength
		if(k[SDLK_SPACE])
			jump_strength_ = std::min(jump_strength_+8,225u);
		else //stopped charging up jump
			jump_strength_ = 0;
	}
	else //airborne
		jump_strength_ = 0; //can't chargeup jump

	//debug
	if(pos_.x < 0)
	{
		pos_.x = 0;
		veloc_.x = 0;
	}

	update_animation(); //private helper fcn
}

/*private*/
void player::update_animation()
{
	std::string anim;
#if 1
	if(is_on_floor())
	{
		if(abs(veloc_.x) < 1)
			anim = "standing";
		else
		{
			facing_right_ = (veloc_.x > 0);
			if(abs(veloc_.x) < 6)
				anim = "walking";
			else //moving
				anim = "running";
		}
	}
	else //airborne
	{
		if(veloc_.y < 0) //rising
			anim = "jump";
		else //falling
			anim = "fall";
	}

//	anim = anim + (facing_right_? "_right": "_left");
#else
	anim = "standing";
#endif
	body_.set_anim_mode(anim);

}

void player::on_jump(keyboard const& k)
{
	jump_strength_ = 500u; //debug
	if(is_on_floor() && !k[SDLK_DOWN])
	{
		veloc_ += standing_on_->normal() * std::sqrt(static_cast<double>(jump_strength_));
		standing_on_ = NULL;
	}
}

