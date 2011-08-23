#ifndef GAME_TEST_H_INCLUDED
#define GAME_TEST_H_INCLUDED

#include <cppunit/extensions/HelperMacros.h>

class game_test
		: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(game_test);
	CPPUNIT_TEST(ctor);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void ctor();
};

#endif //GAME_TEST_H_INCLUDED
