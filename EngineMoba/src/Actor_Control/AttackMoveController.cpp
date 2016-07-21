#include "AttackMoveController.h"

AttackMoveController::AttackMoveController()
{

}

AttackMoveController::AttackMoveController(BattleStateController * battleStateController, WalkState * walkState, Actor *  owner)
{
	m_state = attackMoveStateStandby;
	m_battleStateController = battleStateController;
	m_walkState = walkState;
	m_owner = owner;
	m_target = LMVector3(0.0f, 0.0f, 0.0f);

}

AttackMoveController::~AttackMoveController()
{

}

void AttackMoveController::Update(float deltaTime)
{
	switch (m_state)
	{
	case attackMoveStateDBAttacking:
	case attackMoveStateDBMoving://intentional fallthrough
		if (m_owner->GetState() == actorDead)
		{
			ExitCurrentState();
			OnEnterStandby();
		}
	}

	switch (m_state)
	{
		case attackMoveStateStandby: StandbyBehavior(deltaTime); break;
		case attackMoveRegularWalk: RegularWalk(deltaTime); break;
		case attackMoveStateDBAttacking: AttackingDBBehvaior(deltaTime); break;
		case attackMoveStateDBMoving: MovingDBBehavior(deltaTime); break;
		case attackMoveStateAMAttacking: AttackingAMBehvaior(deltaTime); break;
		case attackMoveStateAMMoving: MovingAMBehavior(deltaTime); break;
		case attackMoveStateCount:
		default:
			MessageBox(NULL, "Bad state in AttackMoveController Update", "Error", MB_OK);
			break;

	}
}


void AttackMoveController::OnEnterStandby()
{
	m_state = attackMoveStateStandby;

	m_battleStateController->ActionPassive();
}

void AttackMoveController::StandbyBehavior(float deltaTime)
{
	
}

void AttackMoveController::OnExitStandby()
{

}

void AttackMoveController::OnEnterRegularWalk()
{
	m_state = attackMoveRegularWalk;

	m_battleStateController->ExitCurrentState();
	m_battleStateController->OnEnterBattleStateDefendPosition();
}

void AttackMoveController::RegularWalk(float deltaTime)
{
	m_battleStateController->Update(deltaTime);
}

void AttackMoveController::OnExitRegularWalk()
{

}

void AttackMoveController::OnEnterAMAttacking()
{
	m_battleStateController->ExitCurrentState();
	m_battleStateController->OnEnterBattleStateDefendPosition();

	m_walkState->OnExitWalking();
	m_walkState->OnEnterStopped();

	m_state = attackMoveStateAMAttacking;
}

void AttackMoveController::AttackingAMBehvaior(float deltaTime)
{
	//do we have a target in range
	//attack it
	if (m_battleStateController->IsAnyTargetInRange())
	{
		m_walkState->OnExitWalking();
		m_walkState->OnEnterStopped();

		m_battleStateController->Update(deltaTime);
	}
	else
	{
		OnExitAMAttacking();
		OnEnterAMMoving();
	}
	//if we dont
	//Enter moving behavior
}
void AttackMoveController::OnExitAMAttacking()
{

}

void AttackMoveController::OnEnterAMMoving()
{
	m_state = attackMoveStateAMMoving;

	m_walkState->ExitCurrentState();
	m_walkState->OnEnterWalking(&m_target);

	m_owner->ExitCurrentState();
	m_owner->OnEnterEnroute();

}

void AttackMoveController::MovingAMBehavior(float deltaTime)
{

	//1 has or walk put us at target position
	if (!m_walkState->GetState() == walkStateStopped)
	{
		//1. if actor target is in range

		if (m_battleStateController->IsAnyTargetInRange())
		{
			OnExitAMMoving();
			OnEnterAMAttacking();
			
		}
		else
		{
			//we should be in OnRoute
			if (m_owner->GetState() != actorWalking)
			{
				OnExitAMMoving();
				OnEnterStandby();
				OutputDebugString("Expected actorWalking state\n");
				OutputDebugString("But it isnt AttackMoveController::MovingBehavior \n");
			}

			// walking behavior towards current target
		}
	}
	else
	{
		OnExitAMMoving();
		OnEnterStandby();
	}

	m_battleStateController->Update(deltaTime);

}
void AttackMoveController::OnExitAMMoving()
{

}

///////////// Drive By Behavior //////////////////////

void AttackMoveController::OnEnterDBAttacking()
{
	m_battleStateController->ExitCurrentState();
	m_battleStateController->OnEnterBattleStateDefendPosition();

	m_state = attackMoveStateDBAttacking;
}

void AttackMoveController::AttackingDBBehvaior(float deltaTime)
{
	//do we have a target in range
		//attack it
	if (m_battleStateController->IsAnyTargetInRange())
	{
		m_battleStateController->Update(deltaTime);
	}
	else
	{
		OnExitDBAttacking();
		OnEnterDBMoving();
	}
	//if we dont
		//Enter moving behavior
}

void AttackMoveController::OnExitDBAttacking()
{

}

void AttackMoveController::OnEnterDBMoving()
{
	m_state = attackMoveStateDBMoving;

	m_owner->ExitCurrentState();
	m_walkState->OnEnterWalking(&m_target);
	m_owner->OnEnterEnroute();

}

void AttackMoveController::MovingDBBehavior(float deltaTime)
{

	//1 has or walk put us at target position
	if (! m_walkState->GetState() == walkStateStopped)
	{
		//1. if actor target is in range

		if (m_battleStateController->IsAnyTargetInRange())
		{
			OnExitDBMoving();
			OnEnterDBAttacking();
		}
		else
		{
			//we should be in OnRoute
			if (m_owner->GetState() != actorWalking)
			{
				OnExitDBMoving();
				OnEnterStandby();
				OutputDebugString("Expected actor to be in actorWalking state\n");
				OutputDebugString("But it isnt AttackMoveController::MovingBehavior \n");
			}

			// walking behavior towards current target
		}



	}
	else
	{

		OnExitDBMoving();
		OnEnterStandby();
	}

	m_battleStateController->Update(deltaTime);

}
void AttackMoveController::OnExitDBMoving()
{

}

void AttackMoveController::ExitCurrentState()
{
	OnExitForState(m_state);
}

void AttackMoveController::OnExitForState(AttackMoveState state)
{
	switch (state)
	{
	case attackMoveStateStandby:		OnExitStandby(); break;
	case attackMoveRegularWalk:			OnExitRegularWalk(); break;
	case attackMoveStateDBAttacking:	OnExitDBAttacking(); break;
	case attackMoveStateDBMoving:		OnExitDBMoving(); break;
	case attackMoveStateAMAttacking:	OnExitAMAttacking(); break;
	case attackMoveStateAMMoving:		OnExitAMMoving(); break;
	case attackMoveStateCount:
	default:
		MessageBox(NULL, "Bad state in AttackMoveController On Exit For State", "Error", MB_OK);
		break;
	}
}

bool AttackMoveController::ForceStandby()
{
	if (m_state != attackMoveStateStandby)
	{
		ExitCurrentState();
		OnEnterStandby();
	}
	return true;
}

void AttackMoveController::ActionOnSleep()
{
	ExitCurrentState();
	OnEnterStandby();
}

void AttackMoveController::ActionRegularWalk()
{
	ExitCurrentState();
	OnEnterRegularWalk();
}


void AttackMoveController::AttackMoveToTarget(float x, float y, float z)
{
	m_battleStateController->ExitCurrentState();
	m_battleStateController->OnEnterBattleStateDefendPosition();

	NewTarget(x, y, z);

	ExitCurrentState();
	OnEnterAMMoving();
}

void AttackMoveController::DriveByToTarget(float x, float y, float z)
{
	m_battleStateController->ExitCurrentState();
	m_battleStateController->OnEnterBattleStateDefendPosition();

	NewTarget(x, y, z);

	ExitCurrentState();
	OnEnterDBMoving();
}


void AttackMoveController::NewTarget(float x, float y, float z)
{
	m_target.x = x;
	m_target.y = y;
	m_target.z = z;
}

AttackMoveState AttackMoveController::GetState()
{
	return m_state;
}
