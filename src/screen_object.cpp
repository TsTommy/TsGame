#include <cmath>
#include <set>

#include "animation.h"
#include "foreach.h"
#include "path.h"
#include "platform.h"

#include "screen_object.h"

screen_object::screen_object(int x, int y)
		: x_(x)
		, y_(y)
		, xvel_(0)
		, yvel_(0)
		, animation_(IMAGE("hello.bmp"))
{
}

void screen_object::draw(screen& s) const
{
	animation_->draw(s,x_,y_);
}

static int const FLOOR = 440;

static inline bool collide(int,int,int,int,platform const&) {return false;}
static inline void snap_to(int,int,int,platform const&) {}
static inline bool on_floor(int,int, std::set<platform> const&) {return true;}

template<typename num>
static inline num approach(num val, num target, num speed)
{
	if(val > target-speed)
		return std::max(target,val-speed);
	else
		return val+speed;
}

static inline int cap(int val, int min, int max)
	{return std::max(min,std::min(val,max));}

void screen_object::on_frame(Uint8* keyboard, std::set<platform> const& plats)
{
	int const old_x = x_, old_y = y_;

	//accelerate
	{
		//x
		double const GROUND_ACCEL = 1;
		double const AIR_ACCEL = GROUND_ACCEL/4;
		double const ACCEL = (y_ >= FLOOR? GROUND_ACCEL: AIR_ACCEL);
		double const SPEED = 10.0;
		if(keyboard[SDLK_LEFT] == keyboard[SDLK_RIGHT])
			xvel_ = approach(xvel_,0.0,ACCEL);
		else if(keyboard[SDLK_LEFT])
			xvel_ = approach(xvel_,-SPEED,ACCEL);
		else //(keyboard[SDLK_RIGHT])
			xvel_ = approach(xvel_,SPEED,ACCEL);

		//y
		if(y_ > FLOOR && yvel_ > 0) //falling through floor?
			yvel_ = 0; //stop that
		else //airborne
			++yvel_;
	}

	//move
	x_ += static_cast<int>(xvel_);
	y_ += static_cast<int>(yvel_);

	//collide with floor
	if(y_ > FLOOR) {
		yvel_ = 0;
		y_ = FLOOR;
	}

	//calculate jump strength
	if(y_ >= FLOOR && keyboard[SDLK_SPACE]) //on floor
	{
		jump_strength_ += 8;
		int const MAX = 225;
		if(jump_strength_ > MAX)
			jump_strength_ = MAX;
	}
	else
		jump_strength_ = 0;
}

void screen_object::on_jump(std::set<platform> const& plats)
{
	if(y_ >= FLOOR)
		yvel_ = -sqrt(jump_strength_);
}