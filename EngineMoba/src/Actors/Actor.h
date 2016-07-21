#if !defined (ACTOR_H)
#define ACTOR_H

#include "../../../EngineGameModel/src/Utility/LMTimer.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"

#include "VitalEntity.h"
#include "BuffRecipient.h"

#include "ActorStats.h"
#include "StatChangeObject.h"

#include "../../../CoreGame/src/Gameplay/TeamName.h"

enum ActorState
{
	actorUnspawned,
	actorDead,
	actorRecall,
	actorSleeping,
	actorCasting,
	actorBasicAttack,
	actorStationary,
	actorWalking,
	actorWalkToBasicTarget,
	actorInstantCast,
	actorDirectionalCast,
	actorPointCast,
	actorSingleTargetCast,
	actorAttackMoveCast,
	actorDriveByCast,
	actorStateCount
};

struct PlayerKDA
{
	int kills;
	int deaths;
	int assists;
};

enum AfflictionState
{
	afflictionNone,
	afflictionStun,
	afflictionRoot,
	afflictionSilence,
	afflictionCount
};

class Actor : public VitalEntity, public BuffRecipient
{
private:
	PlayerKDA m_kda;

protected:
	ActorState m_state;
	AfflictionState m_afflictionState; //afflictions and debufs seperate?
	LMTimer m_deathTimer;
	LMTimer m_sleepTimer;
	LMTimer m_castAnimationTimer;
	LMTimer m_recallTimer;
	TeamName m_team;

	Actor * m_basicAttackTarget;

	
public:
	Actor(ActorStats * stats, LMVector3 position, LMVector3 rotation, LMVector3 scale, LMVector3 velocity, LMVector3 spin, LMVector3 resize, float acceleration);
	~Actor();
	
	void Update(float deltaTime);
	void DeathTimerUpdate(float deltaTime);
	void StatChangeUpdate(float deltaTime);

	//master states
	void OnEnterUnspawned();
	void Unspawned(float deltaTime);
	void OnExitUnspawned();

	void OnEnterRecallAnimation();
	void RecallAnimation(float deltaTime);
	void OnExitRecallAnimation();

	void OnEnterSleeping();
	void Sleeping(float numberOfSheep);
	void OnExitSleeping();

	void OnEnterStationary();
	void Stationary(float deltaTime);
	void OnExitStationary();

	void OnEnterEnroute();
	void Enroute(float deltaTime);
	void OnExitEnroute();

	void OnEnterWalkToBasicTarget();
	void WalkToBasicTarget(float deltaTime);
	void OnExitWalkToBasicTarget();

	void OnEnterInstantCast();
	void InstantCast(float deltaTime);
	void OnExitInstantCast();

	void OnEnterDirectionalCast();
	void DirectionalCast(float deltaTime);
	void OnExitDirectionalCast();

	void OnEnterPointCast();
	void PointCast(float deltaTime);
	void OnExitPointCast();
	
	void OnEnterSingleTargetCast();
	void SingleTargetCast(float deltaTime);
	void OnExitSingleTargetCast();

	void OnEnterAttackMoveCast();
	void AttackMoveCast(float deltaTime);
	void OnExitAttackMoveCast();

	void OnEnterDriveByCast();
	void DriveByCast(float deltaTime);
	void OnExitDriveByCast();

	void OnEnterCastingState();
	void CastAnimation(float deltaTime);
	void OnExitCastingState();

	void OnEnterBasicAttackAnimationState();
	void BasicAttackAnimation(float deltaTime);
	void OnExitBasicAttackAnimationState();

	void OnEnterDeathState();
	void DeathState(float deltaTime);
	void OnExitDeathState();

	void OnEnterForState(ActorState state);
	void OnExitForState(ActorState state);
	void ExitCurrentState();

	void Respawn(float x, float y, float z);
	void Death(float duration);

	//accessors
	PlayerKDA GetKDA();
	ActorState GetState();
	LMTimer * GetTimer();
	LMTimer * GetRecallTimer();
	LMTimer * GetSleepTimer();
	TeamName GetTeam();

	//mutators

	void SetKDA(PlayerKDA kda);

	void SetTeam(TeamName team);

	void SetBasicAttackTarget(Actor * target);
	

};

#endif