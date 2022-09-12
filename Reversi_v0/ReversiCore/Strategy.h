#pragma once
#include"Field.h"
#include"Array2D.h"
#include <vector>
#include <QObject>

/// @brief simulates a game strategy
class Strategy : public QObject
{
	Q_OBJECT

	public:
		/// @brief calculates the best next move
		/// @return field where the next token should be placed
		virtual Field getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board) = 0;
		
		/// @return true if the strategy needs user interaction (needs a click) and false if it doesn´t
		virtual bool getNeedsUserInteraction() = 0;
		

private:
	int m_player;
	bool m_needsUserInteraction;

};
