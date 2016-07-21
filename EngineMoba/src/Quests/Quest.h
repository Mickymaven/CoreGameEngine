#if !defined(QUEST_H)
#define QUEST_H

#include "../../../EngineMoba/src/Actors/Character.h"
#include "../../../EngineMoba/src/Actors/ShopInventory.h"

#include "QuestItems.h"

/*
struct ConditionalItem
{
	vector<bool> m_itemActive	
	vector<ItemEntity*> m_item;
	ItemConditionScheme m_condition;
	int m_teamName;
	vector<PlayerCharacterController*> m_team;
	vector<PlayerCharacterController*> m_individualPlayers;
};
*/

class Quest
{
private:
protected:
	QuestItems m_items;
	vector <ShopInventory*> m_inventories;

public:
	Quest();
	~Quest();

	bool IsItemAvailable(Character * character, int itemIndex);

	ItemEntity * SelectItem(Character * character, int itemIndex);
	
	void TakeItem(int itemIndex);

	ShopInventory* GetInventory(int index);
	vector <ShopInventory*> * GetInventories();

};

#endif