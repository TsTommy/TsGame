#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <cassert>
#include <iostream>
#include <map>
#include <boost/lexical_cast.hpp>

class data
{
public:
	typedef std::map<std::string,std::string> values_t;
	typedef std::multimap<std::string,data*> children_t;
	typedef children_t::iterator all_children_iterator;
	typedef children_t::const_iterator all_children_const_iterator;
	typedef std::pair<all_children_iterator,all_children_iterator> all_children_itors;
	typedef std::pair<all_children_const_iterator,all_children_const_iterator> all_children_const_itors;
	struct child_iterator : public children_t::iterator
	{
		typedef data value_type;   typedef data& reference;   typedef data* pointer;
		data& operator*() const {return *children_t::iterator::operator*().second;}
		data* operator->() const {return &**this;}
	};
	struct child_const_iterator : public children_t::const_iterator
	{
		typedef data const value_type;   typedef data const& reference;   typedef data const* pointer;
		data const& operator*() const {return *children_t::const_iterator::operator*().second;}
		data const* operator->() const {return &**this;}
	};
	typedef std::pair<child_iterator,child_iterator> child_itors;
	typedef std::pair<child_const_iterator,child_const_iterator> child_const_itors;

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

		child_itors child_range(std::string const& k)
			{return child_.equal_range(k);}
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
	//end access to contents

private:
	void init(std::istream& file);
	void init(char const* filename);
	void init(std::string const& filename);

	values_t value_;
	children_t child_;
};

#endif //DATA_H_INCLUDED
