#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SDL/SDL.h>
#include <set>
#include "image.h"
#include "point.h"
#include "surface.h"

class screen_object;

class screen
{
public:
	typedef screen_object object;

	screen(dimensions const&);

	point camera() const {return camera_;}

	void on_frame(Uint32 curr_time);
	void draw();

	void add(object&);
	void remove(object&);

	void move_camera(point const& p) {camera_ = p;}

private:
	surface screen_;
	surface buffer_;
	std::set<object*> objects_;
	point camera_;
};

#endif //SCREEN_H_INCLUDED
