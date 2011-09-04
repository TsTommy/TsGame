#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "screen.h"
#include "screen_object.h"
#include "vec.h"

class platform
{
public:
	platform(vec const& left_pt, vec const& shape, char const* filename, screen&);
	platform(vec const& left_pt, vec const& shape, std::string const& filename, screen&);
	platform(platform const&);
	platform& operator=(platform const&);
	~platform();

	///Returns a vec that points along the line of this platform
	vec direction() const {return right_pt_-left_pt_;}

	/**
	 * If the given trajectory crosses this platform, adjusts arguments
	 *   as necessary to prevent the crossing
	 * Output arg: altered = whether or not a collision was detected
	 * 
	 * Returns pointer to a platform that ought to be checked again, or NULL if none
	 */
	platform const* alter_trajectory(vec const& pos, vec& motion, vec& new_veloc, bool& altered) const;

	bool is_right_of(vec const&) const;
	bool is_left_of(vec const&) const;

	///Returns a unit vec (i.e. magnitude 1) that points perpendicular to this platform
	vec normal() const {return vec(direction().y,-direction().x).normalized();}

	platform const* left_neighbor() const {return left_neighbor_;}
	platform const* right_neighbor() const {return right_neighbor_;}
	vec const& left_pt() const {return left_pt_;}
	vec const& right_pt() const {return right_pt_;}

	void set_left_neighbor(platform const* p) {left_neighbor_ = p;}
	void set_right_neighbor(platform const* p) {right_neighbor_ = p;}

private:
	friend struct platform_comparator;

	vec left_pt_;
	vec right_pt_;
	screen_object body_;
	platform const* left_neighbor_;
	platform const* right_neighbor_;
	screen& screen_;
};

struct platform_comparator : public vec_comparator {
	bool operator()(platform const& a, platform const& b) const {return vec_comparator::operator()(a.left_pt_,b.left_pt_);}
};

#endif //PLATFORM_H_INCLUDED
