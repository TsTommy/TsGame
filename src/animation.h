#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <map>
#include <vector>
#include "image.h"
#include "point.h"
class data;

class animation
{
public:
	typedef image::screen_t screen_t;

	animation(data const&);
	animation(char const* filename);
	animation(std::string const& filename);

	void draw(screen_t&, point const& pos) const;

	void on_frame(Uint32 curr_time);
	void start(std::string seq_name);

private:
	class sequence
	{
	public:
		sequence();
		sequence(data const&);

		struct frame
		{
			frame(data const&);

			image img;
			unsigned dur; //frame duration
			point hotspot;
		};

		std::vector<frame> frames;
	};

	void init(data const&);
	void init(char const* filename);
	void init(std::string const& filename);

	std::map<std::string,sequence> seq_;
	std::string curr_seq_;
	size_t curr_frame_;
	Uint32 frame_start_time_;
};

#endif //ANIMATION_H_INCLUDED
