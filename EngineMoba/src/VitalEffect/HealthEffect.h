#if !defined(HEALTHEFFECT_H)
#define HEALTHEFFECT_H

#include "../Actors/VitalEntity.h"

enum HealthEffectState
{
	heActive,
	heInactive,
	heCountedTowardsScores,
	heStateCount
};

enum HealthEffectApplicationType
{
	heaSingle,
	heaOverTime,
	heaTypeCount
};

class HealthEffect
{
protected:
	HealthEffectState m_state;
	HealthEffectApplicationType m_appType;

	float m_duration;
	float m_timer;
	float m_inactiveTime;

	float m_value;
	float m_valueCounter;

	VitalEntity * m_owner;
	void * m_abilitySource;
	VitalEntity * m_target;

public:
	HealthEffect();
	~HealthEffect();
	
	//Actions
	float UpdateReturningHealthPortion(float deltaTime);//to give or take away on use of derived context

	void MakeInactive(float gameTime);
	void CountedTowardsScores();

	//Accessors
	HealthEffectState GetState();
	HealthEffectApplicationType GetDamageApplicationType();

	float GetDuration();
	float GetTimer();
	float GetValue();
	VitalEntity * GetOwner();
	void * GetAbilitySource();
	VitalEntity * GetTarget();
	float GetInactiveTime();

	//Mutators
	void SetInactiveTime(float gameTime);
};


#endif