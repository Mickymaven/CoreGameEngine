#if !defined(ITEM_H)
#define ITEM_H

#include <vector>
using std::vector;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../Ability/Ability.h"
#include "../Actors/StatChangeObject.h"

enum ItemConsumableState
{
	itemIsConsumable,
	itemIsNotConsumable,
	itemConsumableStateCount
};

class Item : public StatChangeObject
{
protected:
	int m_value;
	int m_itemClass;
	Ability * m_activeAbility;

public:
	ItemConsumableState m_consumableState;

	Item();
	Item(Item & copy);
	~Item();

	int GetValue();
	int &GetItemClass();
	Ability * GetAbility();
	bool GetIsConsumable();

	void SetValue(int value);
	void SetItemClass(int name);
	void SetAbility(Ability * ability);
};

#endif