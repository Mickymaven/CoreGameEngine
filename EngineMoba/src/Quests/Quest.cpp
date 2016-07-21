#include "Quest.h"

Quest::Quest()
{
}

Quest::~Quest()
{
}

bool Quest::IsItemAvailable(Character * character, int itemIndex)
{
	if (itemRecieveOK == m_items.m_items.at(itemIndex).IsRecievable(character))
		return true;

	return false;
}

ItemEntity * Quest::SelectItem(Character * character, int itemIndex)
{
	return & m_items.m_items.at(itemIndex);
}

void Quest::TakeItem(int itemIndex)
{
	m_items.m_items.at(itemIndex).SetIsActive(false);
	m_items.m_items.at(itemIndex).GetVitalEntity()->SetToState(vitalEntityStateInactive);
}

ShopInventory * Quest::GetInventory(int index)
{
	if (false == (index >= 0 && index < m_inventories.size())) return nullptr;
	
	return m_inventories.at(index);
}

vector<ShopInventory*>* Quest::GetInventories() { return &m_inventories; }