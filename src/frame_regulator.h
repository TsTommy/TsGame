#ifndef FRAME_REGULATOR_H_INCLUDED
#define FRAME_REGULATOR_H_INCLUDED

class frame_regulator {
public:
	frame_regulator(unsigned interval)
			: frame_num_(0)
			, interval_(interval)
			, curr_time_(0)
		{}

	bool time_for_next_frame()
	{
		bool result;
		curr_time_ = SDL_GetTicks();
		unsigned new_frame_num = curr_time_/interval_;
		result = (frame_num_ < new_frame_num);
		frame_num_ = new_frame_num;
		return result;
	}

	Uint32 time() const {return curr_time_;}

private:
	Uint32 curr_time_;
	unsigned frame_num_;
	unsigned interval_;
};

#endif //FRAME_REGULATOR_H_INCLUDED
