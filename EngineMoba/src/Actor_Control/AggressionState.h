#if !defined(AGGRESSIONSTATE_H)
#define AGGRESSIONSTATE_H

#include "Interaction.h"
#include "BattleStateController.h"

#include "../../../EngineGameModel/src/Utility/LMTimer.h"

#include "../../../EngineMoba/src/Actors/VitalEntity.h"
#include "../../../EngineMoba/src/Actors/Actor.h"

enum AggressionBehavior
{
	aggroAngryStandby,
	aggroChaseAttack,
	aggroTargetLostStandby,
	aggroReturn,
	aggroCount
};

class AggressionState : public Interaction
{
private:
	AggressionBehavior m_aggressionState;
	BattleStateController * m_battleStateController;
	WalkState * m_walkState;


	InteractionZone m_autoAggro;
	InteractionZone m_chaseRange;

	LMTimer m_targetLostTimer;

public:
	AggressionState();
	bool Init(BattleStateController * battleStateController, WalkState * walkState, Actor * owner);
	~AggressionState();

	void Update(float deltaTime);

	void OnEnterAngryStandby();
	void AngryStandby(float deltaTime);
	void OnExitAngryStandby();

	void OnEnterChaseAttack();
	void ChaseAttack(float deltaTime);
	void OnExitChaseAttack();

	void OnEnterTargetLostStandby();
	void TargetLostStandBy(float deltaTime);
	void OnExitTargetLostStandby();

	void OnEnterReturn();
	void Return(float deltaTime);
	void OnExitReturn();

	void ExitCurrentState();

	void EnforceChaseRange();
	bool IsInChaseRange();

	void ChaseTarget(VitalEntity * target);
	void ActionPassive();

	AggressionBehavior GetState();

	void OnHit(VitalEntity * owner);
};

#endif