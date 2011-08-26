#ifndef KEYBOARD_TEST_H_INCLUDED
#define KEYBOARD_TEST_H_INCLUDED

#include <cppunit/extensions/HelperMacros.h>

class keyboard_test
		: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(keyboard_test);
	CPPUNIT_TEST(/*testname*/);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void /*testname*/();

private:
};

#endif //KEYBOARD_TEST_H_INCLUDED
