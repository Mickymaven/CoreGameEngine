#include "GameShopMenu.h"

GameShopMenu::GameShopMenu()
{
	m_uiMenuState = menuClosed;
	m_gameAssetFactory = NULL;
}

GameShopMenu::~GameShopMenu()
{
	//delete m_background;
	//delete m_cancelTrade;
	//delete m_confirmTrade;
	//delete m_confirmPreorder;
	//delete m_cancelPreorder;
	//delete m_closeMenu;

	for (unsigned int i = 0; i < m_gameShopViews.size(); i++)
	{
		delete m_gameShopViews.at(i);
		m_gameShopViews.at(i) = nullptr;
	}



}
bool GameShopMenu::Init(
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
	)

{
	if (!UIMenu::Init(viewProfile, theme, origin, size)) return false;
	if (!UIDialogScreen::Init(viewProfile, theme)) return false;
	//ui dialog screen init stuff


	//so this 
	//m_dialogText.SetBounds(170, 210, 1100, 290);



	m_dialogOptionsForButtons = NULL;
	//ui imenu init stuff



	m_gameAssetFactory = gameAssetFactory; //not used

	//used to do initializer list (is now error in compiler v140)
	UIMenu::m_bounds.left = origin->x;
	UIMenu::m_bounds.top = origin->y;
	UIMenu::m_bounds.right = origin->x + size->x;
	UIMenu::m_bounds.bottom = origin->y + size->y;

	
	m_pageOrigin = LMVector4(origin->x, origin->y, origin->x + size->x, origin->x + size->y);
	//m_pageOrigin = LMVector4(origin->x + (0.2f*size->x), origin->y + (0.1f*size->y), origin->x + size->x, origin->x + size->y);

	SetCtrl(playerCharacterController);

	if (!viewProfile->InitElement(gameElementTradeMenuBackground, &m_background)) return false;
	
	m_background.SetPosition(origin->x, 0.0f, origin->y);


	//Button Inits ///////////////////////////////////////////////////////////

	//

	if (!viewProfile->InitElement(gameElementConfirmTrade, &m_confirmTrade)) return false;


	m_confirmPreorder = UIButton(122.0f, 52.0f, "Resources/Shop/Images/shop_preorder.png");
	m_cancelPreorder = UIButton(52.0f, 52.0f, "Resources/Shop/Images/shop_cancel-trade.png");
	//m_confirmTrade = UIButton(122.0f, 52.0f, "Resources/Shop/Images/shop_confirm-trade.png");
	m_cancelTrade = UIButton(52.0f, 52.0f, "Resources/Shop/Images/shop_cancel-trade.png");

	m_confirmPreorder.SetCallbackSTDFunction(std::bind(&GameShopMenu::ActionPreOrder, this));
	m_cancelPreorder.SetCallbackSTDFunction(std::bind(&GameShopMenu::ActionCancelOrder, this));
	m_confirmTrade.SetCallbackSTDFunction(std::bind(&GameShopMenu::ActionConfirmTrade, this));
	m_cancelTrade.SetCallbackSTDFunction(std::bind(&GameShopMenu::ActionCancelTrade, this));

	if (!m_confirmPreorder.Init()) return false;
	if (!m_cancelPreorder.Init()) return false;
	//if (!m_confirmTrade.Init()) return false;
	if (!m_cancelTrade.Init()) return false;

	m_confirmPreorder	.SetPosition(origin->x + size->x - 450.0f, 0.0f, origin->y + size->y - 57.0f);//booo
	m_cancelPreorder	.SetPosition(origin->x + size->x - 300.f, 0.0f, origin->y + size->y - 57.0f);
	//m_confirmTrade		.SetPosition(origin->x + size->x - 200.0, 0.0f, origin->y + size->y - 57.0f);
	m_cancelTrade		.SetPosition(origin->x + size->x - 50.0f, 0.0f, origin->y + size->y - 57.0f);


	//Init GameShopViews for each game shop /////////////////////////////////////////
	//might move this to MobaViewState
	
	tempCharacterController = playerCharacterController;
	
	ShopInventoryView::m_selectedPlayerController = playerCharacterController;
	//TradeInventoryView::m_selectedPlayerController = playerCharacterController;
	
	//TradeInventoryView::m_itemFactory = itemFactory;
	//TradeInventoryView::m_tooltipController = tooltipController;
	//TradeInventoryView::m_lightweightItemViews = lightweightItemViews;

	TradeInventoryView * view = NULL;
	ShopInventoryView * shopView = nullptr;
	for (unsigned int i = 0; i < gameShops->size(); i++)
	{
		view = new TradeInventoryView();	//new objects deleted ~GameShopMenu() using m_gameShopViews

		//todo fix init for floating around game shops
		if (!view->Init(viewProfile, theme, &m_pageOrigin, &gameShops->at(i), shopInvViews)) return false;
		
		/*
		for (unsigned int j = 0; j < gameShops->at(i).GetShopInvVector()->size(); j++)
		{
			shopView = new ShopInventoryView();

			if (!shopView->Init(viewProfile, theme, &m_pageOrigin, gameShops->at(i).GetShopInvVector()->at(j))) return false;

			view->AddShopInventoryView(shopView);
		}*/
		
		m_gameShopViews.push_back(view);
	}


	//init devault page ///////////////////////////////////////////////////
	m_page = m_gameShopViews.at(0);


	// INIT TABS FOR EACH GAME SHOP VIEW //////////////////////////////////
	string path = "Resources/UI/Squares/Grey.png";

	UITab * tab;
	for (unsigned int i = 0; i < m_gameShopViews.size(); i++)
	{
		//todo tabs store shopinv views directly,
		//we kind of want the trade inventory only here but its not uicontentarea anymore

		tab = new UITab(
			m_gameShopViews.at(i),
			52.0f, 52.0f,
			path);

		if (!tab->Init(NULL,NULL)) return false;

		tab->SetCallbackSelectPage(std::bind(&GameShopMenu::SetPage, this, _1));
		m_gameShopViews.at(i)->SetTab(tab);
	}


	LMVector2 taborigin = { 20.0f, 110.0f };
	if (!m_tabgroup.Init(&taborigin,size)) return false;


	//init tab for base shop
	m_tabgroup.GetTabs()->push_back(m_gameShopViews.at(0)->GetTab());
	m_tabgroup.CalcPos();

	return true;
}

void GameShopMenu::Update(float deltaTime, PlayerCharacterController * playerCharacterController)
{
	tempCharacterController = playerCharacterController;
	//set menu tabs based on controlledPCC in range information

	m_tabgroup.GetTabs()->resize(1);//assumption: 0 will always be team shop (always there)

	int shopIndex;
	for (unsigned int i = 0; i < playerCharacterController->GetInRangeShops()->size(); i++)
	{

		shopIndex = playerCharacterController->GetInRangeShops()->at(i);

		if (shopIndex != 0) m_tabgroup.GetTabs()->push_back(m_gameShopViews.at(shopIndex)->GetTab());
		
		m_tabgroup.CalcPos();
	}
}

void GameShopMenu::Render()
{
	if (m_uiMenuState == menuOpened)
	{
		m_background.Render();
		m_close.Render();

		//m_confirmPreorder.Render();
		//m_cancelPreorder.Render();
		m_cancelTrade.Render();
		m_confirmTrade.Render();

		if (m_page != NULL)
		{
			((TradeInventoryView*)m_page)->GetActiveShopInventoryView()->SetInvItems();
			m_page->Render();
		}

		if (UIDialogScreen::m_state == dialogScreenActive)
		{
			m_dialogText.Render();

			for (unsigned int i = 0; i < m_options.size(); i++)
			{
				m_options.at(i).Render();
			}
		}
	}

	m_tabgroup.Render();
}

void GameShopMenu::OnExitOpened()
{
	m_dialogText.SetText(&m_emptyString);
	m_options.resize(0);
	m_dialogOptionsForButtons = NULL;



	UIMenu::OnExitOpened();
}

bool GameShopMenu::ToggleState()
{
	switch (m_uiMenuState)
	{
	case menuOpened:
		GameShopMenu::OnExitOpened();
		UIMenu::OnEnterClosed();

		return false; break;
	case menuClosed:
		UIMenu::OnExitClosed();
		UIMenu::OnEnterOpened();

		return true; break;
	}

	UIMenu::m_inputModel->SetState(m_uiMenuState);

	return true;
}

void GameShopMenu::SelectOnTabs(POINT * p)
{
	m_tabgroup.Select(p);
}

void GameShopMenu::Select(POINT * p)
{
	if (!m_uiMenuState == menuOpened) { m_tabgroup.Select(p); return; }
	if (!UIMenu::IsPointInBounds(p)) return;

	m_tabgroup.Select(p);
	m_close.Select(p);
	//m_confirmPreorder.Select(p);
	//m_cancelPreorder.Select(p);
	m_cancelTrade.Select(p);
	m_confirmTrade.Select(p);
	
	if (m_page != NULL) m_page->Select(p);
}

void GameShopMenu::AltSelect(POINT * p)
{
	if (!m_uiMenuState == menuOpened) return;
	if (!UIMenu::IsPointInBounds(p)) return;

	if (m_page != NULL) m_page->AltSelect(p);
}

bool  GameShopMenu::MouseOver(POINT * p)
{
	if (!m_uiMenuState == menuOpened) return false;
	if (!UIMenu::IsPointInBounds(p)) return false;

	if (m_page != NULL) { if (m_page->MouseOver(p)) return true; }

	return false;
}

void GameShopMenu::SetShopForAutoInv()
{
	ShopInventoryView::m_selectedPlayerController = tempCharacterController;

	int shopId = -1;

	for (unsigned int index = 0; index < tempCharacterController->GetInRangeShops()->size(); index++)
	{
		shopId = tempCharacterController->GetInRangeShops()->at(index);
		m_page = m_gameShopViews.at(shopId);
		return;
	}

	m_page = m_gameShopViews.at(0);

	//new

}


void GameShopMenu::ActionCancelTrade()
{
	((TradeInventoryView*)m_page)->GetActiveShopInventoryView()->ClearSelection();
	//setting selections to false
	//call something frm gameshop zero mem
}

void GameShopMenu::ActionConfirmTrade()
{
	int selectionCount = 0;
	int buyCount = 0;
	
	//1. is(&view->GameShop == any gameshop in PlayerController()->Game SHops In Range())
	//1. cost: for loop over Game Shops in range

	if (IsCurrentGameShopInRange())
	{
		//selectionCount = count not null inv items not selected 
		//buyCount = each item not selection of 0

		//if (selectionCount + buyCount <= 10)
		if (((TradeInventoryView*)m_page)->GetActiveShopInventoryView()->TradeWillFit())
		{
			//Remove Old
			((TradeInventoryView*)m_page)->GetActiveShopInventoryView()->RemoveOld();
		
			//Add New Items
			((TradeInventoryView*)m_page)->GetActiveShopInventoryView()->AddNew();

			//clear selections;
			((TradeInventoryView*)m_page)->GetActiveShopInventoryView()->ClearSelection();



			//process callback vector
			((TradeInventoryView*)m_page)->GetTradeInventory()->ActionOnConfirmTrade();

			/*
			int ib = (int)m_dialogOwner->GetNPCController()->GetInteractionController()->GetState();

			if (ib == 6)
			{
				OutputDebugString("State= 6");
			}
			else OutputDebugString("State != 6");

			
			m_dialogOwner->GetNPCController()->GetInteractionController()->SetState(ibPostRewardInactive);
			*/

			//todo enum index to mean button ids

			if (m_dialogOptionsForButtons!=NULL)
			{
				if (m_dialogOptionsForButtons->size() >= 0) ActionForOption(m_dialogOptionsForButtons->at(0));
			}


			
			

			//1. automatically choose the first dialog option
			//2. have a special code that is interpreted by our dialog behavior

			//this callback will be set here with a mutator that will be called by 
		}
	}
}

void GameShopMenu::ActionPreOrder()
{
	//grey everything out
	//set some autobuy in reange state to true
	//make sure our update is checking to autobuy our stuff when we enter shop zone
}

void GameShopMenu::ActionCancelOrder()
{
	//call something frm gameshop zero mem
}

void GameShopMenu::ToggleMenuWithAutoShop()
{
	if (m_uiMenuState == menuClosed) SetShopForAutoInv();

	ToggleState();
}

bool GameShopMenu::IsCurrentGameShopInRange()
{

	vector<ShopZone*> * zones = ((TradeInventoryView*)m_page)->GetTradeInventory()->GetShopZones();
	for(unsigned int i = 0; i < zones->size(); i++)
	{
		if (zones->at(i)->IsUsable(
			*tempCharacterController->GetCharacter()->GetActor()->GetPhysicsObject()->GetPosition(),
			tempCharacterController->GetCharacter()->GetActor()->GetTeam()))
		{
			return true;
		}
	}


	/*
	for (unsigned int i = 0; i < tempCharacterController->GetInRangeShops()->size(); i++)
	{
		if (m_gameShopViews.at(tempCharacterController->GetInRangeShops()->at(i)) == m_page)
		{
			return true;
		}
	}
	*/

	return false;
}

TradeInventoryView * GameShopMenu::GetGameShopView()
{
	return (TradeInventoryView*)m_page;
}

void GameShopMenu::SetGameShopView(TradeInventoryView * gameShopView)
{
	m_page = gameShopView;
}

PlayerCharacterController * GameShopMenu::GetCtrl()
{
	return tempCharacterController;
}

void GameShopMenu::SetCtrl(PlayerCharacterController * playerCharacterController)
{
	tempCharacterController = playerCharacterController;
}


bool GameShopMenu::SetPage(UIContentArea * contentArea)
{
	if (m_uiMenuState == menuClosed)
	{
		UIMenu::OnExitClosed();
		UIMenu::OnEnterOpened();
	}
	else if (m_page == contentArea)
	{
		GameShopMenu::OnExitOpened();
		UIMenu::OnEnterClosed();
	}
	return TabLayoutMenu::SetPage(contentArea);
}

void GameShopMenu::SetButtonOptions(int dialogScreenIndex)
{
	m_dialogOptionsForButtons = &m_dialogBehavior->GetOptionsByScreenIndex(dialogScreenIndex)->m_TradeScreenOptions;	
}
