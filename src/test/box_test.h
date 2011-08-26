#ifndef BOX_TEST_H_INCLUDED
#define BOX_TEST_H_INCLUDED

#include <cppunit/extensions/HelperMacros.h>

class box_test
		: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(box_test);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void test();

private:
};

#endif //BOX_TEST_H_INCLUDED
