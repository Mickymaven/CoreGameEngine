#if !defined(HIDDENPOWER_H)
#define HIDDENPOWER_H

#include "../../../../EngineMoba/src/Ability/SingleTargetAbility.h"
#include "AbilityIncludes.h"

class HiddenPower : public SingleTargetAbility
{
private:
	LMTimer m_delayTimer;
	float m_delayDuration;

public:
	HiddenPower();
	HiddenPower(Actor * owner);
	~HiddenPower();

	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();
};

#endif