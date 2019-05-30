#if !defined(TRADEINVENTORYVIEW_H)
#define TRADEINVENTORYVIEW_H

#include<vector>
using std::vector;

#include <functional>
using namespace std::placeholders;

#include "../../../EngineMoba/src/Actors/TradeInventory.h"
#include "../../../CoreGame/src/Gameplay/Quests/InvName.h"

#include "ShopInventoryView.h"

class TradeInventoryView : public UIContentArea
{
protected:
	string s;
	TradeInventory * m_tradeInventory;
	UITab * m_tab;

	vector<ShopInventoryView*> m_shopInvViews;

	InvName m_currentShopViewID;
	ShopInventoryView * m_selectedShopView;

	vector<ShopInventoryView*>* m_allShopViews; //this one is huge and has empty values, should be inited on load in MobaViewState;

	UILabel m_shopLabel;


public:
	TradeInventoryView();
	~TradeInventoryView();

	bool Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, TradeInventory * tradeInventory, vector<ShopInventoryView*>* shopViews);

	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	TradeInventory * GetTradeInventory();
	ShopInventoryView * GetActiveShopInventoryView();
	void AddShopInventoryView(ShopInventoryView * shopInvView);
	UITab * GetTab();
	//mutators
	void SetTab(UITab * tab);


	bool EventChangeShopInv(int invId);
	bool SetShopViewFromModel();

	//

};

#endif