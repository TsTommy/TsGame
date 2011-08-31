#include "player.h"

#include "keyboard.h"
#include "path.h"
#include "screen.h"

player::player(point const& p, screen& s)
		: body_(p,IMAGE("hello.bmp"))
		, pos_(p)
		, veloc_(0,0)
		, screen_(s)
{
	s.add(body_);
}

static int const FLOOR = 440;

/*private*/
bool player::is_on_floor() const
{
	return (pos_.y >= FLOOR);
}

/*private*/
void player::move_to(vec const& v)
{
	pos_ = v;
	body_.move_to(point(pos_));
}

void player::on_frame(keyboard const& k)
{
	//accelerate
	veloc_.x
	veloc_.y += 1;

	//move
	move_to(pos_ + veloc_);

	//update
	if(is_on_floor())
	{
		veloc_.y = std::min(veloc_.y,0.0);
		move_to(vec(pos_.x,FLOOR));
	}
}

void player::on_jump()
{
	if(is_on_floor())
		veloc_.y = -15.0;
}
