#if !defined(HAUNTEDCREATURE_H)
#define HAUNTEDCREATURE_H

#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../../EngineGameModel/src/Utility/LMTimer.h"
#include "../../../../EngineMoba/src/Actors/VitalEntity.h"

#include "../../../../EngineGameModel/src/Utility/LMTimer.h"

enum HauntedCreatureState
{
	hauntedCreatureStateInactive,
	hauntedCreatureStateSpawning,
	hauntedCreatureStateSeek,
	hauntedCreatureStateDone,
	hauntedCreatureStateCount
};

class HauntedCreature : public Sprite
{
private:
	HauntedCreatureState m_state;
	float m_spawnEventDuration;

	float m_creatureSpeed;

	VitalEntity * m_target;

	LMVector3 m_normalisedDirection;
	LMVector3 m_normalisedVectorToTarget;
	LMVector3 m_displacementTowardsTarget;

	LMVector3 * m_targetPosition;
	LMTimer m_spawnEventTimer;


	LMVector3 * m_pos;
	LMVector3 * m_targpos;
	float m_radiusCopy;
	float m_targradiusCopy;


public:
	HauntedCreature();
	HauntedCreature(LMVector3 position,
		LMVector3 rotation,
		LMVector3 scale,
		LMVector3 velocity,
		LMVector3 spin,
		LMVector3 resize,
		float acceleration,
		LMVector3 origin);
	~HauntedCreature();

	void Update(float deltaTime);

	void SetTarget(VitalEntity * target);
	bool IsOverTarget();
	void SeekTarget(float deltaTime);
	void Wander(float deltaTime);
	void OnEnterSpawning(int index, VitalEntity * target);
	void OnEnterSeeking();
	void OnEnterDone();
	
	VitalEntity * GetTarget();
	HauntedCreatureState GetState();
};

#endif