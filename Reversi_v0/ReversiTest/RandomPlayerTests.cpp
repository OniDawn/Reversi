#include <boost/test/unit_test.hpp>
#include "ReversiCore/RandomPlayer.h"

BOOST_AUTO_TEST_SUITE(TS_RandomPlayer)

BOOST_AUTO_TEST_CASE(RandomPlayerChoosesValidIndex)
{
	RandomPlayer player;
	std::vector<Field> possibilities;
	// aufruf
	Field result;
		
	//auto iter = std::find(possibilities.begin(), possibilities.end(), result);
	//BOOST_CHECK(iter != possibilities.end());
}

BOOST_AUTO_TEST_SUITE_END()