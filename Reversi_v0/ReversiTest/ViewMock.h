#pragma once
#include "ReversiCore/ViewInterface.h"

class ViewMock : public ViewInterface
{
	public:
		void draw(Array2D board) const override
		{

		}

		void drawScore(int scorePlayer1, int scorePlayer2) const override
		{

		}

		int getWidth() const override
		{
			return 8;
		}

		int getHeight() const override
		{
			return 8;
		}
};
