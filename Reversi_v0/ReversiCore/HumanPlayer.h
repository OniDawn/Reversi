#pragma once
#include "Strategy.h"
#include "DLL.h"

/// @brief simulates a game strategy where the next move is determined by the the user by clicking on a field
class REVERSI_EXPORT HumanPlayer : public Strategy
{
	Q_OBJECT

public:
	static inline const auto Description = QStringLiteral("Setzt den Spielstein an die Stelle, an die man klickt");
	static constexpr auto Name = "Human";

	HumanPlayer();

	/// @brief just overrides the getBestMove function but is not called
	/// @return field
	Field getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board) override;

	/// @return true if the strategy needs user interaction (needs a click) and false if it doesn´t
	bool getNeedsUserInteraction() override;
	

private:
	bool m_needsUserInteraction;
};

