#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <boost/noncopyable.hpp>
#include "screen_object.h"
#include "vec.h"
class keyboard;
class screen;

class player
		: private boost::noncopyable
{
public:
	player(point const& location, screen&);

	void add_to_screen(screen&) const;

	void on_frame(keyboard const& k);
	void on_jump();

private:
	bool is_on_floor() const;
	void move_to(vec const&);

	screen_object body_;
	vec pos_;
	vec veloc_;
	screen& screen_;
};

#endif //PLAYER_H_INCLUDED
