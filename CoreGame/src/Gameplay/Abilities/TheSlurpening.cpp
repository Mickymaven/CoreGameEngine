#include "TheSlurpening.h"

TheSlurpening::TheSlurpening(Actor * owner) : SingleTargetAbility(owner)
{
	m_range = 8.0f;
	m_name = "The Slurpening";
	OnEnterInactive();
	m_castType = abilityCastTypeSingleTargetCast;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;
	m_defaultCooldown = 1.8f;
	m_cooldownExpires = 0.0f;

	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;

	
	ownerPhysics = nullptr;
	strawPhysics = nullptr;
	targetPhysics = nullptr;

	m_straw = Sprite(
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(1.0f, 1.0f, 1.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f);

}

TheSlurpening::~TheSlurpening()
{
}

void TheSlurpening::OnEnterActive(float gameTime)
{
	m_state = abilityActive;

	m_castTime = gameTime;
	m_timeActive = 0.0f;
	m_maximumLife = 1.51f;

	float damageValue = 1.0f * m_ownerCatVoodooOnCast;

	//"the slurpening straw" applies 200 units of Cat Voodoo damage to the target over 1.5s
	AddDamage(damageValue, m_damageType, m_owner, m_singleTarget, 
	m_maximumLife, 0.0f, m_appType);

	// BUFF SUGAR OVERLOAD ///////
	CreateBuff(m_owner, buffBuff, buffSugarPower, 10.0f);	
	m_tempBuff->stat()->m_catVoodoo = 100.0f;
	//////////////////////////////

	m_straw.GetPhysicsObject()->GetRotation()->y = 1.57f;
	m_straw.GetPhysicsObject()->GetRotation()->z = 1.57f;

	ownerPhysics = m_owner->GetPhysicsObject();
	strawPhysics = m_straw.GetPhysicsObject();
	targetPhysics = m_singleTarget->GetPhysicsObject();
}

void TheSlurpening::Active(float deltaTime)
{
	strawPhysics->GetPosition()->x = ownerPhysics->GetPosition()->x;
	m_straw.GetPhysicsObject()->GetPosition()->y = 1.80f;
	strawPhysics->GetPosition()->z = ownerPhysics->GetPosition()->z;

	float difx = strawPhysics->GetPosition()->x - targetPhysics->GetPosition()->x;
	float difz = strawPhysics->GetPosition()->z - targetPhysics->GetPosition()->z;

	//normalize
	m_direction.x = difx;
	m_direction.y = 0.0f;
	m_direction.z = difz;

	m_direction.Normalize();

	//rotate
	float angleRadians = atan2(m_direction.x, m_direction.z);
	m_straw.GetPhysicsObject()->GetRotation()->x = 0.0f;
	m_straw.GetPhysicsObject()->GetRotation()->y = angleRadians - 1.57f;
	m_straw.GetPhysicsObject()->GetRotation()->z = 1.57f;

	ownerPhysics->GetRotation()->y = angleRadians - 3.141f;

	//scale

	m_straw.GetPhysicsObject()->GetScale()->y =
		sqrt((abs(difx) * abs(difx)) + (abs(difz) * abs(difz)));

	//should this be a buff?

		m_owner->GetStats()->AddHealth(0.5f * m_catVoodooApplied);


	UpdateLifeTimer(deltaTime);
}

void TheSlurpening::OnExitActive()
{

}

void TheSlurpening::OnEnterInactive()
{
	m_state = abilityInactive;
}

void TheSlurpening::Inactive(float deltaTime)
{

}
void TheSlurpening::OnExitInactive()
{

}
Sprite * TheSlurpening::GetStraw(){ return &m_straw;  }