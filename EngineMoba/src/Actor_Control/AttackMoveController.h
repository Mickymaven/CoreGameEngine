#if !defined(ATTACKMOVECONTROLLER_H)
#define ATTACKMOVECONTROLLER_H

#include "../../../EngineGameModel/src/Maths/LMVector3.h"

#include "../../../EngineMoba/src/Actors/Actor.h"
#include "BattleStateController.h"


enum AttackMoveState
{
	attackMoveStateStandby,
	attackMoveRegularWalk,
	attackMoveStateDBAttacking,
	attackMoveStateDBMoving,
	attackMoveStateAMAttacking,
	attackMoveStateAMMoving,
	attackMoveStateCount
};

class AttackMoveController
{


protected:
	AttackMoveState m_state;
	LMVector3 m_target;

	BattleStateController * m_battleStateController;
	WalkState * m_walkState;
	Actor *  m_owner;

public:
	AttackMoveController();
	AttackMoveController(BattleStateController * battleStateController, WalkState * walkState, Actor *  owner);
	~AttackMoveController();

	void Update(float deltaTime);

	void OnEnterStandby();
	void StandbyBehavior(float deltaTime);
	void OnExitStandby();

	void OnEnterRegularWalk();
	void RegularWalk(float deltaTime);
	void OnExitRegularWalk();


	void OnEnterAMAttacking();
	void AttackingAMBehvaior(float deltaTime);
	void OnExitAMAttacking();

	void OnEnterAMMoving();
	void MovingAMBehavior(float deltaTime);
	void OnExitAMMoving();

	void OnEnterDBAttacking();
	void AttackingDBBehvaior(float deltaTime);
	void OnExitDBAttacking();

	void OnEnterDBMoving();
	void MovingDBBehavior(float deltaTime);
	void OnExitDBMoving();

	void ExitCurrentState();
	void OnExitForState(AttackMoveState state);

	//Interface Functions
	bool ForceStandby();
	void ActionOnSleep();
	void ActionRegularWalk();

	void AttackMoveToTarget(float x, float y, float z);
	void DriveByToTarget(float x, float y, float z);

	void NewTarget(float x, float y, float z);

	//accessor
	AttackMoveState GetState();
};

#endif