#include "screen_object.h"
#include "tag.h"

#include "screen.h"
#include "test/screen_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(screen_test);

typedef screen<isolated_tag> isolated_t;

void screen_test::setUp()
{
}
void screen_test::tearDown()
{
}

void screen_test::test_drive()
{
	isolated_t to_test;

	isolated_t::object obj_1;
	isolated_t::object obj_2;
	isolated_t::object obj_3;

	to_test.add(obj_2);
	to_test.add(obj_1);
	to_test.add(obj_3);

	to_test.draw();

	CPPUNIT_ASSERT_EQUAL(size_t(1), obj_1.draw_count());
	CPPUNIT_ASSERT_EQUAL(size_t(1), obj_2.draw_count());
	CPPUNIT_ASSERT_EQUAL(size_t(1), obj_3.draw_count());

	to_test.remove(obj_1);
	to_test.remove(obj_2);
	to_test.remove(obj_3);
}
