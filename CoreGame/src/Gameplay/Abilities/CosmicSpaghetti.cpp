#include "CosmicSpaghetti.h"

CosmicSpaghetti::CosmicSpaghetti(Actor * owner) : DirectionalAbility(owner)
{
	OnEnterInactive();

	m_range = 16.0f;
	m_name = "Cosmic Spaghetti";
	m_defaultCooldown = 5.0f;
	m_castType = abilityCastTypeDirectionalCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;

	//derived class inits

	m_ballSpeed =20.0f;

	m_enemypos = NULL;
	m_pos = NULL;
	m_newTarget = NULL;

	LMVector3 * pos = m_owner->GetPhysicsObject()->GetPosition();

	m_spaghettiball = Sprite(
		LMVector3(pos->x, pos->y, pos->z),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.2f, 0.2f, 0.2f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f);

}

CosmicSpaghetti::~CosmicSpaghetti()
{

}

void CosmicSpaghetti::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	
	m_castTime = currentGameTime;
	
	m_timeActive = 0.0f;
	m_maximumLife = m_range / m_ballSpeed;

	m_spaghettiball.GetPhysicsObject()->GetPosition()->x = m_owner->GetPhysicsObject()->GetPosition()->x;
	m_spaghettiball.GetPhysicsObject()->GetPosition()->y = 1.0f;
	m_spaghettiball.GetPhysicsObject()->GetPosition()->z = m_owner->GetPhysicsObject()->GetPosition()->z;
}

void CosmicSpaghetti::Active(float deltaTime)
{
	m_newTarget = NULL;
	m_enemypos = NULL;
	m_pos = m_spaghettiball.GetPhysicsObject()->GetPosition();

	m_spaghettiball.GetPhysicsObject()->GetVelocity()->x = m_indicatorDirection.x * m_ballSpeed;
	m_spaghettiball.GetPhysicsObject()->GetVelocity()->y = m_indicatorDirection.y * m_ballSpeed;
	m_spaghettiball.GetPhysicsObject()->GetVelocity()->z = m_indicatorDirection.z * m_ballSpeed;

	m_spaghettiball.GetPhysicsObject()->Update(deltaTime);

	m_newTarget = ClosestTargetInRange(m_pos, 0.1f, neutralCategoryAll);

	if (m_newTarget != NULL)
	{
		AddDamage(1.0f * m_owner->GetStats()->m_catVoodoo, m_damageType,
			m_owner, m_newTarget, 0.2f, 0.0f, m_appType);
		OnEnterInactive();
	}

	UpdateLifeTimer(deltaTime);
}

void CosmicSpaghetti::OnExitActive()
{

}

void CosmicSpaghetti::OnEnterInactive()
{
	m_state = abilityInactive;
}

void CosmicSpaghetti::Inactive(float deltaTime)
{

}
void CosmicSpaghetti::OnExitInactive()
{

}

Sprite * CosmicSpaghetti::GetSpaghettiBall() { return &m_spaghettiball; }