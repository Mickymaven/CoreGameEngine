#include "VisionOwlInteractionController.h"

VisionOwlInteractionController::VisionOwlInteractionController()
{

}

VisionOwlInteractionController::~VisionOwlInteractionController()
{

}


bool VisionOwlInteractionController::Init(
	Character * character,
	AggressionState * aggressionState,
	VisionOwlDialogBehavior * visionOwlDialogBehavior,
	DialogStandbyBehavior * dialogStandbyBehavior)
{
	m_visionOwlDialogBehavior = visionOwlDialogBehavior;
	m_dialogStandbyBehavior = dialogStandbyBehavior;
	m_aggressionState = aggressionState;
	m_actorInv = character->GetTradeInventory();
	m_actor = character->GetActor();
	m_character = character;

	return true;
}
/*
DialogScreenData * VisionOwlInteractionController::ActionRequestDialogScreen()//is used confirmed
{

	OutputDebugString("\nBASE CLASS VisionOwlInteractionController::ActionRequestDialogScreen()\n");
	return NULL;

	
}

int VisionOwlInteractionController::ActionRequestDialogEntryPoint()
{
	OutputDebugString("\nBASE CLASS VisionOwlInteractionController::ActionRequestDialogEntryPoint()\n");
	return -50;
	/*
	if (m_state == ibQuest)
	{
		if (true)
		{
			OutputDebugString("Check quest complete = true \n");

			ExitCurrentState();
			OnEnterReturnDialog();

			return visionOwlDialogScreenQuestReturnWin;
		}
	}
	else return m_visionOwlDialogBehavior->GetEntryOptionIndex(GetState());
	

}
*/