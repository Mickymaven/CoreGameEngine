#if !defined(WALKSTATE_H)
#define WALKSTATE_H

#include "../../../EngineGameModel/src/Maths/LMVector3.h"

#include "../../../EngineMoba/src/Actors/Actor.h"

enum ActorWalkState
{
	walkStateStopped,
	walkStatePaused,
	walkStateWalking,
	walkStateCount
};

class WalkState
{
private:
	ActorWalkState m_state;
	Actor *  m_owner;
	LMVector3 * m_ownerPosition;
	LMVector3 * m_ownerRotation;


	LMVector3 m_targetPosition;
	LMVector3 m_displacement;
	LMVector3 m_unitDirection;

	LMVector3 m_vectorEachUpdate;
	float m_radiansAngle;

	bool m_isWalkingBeforeCast;

public:
	WalkState();
	WalkState(Actor *  owner);
	~WalkState();


	void Update(float deltaTime);

	void OnEnterWalking(LMVector3 * target);
	void Walking(float deltaTime);
	void OnExitWalking();

	void OnEnterPaused();
	void Paused(float deltaTime);
	void OnExitPaused();

	void OnEnterStopped();
	void Stopped(float deltaTime);
	void OnExitStopped();

	void ExitCurrentState();

	//helpers
	bool StopIfWalkFlipped();

	//Actions Interface
	void ActionStop();
	void ActionWalkTo(LMVector3 * target);

	LMVector3 * GetTargetPosition();
	ActorWalkState GetState();

	//Accessors


};


#endif