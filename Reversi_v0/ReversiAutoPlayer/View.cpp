#include "View.h"
#include <string>
#include <map>
#include <iostream>

void View::drawBoard(Array2D board, int player)
{
	std::string output;
	for (int j = 0; j < board.getSize().height; j++)
	{
		for (int i = 0; i < board.getSize().width; i++)
		{
			output += (board.getValue(Field(i, j)) == 0 ? "_\t" : (board.getValue(Field(i, j)) == 1 ? "X\t" : "O\t"));
		}
		output += "\n\n";
	}
	std::cout << output << std::endl;
}


void  View::drawScore(int scorePlayer1, int scorePlayer2) const
{
	std::cout << std::endl << "Score Player 1: " << scorePlayer1 << std::endl;
	std::cout << "Score Player 2: " << scorePlayer2 << std::endl << std::endl;
}


QString  View::getCurrentStrategyPlayer1()
{
	return "Random";
}


QString  View::getCurrentStrategyPlayer2()
{
	return "Random";
}


int  View::getWidth() const
{
	return 0;
}


int  View::getHeight() const
{
	return 0;
}


void  View::drawPossibleMoves(std::vector<Field> moves) const
{

}


Size  View::getSizeClickableLabel() const
{
	return Size(0, 0);
}


QPoint  View::cursorPosition()
{
	return QPoint(0, 0);
}


void  View::showWinnerWindow(int player, int scorePlayer)
{
	
}


int  View::getCurrentSpeed()
{
	return 0;
}

void View::drawAllStrategiesUsed(QString player1Strategy, QString player2Strategy)
{
	std::cout << "Es spielt " << player1Strategy.toStdString() << " gegen " << player2Strategy.toStdString() << std::endl;
}

void View::showAllAgainstAllTable(std::vector<QString> &winners)
{
	std::cout << " GAME   | WINNER " << std::endl;
	std::cout << "--------|-----------------" << std::endl;
	for (int i = 0; i < winners.size(); i++)
	{
		QString twoDigits = "     | ";
		QString oneDigit = "      | ";
		std::cout << " " << i << (i > 9 ? twoDigits.toStdString() : oneDigit.toStdString()) << winners[i].toStdString() << std::endl;
		std::cout << "--------|-----------------" << std::endl;
	}
	showRankingList(winners);
}

void View::showRankingList(std::vector<QString> &winners)
{
	std::sort(winners.begin(), winners.end());
	std::map<QString, int> winnerCount;
	for (auto& winner : winners)
	{
		++winnerCount[winner];
	}
	std::vector<WinnerFrequencyPair> winnerOrder;
	for (const auto& winner : winnerCount) {
		winnerOrder.push_back(WinnerFrequencyPair(winner.first, winner.second));
	}

	std::sort(winnerOrder.begin(), winnerOrder.end());

	for (int i = winnerOrder.size()-1; i > -1; i--)
	{
		std::cout << std::endl << "Platz " << winnerOrder.size() - i << ": " << winnerOrder[i].winnerName.toStdString() << " mit " << winnerOrder[i].winnerFrequency << " Siegen" << std::endl;
	}

}