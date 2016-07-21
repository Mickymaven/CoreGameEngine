#include "ItemFactory.h"

const bool ItemFactory::hasAbility[itemCount] =
{
	false,//gameItemBasicBoots,
	false,//gameItemBasicSneakers,
	false,//gameItemTreeBranch,
	true,//gameItemNomBar,
	true,//gameItemKetchup,
	true,//gameItemBike,
	false//gameItemOwlDrill
};

ItemFactory::ItemFactory()
{

}

ItemFactory::~ItemFactory()
{

}

bool ItemFactory::Init(AbilityFactory * abilityFactory)
{
	m_abilityFactory = abilityFactory;
	InitItems();
	return true;
}

void ItemFactory::InitItems()
{
	m_items.resize(itemCount, nullptr);

	for (int index = 0; index < itemCount; index++)
	{
		m_items.at(index) = GetItemCopyByEnum((ItemName)index);
	}
}

Item * ItemFactory::GetItem(bool* isCopy, ItemName itemEnum)
{
	//this returns an item ref to lightweight or a copy
	//if it is a copy, a you will have do deal with its lifespan and know in advance.

	bool copy = hasAbility[itemEnum];
	
	
	if (isCopy != NULL) *isCopy = copy;


	if (copy) return GetItemCopyByEnum(itemEnum);
	else return GetItemByEnum(itemEnum);

	return NULL;
}

Item * ItemFactory::GetItemByEnum(ItemName itemEnum)//Lightweight Assets
{
	return m_items.at(itemEnum);
}

Item * ItemFactory::GetItemCopyByEnum(ItemName itemEnum)
{
	Item * item = new Item();

	item->SetItemClass(itemEnum);

	switch (itemEnum)
	{
	case itemBasicBoots:
		item->SetValue(1);

		item->m_armor = 2.0f;
		item->m_attackSpeed = 0.0f;
		item->m_catVoodoo = 0.0f;
		item->m_catVoodooResist = 0.0f;
		item->m_health = 0.0f;
		item->m_healthRegen = 0.0f;
		item->m_maxHealth = 0.0f;
		item->m_moveSpeed = 1.0f;
		item->m_physicalDamage = 0.0f;
		item->m_range = 0.0f;

		item->m_consumableState = itemIsNotConsumable;

		break;
	case itemBasicSneakers:
		item->SetValue(1);

		item->m_armor = 1.0f;
		item->m_attackSpeed = 0.0f;
		item->m_catVoodoo = 0.0f;
		item->m_catVoodooResist = 0.0f;
		item->m_health = 0.0f;
		item->m_healthRegen = 0.0f;
		item->m_maxHealth = 0.0f;
		item->m_moveSpeed = 2.0f;
		item->m_physicalDamage = 0.0f;
		item->m_range = 0.0f;


		item->m_consumableState = itemIsNotConsumable;
		break;
	case itemTreeBranch:
		item->SetValue(1);

		item->m_armor = 0.0f;
		item->m_attackSpeed = 0.2f;
		item->m_catVoodoo = 0.0f;
		item->m_catVoodooResist = 0.0f;
		item->m_health = 0.0f;
		item->m_healthRegen = 0.0f;
		item->m_maxHealth = 0.0f;
		item->m_moveSpeed = 0.0f;
		item->m_physicalDamage = 5.0f;
		item->m_range = 0.0f;

		item->m_consumableState = itemIsNotConsumable;

		break;
	case itemNomBar:
		
		item->SetValue(1);

		item->m_armor = 0.0f;
		item->m_attackSpeed = 0.0f;
		item->m_catVoodoo = 0.0f;
		item->m_catVoodooResist = 0.0f;
		item->m_health = 0.0f;
		item->m_healthRegen = 0.0f;
		item->m_maxHealth = 0.0f;
		item->m_moveSpeed = -0.05f;
		item->m_physicalDamage = 0.0f;
		item->m_range = 0.0f;

		item->m_consumableState = itemIsConsumable;

		break;
	case itemKetchup:

		item->SetValue(1);

		item->m_armor = 0.0f;
		item->m_attackSpeed = 0.0f;
		item->m_catVoodoo = 0.0f;
		item->m_catVoodooResist = 0.0f;
		item->m_health = 0.0f;
		item->m_healthRegen = 0.0f;
		item->m_maxHealth = 0.0f;
		item->m_moveSpeed = -0.05f;
		item->m_physicalDamage = 0.0f;
		item->m_range = 0.0f;

		item->m_consumableState = itemIsNotConsumable;
		break;
	case itemBike:
		item->SetValue(1);

		item->m_armor = 0.0f;
		item->m_attackSpeed = 0.0f;
		item->m_catVoodoo = 0.0f;
		item->m_catVoodooResist = 0.0f;
		item->m_health = 0.0f;
		item->m_healthRegen = 0.0f;
		item->m_maxHealth = 0.0f;
		item->m_moveSpeed = 0.0f;
		item->m_physicalDamage = 0.0f;
		item->m_range = 0.0f;
		item->m_consumableState = itemIsNotConsumable;
		break;

	case itemOwlDrill:
		item->SetValue(0);

		item->m_armor = 0.0f;
		item->m_attackSpeed = 0.0f;
		item->m_catVoodoo = 0.0f;
		item->m_catVoodooResist = 0.0f;
		item->m_health = 0.0f;
		item->m_healthRegen = 0.0f;
		item->m_maxHealth = 0.0f;
		item->m_moveSpeed = 0.0f;
		item->m_physicalDamage = 0.0f;
		item->m_range = 0.0f;
		item->m_consumableState = itemIsNotConsumable;
		break;


	default:case itemCount:
		MessageBox(NULL, "Bad Item initialsed in GameAssetFactory::GetNewItem", "Error", MB_OK);
		break;
	}

	//init abilities
	switch (itemEnum)
	{
	case itemBasicBoots: break;
	case itemBasicSneakers: break;
	case itemTreeBranch: break;
	case itemNomBar: item->SetAbility(new NomBarHeal(NULL)); break;
	case itemKetchup: item->SetAbility(new BudgetMenuBeverage(NULL)); break;
	case itemBike: item->SetAbility(new RideBike(NULL)); break;
	case itemOwlDrill:break;
	default:case itemCount: MessageBox(NULL, "Bad item in GameAssetFactory::GetItemCopyByEnum", "Error", MB_OK); break;
	}



	return item;
}

Item * ItemFactory::GetItemSharedOrCopyByEnum(ItemName itemEnum)
{
	if (ItemFactory::hasAbility[itemEnum])
	{
		return GetItemCopyByEnum(itemEnum);
	}
	else
	{
		return GetItemByEnum(itemEnum);
	}

	return nullptr;
}

vector<Item *> *  ItemFactory::GetLightweightItems()
{
	return &m_items;
}