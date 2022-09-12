#pragma once
#include "DLL.h"
#include <vector>
#include "Field.h"
#include "Array2D.h"

/// @brief handles the calculation of the possible fields and the fields that schould be flipped
class REVERSI_EXPORT MoveCalculator
{
	public:
		MoveCalculator() = default;

		/// @brief calculates the possible fields where one player could place their token
		/// @param board Array2D that contains the information which field is occupied by whom
		/// @param areYouPlayerOne true if it is the turn of player 1 and false if it is the turn of player 2
		/// @return a vector of fields where the player could place his next token
		std::vector<Field> calculatePossibleMoves(Array2D board, bool areYouPlayerOne);

		/// @brief calculates the fields, that have to be flipped after placing the token on a specific field
		/// @param field field where the token is placed
		/// @param player number of player whos turn it is
		/// @param board Array2D that contains the information which field is occupied by whom
		/// @return a vector of fields where the player could place his next token
		std::vector<Field> calculateFlippedFields(Field field, int player, Array2D board);

};
