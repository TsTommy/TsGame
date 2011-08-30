#include "player.h"

#include "path.h"
#include "screen.h"

player::player(point const& p, screen& s)
		: body_(p,IMAGE("hello.bmp"))
		, velocity_(0,0)
		, screen_(s)
{
	s.add(body_);
}

static int const FLOOR = 440;

/*private*/
bool player::is_on_floor() const
{
	return (body_.pos().y >= FLOOR);
}

void player::on_frame()
{
	velocity_.y += 1;

	body_.move_to(point(body_.pos().x + velocity_.x, body_.pos().y + velocity_.y));

	if(is_on_floor())
	{
		velocity_.y = std::min(velocity_.y,0);
//		if(body_.pos().y > FLOOR)
			body_.move_to(point(body_.pos().x,FLOOR));
	}
}

void player::on_jump()
{
	if(is_on_floor())
		velocity_.y = -15;
}