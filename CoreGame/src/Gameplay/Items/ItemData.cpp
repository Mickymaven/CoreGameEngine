#include "ItemData.h"

vector<AbilityName> ItemData::m_itemAbilities;

ItemData::ItemData()
{
	if (m_itemAbilities.size() <= 0) InitItemData();
}

void ItemData::InitItemData()
{
	m_itemAbilities.resize(itemCount, abilityCount);

	//m_itemAbilities[itemBasicBoots]		 = abilityCount;
	//m_itemAbilities[itemBasicSneakers]	 = abilityCount;
	//m_itemAbilities[itemTreeBranch]		 = abilityCount;
	m_itemAbilities[itemNomBar]			 = abilityNomBarHeal;
	m_itemAbilities[itemKetchup]		 = abilityBudgetMenuBeverage;
	m_itemAbilities[itemBike]			 = abilityRideBike;
}
