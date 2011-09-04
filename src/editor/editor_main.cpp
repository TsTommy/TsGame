#include <iostream>

#include "editor.h"

inline static void pause()
{
	char useless[1];
	std::cin.getline(useless,1);
}

int main(int argc, char** argv)
{
	editor e;
	e.run();
	//pause();
	//e.~editor();

 	return argc+argv, 0;
}
