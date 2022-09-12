#pragma once
#include "Field.h"

struct FieldValuePair
{
	FieldValuePair(Field field, int value);

	bool operator<(const FieldValuePair& other)	const;

	Field field;
	int value;
};
