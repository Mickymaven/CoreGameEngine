#if !defined(CORECHARACTER_H)
#define CORECHARACTER_H

#include <vector>
using std::vector;

#include "../../../../EngineMoba/src/Actors/Character.h"

//not done in factory as used for all PlayerCharacters
#include "../Abilities/BasicAttack.h"
#include "../Abilities/Recall.h"
#include "../Abilities/ZZzzz.h"

#include "AbilitySlotType.h" //todo is kind of core implementation to talk about Recall etc

class CoreCharacter : public Character
{
protected:
	BasicAttack * m_SlotBasicAttack;
	Ability * m_slot1;//0
	Ability * m_slot2;//1
	Ability * m_slot3;//2
	Ability * m_slot4;//3
	Ability * m_custom1;//4
	Ability * m_custom2;//5
	Recall * m_recall;//6
	ZZzzz * m_sleep;//7

public:
	CoreCharacter();
	CoreCharacter(
		Actor * actor,
		Pathfinder * pathfinder,
		vector<Actor * > * teamActors,
		vector<Actor * > * opponentActors,
		vector<Actor * > * neutralActors);

	~CoreCharacter();
	//Init
	void AddAbility(Ability * ability, AbilitySlotType slot);

	//Actions
	void ActionCastRecall(float gameTime);
	void ActionCastSleep(float gameTime);

	//Accessors


};

#endif