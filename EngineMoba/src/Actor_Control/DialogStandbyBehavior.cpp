#include "DialogStandbyBehavior.h"

DialogStandbyBehavior::DialogStandbyBehavior() : Interaction()
{
	m_state = dialogStandbyInitial;
}
	
bool DialogStandbyBehavior::Init(WalkState * walkState, Actor * owner)
{

	return true;
}

DialogStandbyBehavior::~DialogStandbyBehavior()
{

}

void DialogStandbyBehavior::Update(float deltaTime)
{
	switch (m_state)
	{
	case dialogStandbyInitial: Initial(deltaTime); break;
	}
}

void DialogStandbyBehavior::OnEnterInitial()
{
	m_state = dialogStandbyInitial;
}

void DialogStandbyBehavior:: Initial(float deltaTime)
{

}

void DialogStandbyBehavior::OnExitInitial()
{

}

void DialogStandbyBehavior::ExitCurrentState()
{
	switch (m_state)
	{
	case dialogStandbyInitial: OnExitInitial(); break;
	}
}

DialogStandbyState DialogStandbyBehavior::GetState()
{
	return m_state;
}

void DialogStandbyBehavior::OnHit(VitalEntity * owner)
{

}