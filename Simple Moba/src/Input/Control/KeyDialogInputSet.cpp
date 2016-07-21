#include "KeyDialogInputSet.h"


KeyDialogInputSet::KeyDialogInputSet() : InputSet()
{
	gameState = NULL;
	gameView = NULL;
}

KeyDialogInputSet::KeyDialogInputSet(StandardMatch5v5State * state, MobaViewState * view)
{
	gameState = state;
	gameView = view;

	m_keyDialog = gameView->GetKeyDialog();
}

KeyDialogInputSet::~KeyDialogInputSet()
{
	
}

void KeyDialogInputSet::Update(float deltaTime)
{
	m_keyDialog->Update(deltaTime);
	
	if (m_keyDialog->GetUIMenuState() == menuOpened)
	{
		//expend for all so nothing happens to rest of game.

		if (m_keyDialog->GetKeyDialogState() == keyDialogStateChecking)
			sm_gameInputController->ExpendAllTheThings(true, true);
		//else not checking
		else sm_gameInputController->ExpendAllTheThings(true, false);

	}

}

void KeyDialogInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
	case keyDialogActionSelect:
		
		if (m_keyDialog->IsOpen())
		{
			m_keyDialog->Select(&g_mouseClientPosition);
		}
		break;

	case keyDialogActionClose:
		/*
		if (m_keyDialog->IsOpen())
		{
			m_keyDialog->CloseMenu();
		}*/
		break;
	case keyDialogActionFinally:

		break;

	}
}

void KeyDialogInputSet::SpamAction(int action, float deltaTime)
{

	if (m_keyDialog->IsOpen())
	{
		switch (action)
		{
		case mainMenuActionLeftClick:
			sm_gameInputController->ExpendForBounds(LEFT_BUTTON, m_keyDialog);
			break;
		case mainMenuActionRightClick:
			sm_gameInputController->ExpendForBounds(RIGHT_BUTTON, m_keyDialog);
			break;
		}
	}
}

void KeyDialogInputSet::Finally(float deltaTime)
{
	if (m_keyDialog->IsOpen())
	{
		sm_gameInputController->ExpendAllTheThings(true, false);
	}
}