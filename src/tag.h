#ifndef TAG_H_INCLUDED
#define TAG_H_INCLUDED

class stub_tag
{
private:
	typedef int stubs_should_not_have_neighbors;

public:
	typedef stubs_should_not_have_neighbors neighbor_tag;
};

class isolated_tag
{
public:
	typedef stub_tag neighbor_tag;
};

class normal_tag
{
public:
	typedef normal_tag neighbor_tag;
};

#endif //TAG_H_INCLUDED
