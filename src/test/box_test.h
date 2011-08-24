#ifndef BOX_TEST_H_INCLUDED
#define BOX_TEST_H_INCLUDED

#include <cppunit/extensions/HelperMacros.h>

class game_test
		: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(game_test);
	CPPUNIT_TEST(/*testname*/);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void /*testname*/();

private:
};

#endif //BOX_TEST_H_INCLUDED
