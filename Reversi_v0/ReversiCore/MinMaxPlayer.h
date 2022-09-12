#pragma once
#include "Strategy.h"
#include "TablePlayer.h"
#include "DLL.h"
#include "Game.h"
#include "FieldValuePair.h"


/// @brief simulates a game strategy where the next move is determined by calculating the best 4 moves
/// from both players and choosing the one, that has the best outcome
class REVERSI_EXPORT MinMaxPlayer : public Strategy
{
	Q_OBJECT

public:
	static inline const auto Description = QStringLiteral("Setzt den Spielstein an die Stelle, die durch Berechnung der nächsten 4 Züge am meisten bringt");
	static constexpr auto Name = "MinMaxAlgorithm";

	MinMaxPlayer();

	~MinMaxPlayer();

	/// @brief calculates best move by calculating the best possible moves for this player and for the other player for the next 4 moves with a table
	/// @param possibleMoves vector that contains the moves that are possible for that player
	/// @param areYouPlayer1 is true if it is the turn of player 1 and false if it is the turn of player 2
	/// @param board game board with information which field is occupied by whom
	/// @return field where the next token should be placed
	Field getBestMove(const std::vector<Field>& possibleMoves, bool areYouPlayer1, const Array2D& board) override;

	/// @brief calculates best move by calculating the best possible moves for this player and for the other player for the next 4 moves with a table
	/// @param possibleMoves vector that contains the moves that are possible for that player
	/// @param board  with information which field is occupied by whom
	/// @param movesMade moves that have already been made
	/// @param areYouPlayer1 is true if it is the turn of player 1 and false if it is the turn of player 2
	/// @return FieldValuePar that contains the best possible field and the value that would result if you choose this move
	FieldValuePair calculateBestMove(const std::vector<Field> &possibleMoves, Array2D &board, std::vector<Field> &movesMade, bool areYouPlayer1);

	/// @brief calculates the value of the moves that have been made to this specific state with the table of the tablePlayer
	/// @param movesMade moves that have already been made
	/// @return integer that represents the value
	int calculateValue(const std::vector<Field> &movesMade);

	/// @brief checks which turn it is, so it can be determined if the player is searching for the highest or the lowest value
	/// @param mavesMade moves that alredy have been made
	/// @return bool that is true, if it is the turn of the player who is currently on the move
	bool isMyTurn(const std::vector<Field> &movesMade);

	/// @return true if the strategy needs user interaction (needs a click) and false if it doesn´t
	bool getNeedsUserInteraction() override;

private:
	bool m_needsUserInteraction;
	TablePlayer* m_tablePlayer;
	Game* m_game;
	int m_maxDepth;
};
