#include <boost/test/unit_test.hpp>
#include "ReversiCore/Size.h"
//macht Namespace auf
BOOST_AUTO_TEST_SUITE(TS_Size) 

BOOST_AUTO_TEST_CASE(width)
{
	Size s(5, 7);
	BOOST_CHECK_EQUAL(5, s.width);
}

BOOST_AUTO_TEST_CASE(height)
{
	Size s(5, 7);
	BOOST_CHECK_EQUAL(7, s.height);
}

//macht Namespace zu
BOOST_AUTO_TEST_SUITE_END()
