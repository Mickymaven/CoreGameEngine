#if !defined(BUDGETMENUBEVERAGE_H)
#define BUDGETMENUBEVERAGE_H

#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "AbilityIncludes.h"


class BudgetMenuBeverage : public InstantAbility
{
private:

public:
	BudgetMenuBeverage();
	BudgetMenuBeverage(Actor * owner);
	virtual ~BudgetMenuBeverage();

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
