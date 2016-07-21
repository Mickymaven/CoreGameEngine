#if !defined(ZZZZZ_H)
#define ZZZZZ_H

#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "AbilityIncludes.h"

class ZZzzz : public InstantAbility
{
	LMTimer m_sleepTimer;

public:
	ZZzzz::ZZzzz(Actor * owner);
	~ZZzzz();

	//void Update(float deltaTime);
	//void TargetEliminated();
	void Activate(float currentGameTime);

protected:
	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();
public:

};

#endif