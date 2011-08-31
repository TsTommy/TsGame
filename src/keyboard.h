#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <SDL/SDL.h>

class keyboard
{
public:
	keyboard(): keys_(SDL_GetKeyState(NULL)) {}

	bool operator[](size_t i) const {return keys_[i] > 0;}

private:
	Uint8* keys_;
};

#endif //KEYBOARD_H_INCLUDED
