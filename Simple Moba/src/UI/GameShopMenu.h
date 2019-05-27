#if !defined(GAMESHOPMENU_H)
#define GAMESHOPMENU_H

#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIButton.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIContentArea.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"//todo bad?
#include "../GameplayView/PlayerCharacterView.h"
#include "../GameplayView/TradeInventoryView.h"
#include "../GamestateViewIO/GameAssetFactory.h"
#include "../UI_Base/UIDialogScreen.h"
#include "Shop_Menu/ShopDialogTabLayoutMenu.h" 
#include "TabLayoutMenu.h"

#include "../../../EngineMoba/src/GamestateIO/ItemFactory.h"

class GameShopMenu : public ShopDialogTabLayoutMenu//, public UIDialogScreen
{
private:
	string m_emptyString = "";

	GameAssetFactory * m_gameAssetFactory;//not really used, static init og gameshopview that we might be moving

	PlayerCharacterController * tempCharacterController;
	TradeInventoryView * m_tempGameShopView;

	//TradeInventoryView * m_tempGameShopView;
	vector<TradeInventoryView *> m_gameShopViews;
	
	vector<DialogOption *> * m_dialogOptionsForButtons;

	//TradeInventoryView * m_page;

	UIButton m_confirmPreorder;
	UIButton m_cancelPreorder;
	UIButton m_confirmTrade;
	UIButton m_cancelTrade;

	
public:
	GameShopMenu();
	~GameShopMenu();


	bool Init(
		InputModel * mainMenuInputModel,
		ViewProfile * viewProfile,
		ThemeResources * theme,
		LMVector2 * origin,
		LMVector2 * size,
		vector<TradeInventory> * gameShops,
		vector<ShopInventoryView *> * shopInvViews,
		vector<ItemView> * lightweightItemViews,
		ItemFactory * itemFactory,
		GameAssetFactory * gameAssetFactory,
		TooltipController * tooltipController,
		PlayerCharacterController * playerCharacterController
		);

	void Update(float deltaTime, PlayerCharacterController * playerCharacterController);
	void Render();

	void OnExitOpened();

	bool ToggleState();

	void SelectOnTabs(POINT * p);
	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	void SetShopForAutoInv(); //contorl

	void ActionCancelTrade(); //control
	void ActionConfirmTrade();//control
	void ActionPreOrder();//control
	void ActionCancelOrder();//control

	void ToggleMenuWithAutoShop();//control

	bool IsCurrentGameShopInRange();//control helper

	TradeInventoryView * GetGameShopView();

	void SetGameShopView(TradeInventoryView * gameShopView);

	PlayerCharacterController * GetCtrl();
	void SetCtrl(PlayerCharacterController * playerCharacterController);

	bool SetPage(UIContentArea * contentArea);


	void SetButtonOptions(int dialogScreenIndex);
};

#endif