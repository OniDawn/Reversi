#include "FieldValuePair.h"

FieldValuePair::FieldValuePair(Field field, int value):
	field(field), value(value)
{

}

bool FieldValuePair::operator<(const FieldValuePair& other)	const
{
	return this->value < other.value;
}