#include <iostream>

#include <SDL.h>

#include "game.h"

inline static void pause()
{
	char useless[1];
	std::cin.getline(useless,1);
}

int main(int argc, char** argv)
{
	game g;
	g.play();
	//g.~game()

 	return argc+argv, 0;
}
