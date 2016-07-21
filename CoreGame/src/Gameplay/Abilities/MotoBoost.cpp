#include "MotoBoost.h"

MotoBoost::MotoBoost(Actor * owner) : InstantAbility(owner)
{
	OnEnterInactive();

	m_range = 0.0f;
	m_name = "Moto-Boost";
	m_defaultCooldown = 10.0f;
	m_castType = abilityCastTypeInstantCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;


	//
	m_ownerPosition = owner->GetPhysicsObject()->GetPosition();
	m_ownerRadius = owner->GetPhysicsObject()->GetRadius();

}

MotoBoost::~MotoBoost()
{

}
void MotoBoost::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	m_castTime = currentGameTime;

	m_timeActive = 0.0f;//reset to zero each time
	m_maximumLife = 5.0f;//5 seconds of scary fear and stuff

	//SPEED UP BUFF //////////
	CreateBuff(m_owner, buffBuff, buffPowerOfTheBoost, m_maximumLife);
	m_tempBuff->stat()->m_moveSpeed = 6.0f;
	m_buff = m_tempBuff; //save buff to do stuff on activate.
	//////////////////////////

}

void MotoBoost::Active(float deltaTime)
{
	Actor * m_newTarget = ClosestTargetInRange(m_ownerPosition, m_ownerRadius, neutralCategoryAll);

	if (m_newTarget != NULL)
	{
		AddDamage(2.0f * m_owner->GetStats()->m_physicalDamage, m_damageType,
			m_owner, m_newTarget, 1.5f, 0.0f, m_appType);

		if (m_buff != NULL) m_buff->GetTimer()->RestartWithDuration(0.0f, true);

		// CRASH BUFF ///////////
		CreateBuff(m_owner, buffDebuff, buffMotoSmash, 6.0);
		m_tempBuff->stat()->m_moveSpeed = -3.0f;

		OnExitActive();
		OnEnterInactive();
		return;
		/////////////////////////
	}

	UpdateLifeTimer(deltaTime);

}

void MotoBoost::OnExitActive()
{

}

void MotoBoost::OnEnterInactive()
{
	m_state = abilityInactive;
}

void MotoBoost::Inactive(float DeltaTime)
{

}

void MotoBoost::OnExitInactive()
{

}