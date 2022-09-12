#include "HumanPlayer.h"
#include "StrategyFactory.h"

REGISTER_STRATEGY(HumanPlayer);

HumanPlayer::HumanPlayer() :
	m_needsUserInteraction(true)
{
	
}

bool HumanPlayer::getNeedsUserInteraction()
{
	return m_needsUserInteraction;
}

Field HumanPlayer::getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board)
{
	return Field(0, 0);
}
