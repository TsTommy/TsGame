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
	if(on_floor(x_,y_,plats) && yvel_ > 0) //falling through floor?
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

	foreach(platform const& plat, plats)
		if(collide(old_x,old_y,x_,y_,plat))
			snap_to(x_,y_,yvel_,plat);

	//collide with floor
	if(y_ > FLOOR) {
		yvel_ = 0;
		y_ = FLOOR;
	}
}

void screen_object::on_jump(std::set<platform> const& plats)
{
	if(on_floor(x_,y_,plats))
		yvel_ = -20;
}