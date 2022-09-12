#pragma once
#include "DLL.h"
#include"Strategy.h"
#include <functional>
#include <memory>
#include <QString>

#define REGISTER_STRATEGY(NAME)									\
static auto NAME##_registered = [](){							\
    StrategyFactory::instance().addCreator(NAME::Name, { []()	\
    {															\
        return std::make_shared<NAME>();						\
    }, NAME::Description										\
    });															\
    return true;												\
}();


/// @brief determines the strategy a player is playing
class REVERSI_EXPORT StrategyFactory
{
	public:
		using CreatorFunction = std::function<std::shared_ptr<Strategy> ()>;

		/// @brief contains the properties CreatorFunktion and Description of a Strategy
		struct StrategyProperties
		{
			CreatorFunction Creator;
			QString Description;
		};

		/// @brief ensures that only one object of this class can exist
		/// @return StrategyFactory object
		static StrategyFactory& instance();

		/// @brief selects strategy
		/// @param name string with the name of the strategy that is selected
		/// @return strategy object from certain class
		std::shared_ptr<Strategy> selectStrategy(const QString& name) const;

		/// @return  names of the existing strategies
		std::vector<QString> getNames() const;

		/// @brief finds out which description belongs to the selected strategy
		/// @param name string with the name of the strategy that is selected
		/// @return description of strategy
		QString getDescription(const QString& name) const;

		/// @brief adds a strategy to the StrategyFactory
		/// @param name string with the name of the strategy that is selected
		/// @param properties struct with the properties of the new strategy
		void addCreator(const QString& name, const StrategyProperties& properties);

private:
	std::map<QString, StrategyProperties> m_playerCreators;
};