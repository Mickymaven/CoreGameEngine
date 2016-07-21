#if !defined(RIDEBIKE_H)
#define RIDEBIKE_H


#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "../../../../EngineMoba/src/Actors/Actor.h"

#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../../Simple Moba/src/UI/Tooltips/TooltipEffect.h"
#include "AbilityIncludes.h"

class RideBike :public InstantAbility
{
private:
	Buff * m_buff;

public:
	RideBike();
	RideBike(Actor * owner);
	~RideBike();

	//void Update(float deltaTime);
	//void TargetEliminated();

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