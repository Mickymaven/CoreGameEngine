#include "AggressionState.h"

AggressionState::AggressionState()
{
	m_battleStateController = NULL;
}

bool AggressionState::Init(BattleStateController * battleStateController, WalkState * walkState, Actor * owner)
{
	m_owner = owner;
	m_ownerPosition = owner->GetPhysicsObject()->GetPosition();
	m_battleStateController = battleStateController;
	m_walkState = walkState;

	//start our state
	OnEnterAngryStandby(); //m_aggressionState = aggroAngryStandby;
	
	m_autoAggro.Init(interactionZoneStateActive);
	m_autoAggro.SetRadius(1.25f);
	m_autoAggro.SetPosition(m_ownerPosition);

	m_chaseRange.Init(interactionZoneStateActive);
	m_chaseRange.SetRadius(15.0f);
	m_chaseRange.SetPosition(m_ownerPosition);

	m_interactionZones.push_back(&m_autoAggro);
	m_interactionZones.push_back(&m_chaseRange);

	return true;
}

AggressionState::~AggressionState()
{

}

void AggressionState::Update(float deltaTime)
{
	switch (m_aggressionState)
	{
	case aggroAngryStandby:AngryStandby(deltaTime); break;
	case aggroChaseAttack: ChaseAttack(deltaTime); break;
	case aggroTargetLostStandby: TargetLostStandBy(deltaTime); break;
	case aggroReturn: Return(deltaTime); break;
	case aggroCount:default:break;
	}
}

void AggressionState::OnEnterAngryStandby()
{
	m_aggressionState = aggroAngryStandby;

	m_battleStateController->ExitCurrentState();
	m_battleStateController->OnEnterBattleStateStopped();
}

void AggressionState::AngryStandby(float deltaTime)
{

	m_battleStateController->Update(deltaTime);

	if (m_autoAggro.GetInteractionZoneState() == interactionZoneStateActive)
	{
		Actor * target = SelectTargetInRange(m_ownerPosition, m_owner->GetTeam(), m_autoAggro.GetRadius(), true);

		ChaseTarget(target);
	}
}

void AggressionState::OnExitAngryStandby()
{

}

void AggressionState::OnEnterChaseAttack()
{
	m_aggressionState = aggroChaseAttack;
	m_battleStateController->GetChaseTimer()->RestartWithDuration(5.0f, true);
}

void AggressionState::ChaseAttack(float deltaTime)
{
	if (m_battleStateController->GetTarget() != NULL)
	{
		if (m_battleStateController->GetTarget()->GetVitalEntityState() == vitalEntityStateInactive)
		{
			OnExitChaseAttack();
			OnEnterTargetLostStandby();
			return;
		}
	}

	m_battleStateController->Update(deltaTime);
	
	if (m_owner->GetVitalEntityState() == vitalEntityStateInactive)
	{
		OnExitChaseAttack();
		OnEnterReturn();
		return;
	}
	else EnforceChaseRange();
}

void AggressionState::OnExitChaseAttack()
{

}

void AggressionState::OnEnterTargetLostStandby()
{
	m_aggressionState = aggroTargetLostStandby;
	m_targetLostTimer.RestartWithDuration(5.0f, true);

	m_battleStateController->ActionPassive();
}

void AggressionState::TargetLostStandBy(float deltaTime)
{
	m_battleStateController->Update(deltaTime);
	m_targetLostTimer.Update(deltaTime);
	
	Actor * target = SelectTargetInRange(m_ownerPosition, m_owner->GetTeam(), m_owner->GetStats()->GetRange(), true);

	if (target != nullptr)
	{
		ChaseTarget(target);
		return;
	}

	else if (m_targetLostTimer.GetState() == timerFinished)
	{
		OnExitTargetLostStandby();
		OnEnterReturn();
	}
}

void AggressionState::OnExitTargetLostStandby()
{

}

void AggressionState::OnEnterReturn()//todo use path controller for npc chase here.
{
	m_aggressionState = aggroReturn;

	m_battleStateController->ActionPassive();

	m_walkState->ActionWalkTo(m_chaseRange.GetPosition());
}

void AggressionState::Return(float deltaTime)
{
	m_battleStateController->Update(deltaTime);

	if (m_walkState->GetState() == walkStateStopped)
	{
		OnExitReturn();
		OnEnterAngryStandby();
	}
}

void AggressionState::OnExitReturn()
{

}

void AggressionState::ExitCurrentState()
{
	switch (m_aggressionState)
	{
	case aggroAngryStandby: OnExitAngryStandby(); break;
	case aggroChaseAttack: OnExitChaseAttack(); break;
	case aggroTargetLostStandby: OnExitTargetLostStandby(); break;
	case aggroReturn: OnExitReturn(); break;
	case aggroCount:default:break;
	}
}

void AggressionState::EnforceChaseRange()
{
	if (!IsInChaseRange())
	{
		//m_battleStateController->ExitCurrentState();
		//m_battleStateController->OnEnterBattleStateDefendPosition();
		
		if (m_battleStateController->GetChaseTimer()->GetState() == timerFinished)
		{
			ExitCurrentState();
			OnEnterReturn();
			return;

			/*
			m_battleStateController->ExitCurrentState();
			m_battleStateController->OnExitBattleStateDefendPosition();

			m_walkState->ExitCurrentState();
			m_walkState->OnEnterWalking(m_chaseRange.GetPosition());

			OnExitChaseAttack();
			OnEnterAngryStandby();
			*/
		}

		else
		{

			LMVector3 displacement;

			displacement.x = m_owner->GetPhysicsObject()->GetPosition()->x - m_chaseRange.GetPosition()->x;
			displacement.y = 0;
			displacement.z = m_owner->GetPhysicsObject()->GetPosition()->z - m_chaseRange.GetPosition()->z;
		
			displacement.Normalize();

			displacement *= 0.98f * m_chaseRange.GetRadius();

			m_ownerPosition->x = m_chaseRange.GetPosition()->x + displacement.x;
			m_ownerPosition->z = m_chaseRange.GetPosition()->z + displacement.z;

			OnExitChaseAttack();
			OnEnterTargetLostStandby();
		}
	}
	else
	{
		m_battleStateController->GetChaseTimer()->RestartWithDuration(5.0f, true);
	}
}
bool AggressionState::IsInChaseRange()
{
	float displacementMagnitude = ((LMVector3*)m_owner->GetPhysicsObject()->GetPosition())->DisplacementMag(*m_chaseRange.GetPosition());

	if (displacementMagnitude > m_chaseRange.GetRadius())
	{
		return false;
	}

	return true;
}

void AggressionState::ChaseTarget(VitalEntity * target)
{
	if (target != nullptr)
	{
		if (m_owner->GetVitalEntityState() != vitalEntityStateInactive)
		{
			m_battleStateController->ExitCurrentState();

			m_battleStateController->OnEnterBattleStateChase(target); //make them chase

			ExitCurrentState();
			OnEnterChaseAttack();
		}
	}
}

void AggressionState::ActionPassive()
{
	ExitCurrentState();
}

AggressionBehavior AggressionState::GetState() { return m_aggressionState; }

void AggressionState::OnHit(VitalEntity * owner)
{
	ChaseTarget(owner);
}