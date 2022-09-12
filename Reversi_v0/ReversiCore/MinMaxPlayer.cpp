#include "MinMaxPlayer.h"
#include "StrategyFactory.h"


REGISTER_STRATEGY(MinMaxPlayer);

MinMaxPlayer::MinMaxPlayer() :
	m_needsUserInteraction(false)
{
	m_game = new Game(Array2D(Size(8, 8)), StrategyFactory(), MoveCalculator());
	m_tablePlayer = new TablePlayer();
	m_maxDepth = 4;
}

MinMaxPlayer::~MinMaxPlayer()
{
	delete m_game;
	delete m_tablePlayer;
}

bool MinMaxPlayer::getNeedsUserInteraction()
{
	return m_needsUserInteraction;
}

Field MinMaxPlayer::getBestMove(const std::vector<Field>& possibleMoves, bool areYouPlayer1, const Array2D& board)
{
	std::vector<Field> movesMade = std::vector<Field>();
	Array2D newBoard = board;
	return calculateBestMove(possibleMoves, newBoard, movesMade, areYouPlayer1).field;
}

FieldValuePair MinMaxPlayer::calculateBestMove(const std::vector<Field> &possibleMoves, Array2D &board, std::vector<Field> &movesMade, bool areYouPlayer1)
{
	if (movesMade.size() == m_maxDepth-1)
	{
		Field bestField = Field(0, 0);
		int bestValue = std::numeric_limits<int>::min();
		int value = 0;

		for (auto& movePossible : possibleMoves)
		{
			movesMade.push_back(movePossible);
			value = calculateValue(movesMade);
			movesMade.pop_back();
			if (value > bestValue)
			{
				bestValue = value;
				bestField = movePossible;
			}
			value = 0;
		}
		return FieldValuePair(bestField, bestValue);
	}
	else if (isMyTurn(movesMade))
	{
		std::vector<FieldValuePair> fieldValueVector;
		std::vector<Field> possibleMovesTemp = possibleMoves;

		for (auto& movePossible : possibleMoves)
		{
			
			movesMade.push_back(movePossible);
			Array2D newBoard = m_game->simulateUpdateBoard(board, movePossible, (areYouPlayer1 ? 1 : 2));
			possibleMovesTemp = m_game->simulateCalculatePossibleMoves(newBoard, (areYouPlayer1 ? 2 : 1));
			if (possibleMovesTemp.size() == 0)
			{
				return FieldValuePair(movePossible, 0);
			}
			fieldValueVector.push_back(calculateBestMove(possibleMovesTemp, newBoard, movesMade, !areYouPlayer1));
			movesMade.pop_back();
		}

		auto bestValueField = std::max_element(fieldValueVector.begin(), fieldValueVector.end(),
			[](const FieldValuePair& x,
				const FieldValuePair& y) {
					return x < y;
			});
		int index = std::distance(fieldValueVector.begin(), bestValueField);

		return FieldValuePair(possibleMoves[index], (*bestValueField).value);
	}
	else
	{
		std::vector<FieldValuePair> fieldValueVector;
		std::vector<Field> possibleMovesTemp = possibleMoves;

		for (auto& movePossible : possibleMoves)
		{
			movesMade.push_back(movePossible);
			Array2D newBoard = m_game->simulateUpdateBoard(board, movePossible, (areYouPlayer1 ? 2 : 1));
			possibleMovesTemp = m_game->simulateCalculatePossibleMoves(newBoard, (areYouPlayer1 ? 1 : 2));
			if (possibleMovesTemp.size() == 0)
			{
				return FieldValuePair(movePossible, 0);
			}
			fieldValueVector.push_back(calculateBestMove(possibleMovesTemp, newBoard, movesMade, areYouPlayer1));
			movesMade.pop_back();
		}

		auto worstValueField = std::min_element(fieldValueVector.begin(), fieldValueVector.end(),
			[](const FieldValuePair& x,
				const FieldValuePair& y) {
					return x < y;
			});
		int index = std::distance(fieldValueVector.begin(), worstValueField);

		return FieldValuePair(possibleMoves[index], (*worstValueField).value);
	}
}

bool MinMaxPlayer::isMyTurn(const std::vector<Field> &movesMade)
{
	return movesMade.size() % 2 != 0;
}

int MinMaxPlayer::calculateValue(const std::vector<Field> &movesMade)
{
	int value = 0;
	int prefix = 1;

	for (auto& moveMade : movesMade)
	{
		value += m_tablePlayer->getValue(moveMade) * prefix;
		prefix *= (-1);
	}

	return value;
}