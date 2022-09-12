#include "StrategyFactory.h"
#include "RandomPlayer.h"
#include "TablePlayer.h"
#include "MaximizePlayer.h"
#include "MinimizePlayer.h"
#include "HumanPlayer.h"
#include "CounselPlayer.h"

StrategyFactory& StrategyFactory::instance()
{
	static StrategyFactory inst;
	return inst;
}

std::shared_ptr<Strategy> StrategyFactory::selectStrategy(const QString& name) const
{
	return m_playerCreators.at(name).Creator();
}

std::vector<QString> StrategyFactory::getNames() const
{
	std::vector<QString> names;
	for (auto& pair : m_playerCreators)
	{
		names.push_back(pair.first);
	}
	return names;
}

QString StrategyFactory::getDescription(const QString& name) const
{
	return m_playerCreators.at(name).Description;
}

void StrategyFactory::addCreator(const QString& name, const StrategyProperties& properties)
{
	m_playerCreators[name] = properties;
}