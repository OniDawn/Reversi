#pragma once
#include "DLL.h"
#include "Size.h"
#include "Field.h"
#include <vector>

/// @brief translates a vector into a two dimensional board with fields where every field could have a value
class REVERSI_EXPORT Array2D
{
	public:
		/// @brief initializes the size of the array and initializes an array with that size
		Array2D(Size arraySize);

		Array2D() = default;

		/// @brief sets the value on the specific field
		/// @param field field on that the value should be changed
		/// @param value value that is to be entered
		void setValue(Field field, int value);

		/// @return value on that field
		int getValue(Field field) const;

		/// @return size of the array
		Size getSize() const;
	private:
		Size m_array2DSize;
		std::vector<int> m_values;
};