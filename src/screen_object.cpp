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
		, yvel_(0)
		, animation_(IMAGE("hello.bmp"))
{
}

void screen_object::draw(screen& s) const
{
	animation_->draw(s,x_,y_);
}

static int const FLOOR = 440;

static bool collide(int,int,int,int,platform const&) {return false;}
static void snap_to(int,int,int,platform const&) {}
static bool on_floor(int,int, std::set<platform> const&) {return true;}

void screen_object::on_frame(Uint8* keyboard, std::set<platform> const& plats)
{
	int const old_x = x_, old_y = y_;

	//accelerate
	if(y_ > FLOOR && yvel_ > 0) //falling through floor?
		yvel_ = 0; //stop that
	else //airborne
		++yvel_;

	//move
	int const SPEED = 5;
	if(keyboard[SDLK_RIGHT])
		x_+=SPEED;
	if(keyboard[SDLK_LEFT])
		x_-=SPEED;
	y_ += yvel_;

	//collide with floor
	if(y_ > FLOOR) {
		yvel_ = 0;
		y_ = FLOOR;
	}

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
		yvel_ = -static_cast<int>(sqrt(static_cast<double>(jump_strength_)));
}