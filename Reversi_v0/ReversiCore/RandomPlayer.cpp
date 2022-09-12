#include "RandomPlayer.h"
#include "StrategyFactory.h"
#include <functional>
#include <random>
#include <ctime>

REGISTER_STRATEGY(RandomPlayer);

RandomPlayer::RandomPlayer() :
	m_needsUserInteraction(false)
{

}

bool RandomPlayer::getNeedsUserInteraction()
{
	return m_needsUserInteraction;
}

Field RandomPlayer::getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board)
{
	int numberField = (rand() % (possibleMoves.size()));

	return possibleMoves[numberField];
}