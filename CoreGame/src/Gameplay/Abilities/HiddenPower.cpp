#include "HiddenPower.h"

HiddenPower::HiddenPower()
{
}

HiddenPower::HiddenPower(Actor * owner) : SingleTargetAbility(owner)
{
	m_range = 2.0f;
	m_name = "Hidden Power";

	m_targetGroup = abilityTargetTeam;

	OnEnterInactive();
	m_castType = abilityCastTypeSingleTargetCast;
	m_damageType = damageTypeDamage;
	m_appType = heaSingle;
	m_defaultCooldown = 15.0f;
	m_cooldownExpires = 0.0f;

	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;

	m_delayDuration = 3.0f;
	

}

HiddenPower::~HiddenPower()
{
}

void HiddenPower::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;

	m_delayTimer.RestartWithDuration(m_delayDuration, true);
}

void HiddenPower::Active(float deltaTime)
{
	if (m_delayTimer.GetState() == timerFinished)
	{
		CreateBuff(m_singleTarget, buffBuff, buffOmNomNom, 30.0f);
		m_tempBuff->stat()->m_catVoodoo = 10.0f;
		m_tempBuff->stat()->m_armor = 10.0f;
		m_tempBuff->stat()->m_attackSpeed = 10.0f;
		m_tempBuff->stat()->m_catVoodooResist = 10.0f;
		m_tempBuff->stat()->m_healthRegen = 10.0f;
		m_tempBuff->stat()->m_moveSpeed = 10.0f;
		m_tempBuff->stat()->m_physicalDamage = 10.0f;
		m_tempBuff->stat()->m_range = 10.0f;

		OnExitActive();
		OnEnterInactive();
	}

	m_delayTimer.Update(deltaTime);
}

void HiddenPower::OnExitActive()
{
}

void HiddenPower::OnEnterInactive()
{
	m_state = abilityInactive;
}

void HiddenPower::Inactive(float DeltaTime)
{
}

void HiddenPower::OnExitInactive()
{
}
