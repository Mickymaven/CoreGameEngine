#if !defined(MOTOBOOST_H)
#define MOTOBOOST_H

#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "../../../../EngineMoba/src/Actors/Actor.h"

#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../../Simple Moba/src/UI/Tooltips/TooltipEffect.h"
#include "AbilityIncludes.h"

class MotoBoost : public InstantAbility
{
private:
	static UIElement * icon;
	static vector<TooltipEffect> * buffEffectVector;
	static TooltipEffect * buffEffect1;

	Buff * m_buff;


	LMVector3 * m_ownerPosition;
	float m_ownerRadius;


public:
	MotoBoost(Actor * owner);
	~MotoBoost();

	//void Update(float deltaTime);
	//void TargetEliminated();

	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();

};

#endif