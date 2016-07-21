#include "WalkState.h"

WalkState::WalkState()
{

}

WalkState::WalkState(Actor *  owner)
{
	m_owner = owner;
	m_ownerPosition = m_owner->GetPhysicsObject()->GetPosition();
	m_ownerRotation = m_owner->GetPhysicsObject()->GetRotation();
}

WalkState::~WalkState()
{

}

void WalkState::Update(float deltaTime)
{
	switch (m_state)
	{
	case walkStateStopped: Stopped(deltaTime); break;
	case walkStatePaused: Paused(deltaTime); break;
	case walkStateWalking: Walking(deltaTime); break;
	}
}

void WalkState::OnEnterWalking(LMVector3 * target)
{
	m_state = walkStateWalking;

	m_targetPosition.x = target->x;
	m_targetPosition.y = target->y;
	m_targetPosition.z = target->z;

	m_unitDirection.x *= 0.0f;
	m_unitDirection.y *= 0.0f;
	m_unitDirection.z *= 0.0f;
}

void WalkState::Walking(float deltaTime)
{
	switch (m_owner->GetState())
	{
	case actorBasicAttack:
	case actorRecall:
	case actorDead:
	case actorSleeping:
	case actorUnspawned:
		return;
	}

	m_displacement.x = m_targetPosition.x - m_ownerPosition->x;
	m_displacement.y = m_targetPosition.y - m_ownerPosition->y;
	m_displacement.z = m_targetPosition.z - m_ownerPosition->z;
	
	if (StopIfWalkFlipped()) return;

	m_unitDirection.x = m_displacement.x;
	m_unitDirection.y = m_displacement.y;
	m_unitDirection.z = m_displacement.z;

	m_unitDirection.Normalize();
	
	m_vectorEachUpdate = m_unitDirection * (m_owner->GetStats()->m_moveSpeed * deltaTime);

	if (m_displacement.LengthSq() < m_vectorEachUpdate.LengthSq())
	{
		m_ownerPosition->x = m_targetPosition.x;
		m_ownerPosition->y = m_targetPosition.y;
		m_ownerPosition->z = m_targetPosition.z;

		OnExitWalking();
		OnEnterStopped();
		return;
	}

	else if (m_unitDirection.x != 0.0f && m_unitDirection.z != 0.0f)
	{
		m_ownerPosition->x += m_vectorEachUpdate.x;
		m_ownerPosition->y += m_vectorEachUpdate.y;
		m_ownerPosition->z += m_vectorEachUpdate.z;

		m_radiansAngle = atan2(m_unitDirection.x, m_unitDirection.z);
		m_ownerRotation->y = m_radiansAngle;
	}
}

void WalkState::OnExitWalking()
{
	//m_owner->ExitCurrentState();
	//m_owner->OnEnterStationary();
}

void WalkState::OnEnterPaused()
{
	m_state = walkStatePaused;
}
void WalkState::Paused(float deltaTime)
{
	OnExitPaused();
}
void WalkState::OnExitPaused()
{
	OnEnterWalking(&m_targetPosition);
}

void WalkState::OnEnterStopped()
{
	m_state = walkStateStopped;
}

void WalkState::Stopped(float deltaTime)
{

}

void WalkState::OnExitStopped()
{
	m_owner->OnExitEnroute();
}

void WalkState::ExitCurrentState()
{
	switch (m_state)
	{
	case walkStateWalking:OnExitWalking(); break;
	case walkStatePaused: OnExitPaused(); break;
	case walkStateStopped:OnExitStopped(); break;
	}
}


bool WalkState::StopIfWalkFlipped()
{
	if (((m_displacement.x > 0 && m_unitDirection.x < 0) || (m_displacement.x < 0 && m_unitDirection.x > 0))
		&&
		((m_displacement.z >  0 && m_unitDirection.z < 0) || (m_displacement.z < 0 && m_unitDirection.z > 0))
		)
	{
		m_unitDirection.x *= 0.0f;
		m_unitDirection.y *= 0.0f;
		m_unitDirection.z *= 0.0f;

		m_ownerPosition->x = m_targetPosition.x;
		//m_ownerPosition.y = m_targetPosition.y;
		m_ownerPosition->z = m_targetPosition.z;

		OnExitWalking();
		OnEnterStopped();
		//m_owner->ExitCurrentState();
		//m_owner->OnEnterStationary();
		return true;
	}

	return false;
}

void WalkState::ActionStop()
{
	ExitCurrentState();
	OnEnterStopped();
}

void WalkState::ActionWalkTo(LMVector3 * target)
{
	ExitCurrentState();
	OnEnterWalking(target);
}

LMVector3 * WalkState::GetTargetPosition()
{
	return &m_targetPosition;
}

ActorWalkState WalkState::GetState()
{
	return m_state;
}