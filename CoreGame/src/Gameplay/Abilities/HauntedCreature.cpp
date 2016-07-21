#include "HauntedCreature.h"

HauntedCreature::HauntedCreature(
	LMVector3 position,
	LMVector3 rotation,
	LMVector3 scale,
	LMVector3 velocity,
	LMVector3 spin,
	LMVector3 resize,
	float acceleration,
	LMVector3 origin)
	:Sprite(position, rotation, scale, velocity, spin, resize, acceleration)
{
	m_spawnEventDuration = 2.5f;
	m_state = hauntedCreatureStateInactive;

	m_creatureSpeed = 9.0f;

	//m_normalisedDirection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_normalisedVectorToTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_displacementTowardsTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_spawnEventTimer = LMTimer(m_spawnEventDuration, false);

	m_pos = m_physicsObject.GetPosition();
	m_targpos = NULL;

	m_radiusCopy = m_physicsObject.GetRadius();
	m_targradiusCopy = 0.0f;

}

HauntedCreature::HauntedCreature()
{

}

HauntedCreature::~HauntedCreature()
{

}

void HauntedCreature::Update(float deltaTime)
{
	m_spawnEventTimer.Update(deltaTime);
	m_physicsObject.Update(deltaTime);

	switch (m_state)
	{
	case hauntedCreatureStateInactive:
		break;
	case hauntedCreatureStateSpawning:
		if (m_spawnEventTimer.GetState() == timerFinished)
		{
			OnEnterSeeking();
			//OutputDebugString(" ExitSpawning/Enter Seeking. \n");
		}
		else
		{
			m_physicsObject.SetVelocity(m_normalisedDirection);
			//OutputDebugString(" Set velocity. \n");
		}
		break;

	case hauntedCreatureStateSeek:
		if ((m_target)->GetVitalEntityState() != vitalEntityStateInactive)
		{
			SeekTarget(deltaTime);
			
		}
		else
		{
			OnEnterDone();
		}
		break;
	case hauntedCreatureStateDone:
			Wander(deltaTime);
		break;
	default:
		break;
	}

	//m_physicsObject->SetPosition;
	
	//rotate and move in direction of enemy
}


void HauntedCreature::SetTarget(VitalEntity * target)
{
	m_target = target;
	m_targpos = m_target->GetPhysicsObject()->GetPosition();

	m_targradiusCopy = m_target->GetPhysicsObject()->GetRadius();

}

bool HauntedCreature::IsOverTarget()
{
	float x = abs(m_pos->x - m_targpos->x);
	float z = abs(m_pos->z - m_targpos->z);
	float displacementsq = x*x + z*z;

	float test = m_targradiusCopy + m_radiusCopy;
		  test = test*test - 0.5f;

	//char bufferx[100];
	//sprintf_s(bufferx, "test: %f, real: %f \n", test, displacementsq);
	//OutputDebugString(bufferx);

	if (displacementsq <= test)
		return true;

	return false;
}

void HauntedCreature::SeekTarget(float deltaTime)
{
	m_normalisedVectorToTarget.x = (m_targpos->x - m_pos->x);
	m_normalisedVectorToTarget.z = (m_targpos->z - m_pos->z);
	
	m_normalisedVectorToTarget.Normalize();
	//D3DXVec3Normalize(&m_normalisedVectorToTarget, &m_normalisedVectorToTarget);

	m_pos->x += m_normalisedVectorToTarget.x * m_creatureSpeed *deltaTime;
	//m_physicsObject->GetPosition()->y = m_normalisedVectorToTarget.y  * m_creatureSpeed * deltaTime;
	m_pos->z += m_normalisedVectorToTarget.z * m_creatureSpeed * deltaTime;
}

void HauntedCreature::Wander(float deltaTime)
{
	m_normalisedDirection.x = (rand() % 100) / 100.0f;
	m_normalisedDirection.y = 0.0f;
	m_normalisedDirection.z = (rand() % 100) / 100.0f;

	m_normalisedDirection.x -= 0.5f, m_normalisedDirection.z -= 0.5f;

	m_normalisedDirection.Normalize();
	//D3DXVec3Normalize(&m_normalisedDirection, &m_normalisedDirection);

	m_pos->x += m_normalisedDirection.x * m_creatureSpeed * 0.2f * deltaTime;
	//m_physicsObject->GetPosition()->y = m_normalisedVectorToTarget.y  * m_creatureSpeed * deltaTime;
	m_pos->z += m_normalisedDirection.z * m_creatureSpeed * 0.2f * deltaTime;

}

void HauntedCreature::OnEnterSpawning(int index, VitalEntity * target)
{
	m_state = hauntedCreatureStateSpawning;

	m_creatureSpeed = target->GetStats()->m_moveSpeed * 1.1f;

	SetTarget(target);

	m_normalisedDirection.x = (rand() % 100) / 100.0f;
	m_normalisedDirection.y = 0.0f;
	m_normalisedDirection.z = (rand() % 100) / 100.0f;

	m_normalisedDirection.x -= 0.5f, m_normalisedDirection.z -= 0.5f;
	
	m_normalisedDirection.Normalize();
	//	D3DXVec3Normalize(&m_normalisedDirection, &m_normalisedDirection);

	//m_normalisedDirection *= 1.0f;// * metres per second
	m_spawnEventTimer.RestartWithDuration(m_spawnEventDuration, true);
}

void HauntedCreature::OnEnterSeeking()
{
	m_state = hauntedCreatureStateSeek;

	//exit spawning stuff
	m_physicsObject.GetVelocity()->x = 0.0f;
	//m_physicsObject->GetVelocity()->y = 0.0f;
	m_physicsObject.GetVelocity()->z = 0.0f;
	
	
}

void HauntedCreature::OnEnterDone()
{
	m_state = hauntedCreatureStateDone;
	m_target = NULL;
}

VitalEntity * HauntedCreature::GetTarget()
{
	return m_target;
}

HauntedCreatureState HauntedCreature::GetState()
{
	return m_state;
}
