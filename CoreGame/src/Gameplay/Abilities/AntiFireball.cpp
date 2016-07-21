#include "AntiFireball.h"

AntiFireball::AntiFireball(Actor * owner) : SingleTargetAbility(owner)
{
	m_moveSpeed = 10.0f;
	m_fireBallRadius = 1.0f;
	m_owner = owner;
	m_range = 150.0f;
	m_name = "SpamFireGhettiBall";
	OnEnterInactive();
	m_castType = abilityCastTypeSingleTargetCast;
	m_damageType = damageTypeDamage;
	m_appType = heaOverTime;
	m_defaultCooldown = 1.8f;
	m_cooldownExpires = 0.0f;

	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;


	//float rotation = pPhysicsObject->GetRotation()->y;

	//D3DXVECTOR3 velocity = D3DXVECTOR3(sin(rotation), 0.0f, cos(rotation));

	m_fireball = Sprite(
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(1.0f, 1.0f, 1.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f);

}

AntiFireball::~AntiFireball()
{

}


void AntiFireball::OnEnterActive(float gameTime)
{
	m_state = abilityActive;

	m_castTime = gameTime;
	m_timeActive = 0.0f;
	m_maximumLife = 1000.0f;

	m_fireball.GetPhysicsObject()->GetPosition()->x = m_owner->GetPhysicsObject()->GetPosition()->x;
	m_fireball.GetPhysicsObject()->GetPosition()->y = 1.5f;
	m_fireball.GetPhysicsObject()->GetPosition()->z = m_owner->GetPhysicsObject()->GetPosition()->z;
}

void AntiFireball::Active(float deltaTime)
{
	if (m_singleTarget->GetPhysicsObject()->GetPosition()->IsRangeFurther(
		*m_fireball.GetPhysicsObject()->GetPosition(), 2.0f))
	{

		float damageValue = 1.0f * m_ownerPhysicalDamageOnCast;
		/*
		AddDamage(damageValue, m_damageType, m_owner, m_singleTarget,
		0.5f, 0.0f, m_damageApplicationType);
		*/

		AddDamage(9.5f * m_ownerPhysicalDamageOnCast, m_damageType, m_owner, m_singleTarget,
			3.0f, 0.0f, m_appType);


		CreateBuff(m_singleTarget, buffDebuff, buffCoveredInSpam, 9.0f);

		if (m_singleTarget->GetStats()->m_armor > 10.0f) m_tempBuff->stat()->m_armor = -10.0f;
		else m_tempBuff->stat()->m_armor = -m_singleTarget->GetStats()->m_armor;
			
		OnExitActive();
		OnEnterInactive();

	}
	else
	{

		m_tempDisplacement = *m_singleTarget->GetPhysicsObject()->GetPosition();
		m_tempDisplacement -= *m_fireball.GetPhysicsObject()->GetPosition();
		m_tempDisplacement.Normalize();

		m_fireball.GetPhysicsObject()->GetPosition()->x += m_tempDisplacement.x * m_moveSpeed * deltaTime;
		//m_physicsObject->GetPosition()->y += m_tempDisplacement.y  * m_moveSpeed * deltaTime;
		m_fireball.GetPhysicsObject()->GetPosition()->z += m_tempDisplacement.z * m_moveSpeed * deltaTime;
	}
}

void AntiFireball::OnExitActive()
{

}

void AntiFireball::OnEnterInactive()
{
	m_state = abilityInactive;
}

void AntiFireball::Inactive(float deltaTime)
{

}
void AntiFireball::OnExitInactive()
{

}

Sprite * AntiFireball::GetFireball()
{
	return &m_fireball;
}
