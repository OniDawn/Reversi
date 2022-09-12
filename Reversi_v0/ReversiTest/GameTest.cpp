#include <boost/test/unit_test.hpp>
#include "ReversiCore/Game.h"

BOOST_AUTO_TEST_SUITE(TS_Array2D)

BOOST_AUTO_TEST_CASE(play)
{
	Game g(Array2D(Size(4, 4)), StrategyFactory(), 0, 0, MoveCalculator());

	g.play(1);

	//BOOST_CHECK_EQUAL(0, array2.getSize().width);
}


BOOST_AUTO_TEST_SUITE_END()