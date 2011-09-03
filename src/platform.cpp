#include "platform.h"

#include <utility>

platform::platform(vec const& left_pt, vec const& shape, char const* filename, screen& s)
		: left_pt_(left_pt)
		, right_pt_(left_pt+shape)
		, body_(point(static_cast<int>(std::min(left_pt_.x,right_pt_.x)),static_cast<int>(std::min(left_pt_.y,right_pt_.y)))
				, filename)
		, left_neighbor_(NULL)
		, right_neighbor_(NULL)
		, screen_(s)
{
	s.add(body_);
}

platform::platform(vec const& left_pt, vec const& shape, std::string const& filename, screen& s)
		: left_pt_(left_pt)
		, right_pt_(left_pt+shape)
		, body_(point(static_cast<int>(std::min(left_pt_.x,right_pt_.x)),static_cast<int>(std::min(left_pt_.y,right_pt_.y)))
				, filename)
		, left_neighbor_(NULL)
		, right_neighbor_(NULL)
		, screen_(s)
{
	s.add(body_);
}

platform::platform(platform const& that)
		: left_pt_(that.left_pt_)
		, right_pt_(that.right_pt_)
		, body_(that.body_)
		, left_neighbor_(that.left_neighbor_)
		, right_neighbor_(that.right_neighbor_)
		, screen_(that.screen_)
{
	screen_.add(body_);
}
platform& platform::operator=(platform const& that)
{
	//gracefully handles self-assignment
	left_pt_ = that.left_pt_;
	right_pt_ = that.right_pt_;
	body_ = that.body_;
	left_neighbor_ = that.left_neighbor_;
	right_neighbor_ = that.right_neighbor_;
	if(&screen_ != &that.screen_)
		throw "Can't change what a reference points to!";
	return *this;
}

platform::~platform()
{
	screen_.remove(body_);
}

template<typename num>
static inline bool in_range(num val, num min, num max)
	{return min==max || (val>=min && val<=max);} //inclusive

template<typename num>
static inline bool between(num val, num one, num two)
{
	static num const epsilon = 0.001;
	num min, max;
	if(one < two)
		min = one-epsilon, max = two+epsilon;
	else
		min = two-epsilon, max = one+epsilon;
	return in_range(val,min,max);
}

template<typename num>
static inline bool range_overlap(std::pair<num,num> const& a, std::pair<num,num> const& b)
{
	static num const epsilon = 0.001;
	num a_min, a_max, b_min, b_max;
	if(a.first < a.second)
		a_min = a.first-epsilon, a_max = a.second+epsilon;
	else
		a_min = a.second-epsilon, a_max = a.first+epsilon;
	if(b.first < b.second)
		b_min = b.first-epsilon, b_max = b.second+epsilon;
	else
		b_min = b.second-epsilon, b_max = b.first+epsilon;
	return a_min <= b_max && b_min <= a_max;
}

static inline vec intersection(vec const& pos, vec const& motion, vec const& left_pt, vec const& right_pt)
{
	vec const plat_dir = right_pt - left_pt;

	if((pos-left_pt).normalized() == plat_dir.normalized())
		return pos;
	else if((motion+pos-left_pt).normalized() == plat_dir.normalized())
		return motion+pos;
	
//	Solving equation: pos + motion*c == left_pt + plat_dir*k

//	if(motion.x == 0 || ((motion.y*(left_pt.x-right_pt.x)/motion.x)+(left_pt.y-right_pt.y)) == 0)
//	if(0 == motion.y
//			|| 0 == (left_pt.x-right_pt.x)
//			|| 0 == (1 - (((motion.x*(left_pt.y-right_pt.y)/motion.y)/(left_pt.x-right_pt.x)))))
	if(0 == motion.x
			|| 0 == (motion.y*plat_dir.x/motion.x - plat_dir.y))
	{
//		if(((motion.x*(left_pt.y-right_pt.y)/motion.y)+(left_pt.x-right_pt.x)) == 0 || motion.y == 0)
//		if(0 == motion.x
//				|| 0 == (left_pt.y-right_pt.y)
//				|| 0 == (1 - (((motion.y*(left_pt.x-right_pt.x)/motion.x)/(left_pt.y-right_pt.y)))))
		if(0 == motion.y
				|| 0 == (motion.x*plat_dir.y/motion.y - plat_dir.x))
			return vec(std::max(left_pt.x,right_pt.x)+1,0); //no intersection

//		double k = (pos.x + motion.x*(left_pt.y - pos.y)/motion.y - left_pt.x)/((motion.x*(left_pt.y-right_pt.y)/motion.y)+(left_pt.x-right_pt.x));
//		double k = ((left_pt.y - pos.y + motion.y*(left_pt.x - pos.x)/motion.x)/(left_pt.y-right_pt.y))/(1 - (((motion.y*(left_pt.x-right_pt.x)/motion.x)/(left_pt.y-right_pt.y))));
		double k = (left_pt.x - (pos.x + motion.x*(left_pt.y - pos.y)/motion.y))/(motion.x*plat_dir.y/motion.y - plat_dir.x);
		return left_pt + plat_dir*k;
//		double c = ((left_pt.x + (left_pt.x-right_pt.x)*k - pos.x) / motion.x);
	}

//	double k = -(pos.y + motion.y*(left_pt.x - pos.x)/motion.x - left_pt.y)/((motion.y*(left_pt.x-right_pt.x)/motion.x)+(left_pt.y-right_pt.y));
//	double k = ((left_pt.x - pos.x + motion.x*(left_pt.y - pos.y)/motion.y)/(left_pt.x-right_pt.x))/(1 - (((motion.x*(left_pt.y-right_pt.y)/motion.y)/(left_pt.x-right_pt.x))));
	double k = (left_pt.y - (pos.y + motion.y*(left_pt.x - pos.x)/motion.x))/(motion.y*plat_dir.x/motion.x - plat_dir.y);
	return left_pt + plat_dir*k;
//	double c = ((left_pt.y + (left_pt.y-right_pt.y)*k - pos.y) / motion.x);
}

platform const* platform::alter_trajectory(vec const& pos, vec& motion, vec& new_veloc, bool& altered) const
{
	altered = false;

	bool debug = ((pos + motion).y > 400);
	if(debug)
		int debugg = 0;

	vec const dst = (pos + motion);

	//locality optimization -- hopefully
#if 0
	if(!range_overlap(std::make_pair(left_pt_.x,right_pt_.x),std::make_pair(pos.x,dst.x))
			|| !range_overlap(std::make_pair(left_pt_.y,right_pt_.y),std::make_pair(pos.y,dst.y)))
		if(debug)
			return NULL;
		else
			return NULL;
#endif

	vec const dir = direction();

	//check whether falling from above or jumping up from below
	if((dir.x*motion.y - dir.y*motion.x) < 0)
		return NULL;

	//check whether a collision occurred
	vec intersect = intersection(pos,motion,left_pt_,right_pt_);
	if(!between(intersect.x,left_pt_.x,right_pt_.x)
			|| !between(intersect.y,left_pt_.y,right_pt_.y)
			|| !between(intersect.x,pos.x,dst.x)
			|| !between(intersect.y,pos.y,dst.y))
		if(debug)
			return NULL;
		else
			return NULL;

	altered = true;

	//compute adjustment
	vec const old_pos = pos;
	vec const old_motion = motion;
	vec excess = dst-intersect;
	bool const motion_equals_excess = (abs((motion-excess).mag())<0.00001);
	motion = motion + excess.project(dir) - excess;
	new_veloc = motion.project(dir);

	vec const new_dst = pos + motion;
	if(is_right_of(new_dst))
		return left_neighbor_;
	else if(is_left_of(new_dst))
		return right_neighbor_;
	else return NULL;
}

bool platform::is_right_of(vec const& v) const
{
	return left_pt_.x >= v.x;
}

bool platform::is_left_of(vec const& v) const
{
	return right_pt_.x < v.x;
}
