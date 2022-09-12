#pragma once
#include "DLL.h"
#include "Array2D.h"
#include "Strategy.h"
#include "StrategyFactory.h"
#include "Field.h"
#include "MoveCalculator.h"
#include <QObject>

/// @brief handles the logic of the game
class REVERSI_EXPORT Game : public QObject
{
	Q_OBJECT

	public:
		/// @brief initializes the game 
		/// @param board Array2D that contains the information which field is occupied by whom
		/// @param factory selects the strategy of the players depending on what strategy is chosen
		/// @param moveCalculator contains the math of the game (calculates the possible fields and what fields have to flip)
		Game(Array2D board, StrategyFactory factory, MoveCalculator moveCalculator);
		
		Game(Array2D board);

		~Game();

		/// @brief initializes the strategy
		/// @param player1Strategy string that contains the strategy according to which the first player should proceed
		/// @param player2Strategy string that contains the strategy according to which the second player should proceed
		void initializePlayerStrategy(const QString &player1Strategy, const QString &player2Strategy);

		/// @brief makes one turn without user interaction
		/// @param numberPlayer 1 if it is the turn of player 1 and 2 if it is the turn of the player 2
		/// @retun true if the player can place a token and false if there are no possible fields
		bool play(int numberPlayer);
		
		
		/// @return game board
		const Array2D &getBoard() const;


		/// @brief simulates how a board is updates after a move and flips the tokens in between after a player has placed one
		/// @param board Array that contains the board information
		/// @param field field on the game board that should be occupied
		/// @param player 1 if player 1 has placed a token and 2 if player 2 has placed a token
		/// @return updated board
		Array2D simulateUpdateBoard(Array2D &board, Field field, int player);

		/// @brief simulates how the possible moves of a player would be calculated
		/// @param board Array that contains the board information
		/// @param player 1 if player 1 has placed a token and 2 if player 2 has placed a token
		/// @return possible moves
		std::vector<Field> simulateCalculatePossibleMoves(const Array2D &board, int player);
		

		/// @brief initializes the game by adding tokens to the 4 fields in the middle of the board
		/// @param speed integer that represents the speed of the players that do not require interaction of the user in milliseconds
		void initialize(int speed);

		/// @brief updates the board and flips the tokens in between after a player has placed one
		/// @param field field on the game board that should be occupied
		/// @param player 1 if player 1 has placed a token and 2 if player 2 has placed a token
		void updateBoard(Field field, int player);

		/// @brief counts the number of fields one player has occupied
		/// @param player 1 if the score of player 1 is to be determined an 2 if thats the case for player 2 
		void countScore(int player);
		
		/// @return score of player 1
		int getScorePlayer1() const;
		
		/// @return score of player 2
		int getScorePlayer2() const;
		

		/// @brief calculates all fields for one player that could possibly be occupied by this player
		/// @param player 1 if the score of player 1 is to be determined an 2 if thats the case for player 2 
		std::vector<Field> calculatePossibleMoves(int player);

		/// @brief updates the speed of the moves of the players that don�t need user interaction
		/// @param speed integer that represents the speed of the moves in milliseconds
		void updateSpeed(int speed);

signals:

	/// @brief is emitted when a player has selected his next move
	void boardDrawRequest();

	/// @brief is emitted when there are no more available moves for one player 
	void gameFinished();

	/// @brief is emitted when the game is finished and the winner is determined
	void winnerDetermined();

public slots:

	/// @brief is called, when the game has started and when a player who needs user interaction has finished his turn, simulates a turn
	/// if the player does not need user interaction it calls the method play and when play was successful the method calls itself again
	void nextTurn();

	/// @brief is called, when the player clicked on a field, checks if the user clicked on a possible field and updates the board
	/// @param field field on which the user has clicked
	void userClickedTurn(Field field);

	/// @brief is called when the game ended, sets the variable to false, that is responsible for whether further moves are executed or not
	void endGame();

	/// @brief is called when the game starts, sets the variable to true, that is responsible for whether further moves are executed or not
	void gameIsOn();

	/// @brief is called when the game gets initialized, resets the score of the two players
	void resetScore();


	private:
		Array2D m_gameBoard;
		bool m_isPlayer1Turn;
		std::shared_ptr<Strategy> m_player1;
		std::shared_ptr<Strategy> m_player2;
		MoveCalculator m_moveCalculator;
		int m_scorePlayer1;
		int m_scorePlayer2;
		bool m_isPlayerStrategyInitialized;
		bool m_waitForClick;
		bool m_possibleMovesAvailable;
		bool m_gameIsOn;
		int m_speed;
};
