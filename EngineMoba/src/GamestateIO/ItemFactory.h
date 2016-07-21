#if !defined(ITEMFACTORY_H)
#define ITEMFACTORY_H

#include "../../../CoreGame/src/Gameplay/Items/ItemName.h" //forward dependency
#include "../Item/Item.h"

#include "../../../CoreGame/src/Gameplay/Abilities/RideBike.h"
#include "../../../CoreGame/src/Gameplay/Abilities/NomBarHeal.h"
#include "../../../CoreGame/src/Gameplay/Abilities/BudgetMenuBeverage.h"


#include "GameObjectFactory.h"

#include "AbilityFactory.h"



class ItemFactory :public GameObjectFactory
{
private:
	vector<Item *> m_items;
	AbilityFactory * m_abilityFactory;

public:
	static const bool hasAbility[itemCount];

	ItemFactory();
	~ItemFactory();
	bool Init(AbilityFactory * abilityFactory);

	void InitItems();
	Item * GetItem(bool* isCopy, ItemName itemEnum);//
	Item * GetItemByEnum(ItemName itemEnum); //Lightweight Assets
	Item * GetItemCopyByEnum(ItemName itemEnum);

	Item * GetItemSharedOrCopyByEnum(ItemName itemEnum);



	vector<Item *> * GetLightweightItems();

};

#endif