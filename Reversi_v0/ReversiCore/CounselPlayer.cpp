#include "CounselPlayer.h"
#include "StrategyFactory.h"
#include <unordered_set>

REGISTER_STRATEGY(CounselPlayer);

CounselPlayer::CounselPlayer() :
	m_needsUserInteraction(false)
{
	for (auto& name : StrategyFactory::instance().getNames())
	{
		if (name == "Counsel")
		{
			continue;
		}
		std::shared_ptr<Strategy> newStrategy = StrategyFactory().instance().selectStrategy(name);
		if (!newStrategy->getNeedsUserInteraction())
		{
			m_strategies.push_back(newStrategy);
			
		}
	}
}

CounselPlayer::~CounselPlayer()
{
	m_strategies.clear();
}

bool CounselPlayer::getNeedsUserInteraction()
{
	return m_needsUserInteraction;
}

Field CounselPlayer::getBestMove(const std::vector<Field> &possibleMoves, bool areYouPlayer1, const Array2D &board)
{
	std::vector<Field> counselMovesVector;
	for (auto& strategy : m_strategies)
	{
		counselMovesVector.push_back(strategy->getBestMove(possibleMoves, areYouPlayer1, board));
	}

	std::unordered_set<Field> counselMoves;
	for (int i = 0; i < counselMovesVector.size(); i++)
	{
		auto p = (counselMoves.insert(counselMovesVector[i]));
		if (p.second == false)
		{
			return counselMovesVector[i];
		}
	}

	int numberField = (rand() % (counselMovesVector.size()));

	return counselMovesVector[numberField];
}
