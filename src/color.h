#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

//This class is basically a replica of the SDL_Color class,
//but with the addition of a constructor
class color
		: private SDL_Color
{
public:
	color() //performs no initialization!
			: SDL_Color()
			, r(SDL_Color::r)
			, g(SDL_Color::g)
			, b(SDL_Color::b)
		{}
	color(int arg_r, int arg_g, int arg_b)
			: SDL_Color()
			, r(SDL_Color::r)
			, g(SDL_Color::g)
			, b(SDL_Color::b)
	{
		r = arg_r;
		g = arg_g;
		b = arg_b;
	}

	SDL_Color base() const
		{return *static_cast<SDL_Color const*>(this);}

//fields public for convenience
	//reference-type fields provide transparency
	Uint8& r;
	Uint8& g;
	Uint8& b;
};

#endif //COLOR_H_INCLUDED
