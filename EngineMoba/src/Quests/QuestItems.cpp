#include "QuestItems.h"

QuestItems::QuestItems()
{
}

QuestItems::~QuestItems()
{
}

vector<ItemEntity>* QuestItems::GetItems()
{
	return &m_items;
}