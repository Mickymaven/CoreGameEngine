#include "ZZzzz.h"

ZZzzz::ZZzzz(Actor * owner) : InstantAbility(owner)
{
	OnEnterInactive();

	//m_range = 6.0f;
	m_name = "ZZzzz";
	//m_defaultCooldown = 0.0f;
	//m_castType = abilityCastTypeDirectionalCast;
	//m_cooldownExpires = 0.0f;
	//m_castTime = 0.0f;
	//m_timeActive = 0.0f;
	//m_maximumLife = 0.0f;
	//m_damageType = damageTypeCatVoodoo;
	//m_damageApplicationType = damageApplicationTypeOverTime;

	m_sleepTimer = LMTimer(0.0f, false);

}

ZZzzz::~ZZzzz()
{

}

void ZZzzz::Activate(float currentGameTime)
{
	if (m_state != abilityActive)
	{
		ExitCurrentState();
		OnEnterActive(currentGameTime);
	}
}

void ZZzzz::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	m_castTime = currentGameTime;

	m_sleepTimer.RestartWithDuration(10.0f, true);

	// BUFF SUGAR OVERLOAD ///////
	CreateBuff(m_owner, buffBuff, buffSleeping, 10.0f);
	m_tempBuff->SetHPCurve(true, 100.0f);//100 hp via regen buff
	//////////////////////////////
	
}

void ZZzzz::Active(float deltaTime)
{
	m_sleepTimer.Update(deltaTime);

	if (m_sleepTimer.GetState() == timerFinished)
	{
		OnExitActive();
		OnEnterInactive();
	}
}

void ZZzzz::OnExitActive()
{

}

void ZZzzz::OnEnterInactive()
{
	m_state = abilityInactive;

	m_sleepTimer.RestartWithDuration(0.0f, false);
}

void ZZzzz::Inactive(float deltaTime)
{

}

void ZZzzz::OnExitInactive()
{

}