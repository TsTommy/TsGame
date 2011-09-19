#include "image.h"

#include <SDL/SDL_image.h>

//file-scope functor for releasing surfaces
namespace {
	struct surface_deleter { void operator()(SDL_Surface*& s) {SDL_FreeSurface(s);} };
} //namespace

image::image(char const* filename)
		: surface_(image::load(filename),surface_deleter())
{
	init();
}

image::image(std::string const& filename)
		: surface_(image::load(filename.c_str()),surface_deleter())
{
	init();
}

void image::draw(screen_t& s, point const& p) const
{
	surface(&*surface_).blit(s,p);
}

/*private*/
void image::init()
{
	assert(surface_);
}

/*static*/ /*private*/
SDL_Surface* image::load(char const* filename)
{
	SDL_Surface* temp = IMG_Load(filename);
	if(!temp)
		throw "Failed to load image";
	SDL_Surface* result = SDL_DisplayFormatAlpha(temp);
	if(!result)
		throw "Failed to load image";
	SDL_FreeSurface(temp);
	return result;
}
