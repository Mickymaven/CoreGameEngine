#include "AngryCatInteractionController.h"

AngryCatInteractionController::AngryCatInteractionController()
{

}

AngryCatInteractionController::AngryCatInteractionController(
	Actor * actor,
	AggressionState * aggressionState) :
	m_aggressionState(aggressionState)
{

	m_stateInstance = NULL;
	m_actor = actor;

	//init state
	m_state = ibAggressive;
	m_stateInstance  = aggressionState;
}

AngryCatInteractionController::~AngryCatInteractionController()
{

}

void AngryCatInteractionController::Update(float deltaTime)
{


	m_stateInstance->Update(deltaTime);


	/*
	switch (m_state)
	{
		case ibAggressive: AggressiveBehavior(deltaTime); break;
	};*/
}


void AngryCatInteractionController::OnEnterAgressive()
{
}

void AngryCatInteractionController::Aggressive(float deltaTime)
{
	m_aggressionState->Update(deltaTime);
}

void AngryCatInteractionController::OnExitAgressive()
{
}

void AngryCatInteractionController::OnHit(VitalEntity * owner)
{
	m_aggressionState->OnHit(owner);
}

DialogScreenData * AngryCatInteractionController::ActionRequestDialogScreen(){ return NULL; }

int AngryCatInteractionController::ActionRequestDialogEntryPoint() { return -1; }


DialogBehavior * AngryCatInteractionController::GetDialogBehavior() { return NULL; }
void AngryCatInteractionController::ActionEvent(int index) {  }