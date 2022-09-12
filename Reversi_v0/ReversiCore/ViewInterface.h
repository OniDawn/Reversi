#pragma once
#include "Array2D.h"
#include "DLL.h"
#include <functional>
#include <vector>
#include <qstring>
#include <QObject>

/// @brief interface for the view class so there could be a mock object for the view class so the presenter can be tested
class REVERSI_EXPORT ViewInterface : public QObject 	
{
	Q_OBJECT
public:
	/// @brief draws the game board
	virtual void drawBoard(Array2D board, int player) = 0;

	/// @brief draws the score
	/// @param scorePlayer1 score of the first player
	/// @param scorePlayer2 score of the second player
	virtual void drawScore(int scorePlayer1, int scorePlayer2) const = 0;

	/// @return strategy of the first player
	virtual QString getCurrentStrategyPlayer1() = 0;

	/// @return strategy of the second player
	virtual QString getCurrentStrategyPlayer2() = 0;

	/// @return width of the view
	virtual int getWidth() const = 0;

	/// @return height of the view
	virtual int getHeight() const = 0;

	/// @brief shows all possible moves for one player
	/// @param moves all possible moves
	virtual void drawPossibleMoves(std::vector<Field> moves) const = 0;

	/// @return size of the clickable label 
	virtual Size getSizeClickableLabel() const = 0;

	/// @return cursor position
	virtual QPoint cursorPosition() = 0;

	/// @brief opens window where the winner is displayed 
	/// @param player 1 if the first player is the winner and 2 if the second player is the winner
	/// @param scorePlayer integer that represents the score of the player
	virtual void showWinnerWindow(int player, int scorePlayer) = 0;

	/// @return returns current speed
	virtual int getCurrentSpeed() = 0;

	/// @brief shows the strategies of the players
	virtual void drawAllStrategiesUsed(QString player1Strategy, QString player2Strategy) = 0;

	/// @brief shows table of the winners
	/// @param winners contains the players who won in one on one against each other
	virtual void showAllAgainstAllTable(std::vector<QString> &winners) = 0;

signals:
	/// @brief is emitted when the start button is pressed
	void startGame();

	/// @brief is emitted when the window is closed
	void gameCloseRequest();

	/// @brief is emitted when the user has clicked on the left
	void clickedLeft();

	/// @brief is emitted when the end button is pressed
	void endGameRequest();

	/// @brief is emitted when the horizontal slider has changed it value
	void speedUpdateRequest();
};

