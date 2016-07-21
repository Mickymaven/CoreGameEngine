#if !defined(NOMBARHEAL_H)
#define NOMBARHEAL_H

#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "AbilityIncludes.h"

class NomBarHeal : public InstantAbility
{
private:
	static UIElement * icon;
	static vector<TooltipEffect> * buffEffectVector;
	static TooltipEffect * buffEffect1;

public:
	NomBarHeal();
	NomBarHeal(Actor * owner);
	~NomBarHeal();

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
