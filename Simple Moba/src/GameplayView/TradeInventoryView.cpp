#include "TradeInventoryView.h"

TradeInventoryView::TradeInventoryView()
{
	m_selectedShopView = nullptr;

}

TradeInventoryView::~TradeInventoryView()
{
}

bool TradeInventoryView::Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, TradeInventory * tradeInventory, vector<ShopInventoryView*>* shopViews)
{
	m_tradeInventory = tradeInventory;

	tradeInventory->AddCallbackOnChangeShopInventory(std::bind(&TradeInventoryView::EventChangeShopInv, this, _1));

	m_allShopViews = shopViews;

	SetShopViewFromModel();

	m_bounds.values[0] = bounds->x;
	m_bounds.values[1] = bounds->y;
	m_bounds.values[2] = bounds->z;
	m_bounds.values[3] = bounds->w;

	// SHOP LABEL /////////////////

	RECT rect = { 0, 0, 0, 0 };

	//s = "HEY LISTEN!";

	m_shopLabel = UILabel();

	m_shopLabel.Init(rect, &theme->m_dialogLabel, tradeInventory->GetName());
	//m_shopLabel.SetBounds(bounds->left() + 120.0f, bounds->top() + 10.0f, bounds->right() + 620.0f, bounds->bottom() + 200.0f);

	if (!viewProfile->InitLabel(gameElementTradeMenuTitle, &m_shopLabel, &theme->m_dialogLabel, nullptr));

	return true;
}

void TradeInventoryView::Render()
{
	//m_shopLabel.SetBounds(m_bounds.left() + 120.0f, m_bounds.top() + 10.0f, m_bounds.right() + 620.0f, m_bounds.bottom() + 200.0f);
	m_shopLabel.Render();

	if (m_selectedShopView != nullptr) m_selectedShopView->Render();

	//m_shopInvViews.at(m_tradeInventory->GetSelectedShopIndex())->Render();
}

void TradeInventoryView::Select(POINT * p)
{
	m_selectedShopView->Select(p);
	//m_shopInvViews.at(m_tradeInventory->GetSelectedShopIndex())->Select(p);
}

void TradeInventoryView::AltSelect(POINT * p)
{
	m_selectedShopView->AltSelect(p);
	//m_shopInvViews.at(m_tradeInventory->GetSelectedShopIndex())->AltSelect(p);
}

bool TradeInventoryView::MouseOver(POINT * p)
{
	return m_selectedShopView->MouseOver(p);
	//return m_shopInvViews.at(m_tradeInventory->GetSelectedShopIndex())->MouseOver(p);
}

TradeInventory * TradeInventoryView::GetTradeInventory() { return m_tradeInventory; }

ShopInventoryView * TradeInventoryView::GetActiveShopInventoryView()
{
	return m_selectedShopView;
		
	//m_shopInvViews.at(m_tradeInventory->GetSelectedShopIndex());
}

void TradeInventoryView::AddShopInventoryView(ShopInventoryView * shopInvView)
{
	//m_shopInvViews.push_back(shopInvView);
}

UITab * TradeInventoryView::GetTab() { return m_tab; }
//mutators
void TradeInventoryView::SetTab(UITab * tab) { m_tab = tab; }

bool TradeInventoryView::EventChangeShopInv(int invId)
{
	//need to have inv set during init?

	if (true)
	{
		if (m_allShopViews->at(invId) != nullptr)
		{
			m_selectedShopView = m_allShopViews->at(invId);
			m_currentShopViewID = (InvName)invId;

			return true;
		}
		else
		{
			return false;//not purpose of return but need break point
		}
	}

	return false;//we didnt change inv view with this callback

}


bool TradeInventoryView::SetShopViewFromModel()
{

	if (m_tradeInventory->GetShopInvVector()->size() == 0) return false;

	//need to have inv set during init?

	int id = m_tradeInventory->GetSelectedShopInventory()->GetInventoryID();

	if (true)
	{
		if (m_allShopViews->at(id) != nullptr)
		{
			m_selectedShopView = m_allShopViews->at(id);
			m_currentShopViewID = (InvName)id;

			return true;
		}
		else
		{
			return false;//not purpose of return but need break point
		}
	}

	return false;//we didnt change inv view with this callback

}