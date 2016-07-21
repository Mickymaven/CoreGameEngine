#include "UILayoutInventory.h"

UILayoutInventory::UILayoutInventory()
{

}

UILayoutInventory::~UILayoutInventory()
{

}

bool UILayoutInventory::Init()
{
	m_pVector.resize(m_items.size());

	for (unsigned int i = 0; i < m_items.size(); i++)
	{
		m_pVector.at(i) = &m_items.at(i);
	}

	return true;
}

void UILayoutInventory::Update(float deltaTime)
{

}

void UILayoutInventory::Render()
{
	for (unsigned int i = 0; i < m_items.size(); i++)
	{
		if (m_items.at(i).GetItem() != NULL) m_items.at(i).Render();
	}
}

void UILayoutInventory::Select(POINT * p)
{

}

void UILayoutInventory::AltSelect(POINT * p)
{

}

bool UILayoutInventory::MouseOver(POINT * p)
{
	for (unsigned int i = 0; i < m_items.size(); i++)
	{
		if ( m_items.at(i).GetItem() != NULL )
			if (m_items.at(i).MouseOver(p)) return true;
	}
	return false;
}

void UILayoutInventory::SetItems(vector<Item *> * inventory)
{
	for (unsigned int i = 0; i < inventory->size(); i++)
	{
		if (inventory->at(i) != NULL)
		{
			m_items.at(i).SetWithItemView(&m_itemViews->at(inventory->at(i)->GetItemClass()));
			//not making view model from actual game data.
			//m_items.at(i).SetItem(inventory->at(i));
			//m_items.at(i).SetItemView(&m_itemViews->at(inventory->at(i)->GetItemClass()));
			//m_items.at(i).SetIcon(m_itemViews->at(inventory->at(i)->GetItemClass()).GetIcon());

		}
		else
		{
			m_items.at(i).SetItem(NULL);
			m_items.at(i).SetItemView(NULL);
			m_items.at(i).SetIcon(NULL);
		}
	}
}

void UILayoutInventory::SetItemViews(vector<ItemView> * itemViews) { m_itemViews = itemViews; }

