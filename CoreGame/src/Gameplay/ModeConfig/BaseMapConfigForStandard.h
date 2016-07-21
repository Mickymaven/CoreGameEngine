#if !defined(BASEMAPCONFIGFORSTANDARD_H)
#define BASEMAPCONFIGFORSTANDARD_H

#include "../../../../EngineMoba/src/ModeConfig/BaseMapConfigForMode.h"

//Quest Configs
#include "../Quests/OwlQuestStandard1Config.h"

class BaseMapConfigForStandard : public BaseMapConfigForMode
{
protected:
public:
	OwlQuestStandard1Config m_owlStandard1config;


	//data model for map config as it applies to 'StandardMatch' mode

	//standard will have a list of QuestConfig objects


	BaseMapConfigForStandard();
	~BaseMapConfigForStandard();

};

#endif