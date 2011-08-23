#include "game.h"
#include "test/game_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(game_test);

void game_test::setUp() {}
void game_test::tearDown() {}

void game_test::ctor()
{
	game g(0,NULL);
	g.play();
}
