#include "BattleStateController.h"

BattleStateController::BattleStateController()
{

}

BattleStateController::BattleStateController(PathController * pathController, WalkState * walkState, SingleTargetAbility * ability, Actor * owner)
{
	m_pathController = pathController;
	m_walkState = walkState;
	m_battleState = actorBattleStateStopped;

	m_owner = owner;
	m_basicAttack = ability;

	m_target = NULL;

	m_chaseTimer = LMTimer(5.0f, false);
}

BattleStateController::~BattleStateController()
{

}

void BattleStateController::Update(float deltaTime)
{
	switch (m_battleState)
	{
	case actorBattleStateDefendPosition:
		BattleStateDefendPositionBehavior(deltaTime);
		break;
	case actorBattleStateDefendArea:
		BattleStateDefendAreaBehavior(deltaTime);
		break;
	case actorBattleStateChase:
		BattleStateChaseBehavior(deltaTime);
		break;
	case actorBattleStateStopped:
		BattleStateStoppedBehavior(deltaTime);
		break;
	default:
		//MessageBox(NULL, "Bad battle state in BattleStateController::UpdateBattleState()", "Error", MB_OK);
		break;
	};

}

void BattleStateController::ActionPassive()
{
	ExitCurrentState();
	OnEnterBattleStateStopped();	
}

bool BattleStateController::IsAnyTargetInRange()
{
	Actor * tempTarget = ClosestTargetInRange();
	if (tempTarget != NULL)
		if (m_owner->GetPhysicsObject()->GetPosition()->IsRangeFurther(*tempTarget->GetPhysicsObject()->GetPosition(), m_owner->GetStats()->m_range))
			return true;
	return false;
}

Actor * BattleStateController::ClosestTargetInRange()
{
	//Can return Null !!!
	return m_basicAttack->ClosestTargetInRange(
		m_owner->GetPhysicsObject()->GetPosition(),
		m_owner->GetStats()->m_range,
		neutralCategoryAll);
}

void BattleStateController::OnEnterBattleStateDefendPosition()
{
	m_battleState = actorBattleStateDefendPosition;
}

void BattleStateController::BattleStateDefendPositionBehavior(float deltaTime)
{
	if (m_target != NULL)
	{
		if (m_target->GetVitalEntityState() == vitalEntityStateInactive)
		{
			m_target = NULL;
		}
	}

	//get a target if we dont have one
	if (m_target == NULL)
	{
		m_target = ClosestTargetInRange();//could be null
	}

	//either way we now have a target ffor the next lines
	bool isAttackSuccess = false;

	//attack them if in range
	if (m_target != NULL)
	{

		//if target is in your basic attack range
		if (!TryToAttackTarget())
			m_target = NULL;
	}
	//else {} //no target

	m_pathController->Update(deltaTime);
}

void BattleStateController::OnExitBattleStateDefendPosition()
{

}

void BattleStateController::OnEnterBattleStateDefendArea()
{
	m_battleState = actorBattleStateDefendArea;
}

void BattleStateController::BattleStateDefendAreaBehavior(float deltaTime)
{
	m_pathController->Update(deltaTime);
}

void BattleStateController::OnExitBattleStateDefendArea()
{

}

void BattleStateController::OnEnterBattleStateChase(VitalEntity * target)
{
	m_battleState = actorBattleStateChase;
	m_target = target;

	m_owner->ExitCurrentState();
	m_owner->OnEnterWalkToBasicTarget();

	m_chaseTimer.RestartWithDuration(5.0f, true); //possibly move to agreessionstate

	m_isGoodEnough = false;

}

void BattleStateController::BattleStateChaseBehavior(float deltaTime)
{
	m_chaseTimer.Update(deltaTime);	//purely for aggression state to time walking back to chase interaction zone origin

									/*
									if (m_owner->GetState() == actorStationary)
									{
									m_owner->ExitCurrentState();
									m_owner->OnEnterWalkToBasicTarget();
									}*/

	if (m_owner->GetVitalEntityState() == vitalEntityStateInactive)
	{
		m_target = NULL;

		m_walkState->OnExitWalking();//walk behavior state
		m_walkState->OnEnterStopped();//walk behavior state

		m_owner->ExitCurrentState();//actor state
		m_owner->OnEnterStationary();

		OnExitBattleStateChase();
		OnEnterBattleStateDefendPosition();
		return;
	}

	if (m_target != NULL)
	{
		if (m_target->GetVitalEntityState() == vitalEntityStateInactive)
		{
			//OutputDebugString("target vitalEntityStateInactive");
			OnExitBattleStateChase();
			OnEnterBattleStateDefendPosition();
			m_target = NULL;
		}
	}

	if (m_target != NULL)
	{
		//if target is in your basic attack range
		if (!TryToAttackTarget())
		{
			m_walkState->ExitCurrentState();
			//m_walkState->OnEnterWalking(m_target->GetPhysicsObject()->GetPosition());


			//sol 2 very easy (not used)
			// get a path first time, have a big timer to get a new path (1 second or so)
			// a problem could happen where they radically change position and you are stucl walking to where they were > 1s ago

			//sol 1 easy (used below around m_pathController->WalkToPosition(..) call)
			// if you have a path since you entered chase, reuse it
			//  - only if the target displacement changes too much would we make a new path
			//  -- optimal: could build in this search reuse stuff into pathcontroller itself


			//wont hit this first time around,, next time we would already have a usable
			// targetPositionLast so it relies on next section of code to give us one
			if (m_isGoodEnough == true)
			{
				m_targDispAgainstChecked.x = m_target->GetPhysicsObject()->GetPosition()->x - m_targPositionLast.x;//todo possibly override - in LMVector3
				m_targDispAgainstChecked.y = m_target->GetPhysicsObject()->GetPosition()->y - m_targPositionLast.y;
				m_targDispAgainstChecked.z = m_target->GetPhysicsObject()->GetPosition()->z - m_targPositionLast.z;

				if (m_targDispAgainstChecked.Magnitude() > 5.0f) m_isGoodEnough = false;

			}

			//on first time around get path controller to walk
			//on second time around if the preceeding displacment check code tells us to check again

			if (m_isGoodEnough==false)
			{
				m_targPositionLast = *m_target->GetPhysicsObject()->GetPosition();//remember

				m_pathController->WalkToPosition(
					true,//ignoreRateLowering
					m_target->GetPhysicsObject()->GetPosition(),//target
					m_owner->GetPhysicsObject()->GetPosition()//origin
					);
			}
			//this breaks if you have the target in an invalid place (on a wall).
			//they use the path finding and get stuck in search (for what ever reason).

		}
		else
		{
			m_chaseTimer.RestartWithDuration(5.0f, true);

			m_walkState->OnExitWalking();
			m_walkState->OnEnterStopped();
			// OnExit (above) contains on enter stopped walk state function
		}
	}

	m_pathController->Update(deltaTime);
}

void BattleStateController::OnExitBattleStateChase()
{
	m_target = NULL;

	m_walkState->OnExitWalking();//walk behavior state
	m_walkState->OnEnterStopped();
}

void BattleStateController::OnEnterBattleStateStopped()
{
	m_battleState = actorBattleStateStopped;
	m_target = NULL;

	m_walkState->ActionStop();
}

void BattleStateController::BattleStateStoppedBehavior(float deltaTime)
{
	m_pathController->Update(deltaTime);
}

void BattleStateController::OnExitBattleStateStopped()
{

}

void BattleStateController::OnExitForState(ActorBattleState state)
{
	switch (state)
	{
	case actorBattleStateDefendPosition: OnExitBattleStateDefendPosition(); break;
	case actorBattleStateDefendArea: OnExitBattleStateDefendArea(); break;
	case actorBattleStateChase: OnExitBattleStateChase(); break;
	case actorBattleStateStopped: OnExitBattleStateStopped(); break;
	default:
		break;
	}
}

void BattleStateController::ExitCurrentState()
{
	OnExitForState(m_battleState);
}


bool BattleStateController::TryToAttackTarget()
{
	//is targ in range

	if (! m_target->GetVitalEntityState() == vitalEntityStateActive) return false;

	if (m_owner->GetPhysicsObject()->GetPosition()->IsRangeFurther(
		*m_target->GetPhysicsObject()->GetPosition(),
		m_owner->GetStats()->m_range + m_target->GetPhysicsObject()->GetRadius()))
	{
		//todo combine this with ability targeting Loop teams > test if allowed to target or they are targetable > radius test > true > 

		//attack
		AbilityResult result = m_basicAttack->Activate(0.0f, NULL, NULL, m_target, NULL, NULL, NULL);

		if (result == abilityResultOK) //sucessfully attacked
		{
			m_owner->ExitCurrentState();
			m_owner->OnEnterBasicAttackAnimationState();
		}
		return true;//target was in range (desipte whether we could attack or not)

	}

	return false;//target not in range
}

ActorBattleState BattleStateController::GetBattleState()
{
	return m_battleState;
}

void BattleStateController::SetBattleState(ActorBattleState state)
{
	m_battleState = state;
}

LMTimer * BattleStateController::GetChaseTimer()
{
	return &m_chaseTimer;
}

VitalEntity * BattleStateController::GetTarget()
{
	return m_target;
}