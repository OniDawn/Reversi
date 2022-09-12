#include "FieldSystem.h"
#include <QDebug>


FieldSystem::FieldSystem(const Array2D &board, Size size) :
	m_board(board), m_size(size)
{

}

Field FieldSystem::coordToField(int xCoord, int yCoord)
{
	int xField = (xCoord / ((m_size.width) / (m_board.getSize().width)));

	int yField = (yCoord / ((m_size.height) / (m_board.getSize().height)));

	return Field(xField, yField);
}

int FieldSystem::fieldToCoordX(Field field)
{
	int xCoord = field.xPos * 100;

	return xCoord;
}

int FieldSystem::fieldToCoordY(Field field)
{
	int yCoord = field.yPos * 100;

	return yCoord;
}