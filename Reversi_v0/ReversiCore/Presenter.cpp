#include "Presenter.h"
#include "FieldSystem.h"
#include "CommonMacros.h"
#include <QTime>
#include <QCoreApplication>
#include <QDebug>

Presenter::Presenter(ViewInterface& v, Game& g) :
	m_view(v), m_game(g), m_player(2), m_fieldSystem(FieldSystem(m_game.getBoard(), m_view.getSizeClickableLabel()))
{

	connect(&m_view, &ViewInterface::startGame, &m_game, &Game::gameFinished);
	connect(&m_view, &ViewInterface::startGame, &m_game, &Game::endGame);
	connect(&m_view, &ViewInterface::startGame, this, &Presenter::start);
	connect(&m_game, &Game::boardDrawRequest, this, &Presenter::draw);
	
	connect(this, &Presenter::startGameRequest, &m_game, &Game::gameIsOn);
	connect(this, &Presenter::startGameRequest, &m_game, &Game::nextTurn);
	connect(this, &Presenter::startGameRequest, &m_game, &Game::resetScore);

	connect(&m_view, &ViewInterface::clickedLeft, this, &Presenter::userClickedTurn);

	connect(&m_view, &ViewInterface::gameCloseRequest, &m_game, &Game::gameFinished);
	connect(&m_view, &ViewInterface::gameCloseRequest, &m_game, &Game::endGame);

	connect(&m_game, &Game::winnerDetermined, this, &Presenter::showWinner);
	connect(&m_view, &ViewInterface::endGameRequest, &m_game, &Game::gameFinished);
	connect(&m_view, &ViewInterface::speedUpdateRequest, this, &Presenter::updateSpeed);
	
}

void Presenter::initializeGame()
{
	m_game.initialize(m_view.getCurrentSpeed());
	draw();
}

void Presenter::simulateAllAgainstAll(int numberOfGames)
{
	int countWinsPlayer1 = 0;
	int countWinsPlayer2 = 0;
	std::vector<QString> winners = std::vector<QString>();
	for (auto& strategyPlayer1 : StrategyFactory::instance().getNames())
	{
		if (strategyPlayer1 == "Human")
		{
			continue;
		}
		for (auto& strategyPlayer2 : StrategyFactory::instance().getNames())
		{
			if (strategyPlayer2 == "Human" || strategyPlayer2 == strategyPlayer1)
			{
				continue;
			}
			std::vector<int> playerWin = std::vector<int>();
			for (int i = 0; i < numberOfGames; i++)
			{
				playerWin.push_back(play(strategyPlayer1, strategyPlayer2));
			}
			for (const int target : {1}) {
				countWinsPlayer1 = std::count(playerWin.cbegin(), playerWin.cend(), target);
			}
			for (const int target : {2}) {
				countWinsPlayer2 = std::count(playerWin.cbegin(), playerWin.cend(), target);
			}
			if (countWinsPlayer1 > countWinsPlayer2)
			{
				winners.push_back(strategyPlayer1);
			}
			else if (countWinsPlayer1 < countWinsPlayer2)
			{
				winners.push_back(strategyPlayer2);
			}
		}
	}
	m_view.showAllAgainstAllTable(winners);
}

int Presenter::play(QString strategyPlayer1, QString strategyPlayer2)
{
	m_game.initialize(m_view.getCurrentSpeed());
	m_game.initializePlayerStrategy(strategyPlayer1, strategyPlayer2);
	bool n = true;
	int turnPlayer = 1;
	while (n)
	{
		n = m_game.play(turnPlayer);
		m_game.countScore(turnPlayer);
		turnPlayer = (turnPlayer == 1 ? 2 : 1);
		m_game.countScore(turnPlayer);
	} 
	//m_view.drawScore(m_game.getScorePlayer1(), m_game.getScorePlayer2());
	m_view.drawAllStrategiesUsed(strategyPlayer1, strategyPlayer2);
	//m_view.showWinnerWindow(player, scorePlayer);

	if (m_game.getScorePlayer1() > m_game.getScorePlayer2())
	{
		return 1;
	}
	else if (m_game.getScorePlayer1() < m_game.getScorePlayer2())
	{
		return 2;
	}
	else
	{
		return 0;
	}

}

bool Presenter::makeOneTurn(int turnPlayer)
{
	bool n = m_game.play(turnPlayer);
	m_game.countScore(turnPlayer);
	turnPlayer = (turnPlayer == 1 ? 2 : 1);
	m_game.countScore(turnPlayer);
	draw();
	return n;
}

void Presenter::draw()
{
	m_view.drawBoard(m_game.getBoard(), m_player);
	m_player = (m_player == 1 ? 2 : 1);
	m_view.drawScore(m_game.getScorePlayer1(), m_game.getScorePlayer2());
}

void Presenter::drawStartBoard()
{
	m_view.drawBoard(m_game.getBoard(), 2);
}

void Presenter::start()
{
	m_game.initializePlayerStrategy(m_view.getCurrentStrategyPlayer1(), m_view.getCurrentStrategyPlayer2());
	m_player = 2;
	initializeGame();
	
	emit startGameRequest();
}

void Presenter::userClickedTurn()
{
	Field f = m_fieldSystem.coordToField(m_view.cursorPosition().x(), m_view.cursorPosition().y());
	m_game.userClickedTurn(f);


	LOG("SLOT: userClickedTurn, Coordinates: " << QString::number(m_view.cursorPosition().x()) << ", " << QString::number(m_view.cursorPosition().y()));
	LOG("SLOT: userClickedTurn, Field: " << f.xPos << ", " << f.yPos);

}


void Presenter::showWinner()
{
	int winner = 0;
	if (m_game.getScorePlayer1() < m_game.getScorePlayer2())
	{
		winner = 2;
	}
	else if (m_game.getScorePlayer1() > m_game.getScorePlayer2())
	{
		winner = 1;
	}
	m_view.showWinnerWindow(winner, (winner == 1 ? m_game.getScorePlayer1() : m_game.getScorePlayer2()));
}

void Presenter::updateSpeed() {

	m_game.updateSpeed(m_view.getCurrentSpeed());
}