#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <set>
#include <SDL.h>

class screen
{
public:
	screen();
	~screen();

private:
	SDL_Surface& screen_;
	std::set<SDL_Surface*> images_;
};

#endif //SCREEN_H_INCLUDED
