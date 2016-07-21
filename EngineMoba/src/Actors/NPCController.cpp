#include "NPCController.h"
#include "NPCController.h"

NPCController::NPCController()
{
	m_interactionControllerInstance = nullptr;
	m_dialogBehaviorInstance = nullptr;
	m_interactionControllerInstance = nullptr;
	m_dialogBehaviorInstance = nullptr;
}

NPCController::NPCController(
	Character * character)
: CharacterController(character)
{
	
}

NPCController::~NPCController()
{

}

void NPCController::Update(float deltaTime)
{
}

void NPCController::OnRespawn(float x, float y, float z)
{
}

LMVector3 *	NPCController::GetSpawn(int i)
{
	return &m_spawn;
}

vector<Interaction*>  * NPCController::GetInteractions()
{
	return &m_interactions;
}

NPCSelectAction NPCController::GetSelectBehavior()
{
	MessageBox(NULL, "NPCController Get Select Behavior", "Simple MOBA debug", MB_OK);
	return npcSelectAllowInfoClick;
}

InteractionController * NPCController::GetInteractionController()
{
	return m_interactionControllerInstance;
}

DialogBehavior * NPCController::GetDialogBehavior()
{
	return m_dialogBehaviorInstance;
}
/*
void NPCController::SetInteractionControllerSet(vector<InteractionController*>* ic_list)
{

}
*/