#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#include "box.h"
#ifdef BOX
#else
#endif

struct platform
{
	int x1_,y1_, x2_,y2_;
	bool operator<(platform const& that) const {return this<&that;}
};

#endif //PLATFORM_H_INCLUDED
