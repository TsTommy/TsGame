#include "font.h"

font::font(char const* filename, int size)
		: p_(TTF_OpenFont(filename,size))
	{}

font::font(std::string const& filename, int size)
		: p_(TTF_OpenFont(filename.c_str(),size))
	{}

font::~font()
{
	TTF_CloseFont(p_);
}

surface font::render(char const* msg, color c) const
{
	return surface(TTF_RenderText_Solid(p_,msg,c.base()));
}

surface font::render(std::string const& msg, color c) const
{
	return surface(TTF_RenderText_Solid(p_,msg.c_str(),c.base()));
}
