#if !defined(SPOOKYSPACEMERINGUE_H)
#define SPOOKYSPACEMERINGUE_H

#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../../EngineMoba/src/Ability/PointAbility.h"
#include "AbilityIncludes.h"


class SpookySpaceMeringue : public PointAbility
{
private:
	Sprite m_meringue;
	bool m_triggered;

public:
	SpookySpaceMeringue(Actor * owner);
	~SpookySpaceMeringue();

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
	Sprite * GetMeringue();
	bool IsTriggered();
};

#endif