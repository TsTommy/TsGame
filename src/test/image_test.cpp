#include "tag.h"

#include "image.h"
#include "test/image_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(image_test);

typedef image<isolated_tag> isolated_t;

void image_test::setUp()
{
}
void image_test::tearDown()
{
}

void image_test::test_drive()
{
	image<isolation_tag> img;
	CPPUNIT_ASSERT_EQUAL(0,1);
}
