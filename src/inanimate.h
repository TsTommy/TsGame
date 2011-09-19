#ifndef INANIMATE_H_INCLUDED
#define INANIMATE_H_INCLUDED

#include <boost/noncopyable.hpp>
#include "platform.h"
#include "screen_object.h"
#include "vec.h"
class screen;

class inanimate
		: boost::noncopyable
{
public:
	inanimate(vec pos, double mass, char const* filename, screen&);
	inanimate(vec pos, double mass, std::string const& filename, screen&);

	bool is_on_floor() const {return standing_on_ != NULL;}

	void on_frame(std::set<platform,platform_comparator> const&);

private:
	vec pos_;
	vec veloc_;
	double mass_;
	screen_object body_;

	platform const* standing_on_;
	screen& screen_;
};

#endif //INANIMATE_H_INCLUDED
