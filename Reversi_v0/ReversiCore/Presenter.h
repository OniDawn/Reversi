#pragma once
#include "DLL.h"
#include "Game.h"
#include "ViewInterface.h"
#include "FieldSystem.h"
#include <QObject>

/// @brief coordinates the different parts of the program, an instance of this class is generated in the main function
class REVERSI_EXPORT Presenter : public QObject
{
	Q_OBJECT

	public:
		/// @brief initializes the view and a game
		Presenter(ViewInterface& v, Game& g);

		/// @brief initializes the game and draws the board the first time
		void initializeGame();

		/// @brief simulates multiple games where everyone plays against each other once
		void simulateAllAgainstAll(int numberOfGames);

		/// @brief calls the play-function of the game class and coordinates the order of events
		int play(QString strategyPlayer1, QString strategyPlayer2);

		/// @brief makes one turn of a certain player
		/// @param turnPlayer 1 if it is the turn of the first player and 2 if it is the turn of the second player
		/// @return true if the turn was successful and false if there are no possible moves left
		bool makeOneTurn(int turnPlayer);

		/// @brief calls the draw-function of the view class and prints the board and the score
		void draw();

		/// @brief draws the start board with the 4 tokens in the middle of the board
		void drawStartBoard();

signals:
	/// @brief is emitted when the start button is pressed
	void startGameRequest();

public slots:
	/// @brief is called when the start button is pressed, starts the game
	void start();

	/// @brief is called when the user clicked on the label, makes a turn
	void userClickedTurn();

	/// @brief opens a window where the winner is displayed
	void showWinner();

	/// @brief updates the speed of the moves of the players that don´t need user interaction
	void updateSpeed();

private:
		ViewInterface& m_view;
		Game &m_game;
		int m_player;
		FieldSystem m_fieldSystem;
};