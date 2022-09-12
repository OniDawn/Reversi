#include "View.h"
#include <iostream>
#include <string>

using namespace std;

View::View(int width, int height) : 
	m_width(width), m_height(height)
{

}

void View::draw(Array2D board)
{
	string output;
	for (int j = 0; j < m_height; j++)
	{
		for (int i = 0; i < m_width; i++)
		{
			output += (board.getValue(Field(i, j)) == 0 ? "_\t" : (board.getValue(Field(i, j)) == 1 ? "X\t" : "O\t"));
		}
		output += "\n\n";
	}
	cout << output << "\n";
}

void View::drawScore(int scorePlayer1, int scorePlayer2) const
{
	cout << "Score: \n" << "Player 1: " << scorePlayer1 << "\nPlayer 2: " << scorePlayer2 << "\n\n\n\n";
}

int View::getWidth() const
{
	return m_height;
}

int View::getHeight() const
{
	return m_height;
}

int View::getCurrentStrategyPlayer1Index()
{
	return 0;
}
int View::getCurrentStrategyPlayer2Index()
{
	return 0;
}

void View::drawPossibleMoves(std::vector<Field> moves) const
{
	cout << "Possible Moves: \n";
	for (int i = 0; i < moves.size(); i++)
	{
		cout << moves[i].xPos << ", " << moves[i].yPos << "\n";
	}

	cout << "\n\n";
}

void View::drawAllStrategiesUsed()
{

}