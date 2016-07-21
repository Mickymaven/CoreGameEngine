#include "InteractionController.h"


/*
InteractionController::InteractionController()
{
	m_stateInstance = NULL;
}

InteractionController::InteractionController(NPC * npc)
{
	m_stateInstance = NULL;
	m_npc = npc;
}

InteractionController::~InteractionController()
{

}


void InteractionController::Update(float deltaTime)
{

}



void InteractionController::OnHit(VitalEntity * owner)
{
	return;
}

DialogScreenData * InteractionController::ActionRequestDialogScreen()
{
	return nullptr;
}

int InteractionController::ActionRequestDialogEntryPoint()
{
	return -1;
}
*/

InteractionBehavior InteractionController::GetState()
{
	return m_state;
}

/*
DialogBehavior * InteractionController::GetDialogBehavior()
{
	OutputDebugString("Bad call to InteractionController::GetDialogBehavior()");

	return nullptr;
}

void InteractionController::ActionEvent(int index)
{

}
*/

void InteractionController::SetState(InteractionBehavior state)
{
	m_state = state;
}
