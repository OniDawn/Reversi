#include"Array2D.h"
#include <stdexcept>

#if !defined(NDEBUG) || defined(DEBUG)
#	define ASSERT(EXPR, MSG) if (!(EXPR)) { throw std::invalid_argument(MSG); }
#else
#	define ASSERT(EXPR, MSG)
#endif

Array2D::Array2D(Size arraySize):
	m_array2DSize(arraySize)
{
	ASSERT(arraySize.height >= 0, "height must be greater or equal to zero");
	ASSERT(arraySize.width >= 0, "width must be greater or equal to zero");
	
	m_values = std::vector<int>(m_array2DSize.height * m_array2DSize.width);
}

void Array2D::setValue(Field field, int value)
{
	m_values[field.yPos * m_array2DSize.width + field.xPos] = value;
}

int Array2D::getValue(Field field) const
{
	return m_values[field.yPos * m_array2DSize.width + field.xPos];
}

Size Array2D::getSize() const
{
	return m_array2DSize;
}