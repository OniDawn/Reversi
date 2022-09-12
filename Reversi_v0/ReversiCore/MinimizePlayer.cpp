#include "MinimizePlayer.h"
#include "MoveCalculator.h"
#include "StrategyFactory.h"
#include <random>
#include <ctime>
#include <vector>

REGISTER_STRATEGY(MinimizePlayer);

MinimizePlayer::MinimizePlayer():
	m_needsUserInteraction(false)
{

}

bool MinimizePlayer::getNeedsUserInteraction()
{
	return m_needsUserInteraction;
}

Field MinimizePlayer::getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board)
{
	MoveCalculator moveCalculator = MoveCalculator();
	std::vector<Field> flippedFields = std::vector<Field>(0);
	std::vector<Field> bestFields = std::vector<Field>(0);
	int bestNumberFieldsFlipped = 100;

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		flippedFields = moveCalculator.calculateFlippedFields(possibleMoves[i], (areYouPlayer1 ? 1 : 2), board);
		if (flippedFields.size() < bestNumberFieldsFlipped)
		{
			bestFields.clear();
			bestFields.push_back(possibleMoves[i]);
			bestNumberFieldsFlipped = flippedFields.size();
		}
		if (flippedFields.size() == bestNumberFieldsFlipped)
		{
			bestFields.push_back(possibleMoves[i]);
		}
	}
	int randomNumber = (rand() % bestFields.size());

	return bestFields[randomNumber];
}