#include "Item.h"

Item::Item()
{
	m_activeAbility = NULL;
	m_consumableState = itemIsNotConsumable;
}

Item::Item(Item & copy){}

Item::~Item()
{
	delete m_activeAbility;
	m_activeAbility = NULL;
}

int Item::GetValue() { return m_value; }
int & Item::GetItemClass() { return m_itemClass; }

Ability * Item::GetAbility()
{
	if (m_activeAbility == NULL) return NULL;
	return m_activeAbility;
}

bool Item::GetIsConsumable()
{
	if (m_consumableState == itemIsConsumable) return true;	
	return false;
}
void Item::SetItemClass(int itemClass) { m_itemClass = itemClass; }

void Item::SetValue(int value) { m_value = value; }
void Item::SetAbility(Ability * ability) { m_activeAbility = ability;}