#ifndef PLATFORM_TEST_H_INCLUDED
#define PLATFORM_TEST_H_INCLUDED

#include <cppunit/extensions/HelperMacros.h>

class platform_test
		: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(platform_test);
	CPPUNIT_TEST(/*testname*/);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void /*testname*/();

private:
};

#endif //PLATFORM_TEST_H_INCLUDED
