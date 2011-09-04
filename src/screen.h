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

	screen(dimensions const& camera, dimensions const& world);

	point camera() const {return camera_;}
	double zoom() const {return zoom_;}

	void on_frame(Uint32 curr_time);
	void draw();

	void add(object&);
	void remove(object&);

	void move_camera(point const& p) {camera_ = p;}
	void set_zoom(double z) {zoom_ = z;}

private:
	surface screen_;
	surface buffer_;
	surface zoom_buffer_;
	std::set<object*> objects_;
	point camera_;
	double zoom_;
};

#endif //SCREEN_H_INCLUDED
