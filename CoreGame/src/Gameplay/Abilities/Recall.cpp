#include "Recall.h"

Recall::Recall(Actor * owner) : InstantAbility(owner)
{
	OnEnterInactive();

	//m_range = 6.0f;
	m_name = "Recall";
	//m_defaultCooldown = 0.0f;
	//m_castType = abilityCastTypeDirectionalCast;
	//m_cooldownExpires = 0.0f;
	//m_castTime = 0.0f;
	//m_timeActive = 0.0f;
	//m_maximumLife = 0.0f;
	//m_damageType = damageTypeCatVoodoo;
	//m_damageApplicationType = damageApplicationTypeOverTime;

	m_recallTimer = LMTimer(0.0f, false);

}

Recall::~Recall()
{

}

void Recall::Activate(float currentGameTime)
{
	if (m_state != abilityActive)
	{
		ExitCurrentState();
		OnEnterActive(currentGameTime);
	}
}

void Recall::Success()
{
	ExitCurrentState();
	OnEnterInactive();
}

void Recall::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	m_castTime = currentGameTime;

	m_recallTimer.RestartWithDuration(4.5f, true);
}

void Recall::Active(float deltaTime)
{
	m_recallTimer.Update(deltaTime);
}

void Recall::OnExitActive()
{

}

void Recall::OnEnterInactive()
{
	m_state = abilityInactive;
	
	m_recallTimer.RestartWithDuration(0.0f, false);
}

void Recall::Inactive(float deltaTime)
{

}
void Recall::OnExitInactive()
{

}

LMTimer * Recall::GetRecallTimer()
{
	return & m_recallTimer;
}
