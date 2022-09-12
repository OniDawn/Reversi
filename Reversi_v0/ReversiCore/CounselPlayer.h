#pragma once
#include "Strategy.h"
#include "DLL.h"
#include "StrategyFactory.h"
#include <QStringLiteral>

/// @brief simulates a game strategy where the next move is determined by choosing one of 4
/// possible moves calculated by different player strategies
class REVERSI_EXPORT CounselPlayer : public Strategy
{
	Q_OBJECT

public:
	static inline const auto Description = QStringLiteral("Setzt den Spielstein an die Stelle, die von den anderen Spielstrategien vorgeschlagen wird");
	static constexpr auto Name = "Counsel";

	CounselPlayer();
	~CounselPlayer();

	/// @brief calculates best move by calculating the fields that the other strategies would choose
	/// and determine the move by checking if one field is mentioned by multiple strategies or just choosing randomly
	/// @param possibleMoves vector that contains the moves that are possible for that player
	/// @param areYouPlayer1 is true if it is the turn of player 1 and false if it is the turn of player 2
	/// @param game board with information which field is occupied by whom
	/// @return field where the next token should be placed
	Field getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board) override;

	/// @return true if the strategy needs user interaction (needs a click) and false if it doesn´ts
	bool getNeedsUserInteraction() override;

private:
	//int m_player;
	bool m_needsUserInteraction;
	std::vector<std::shared_ptr<Strategy>> m_strategies;
};
