#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <map>
#include <vector>
#include "image.h"
class data;

class animation
{
public:
	typedef image::screen_t screen_t;

	animation(data const&);
	animation(char const* filename);
	animation(std::string const& filename);

	void draw(screen_t&, point const& pos) const;

private:
	class sequence
	{
	public:
		sequence(data const&);

	private:
		struct frame
		{
			frame(data const&);
			image img;
			unsigned dur; //frame duration
		};

		std::vector<frame> frames_;
	};

	void init(data const&);
	void init(char const* filename);
	void init(std::string const& filename);

	std::map<std::string, sequence> seq_;
};

#endif //ANIMATION_H_INCLUDED
