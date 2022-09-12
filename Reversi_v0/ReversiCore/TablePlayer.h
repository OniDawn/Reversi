#pragma once
#include "DLL.h"
#include "Strategy.h"

/// @brief simulates a game strategy where the next move is determined by the amount of value that is recorded in a table
class REVERSI_EXPORT TablePlayer : public Strategy
{
	Q_OBJECT

	public:
		static inline const auto Description = QStringLiteral("Setzt den Spielstein an die Stelle, die den höchsten Wert hat");
		static constexpr auto Name = "Table";

		/// @brief initializes table where the amount of the value of every field is listed
		TablePlayer();

		int getValue(Field field);

		/// @brief calculates best move by selecting the fields with the highest amount of value and then choose randomly 
		/// @param possibleMoves vector that contains the moves that are possible for that player
		/// @param areYouPlayer1 is true if it is the turn of player 1 and false if it is the turn of player 2
		/// @param game board with information which field is occupied by whom
		/// @return field where the next token should be placed
		Field getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board) override;
		
		/// @return true if the strategy needs user interaction (needs a click) and false if it doesn´t
		bool getNeedsUserInteraction() override;
		

	private:
		Array2D m_tableBestMoves;
		bool m_needsUserInteraction;
};