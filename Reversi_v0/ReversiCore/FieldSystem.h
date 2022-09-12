#pragma once
#include "Array2D.h"
#include "Size.h"

/// @brief converts a coordinate into a field and the other way around
class REVERSI_EXPORT FieldSystem
{
	public:
		/// @brief creates a FieldSystem
		/// @param board contains the number of fields
		/// @param size contains the pixel length in x and y direction
		FieldSystem(const Array2D &board, Size size);

		/// @brief converts coordinates into a field
		/// @param xCoord integer that represents the x-coordinate of the pixel
		/// @param yCoord integer that represents the y-coordinate of the pixel
		/// @return field in which the coordinates are located
		Field coordToField(int xCoord, int yCoord);

		/// @brief converts a field into a x coordinate
		/// @param field field that should be converted
		/// @return integer that represents the x coordinate
		int fieldToCoordX(Field field);

		/// @brief converts a field into a y coordinate
		/// @param field field that should be converted
		/// @return integer that represents the y coordinate
		int fieldToCoordY(Field field);

	private:
		Size m_size;
		Array2D m_board;
};