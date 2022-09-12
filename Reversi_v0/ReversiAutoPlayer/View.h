#pragma once
#include "ReversiCore/ViewInterface.h"

class View : public virtual ViewInterface
{
public:
	/// @brief draws the game board
	void drawBoard(Array2D board, int player) override;

	/// @brief draws the score
	/// @param scorePlayer1 score of the first player
	/// @param scorePlayer2 score of the second player
	void drawScore(int scorePlayer1, int scorePlayer2) const override;

	/// @return strategy of the first player
	QString getCurrentStrategyPlayer1() override;

	/// @return strategy of the second player
	QString getCurrentStrategyPlayer2() override;

	/// @return width of the view
	int getWidth() const override;

	/// @return height of the view
	int getHeight() const override;

	/// @brief shows all possible moves for one player
	/// @param moves all possible moves
	void drawPossibleMoves(std::vector<Field> moves) const override;

	/// @return size of the clickable label 
	Size getSizeClickableLabel() const override;

	/// @return cursor position
	QPoint cursorPosition() override;

	/// @brief opens window where the winner is displayed 
	/// @param player 1 if the first player is the winner and 2 if the second player is the winner
	/// @param scorePlayer integer that represents the score of the player
	void showWinnerWindow(int player, int scorePlayer) override;

	/// @return returns current speed
	int getCurrentSpeed() override;

	/// @brief shows the strategies of the players
	void drawAllStrategiesUsed(QString player1Strategy, QString player2Strategy) override;

	/// @brief shows table of the winners
	/// @param winners contains the players who won in one on one against each other
	void showAllAgainstAllTable(std::vector<QString> &winners) override;

	void showRankingList(std::vector<QString> &winners);

private:
	struct WinnerFrequencyPair
	{
		WinnerFrequencyPair(QString name, int frequency)
		{
			winnerName = name;
			winnerFrequency = frequency;
		}

		bool operator<(const WinnerFrequencyPair& other) const
		{
			return this->winnerFrequency < other.winnerFrequency;
		}

		QString winnerName;
		int winnerFrequency;
	};
};