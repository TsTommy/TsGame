#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <cassert>
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

class data
{
public:
	typedef std::map<std::string,std::string> values_t;
	typedef std::multimap<std::string,boost::shared_ptr<data> > children_t;
	//iterator code
		typedef children_t::iterator all_children_iterator;
		typedef children_t::const_iterator all_children_const_iterator;
		typedef std::pair<all_children_iterator,all_children_iterator> all_children_itors;
		typedef std::pair<all_children_const_iterator,all_children_const_iterator> all_children_const_itors;
		struct child_iterator : public children_t::iterator
		{
			typedef children_t::iterator base_t;
			typedef data value_type;   typedef data& reference;   typedef data* pointer;
			child_iterator(base_t const& x): base_t(x) {}
			data& operator*() const {return *base_t::operator*().second;}
			data* operator->() const {return &**this;}
		};
		struct child_const_iterator : public children_t::const_iterator
		{
			typedef children_t::const_iterator base_t;
			typedef data const value_type;   typedef data const& reference;   typedef data const* pointer;
			child_const_iterator(base_t const& x): base_t(x) {}
			data const& operator*() const {return *base_t::operator*().second;}
			data const* operator->() const {return &**this;}
		};
		typedef std::pair<child_iterator,child_iterator> child_itors;
		typedef std::pair<child_const_iterator,child_const_iterator> child_const_itors;
	//end iterator code

	data();
	data(std::istream& file);
	data(char const* filename);
	data(std::string const& filename);

	//access to contents
		std::string& operator[](std::string const& k)
			{return value_[k];}
		std::string const& operator[](std::string const& k) const
			{assert(value_.find(k)!=value_.end());   return value_.find(k)->second;}
		int int_value(std::string const& k) const
			{return boost::lexical_cast<int>((*this)[k]);}
		double double_value(std::string const& k) const
			{return boost::lexical_cast<double>((*this)[k]);}

		child_itors child_range(std::string const& k)
		{
			std::pair<child_iterator,child_iterator> result = child_.equal_range(k);
			return result;
		}
		child_const_itors child_range(std::string const& k) const
			{return child_.equal_range(k);}

		all_children_itors all_children()
			{return std::make_pair(child_.begin(),child_.end());}
		all_children_const_itors all_children() const
			{return std::make_pair(child_.begin(),child_.end());}

		data& child(std::string const& k)
			{assert(child_.count(k)==1);   return *child_range(k).first;}
		data const& child(std::string const& k) const
			{assert(child_.count(k)==1);   return *child_range(k).first;}

		bool has_child(std::string const& k) const
			{return child_.count(k) > 0;}
	//end access to contents

	std::ostream& print(std::ostream& out) const;

private:
	void init(std::istream& file);
	void init(char const* filename);
	void init(std::string const& filename);

	values_t value_;
	children_t child_;
};

inline std::ostream& operator<<(std::ostream& out, data const& d)
	{return d.print(out);}

#endif //DATA_H_INCLUDED
