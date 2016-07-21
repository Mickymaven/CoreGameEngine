#include "EternalLight.h"

EternalLight::EternalLight() {}

EternalLight::EternalLight(Actor * owner) : InstantAbility(owner)
{
	OnEnterInactive();

	m_targetGroup = abilityTargetTeam;

	m_range = 10.0f;
	m_name = "Eternal Light";
	m_defaultCooldown = 5.0f;
	m_castType = abilityCastTypeInstantCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;
}

EternalLight::~EternalLight()
{
}

void EternalLight::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	m_castTime = currentGameTime;

	m_timeActive = 0.0f;
	m_maximumLife = 10.0f;

	m_ownerCatVoodooOnCast = m_owner->GetStats()->m_catVoodoo;

	LMVector3 * position = m_owner->GetPhysicsObject()->GetPosition();
	LMVector3 * targetPosition;
	float radius = m_range;
	float hitDist, a, b , hypoSquared;

	for (unsigned int i = 0; i < m_playerTeam->size(); i++)
	{
		if (m_playerTeam->at(i)->GetVitalEntityState() != vitalEntityStateInactive)
		{
			hitDist = radius + m_playerTeam->at(i)->GetPhysicsObject()->GetRadius();

			targetPosition = m_playerTeam->at(i)->GetPhysicsObject()->GetPosition();
			a = abs(position->x - targetPosition->x);
			b = abs(position->z - targetPosition->z);
			hypoSquared = (a*a + b*b);
			if (hypoSquared < hitDist*hitDist)
			{
				m_targetsToHeal.push_back(m_playerTeam->at(i));
			}
		}
	}

	for (unsigned int i = 0; i < m_targetsToHeal.size(); i++)
	{
		AddHealing(2.0f * m_ownerCatVoodooOnCast, m_owner, m_targetsToHeal.at(i), m_maximumLife, 0.0f, m_appType);
	}

	if (m_targetsToHeal.size() > 0) m_targetsToHeal.resize(0);
}

void EternalLight::Active(float deltaTime)
{
	OnExitActive();
	OnEnterInactive();
}

void EternalLight::OnExitActive()
{
}

void EternalLight::OnEnterInactive()
{
	m_state = abilityInactive;
}

void EternalLight::Inactive(float DeltaTime)
{
}

void EternalLight::OnExitInactive()
{
}
