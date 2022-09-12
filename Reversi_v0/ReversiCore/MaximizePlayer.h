#pragma once
#include "Strategy.h"
#include "DLL.h"

/// @brief simulates a game strategy where the next move is the move, where the least tokens have to be flipped
class REVERSI_EXPORT MaximizePlayer : public Strategy
{
	Q_OBJECT

	public:
		static inline const auto Description = QStringLiteral("Setzt den Spielstein an die Stelle, an der am meisten Steine umgedreht werden");
		static constexpr auto Name = "Maximize";

		MaximizePlayer();

		/// @brief calculates best move by selecting the fields where the most tokens would be flipped and than chooses randomly
		/// @param possibleMoves vector that contains the moves that are possible for that player
		/// @param areYouPlayer1 is true if it is the turn of player 1 and false if it is the turn of player 2
		/// @param game board with information which field is occupied by whom
		/// @return field where the next token should be placed
		Field getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board) override;

		/// @return true if the strategy needs user interaction (needs a click) and false if it doesn´t
		bool getNeedsUserInteraction() override;
		

private:
	bool m_needsUserInteraction;

};