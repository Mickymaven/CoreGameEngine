#include "HealTurret.h"

HealTurret::HealTurret(Actor* owner)
{
	m_owner = owner;
	m_range = 8.0f;
	m_name = "Heal Turret";
	OnEnterInactive();
	m_castType = abilityCastTypePointCast;
	m_damageType = damageTypeDamage;
	m_appType = heaOverTime;
	m_defaultCooldown = 1.8f;
	m_cooldownExpires = 0.0f;

	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;

	m_turret = Sprite(
		LMVector3(0.0f, 0.0f, 0.0f),//Position
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(1.0f, 1.0f, 1.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f);

	m_activated = false;
	m_placed = false;
}

HealTurret::~HealTurret()
{
	for (size_t i = m_HealLasers.size() - 1; i > 0; i--)
	{
		delete m_HealLasers.at(i);
	}
}

void HealTurret::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	m_castTime = currentGameTime;

	m_maximumLife = 60.0f;
	m_placed = true;
	m_activated = false;

	m_turret.GetPhysicsObject()->GetPosition()->x = m_castPoint->x;
	m_turret.GetPhysicsObject()->GetPosition()->y = 0.2f;
	m_turret.GetPhysicsObject()->GetPosition()->z = m_castPoint->z;
}

void HealTurret::Active(float deltaTime)
{
	if (!m_activated)
	{
		m_pos = m_turret.GetPhysicsObject()->GetPosition();

		m_actorsInRange.resize(0);

		GetActorsInRange(&m_actorsInRange, m_playerTeam, m_pos, m_range);

		for (unsigned int i = 0; i < m_actorsInRange.size(); i++)
		{
			//30% of missing HP to be added as heal object.
			float healValue = 0.3f * (m_actorsInRange.at(i)->GetStats()->m_maxHealth - m_actorsInRange.at(i)->GetStats()->m_health);

			AddHealing(healValue, m_owner, m_actorsInRange.at(i), 5.0f, 0.0f, heaOverTime);
		}

		Actor* a = nullptr;
		for (size_t i = 0; i < m_actorsInRange.size(); i++)
		{
			a = m_actorsInRange.at(i);
			break;
		}

		if (a != nullptr)
		{
			PhysicsObject * targetPhysics = a->GetPhysicsObject();
			PhysicsObject * turretPhysics = m_turret.GetPhysicsObject();
			LMVector3 direction = LMVector3();
			float difx = turretPhysics->GetPosition()->x - targetPhysics->GetPosition()->x;
			float difz = turretPhysics->GetPosition()->z - targetPhysics->GetPosition()->z;

			//normalize
			direction.x = difx;
			direction.y = 0.0f;
			direction.z = difz;

			direction.Normalize();

			//rotate
			float angleRadians = atan2(direction.x, direction.z);
			turretPhysics->GetRotation()->x = 0.0f;
			turretPhysics->GetRotation()->y = angleRadians - 1.57f;
			turretPhysics->GetRotation()->z = 0.0f;
		}

		m_activated = true;
	}
}

void HealTurret::OnExitActive()
{
}

void HealTurret::OnEnterInactive()
{
	m_state = abilityInactive;
}

void HealTurret::Inactive(float DeltaTime)
{
}

void HealTurret::OnExitInactive()
{
}

Sprite* HealTurret::GetTurret()
{
	return & m_turret;
}

bool HealTurret::IsPlaced()
{
	return m_placed;
}

bool HealTurret::IsActivated()
{
	return m_activated;
}
