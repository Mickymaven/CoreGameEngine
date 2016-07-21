#if !defined(ETERNALLIGHT_H)
#define ETERNALLIGHT_H

#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "HauntedCreature.h"
#include "AbilityIncludes.h"

class EternalLight : public InstantAbility
{
private:
	vector <Actor *> m_targetsToHeal;

public:
	EternalLight();
	EternalLight(Actor * owner);
	~EternalLight();

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
