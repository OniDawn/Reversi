#include"TablePlayer.h"
#include "StrategyFactory.h"
#include <random>
#include <ctime>

REGISTER_STRATEGY(TablePlayer);

TablePlayer::TablePlayer() :
	m_tableBestMoves(Array2D(Size(8, 8))), m_needsUserInteraction(false)
{
	//initialize tbaleBestMoves
	for (int i = 0; i < 8; i = i + 7)
	{
		m_tableBestMoves.setValue(Field(0, i), 9999);
		m_tableBestMoves.setValue(Field(1, i), 5);
		m_tableBestMoves.setValue(Field(2, i), 500);
		m_tableBestMoves.setValue(Field(3, i), 200);
		m_tableBestMoves.setValue(Field(4, i), 200);
		m_tableBestMoves.setValue(Field(5, i), 500);
		m_tableBestMoves.setValue(Field(6, i), 5);
		m_tableBestMoves.setValue(Field(7, i), 9999);
	}

	for (int i = 1; i < 8; i = i + 5)
	{
		m_tableBestMoves.setValue(Field(0, i), 5);
		m_tableBestMoves.setValue(Field(1, i), 1);
		m_tableBestMoves.setValue(Field(2, i), 50);
		m_tableBestMoves.setValue(Field(3, i), 150);
		m_tableBestMoves.setValue(Field(4, i), 150);
		m_tableBestMoves.setValue(Field(5, i), 50);
		m_tableBestMoves.setValue(Field(6, i), 1);
		m_tableBestMoves.setValue(Field(7, i), 5);
	}

	for (int i = 2; i < 8; i = i + 3)
	{
		m_tableBestMoves.setValue(Field(0, i), 500);
		m_tableBestMoves.setValue(Field(1, i), 50);
		m_tableBestMoves.setValue(Field(2, i), 250);
		m_tableBestMoves.setValue(Field(3, i), 100);
		m_tableBestMoves.setValue(Field(4, i), 100);
		m_tableBestMoves.setValue(Field(5, i), 250);
		m_tableBestMoves.setValue(Field(6, i), 50);
		m_tableBestMoves.setValue(Field(7, i), 500);
	}
	for (int i = 3; i < 8; i = i + 1)
	{
		m_tableBestMoves.setValue(Field(0, i), 200);
		m_tableBestMoves.setValue(Field(1, i), 150);
		m_tableBestMoves.setValue(Field(2, i), 100);
		m_tableBestMoves.setValue(Field(3, i), 50);
		m_tableBestMoves.setValue(Field(4, i), 50);
		m_tableBestMoves.setValue(Field(5, i), 100);
		m_tableBestMoves.setValue(Field(6, i), 150);
		m_tableBestMoves.setValue(Field(7, i), 200);
	}
}

int TablePlayer::getValue(Field field)
{
	return m_tableBestMoves.getValue(field);
}

bool TablePlayer::getNeedsUserInteraction()
{
	return m_needsUserInteraction;
}

Field TablePlayer::getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board)
{
	std::vector<Field> bestFields = std::vector<Field>(0);
	int bestValue = 0;

	for (int i = 0; i < possibleMoves.size(); i++) 
	{
		if (m_tableBestMoves.getValue(possibleMoves[i]) > bestValue)
		{
			bestFields.clear();
			bestFields.push_back(possibleMoves[i]);
			bestValue = m_tableBestMoves.getValue(possibleMoves[i]);
		}
		else if (m_tableBestMoves.getValue(possibleMoves[i]) == bestValue)
		{
			bestFields.push_back(possibleMoves[i]);
		}
	}

	int randomNumber = (rand() % bestFields.size());

	return bestFields[randomNumber];
}