#include "ShopInventory.h"


ShopInventory::ShopInventory()
{
	m_invId = -1;
}

ShopInventory::~ShopInventory()
{

}

int ShopInventory::GetInventoryID() { return m_invId; }
vector <int> * ShopInventory::GetInventory() { return &m_inventory; }
void ShopInventory::SetInventoryID(int id) { m_invId = id; }

/*
vector <Item *> * ShopInventory::GetItemsPointer()
{
	return &m_itemsToRender;
}*/