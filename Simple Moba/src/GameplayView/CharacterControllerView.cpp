#include "CharacterControllerView.h"

CharacterControllerView::CharacterControllerView()
{
}

CharacterControllerView::CharacterControllerView(CharacterView * characterView)
{
	m_characterView = characterView;
}

CharacterControllerView::~CharacterControllerView()
{
	delete m_characterView;
	m_characterView = nullptr;
}

bool CharacterControllerView::InitTradeView(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, vector<ShopInventoryView*>* shopViews)
{
	if (!m_tradeInventoryView.Init(viewProfile, theme, bounds, m_characterView->GetCharacter()->GetTradeInventory(), shopViews)) return false;

	return true;
}

CharacterView * CharacterControllerView::GetCharacterView() { return m_characterView; }
TradeInventoryView * CharacterControllerView::GetTradeInventoryView() { return &m_tradeInventoryView; }
