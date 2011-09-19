#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <string>
#include <boost/noncopyable.hpp>
#include <SDL/SDL_ttf.h>
#include "color.h"
#include "surface.h"

//wraps TTF_Font*
//This class OWNS the underlying pointer!
class font
		: private boost::noncopyable
{
public:
	font(char const* font_filename, int font_size);
	font(std::string const& font_filename, int font_size);
	~font();

	surface render(char const* msg, color) const;
	surface render(std::string const& msg, color) const;

private:
	TTF_Font* p_;
};

#endif //FONT_H_INCLUDED
