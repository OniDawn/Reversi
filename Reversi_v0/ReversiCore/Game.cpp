#include"Game.h"
#include "CommonMacros.h"
#include <QDebug>
#include <QTime>
#include <QCoreApplication>

Game::Game(Array2D board, StrategyFactory factory, MoveCalculator moveCalculator) :
	m_gameBoard(board), m_moveCalculator(moveCalculator), m_scorePlayer1(2), m_scorePlayer2(2), m_isPlayerStrategyInitialized(false)
{
	m_isPlayer1Turn = true;
	m_waitForClick = false;
	m_possibleMovesAvailable = true;
	m_gameIsOn = false;
	m_speed = 10;
	m_player1 = NULL;
	m_player2 = NULL;

	connect(this, &Game::gameFinished, this, &Game::endGame);

}

Game::Game(Array2D board) :
	m_gameBoard(board), m_moveCalculator(MoveCalculator()), m_scorePlayer1(2), m_scorePlayer2(2), m_isPlayerStrategyInitialized(false)
{
	m_isPlayer1Turn = true;
	m_waitForClick = false;
	m_possibleMovesAvailable = true;
	m_gameIsOn = false;
	m_speed = 10;
	m_player1 = NULL;
	m_player2 = NULL;
}

Game::~Game()
{
	/*delete m_player1;
	delete m_player2;*/
}

void Game::initializePlayerStrategy(const QString &player1Strategy, const QString &player2Strategy)
{
	m_player1 = StrategyFactory().instance().selectStrategy(player1Strategy);
	m_player2 = StrategyFactory().instance().selectStrategy(player2Strategy);
	m_isPlayerStrategyInitialized = true;
	m_waitForClick = false;
	m_isPlayer1Turn = true;
	resetScore();
}

bool Game::play(int numberPlayer)
{
	if (m_isPlayerStrategyInitialized == false)
	{
		initializePlayerStrategy("Random", "Random");
		m_isPlayerStrategyInitialized = true;
	}
	Field m;
	std::vector<Field> possibleMoves;
	if (numberPlayer == 1)
	{
		//player 1
		possibleMoves = m_moveCalculator.calculatePossibleMoves(m_gameBoard, true);
		if (possibleMoves.size() == 0) {
			return false;
		}
		m = m_player1->getBestMove(possibleMoves, true, m_gameBoard);
		updateBoard(m, 1);
	}
	if (numberPlayer == 2)
	{
		//player 2
		possibleMoves = m_moveCalculator.calculatePossibleMoves(m_gameBoard, false);
		if (possibleMoves.size() == 0) {
			return false;
		}
		m = m_player2->getBestMove(possibleMoves, false, m_gameBoard);
		updateBoard(m, 2);
	}
	countScore(1);
	countScore(2);
	return true;
}

std::vector<Field> Game::calculatePossibleMoves(int player)
{
	return m_moveCalculator.calculatePossibleMoves(m_gameBoard, (player == 1 ? true : false));
}

const Array2D &Game::getBoard() const
{
	return m_gameBoard;
}

void Game::initialize(int speed)
{
	m_gameBoard = Array2D(m_gameBoard.getSize());
	m_gameBoard.setValue(Field(m_gameBoard.getSize().width/2 - 1 , m_gameBoard.getSize().height / 2), 1);
	m_gameBoard.setValue(Field(m_gameBoard.getSize().width / 2, m_gameBoard.getSize().height / 2 - 1), 1);
	m_gameBoard.setValue(Field(m_gameBoard.getSize().width / 2 , m_gameBoard.getSize().height / 2), 2);
	m_gameBoard.setValue(Field(m_gameBoard.getSize().width / 2 -1, m_gameBoard.getSize().height / 2 - 1), 2);
	m_speed = speed;
}

void Game::updateBoard(Field field, int player)
{
	m_gameBoard.setValue(field, player);
	std::vector<Field> flippedFields = m_moveCalculator.calculateFlippedFields(field, player, m_gameBoard);
	for (int i = 0; i < flippedFields.size(); i++)
	{
		m_gameBoard.setValue(flippedFields[i], player);
	}
}

std::vector<Field> Game::simulateCalculatePossibleMoves(const Array2D &board, int player)
{
	return m_moveCalculator.calculatePossibleMoves(board, (player == 1 ? true : false));
}

Array2D Game::simulateUpdateBoard(Array2D &board, Field field, int player)
{
	board.setValue(field, player);
	std::vector<Field> flippedFields = m_moveCalculator.calculateFlippedFields(field, player, board);
	for (int i = 0; i < flippedFields.size(); i++)
	{
		board.setValue(flippedFields[i], player);
	}
	return board;
}

void Game::countScore(int player)
{
	int counterPlayer = 0;
	for (int y = 0; y < m_gameBoard.getSize().height; y++)
	{
		for (int x = 0; x < m_gameBoard.getSize().width; x++)
		{
			if (m_gameBoard.getValue(Field(x, y)) == (player == 1 ? 1 : 2))
			{
				counterPlayer++;
			}
		}
	}
	if (player == 1)
	{
		m_scorePlayer1 = counterPlayer;
	}
	else if (player == 2)
	{
		m_scorePlayer2 = counterPlayer;
	}
}

int Game::getScorePlayer1() const
{
	return m_scorePlayer1;
}

int Game::getScorePlayer2() const
{
	return m_scorePlayer2;
}

void Game::nextTurn()
{
	LOG("next Turn");

	if (!m_gameIsOn)
	{
		return;
	}

	if (m_isPlayer1Turn)
	{
		if (m_player1->getNeedsUserInteraction() == true)
		{
			m_waitForClick = true;
		}
		else
		{
			m_possibleMovesAvailable = play((1));
			QTime dieTime = QTime::currentTime().addMSecs(m_speed);
			while (QTime::currentTime() < dieTime)
			{
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}
			emit boardDrawRequest();
			if (m_possibleMovesAvailable)
			{
				m_isPlayer1Turn = false;
				nextTurn();
			}
			else
			{
				emit winnerDetermined();
				emit gameFinished();
				return;
			}
		}
	}
	else
	{
		if (m_player2->getNeedsUserInteraction() == true)
		{
			m_waitForClick = true;
		}
		else
		{
			m_possibleMovesAvailable = play((2));
			QTime dieTime = QTime::currentTime().addMSecs(m_speed);
			while (QTime::currentTime() < dieTime)
			{
				QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
			}
			emit boardDrawRequest();
			if (m_possibleMovesAvailable)
			{
				m_isPlayer1Turn = true;
				nextTurn();
			}
			else
			{
				emit winnerDetermined();
				emit gameFinished();
			}
		}
	}
}

void Game::userClickedTurn(Field field)
{
	if (!m_gameIsOn)
	{
		return;
	}

	LOG("Game SLOT: userClickedTurn");

	if (m_waitForClick == true)
	{
		std::vector<Field> possibleMoves = calculatePossibleMoves((m_isPlayer1Turn ? 1 : 2));
		
		LOG("Game SLOT: userClickedTurn waitForClick is true, Field: " << field.xPos << ", " << field.yPos);

		if (possibleMoves.size() == 0)
		{
			m_waitForClick = false;
			emit winnerDetermined();
			emit gameFinished();
			return;
		}

		auto iter = std::find(possibleMoves.begin(), possibleMoves.end(), field);
		if (iter != possibleMoves.end())
		{
			updateBoard(field, (m_isPlayer1Turn ? 1 : 2));
			LOG("Game SLOT: userClickedTurn Move is possible");
			countScore(1);
			countScore(2);
			emit boardDrawRequest();
			m_isPlayer1Turn = (m_isPlayer1Turn ? false : true);
			m_waitForClick = false;
			
			nextTurn();
		}
	}
}

void Game::endGame()
{
	m_gameIsOn = false;
}

void Game::gameIsOn()
{
	m_gameIsOn = true;
}

void Game::resetScore()
{
	m_scorePlayer1 = 2;
	m_scorePlayer2 = 2;
}

void Game::updateSpeed(int speed)
{
	m_speed = speed;
}
