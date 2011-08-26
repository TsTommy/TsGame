#ifndef SCREEN_OBJECT_H_INCLUDED
#define SCREEN_OBJECT_H_INCLUDED

#include "box.h"
#ifdef BOX
	class animation;
#else
	#include "animation.h";
#endif

struct platform;
class screen;

class screen_object
{
public:
	screen_object(int x, int y);

	int x() const {return x_;}
	int y() const {return y_;}
	void draw(screen&) const;

	void on_frame(Uint8* keyboard, std::set<platform> const&);
	void on_jump(std::set<platform> const&);

private:
	int x_;
	int y_;
	int yvel_;
	box<animation> animation_;
};

#endif //SCREEN_OBJECT_H_INCLUDED
