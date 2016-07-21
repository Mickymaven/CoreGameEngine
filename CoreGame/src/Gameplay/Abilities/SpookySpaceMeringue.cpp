#include "SpookySpaceMeringue.h"



SpookySpaceMeringue::SpookySpaceMeringue(Actor * owner) : PointAbility(owner)
{
	m_range = 8.0f;
	m_name = "Spooky Space Meringue";
	OnEnterInactive();
	m_castType = abilityCastTypePointCast;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;
	m_defaultCooldown = 1.8f;
	m_cooldownExpires = 0.0f;

	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;

	m_triggered = false;

	m_meringue = Sprite(
		LMVector3(0.0f, 0.0f, 0.0f),//Position
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.2f, 0.2f, 0.2f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f);

}

SpookySpaceMeringue::~SpookySpaceMeringue()
{

}

void SpookySpaceMeringue::OnEnterActive(float gameTime)
{
	m_state = abilityActive;
	m_castTime = gameTime;

	m_maximumLife = 2.5f;
	m_triggered = false;

	m_meringue.GetPhysicsObject()->GetPosition()->x = m_castPoint->x;
	m_meringue.GetPhysicsObject()->GetPosition()->y = 0.2f;
	m_meringue.GetPhysicsObject()->GetPosition()->z = m_castPoint->z;

}

void SpookySpaceMeringue::Active(float deltaTime)
{
	if (m_triggered == false)
	{
		Actor * newTarget = ClosestTargetInRange(
			m_meringue.GetPhysicsObject()->GetPosition(),
			0.7f,
			neutralCategoryAll);

		if (newTarget != NULL)
		{
			AddDamage(m_owner->GetStats()->m_catVoodoo * 1.5f, m_damageType, m_owner, newTarget,
				m_maximumLife, 0.0f, m_appType);

			// BUFF SUGAR OVERLOAD ///////
			CreateBuff(newTarget, buffBuff, buffSugarOverload, 10.0f);
			m_tempBuff->stat()->m_moveSpeed -= 0.67f * newTarget->GetStats()->m_moveSpeed;
			//////////////////////////////

			m_triggered = true;
		}
	}
}

void SpookySpaceMeringue::OnExitActive()
{

}

void SpookySpaceMeringue::OnEnterInactive()
{
	m_state = abilityInactive;
}

void SpookySpaceMeringue::Inactive(float deltaTime)
{

}
void SpookySpaceMeringue::OnExitInactive()
{

}

Sprite * SpookySpaceMeringue::GetMeringue()
{
	return &m_meringue;
}

bool SpookySpaceMeringue::IsTriggered(){ return m_triggered; }