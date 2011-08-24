#ifndef SCREEN_OBJECT_H_INCLUDED
#define SCREEN_OBJECT_H_INCLUDED

#include "box.h"
#ifdef BOX
	class animation;
#else
	#include "animation.h";
#endif

class screen;

class screen_object
{
public:
	screen_object(screen*, int x, int y);

	int x() const {return x_;}
	int y() const {return y_;}
	void draw() const;

	void move_to(int x, int y);

private:
	screen* screen_;
	int x_;
	int y_;
	box<animation> animation_;
};

#endif //SCREEN_OBJECT_H_INCLUDED
