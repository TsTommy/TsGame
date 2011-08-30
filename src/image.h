#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <boost/noncopyable.hpp>
#include <string>
#include "point.h"
#include "surface.h"

class image
		: private boost::noncopyable
{
public:
	typedef surface screen_t;

	image(char const*);
	image(std::string const&);
	~image();

	void draw(screen_t&, point const&) const;

private:
	surface surface_;
};

#endif //IMAGE_H_INCLUDED
