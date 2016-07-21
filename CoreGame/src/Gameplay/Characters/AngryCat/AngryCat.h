#if !defined(ANGRYCAT_H)
#define ANGRYCAT_H


#include "../../../../../EngineMoba/src/Actors/NPCController.h"
#include "../../../../../EngineMoba/src/Actor_Control/AggressionState.h"

#include "../CoreNPCController.h"

#include "AngryCatInteractionController.h"

enum AngryCatAbility
{
	acBasicAttack,
	acCount
};

class AngryCat: public CoreNPCController
{
private:
	AngryCatInteractionController m_acState;
	AggressionState m_aggroState;



public:
	AngryCat(CoreCharacter * character,
		vector<Actor * > * teamActors,
		vector<Actor * > * opponentActors,
		vector<Actor * > * neutralActors);
	~AngryCat();

	void Update(float deltaTime);

	void OnRespawn(float x, float y, float z);

	void OnHit(VitalEntity * owner);

	NPCSelectAction GetSelectBehavior();

};

#endif