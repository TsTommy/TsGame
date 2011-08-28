#include <iostream>

#include <SDL/SDL.h>

#include "game.h"

inline static void pause()
{
	char useless[1];
	std::cin.getline(useless,1);
}

inline static void print_instructions(std::ostream& out)
{
	out<<"Left and right arrow keys to move.\n"
			<<"Spacebar to jump.\n";
}

int main(int argc, char** argv)
{
	print_instructions(std::cout);

	game g;
	g.play();
	//g.~game()

 	return argc+argv, 0;
}
