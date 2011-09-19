#ifndef SCOPED_TTF_H_INCLUDED
#define SCOPED_TTF_H_INCLUDED

#include <cassert>
#include <SDL/SDL_ttf.h>

struct scoped_ttf {
	scoped_ttf() {bool success = (TTF_Init() >= 0);   assert(success);}
	~scoped_ttf() {TTF_Quit();}
};

#endif //SCOPED_TTF_H_INCLUDED
