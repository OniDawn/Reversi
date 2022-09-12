#include <boost/test/unit_test.hpp>
#include "ReversiCore/MoveCalculator.h"

BOOST_AUTO_TEST_SUITE(TS_MoveCalculator)

BOOST_AUTO_TEST_CASE(getPossibleMoves)
{
	MoveCalculator mc = MoveCalculator();
	Array2D board(Size(8, 8));
	board.setValue(Field(board.getSize().width / 2 - 1, board.getSize().height / 2), 1);
	board.setValue(Field(board.getSize().width / 2, board.getSize().height / 2 - 1), 1);
	board.setValue(Field(board.getSize().width / 2, board.getSize().height / 2), 2);
	board.setValue(Field(board.getSize().width / 2 - 1, board.getSize().height / 2 - 1), 2);
	std::vector<Field> moves1 = mc.getPossibleMoves(board, true);
	std::vector<Field> moves2 = mc.getPossibleMoves(board, false);
	Array2D board2(Size(8, 8));
	std::vector<Field> moves3 = mc.getPossibleMoves(board2, true);
	
	BOOST_CHECK_EQUAL(4, moves1.size());
	BOOST_CHECK_EQUAL(4, moves2.size());
	BOOST_CHECK_EQUAL(0, moves3.size());

}

BOOST_AUTO_TEST_CASE(calculateFlippedFields)
{
	MoveCalculator mc = MoveCalculator();
	Array2D board(Size(8, 8));
	board.setValue(Field(1, 1), 1);
	board.setValue(Field(2, 2), 1);
	board.setValue(Field(1, 2), 2);
	board.setValue(Field(3, 3), 2);
	std::vector<Field> moves1 = mc.calculateFlippedFields(Field(0, 0), 2, board);
	std::vector<Field> moves2 = mc.calculateFlippedFields(Field(3, 2), 2, board);
	std::vector<Field> moves3 = mc.calculateFlippedFields(Field(0, 0), 1, board);

	BOOST_CHECK_EQUAL(2, moves1.size());
	BOOST_CHECK_EQUAL(1, moves2.size());
	BOOST_CHECK_EQUAL(0, moves3.size());
}


BOOST_AUTO_TEST_SUITE_END()