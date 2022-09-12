#include"Field.h"

Field::Field(int xPos, int yPos) :
	xPos(xPos), yPos(yPos)
{

}

bool Field::operator==(const Field& other) const 
{
	return((this->xPos == other.xPos) && (this->yPos == other.yPos));
}