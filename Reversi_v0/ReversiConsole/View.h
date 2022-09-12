#pragma once
#include "ReversiCore/ViewInterface.h"
#include "ReversiCore/Array2D.h"

/// @brief prints into console
class View : public ViewInterface
{
	Q_OBJECT
	public:
		/// @brief initializes width an height
		/// @param width width of the game board
		/// @param height height of the game board
		View(int width, int height);

		/// @brief prints game board into console (occupied by player1 = 'X', occupied by Player 2 = 'O', else = '_')
		/// @param board Array2D which contains the game board
		void draw(Array2D board);

		/// @brief prints the score into the console
		/// @param scorePlayer1 number of fields occupied by player 1
		/// @param scorePlayer2 number of fields occupied by player 2
		void drawScore(int scorePlayer1, int scorePlayer2) const;

		/// @return value of the width of the game board
		int getWidth() const;

		/// @return value of the height of the game board
		int getHeight() const;

		int getCurrentStrategyPlayer1Index();
		int getCurrentStrategyPlayer2Index();

		void drawPossibleMoves(std::vector<Field> moves) const;

		void drawAllStrategiesUsed();

	private:
		int m_width;
		int m_height;
};