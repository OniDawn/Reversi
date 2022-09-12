#include <boost/test/unit_test.hpp>
#include "ReversiCore/Field.h"

BOOST_AUTO_TEST_SUITE(TS_Field)

BOOST_AUTO_TEST_CASE(xPos)
{
	Field field1(0, 0);
	Field field2(7, 8);
	Field field3(3, 0);


	BOOST_CHECK_EQUAL(0, field1.xPos);
	BOOST_CHECK_EQUAL(7, field2.xPos);
	BOOST_CHECK_EQUAL(3, field3.xPos);
}

BOOST_AUTO_TEST_CASE(yPos)
{
	Field field1(0, 0);
	Field field2(7, 8);
	Field field3(3, 0);


	BOOST_CHECK_EQUAL(0, field1.yPos);
	BOOST_CHECK_EQUAL(8, field2.yPos);
	BOOST_CHECK_EQUAL(0, field3.yPos);
}


BOOST_AUTO_TEST_SUITE_END()