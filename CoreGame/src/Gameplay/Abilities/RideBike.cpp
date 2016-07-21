#include "RideBike.h"

RideBike::RideBike(Actor * owner) : InstantAbility(owner)
{	OnEnterInactive();

	m_buff = NULL;

	m_range = 0.0f;
	m_name = "Ride Bike";
	m_defaultCooldown = 3.0f;
	m_castType = abilityCastTypeInstantCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;


}

RideBike::~RideBike()
{
	if (m_buff != NULL)
	{
		m_buff->GetTimer()->RestartWithDuration(0.0f,true);
	}
}

void RideBike::OnEnterActive(float currentGameTime)
{

	if (m_state == abilityActive)
	{
		m_state = abilityInactive;
	}
	else
	{
		m_state = abilityActive;
	}

	m_castTime = currentGameTime;

	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;//5 seconds of scary fear and stuff

	if (m_buff == NULL)
	{
		CreateBuff(m_owner, buffBuff, buffBikeActivated, 10.0f);
		
		m_tempBuff->GetTimer()->Stop();


		m_tempBuff->stat()->m_armor = -5.0f;
		m_tempBuff->stat()->m_catVoodooResist = -5.0f;
		m_tempBuff->stat()->m_physicalDamage = -100.0f;
		m_tempBuff->stat()->m_catVoodoo = -100.0f;
		m_tempBuff->stat()->m_moveSpeed = 15.0f - m_owner->GetStats()->m_moveSpeed;
		
	}
	else
	{
		StatChangeObject * stat = m_buff->GetStatChangeObject();

		if (m_state == abilityInactive)
		{
			stat->m_armor = 0.0f;
			stat->m_catVoodooResist = 0.0f;
			stat->m_physicalDamage = 0.0f;
			stat->m_catVoodoo = 0.0f;
			stat->m_moveSpeed = 0.0f;
		}
		else
		{
			stat->m_armor = -5.0f;
			stat->m_catVoodooResist = -5.0f;
			stat->m_physicalDamage = -100.0f;
			stat->m_catVoodoo = -100.0f;
			stat->m_moveSpeed = 15.0f - m_owner->GetStats()->m_moveSpeed;
		}
	}
}

void RideBike::Active(float deltaTime)
{

}

void RideBike::OnExitActive()
{

}


void RideBike::OnEnterInactive()
{
	m_state = abilityInactive;
}

void RideBike::Inactive(float deltaTime)
{

}
void RideBike::OnExitInactive()
{

}
