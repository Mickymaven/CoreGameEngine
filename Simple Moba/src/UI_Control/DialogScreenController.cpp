#include "DialogScreenController.h"

DialogScreenController::DialogScreenController()
{

}

DialogScreenController::~DialogScreenController()
{

}

bool DialogScreenController::Init(ViewProfile * viewProfile,
	ThemeResources * theme, GameShopMenu * gameShopMenu)
{
	if (! m_dialogScreen.Init(viewProfile, theme)) return false;

	//Set Call back to allow Basic DialogScreens to call function that will set a Game Shop Menu
	// as the dialog view when such an event occurs.

	UIDialogScreen::SetDialogViewChangeCallback(std::bind(&DialogScreenController::DialogViewChangeCallback, this, _1, _2, _3));

	m_activeDialogScreen = &m_dialogScreen;


	m_gameShopMenu = gameShopMenu;

	return true;
}

void DialogScreenController::Render()
{
	if (m_activeDialogScreen == &m_dialogScreen) m_dialogScreen.Render();
}

void DialogScreenController::OpenDialog(NPCView * npcView, PlayerCharacterController * client, vector<PlayerCharacterController *> * clientTeam)
{
	bool allow = npcView->GetNPCController()->GetDialogBehavior()->AuthDialog(client, clientTeam);
	
	if (allow)
	{
		//Here we would determine which UIDialog instance to open (dialog instances have difeerent uses/layouts).
		int npcControllerState = npcView->GetNPCController()->GetInteractionController()->GetState();
		//int npcState = npcController->GetNPC()->GetState();

		int dialogScreenIndex = npcView->GetNPCController()->GetDialogBehavior()->GetEntryOptionIndex(npcControllerState);
	
	
		//int viewScreen = npcController->GetDialogBehavior()->GetEntryOptions(npcControllerState)->m_viewScreenClass;

		DialogViewChangeCallback(npcView, dialogScreenIndex, dialogScreenViewBasic);



		//m_activeDialogScreen->SetOptions(npcController->GetInteractionController()->ActionRequestDialogScreen());

		m_activeDialogScreen->Activate(npcView);
	}
}

void DialogScreenController::ActionSelect(POINT * p)
{
	if (m_activeDialogScreen == &m_dialogScreen) m_dialogScreen.Select(p);
	//we are temporarly only allowing selection from the basic dialog, with trade/gameshop screen selecting diabled while we design
}

void DialogScreenController::DialogViewChangeCallback(NPCView * npcView, int dialogScreenIndex, DialogScreenViewOptions option)
{
	

	DialogScreenViewOptions m_screenOption = (DialogScreenViewOptions)npcView->GetNPCController()->GetDialogBehavior()->GetOptionsByScreenIndex(dialogScreenIndex)->m_viewScreenClass;


	if (m_activeDialogScreen == m_gameShopMenu && m_screenOption != dialogScreenViewGameShop)
	{
		m_gameShopMenu->OnExitOpened();
		m_gameShopMenu->OnEnterClosed();
	}

	switch (m_screenOption)
	{
	case dialogScreenViewBasic: m_activeDialogScreen = &m_dialogScreen;  break;
	case dialogScreenViewGameShop: m_activeDialogScreen = m_gameShopMenu;
		
		//m_gameShopMenu->ShopDialogTabLayoutMenu::Activate(npcController);


		if (m_gameShopMenu->GetUIMenuState() == menuClosed)
		{
			m_gameShopMenu->SetGameShopView(npcView->GetTradeInventoryView());
			m_gameShopMenu->OnExitClosed();
			m_gameShopMenu->OnEnterOpened();
			}
		else
		{
			MessageBox(NULL, "shop was open when we activated a dialog", "simple moba debug", MB_OK);
		}

		break;

	

	}

	
	m_activeDialogScreen->SetDialogModel(npcView);//before set options
	m_activeDialogScreen->SetOptions(dialogScreenIndex);
	m_activeDialogScreen->SetAsActive();


	if (m_screenOption == dialogScreenViewGameShop) m_gameShopMenu->SetButtonOptions(dialogScreenIndex);


	m_activeDialogScreen->ActionNextDialog(dialogScreenIndex);//might do nothing, text this


}

void DialogScreenController::SetActiveDialog(DialogScreenViewOptions option)
{
	switch (option)
	{
	case dialogScreenViewBasic:
		m_activeDialogScreen = &m_dialogScreen;
		break;
	default:
	case dialogScreenViewGameShop:
		m_activeDialogScreen = m_gameShopMenu;
		break;

	}
}