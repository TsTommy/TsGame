#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include "point.h"
#include "surface.h"

class image
{
public:
	typedef surface screen_t;

	image(char const*);
	image(std::string const&);
	~image();

	void draw(screen_t&, point const&) const;

private:
	boost::shared_ptr<SDL_Surface> surface_;
};

#endif //IMAGE_H_INCLUDED
