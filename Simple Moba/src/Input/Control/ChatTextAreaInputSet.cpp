#include "ChatTextAreaInputSet.h"


ChatTextAreaInputSet::ChatTextAreaInputSet() : InputSet()
{
	gameState = NULL;
	gameView = NULL;
}

ChatTextAreaInputSet::ChatTextAreaInputSet(CoreGameState * state, MobaViewState * view)
{
	gameState = state;
	gameView = view;

	m_uiChat = gameView->GetHud()->GetChat();
}

ChatTextAreaInputSet::~ChatTextAreaInputSet()
{

}

void ChatTextAreaInputSet::Update(float deltaTime)
{

	m_model->SetState(m_uiChat->GetInputBox()->GetState());

	m_uiChat->Update(deltaTime);

	if (m_uiChat->GetInputBox()->GetState()== textInputActive)
	{
		m_uiChat->Update(deltaTime);

		//expend all the keyboard letters
		//make sure to deal with excape
		

		/*
		//expend for all so nothing happens to rest of game.

		if (m_keyDialog->GetKeyDialogState() == keyDialogStateChecking)
			sm_gameInputController->ExpendAllTheThings(true, true);
		//else not checking
		else sm_gameInputController->ExpendAllTheThings(true, false);
		*/

	}
}

void ChatTextAreaInputSet::AttemptAction(int action, float deltaTime)
{
	switch (action)
	{
	//closed state
	case chatTextAreaActionOpen: m_uiChat->ActionOpen(); break;
	//open state
	case chatTextAreaActionSelect:m_uiChat->Select(&g_mouseClientPosition); break;
	case chatTextAreaActionClose: m_uiChat->ActionClose(); break;
	case chatTextAreaActionSend: m_uiChat->ActionSend(); break;
	case chatTextAreaActionLeft: m_uiChat->ActionLeft(); break;
	case chatTextAreaActionRight: m_uiChat->ActionRight(); break;
	case chatTextAreaActionBackspace:m_uiChat->ActionBackspace(); break;
	case chatTextAreaActionChatScrollUp:m_uiChat->ActionScrollUp(); break;
	case chatTextAreaActionChatScrollDown:m_uiChat->ActionScrollDown(); break;
	case chatTextAreaActionCycleScope: m_uiChat->ActionCycleScope(); break;
	}
}

void ChatTextAreaInputSet::SpamAction(int action, float deltaTime)
{

}

void ChatTextAreaInputSet::Finally(float deltaTime)
{
	if (m_uiChat->GetInputBox()->GetState() == textInputActive)
	{
		sm_gameInputController->ExpendAllTheThings(true, false);
	}
}