#ifndef IMAGE_TEST_H_INCLUDED
#define IMAGE_TEST_H_INCLUDED

#include <cppunit/extensions/HelperMacros.h>

class image_test
		: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(image_test);
	CPPUNIT_TEST(test_drive);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void test_drive();

private:
};

#endif //IMAGE_TEST_H_INCLUDED
