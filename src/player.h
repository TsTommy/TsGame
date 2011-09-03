#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <set>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "screen_object.h"
#include "vec.h"
class keyboard;
class platform;
class screen;

class player
		: private boost::noncopyable
{
public:
	player(point const& location, screen&);
	~player();

	vec pos() const {return pos_;}

	void add_to_screen(screen&) const;

	void on_frame(keyboard const&, std::set<boost::shared_ptr<platform> > const& level);
	void on_jump(keyboard const&);

private:
	bool is_on_floor() const;
	void move_to(vec const&);
	void update_animation();

	screen_object body_;
	vec pos_;
	vec veloc_;
	bool facing_right_;
	unsigned jump_strength_;
	platform const* standing_on_;
	screen& screen_;
};

#endif //PLAYER_H_INCLUDED
