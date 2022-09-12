#include"MoveCalculator.h"


std::vector<Field> MoveCalculator::calculatePossibleMoves(Array2D board, bool areYouPlayerOne)
{
	std::vector<Field> possibleMoves = std::vector<Field>(0);
	bool foundField = false;

	//go through y positions
	for (int yPos = 0; yPos < board.getSize().height; yPos++)
	{
		//go through x positions
		for (int xPos = 0; xPos < board.getSize().width; xPos++)
		{
			foundField = false;
			//check if field is already occupied
			if (board.getValue(Field(xPos, yPos)) != 0)
			{
				continue;
			}
			//go through all directions (left top, top, right top, ...)
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					//if the next neighbor field would be outside the board check next direction
					if (xPos+j < 0 || yPos+i < 0 || xPos+j >= board.getSize().width || yPos + i >= board.getSize().height )
					{
						continue;
					}
					//if next neighbor field would be occupied by other player move into that direction
					if (board.getValue(Field(xPos+j,yPos+i)) == (areYouPlayerOne ? 2 : 1))
					{
						for (int moves = 1; moves < board.getSize().width; moves++) {
							//if the next field in that direction would be outside the board cancel the movement
							if (xPos + j*moves < 0 || yPos + i*moves < 0 || xPos + j*moves >= board.getSize().width || yPos + i*moves >= board.getSize().height)
							{
								break;
							}
							//if the next field would be empty cancel the movement
							if (board.getValue(Field(xPos + j * moves, yPos + i * moves)) == 0)
							{
								break;
							}
							//if the next field would be occupied by the player add source field to possibleMoves
							if (board.getValue(Field(xPos + j*moves, yPos + i*moves)) == (areYouPlayerOne ? 1 : 2))
							{
								possibleMoves.push_back(Field(xPos, yPos));
								foundField = true;
								break;
							}
						}
						if (foundField)
						{
							break;
						}
					}
				}
				if (foundField)
				{
					break;
				}
			}
		}
	}

	return possibleMoves;
}

std::vector<Field> MoveCalculator::calculateFlippedFields(Field field, int player, Array2D board)
{
	std::vector<Field> flippedFields = std::vector<Field>(0);

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			//if the next neighbor field would be outside the board check next direction
			if (field.xPos + j < 0 || field.yPos + i < 0 || field.xPos + j >= board.getSize().width || field.yPos + i >= board.getSize().height)
			{
				continue;
			}
			//if next neighbor field would be occupied by other player move into that direction
			if (board.getValue(Field(field.xPos + j, field.yPos + i)) == (player == 1 ? 2 : 1))
			{
				for (int moves = 1; moves < board.getSize().width; moves++) {
					//if the next field in that direction would be outside the board cancel the movement
					if (field.xPos + j * moves < 0 || field.yPos + i * moves < 0 || field.xPos + j * moves > board.getSize().width - 1 || field.yPos + i * moves > board.getSize().height - 1)
					{
						break;
					}
					//if the next field would be empty cancel the movement
					if (board.getValue(Field(field.xPos + j * moves, field.yPos + i * moves)) == 0)
					{
						break;
					}
					//if the next field would be occupied by the player add all fields in between to flippedFields
					if (board.getValue(Field(field.xPos + j * moves, field.yPos + i * moves)) == (player == 1 ? 1 : 2))
					{
						for (int g = 1; g < moves; g++)
						{
							flippedFields.push_back(Field(field.xPos + j * g, field.yPos + i * g));
						}
						break;
					}
				}
			}
		}
	}

	return flippedFields;
}
