#pragma once
#include "DLL.h"
/// @brief Size contains a rectangle
struct REVERSI_EXPORT Size
{
	/// @brief initializes the width and height of the rectangle
	Size(int width, int height);

	int width;
	int height;
};