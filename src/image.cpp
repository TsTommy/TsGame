#include "image.h"

image::image(char const* filename)
		: surface_(SDL_LoadBMP(filename))
	{}

image::image(std::string const& filename)
		: surface_(SDL_LoadBMP(filename.c_str()))
	{}

image::~image()
{
	surface_.free();
}

void image::draw(screen_t& s, point const& p) const
{
	surface_.blit(s,p);
}
