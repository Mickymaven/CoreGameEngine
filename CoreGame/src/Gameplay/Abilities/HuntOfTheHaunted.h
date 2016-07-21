#if !defined(HUNTOFTHEHAUNTED_H)
#define HUNTOFTHEHAUNTED_H

#include "../../../../EngineMoba/src/Ability/InstantAbility.h"
#include "HauntedCreature.h"
#include "AbilityIncludes.h"

class HuntOfTheHaunted : public InstantAbility
{
private:
	//HauntedCreature m_hauntedcreature1;
	//HauntedCreature m_hauntedcreature2;
	//HauntedCreature m_hauntedcreature3;
	vector <HauntedCreature *> m_allCreatures;

public:
	HuntOfTheHaunted();
	HuntOfTheHaunted(Actor * owner);
	~HuntOfTheHaunted();

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

	vector <HauntedCreature *> * GetCreatures();
};

#endif
