#include "image.h"

#include <SDL/SDL_image.h>

//file-scope functor for releasing surfaces
namespace {
	struct surface_deleter { void operator()(SDL_Surface*& s) {SDL_FreeSurface(s);} };
} //namespace

image::image(char const* filename)
		: surface_(IMG_Load(filename),surface_deleter())
	{}

image::image(std::string const& filename)
		: surface_(IMG_Load(filename.c_str()),surface_deleter())
	{}

void image::draw(screen_t& s, point const& p) const
{
	surface(&*surface_).blit(s,p);
}
