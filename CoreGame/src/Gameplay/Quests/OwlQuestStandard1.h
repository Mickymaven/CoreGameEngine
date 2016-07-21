#if !defined (OWLQUESTSTANDARD1_H)
#define OWLQUESTSTANDARD1_H

#include "../../../../EngineMoba/src/Quests/Quest.h"

#include "../Items/ItemName.h"
#include "OwlQuestStandard1Config.h"
#include "InvName.h"

enum OwlQuestS1Inv
{
	owlQuestS1InvReward,
	owlQuestS1InvCount
};

class OwlQuestStandard1 : public Quest
{
protected:
	//NPC spawn position
	//NPC spawn time
	//Quest 1 Item spawn locations

	ShopInventory m_rewardInventory;

public:
	OwlQuestStandard1();
	~OwlQuestStandard1();

	bool Init(OwlQuestStandard1Config * config);
	
	void ActionPreQuest();
	void ActionStartQuest();
	void ActionEndQuest();

	//FFFILTHY DIRTY
	//C++ GAME
	//DEVELOPMENT


};

#endif