#ifndef SCREEN_TEST_H_INCLUDED
#define SCREEN_TEST_H_INCLUDED

#include <cppunit/extensions/HelperMacros.h>

class screen_test
		: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(screen_test);
	CPPUNIT_TEST(/*testname*/);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void /*testname*/();

private:
};

#endif //SCREEN_TEST_H_INCLUDED
