#include "MainMenuInputSet.h"

MainMenuInputSet::MainMenuInputSet()
{}

MainMenuInputSet::MainMenuInputSet(StandardMatch5v5State * state, MobaViewState * view)
{
	gameState = state;
	gameView = view;

	m_mainMenu = gameView->GetMainMenu();
}

MainMenuInputSet::~MainMenuInputSet()
{

}

void MainMenuInputSet::Update(float deltaTime)
{
	m_model->SetState(m_mainMenu->GetUIMenuState());

	if (!sm_gameInputController->GetIsMouseOverExpended())
		if (gameView->GetStatPanel()->MouseOver(&g_mouseClientPosition)) sm_gameInputController->SetMouseOverExpended();


	if (!sm_gameInputController->GetIsMouseOverExpended())
		if (gameView->GetHud()->GetGameInfoPanel()->MouseOver(&g_mouseClientPosition)) sm_gameInputController->SetMouseOverExpended();


}

void MainMenuInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
	case mainMenuActionLeftClick:
		if (m_mainMenu->IsOpen())
		{
			m_mainMenu->Select(&g_mouseClientPosition);
			sm_gameInputController->ExpendForBounds(LEFT_BUTTON, m_mainMenu);
		}
		break;

	case mainMenuActionRightClick:
		
		if (m_mainMenu->IsOpen())
		{
			sm_gameInputController->ExpendForBounds(RIGHT_BUTTON, m_mainMenu);
		}
		break;
	case mainMenuActionToggleOpen:

		if (m_mainMenu->ToggleState())
		{
			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetState(infoPanelStateClosed);

		}
		break;
	case mainMenuActionToggleOpenStatPanelItems:
		
		if (gameView->GetStatPanel()->ToggleAction(statPanelOpenedItems))
		{
			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetState(infoPanelStateClosed);
			gameView->GetHud()->SetStateRequest(uiHudOpen);
		}
		else gameView->GetHud()->SetStateRequest(uiHudClosed);

		break;
	case mainMenuActionToggleOpenStatPanelStats:

		if (gameView->GetStatPanel()->ToggleAction(statPanelOpenedStats))
		{
			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetState(infoPanelStateClosed);
			gameView->GetHud()->SetStateRequest(uiHudOpen);

		}
		else gameView->GetHud()->SetStateRequest(uiHudClosed);

		break;

	case mainMenuActionApply:
		m_mainMenu->Apply();
		MessageBox(NULL, "Keybinds saved to ChartacterInput.data", "Simple Moba", MB_OK);
		break;
	case mainMenuActionConfirm:
		break;
	}
}

void MainMenuInputSet::SpamAction(int action, float deltaTime)
{
	if (m_mainMenu->IsOpen())
	{
		switch (action)
		{
		case mainMenuActionLeftClick:
			sm_gameInputController->ExpendForBounds(LEFT_BUTTON, m_mainMenu);
			break;
		case mainMenuActionRightClick:
			sm_gameInputController->ExpendForBounds(RIGHT_BUTTON, m_mainMenu);
			break;
		}
	}
}


void MainMenuInputSet::Finally(float deltaTime)
{
	if (m_mainMenu->IsOpen())
	{
		sm_gameInputController->ExpendAllTheThings(true, false);
	}
}