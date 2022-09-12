#include "MaximizePlayer.h"
#include "MoveCalculator.h"
#include <random>
#include <ctime>
#include <vector>
#include "StrategyFactory.h"

REGISTER_STRATEGY(MaximizePlayer);

MaximizePlayer::MaximizePlayer():
	m_needsUserInteraction(false)
{

}

bool MaximizePlayer::getNeedsUserInteraction()
{
	return m_needsUserInteraction;
}

Field MaximizePlayer::getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board)
{
	MoveCalculator moveCalculator;
	std::vector<Field> flippedFields;
	std::vector<Field> bestFields;
	int bestNumberFieldsFlipped = 0;

	for (int i = 0; i < possibleMoves.size(); i++)
	{
		flippedFields = moveCalculator.calculateFlippedFields(possibleMoves[i], (areYouPlayer1 ? 1 : 2), board);
		if (flippedFields.size() > bestNumberFieldsFlipped)
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