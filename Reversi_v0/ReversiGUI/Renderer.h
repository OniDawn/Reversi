#pragma once
#include "ReversiCore/Array2D.h"
#include "ReversiCore/FieldSystem.h"
#include <QImage>

/// @brief renders the images
class Renderer
{
	public:
		/// @brief constructor of renderer
		/// @param board array that contains the information about the fileds on the game board
		/// @param size contains height and width
		Renderer(Array2D board, Size size);

		/// @brief default constructor
		Renderer() = default;

		/// @brief calculates the image of the board
		/// @return QImage that represents the game board with field boundaries
		QImage calculateBoardImage();

		/// @brief updates the board
		/// @param board array that contains the information about the fields on the game board
		/// @param image QImage that already contains the board before it is updated
		/// @return QImage that represents the game board with field boundaries and tokens in different colors 
		QImage updateBoard(Array2D board, QImage image);

		/// @brief updates the little label in the upper right corner that shows who is next
		/// @param player 1 if it is the turn of the first player and 2 if it is the turn of the second player
		/// @return QImage that contains a token with the color of the player
		QImage updateLabelWhosNext(int player);

		/// @brief calculates the label for the area where the score is displayed
		/// @param player 1 if it is the turn of the first player and 2 if it is the turn of the second player 
		/// @return QImage that contains a token with the color of the player in a small size
		QImage calculateScoreLabel(int player);

	private:
		Array2D m_array;
		Size m_size;
		FieldSystem m_fieldSystem;
};