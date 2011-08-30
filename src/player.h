#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <boost/noncopyable.hpp>
#include "point.h"
#include "screen_object.h"
class screen;

class player
		: private boost::noncopyable
{
public:
	player(point const& location, screen&);

	void add_to_screen(screen&) const;

	void on_frame();
	void on_jump();

private:
	bool is_on_floor() const;

	screen_object body_;
	point velocity_;
	screen& screen_;
};

#endif //PLAYER_H_INCLUDED
