#include <SDL.h>

#include "game.h"

inline static void pause()
{
	char useless[1];
	std::cin.getline(useless,1);
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	game g;
	game().play();

//	struct incomplete;
//	boost::shared_ptr<incomplete> p(reinterpret_cast<incomplete*>(1));

	std::cout<<"Press enter to exit.\n";
	pause();
	SDL_Quit();
 	return argc+argv, 0;
}
