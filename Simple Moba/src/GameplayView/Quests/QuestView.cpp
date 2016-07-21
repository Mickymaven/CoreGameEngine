#include "QuestView.h"

QuestView::QuestView()
{
	m_quest = nullptr;
}

QuestView::~QuestView()
{
}

bool QuestView::Init(Quest * quest, ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds)
{
	m_quest = quest;

	if (!InitShopViews(viewProfile, theme, bounds)) return false;

	return true;
}

bool QuestView::InitShopViews(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds)
{
	vector<ShopInventory*> * shopInvs = m_quest->GetInventories();

	m_shopInventoryViews.resize(shopInvs->size());

	for (unsigned int i = 0; i < shopInvs->size(); i++)
	{
		if (!m_shopInventoryViews.at(i).Init(viewProfile, theme, bounds, shopInvs->at(i))) return false;
	}

	return true;
}

void QuestView::Render()
{
	for (unsigned int i = 0; i < m_itemViews.size(); i++)
	{
		m_itemViews.at(i).Render();
	}
}

void QuestView::AddItemView(LPDIRECT3DDEVICE9 device, ItemEntity * itemEntity, LMMesh * mesh)
{
	m_itemViews.push_back(ItemEntityView(device, itemEntity, mesh));
}

vector<ItemEntityView>* QuestView::GetItemViews()
{
	return &m_itemViews;
}

Quest * QuestView::GetQuest()
{
	return m_quest;
}
