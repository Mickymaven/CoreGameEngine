#include "ShopMenuInputSet.h"


ShopMenuInputSet::ShopMenuInputSet()
{}

ShopMenuInputSet::ShopMenuInputSet(StandardMatch5v5State * state, MobaViewState * view)
{
	gameState = state;
	gameView = view;

	m_shopMenu = gameView->GetGameShopMenu();
	//m_shopView = gameView->GetGameShopMenu()->GetGameShopView(); //todo we dont use this to do anything
}

ShopMenuInputSet::~ShopMenuInputSet()
{

}

void ShopMenuInputSet::Update(float deltaTime)
{
	//m_shopView = gameView->GetGameShopMenu()->GetGameShopView(); //todo we dont use this to do anything***

	m_shopMenu->MouseOver(&g_mouseClientPosition);
}

void ShopMenuInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
	case shopActionClose:
		m_shopMenu->ToggleMenuWithAutoShop();
		break;
	case shopActionConfirmPreOrder:
		break;
	case shopActionConfirmTrade:
		break;
	case shopActionCancelTrade:
		break;
	case shopActionLeftMouse:
		//(each update) hit test clickable elements
		//OutputDebugString("IS LEFT CLICK ACTION\n");

		if (m_shopMenu->GetUIMenuState() == menuOpened)
		{
			m_shopMenu->Select(&g_mouseClientPosition);

			sm_gameInputController->ExpendForBounds(LEFT_BUTTON, (TabLayoutMenu*)m_shopMenu);
		}

		else if (m_shopMenu->GetUIMenuState() == menuClosed)
		{
			m_shopMenu->SelectOnTabs(&g_mouseClientPosition);//tab buttons only
		}

		break;
	case shopActionRightMouse:
		if (m_shopMenu->GetUIMenuState() == menuOpened)
			sm_gameInputController->ExpendForBounds(RIGHT_BUTTON, (TabLayoutMenu*)m_shopMenu);
		break;

	}
}

void ShopMenuInputSet::SpamAction(int action, float deltaTime)
{

}

void ShopMenuInputSet::Finally(float deltaTime)
{
	if (m_shopMenu->GetUIMenuState() == menuOpened)
	{
		sm_gameInputController->ExpendAllTheThings(true, false);
	}
}