#include <boost/test/unit_test.hpp>
#include "ReversiCore/Array2D.h"

#define MAYBE_UNUSED [[maybe_unused]]

BOOST_AUTO_TEST_SUITE(TS_Array2D)

BOOST_AUTO_TEST_CASE(getSize)
{
	Array2D array1(Size(6, 8));
	Array2D array2(Size(0, 0));
	

	BOOST_CHECK_EQUAL(6, array1.getSize().width);
	BOOST_CHECK_EQUAL(8, array1.getSize().height);

	BOOST_CHECK_EQUAL(0, array2.getSize().width);
	BOOST_CHECK_EQUAL(0, array2.getSize().height);

	BOOST_CHECK_THROW(Array2D a MAYBE_UNUSED(Size(-3, -1)), std::invalid_argument);
}


BOOST_AUTO_TEST_SUITE_END()
