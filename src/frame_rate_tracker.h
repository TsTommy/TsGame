#ifndef FRAME_RATE_TRACKER_H_INCLUDED
#define FRAME_RATE_TRACKER_H_INCLUDED

#include <queue>
#include <SDL/SDL.h>

class frame_rate_tracker
{
public:
	frame_rate_tracker()
			: frame_times_()
		{}

	int frame_rate() const
	{
		size_t size = frame_times_.size();
		if(size >= 2)
		{
			Uint32 diff = frame_times_.back() - frame_times_.front();
			if(diff > 0)
				return 1000*(size-1) / diff;
		}
		return -1;
	}

	void on_frame(Uint32 current_time)
	{
		frame_times_.push(current_time);

		if(frame_times_.size() > 10)
			frame_times_.pop();
	}

private:
	std::queue<Uint32> frame_times_;
};

#endif //FRAME_RATE_TRACKER_H_INCLUDED
