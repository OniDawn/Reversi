#pragma once
#include "DLL.h"
#include <functional>

/// @brief struct that represents a field
struct REVERSI_EXPORT Field
{
	/// @brief initializes the x and y position of a field
	Field(int xPos, int yPos);

	Field() = default;

	/// @brief checks if two fields are equal
	/// @param other field that the field should be compared to
	/// @return true if the fields have the same x and y coordinate
	bool operator==(const Field& other)	const;

	int xPos;
	int yPos;
};

template<>
struct std::hash<Field>
{
	inline std::size_t operator() (const Field& field) const noexcept
	{
		std::size_t h1 = std::hash<int>()(field.xPos);
		std::size_t h2 = std::hash<int>()(field.yPos);
		return h1 ^ (h2 << 4);
	}
};