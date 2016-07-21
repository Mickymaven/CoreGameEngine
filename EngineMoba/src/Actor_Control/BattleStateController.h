#if !defined(BATTLESTATECONTROLLER_H)
#define BATTLESTATECONTROLLER_H

#include "../../../EngineMoba/src/Actors/VitalEntity.h"
#include "../../../EngineMoba/src/Actors/Actor.h"

#include "../../../CoreGame/src/Gameplay/Abilities/BasicAttack.h" //forward Dependency

#include "PathController.h"
#include "WalkState.h"

enum ActorBattleState
{
	actorBattleStateDefendPosition,
	actorBattleStateDefendArea,
	actorBattleStateChase,
	actorBattleStateStopped,
	actorBattleStateCount
};

class BattleStateController
{
private:
	ActorBattleState m_battleState;

	LMTimer m_chaseTimer;
	
	Actor * m_owner;

	PathController * m_pathController;
	//path cooldown timer?
	WalkState * m_walkState;

	SingleTargetAbility * m_basicAttack;
	VitalEntity * m_target;


	//variabled specifically for OnEnterBattleStateChase lowering path spam)
	bool m_isGoodEnough;// PathFoundInChase;
	LMVector3 m_targPositionLast;// WhenWeLastAskedForPath;
	LMVector3 m_targDispAgainstChecked;


public:
	BattleStateController();
	BattleStateController::BattleStateController(PathController * pathController, WalkState * walkState, SingleTargetAbility * ability, Actor * owner);
	~BattleStateController();

	void Update(float deltaTime);

	void ActionPassive();

	bool IsAnyTargetInRange();
	Actor * ClosestTargetInRange();

	void OnEnterBattleStateDefendPosition();
	void BattleStateDefendPositionBehavior(float deltaTime);
	void OnExitBattleStateDefendPosition();

	void OnEnterBattleStateDefendArea();
	void BattleStateDefendAreaBehavior(float deltaTime);
	void OnExitBattleStateDefendArea();

	void OnEnterBattleStateChase(VitalEntity * target);
	void BattleStateChaseBehavior(float deltaTime);
	void OnExitBattleStateChase();

	void OnEnterBattleStateStopped();
	void BattleStateStoppedBehavior(float deltaTime);
	void OnExitBattleStateStopped();

	void OnExitForState(ActorBattleState state);
	void ExitCurrentState();

	ActorBattleState GetBattleState();
	void SetBattleState(ActorBattleState state);

	bool TryToAttackTarget();

	LMTimer * GetChaseTimer();


	VitalEntity * GetTarget();

};

#endif