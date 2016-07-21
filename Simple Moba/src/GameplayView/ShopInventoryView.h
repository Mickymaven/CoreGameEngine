#if !defined(SHOPINVENTORYVIEW_H)
#define SHOPINVENTORYVIEW_H

#include <functional>
using namespace std::placeholders;

#include "../../../EngineMoba/src/Actors/ShopInventory.h"
#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../../../EngineMoba/src/GamestateIO/ItemFactory.h"


#include "../../../EngineGameModuleDirectX9/src/UI/UIContentArea.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabel.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UITab.h"

#include "../UI_Base/UILayoutItem.h"
#include "../UI_Base/UILayoutItemClone.h"
#include "../UI/Tooltips/TooltipController.h"

#include "../../../CoreGame/src/Gameplay/Items/ItemName.h"

#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"

//mvc notes
//this has model and view stuff in it

//also full of dirty hardcode positions etc.

class ShopInventoryView : public UIContentArea
{
protected:
	
	ShopInventory * m_shopInventory;

	unsigned int m_shopBuyCount;
	unsigned int m_maxInvSize;

	vector <unsigned int> m_shopSelectionCount;
	vector <UILayoutItem *> m_layoutItems;
	vector <UILabel *> itemLabels;

	vector <UILayoutItemClone> m_shopSelected;
	

	vector <UILayoutItem> m_playerInventory;

	vector <UILayoutItemClone> m_playerInventoryUnselected;
	vector <UILayoutItemClone> m_playerInventorySelected;
	
	LMVector4 m_invBounds;
	LMVector4 m_shopBounds;

public:
	static ItemFactory * m_itemFactory;
	static TooltipController * m_tooltipController;
	static PlayerCharacterController * m_selectedPlayerController;
	static 	vector<ItemView> * m_lightweightItemViews;

	ShopInventoryView();
	ShopInventoryView(const ShopInventoryView &s);
	~ShopInventoryView();

	bool Init(ViewProfile * viewProfile, ThemeResources * theme, LMVector4 * bounds, ShopInventory * shopInventory);
	bool InitCatView();

	void PositionContent(LMVector4 * bounds);

	void PositionInvItems(LMVector4 * bounds);
	void SetInvItems();
	void SetShopSelected();

	void Render() override;

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);


	ShopInventory * GetShopInventory();

	void ClearSelection();

	int UnselectCount();
	int BuyCount();
	bool TradeWillFit();

	void RemoveOld();
	void AddNew();

};

#endif