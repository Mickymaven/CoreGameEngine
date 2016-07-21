#if !defined(CORECHARACTERFACTORY_H)
#define CORECHARACTERFACTORY_H

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../../../EngineMoba/src/GamestateIO/CharacterFactory.h"
#include "../../../EngineMoba/src/GamestateIO/GameObjectFactory.h"
#include "../../../EngineMoba/src/GamestateIO/ActorStatsFactory.h"
#include "../../../EngineMoba/src/GamestateIO/AbilityFactory.h"
#include "../../../EngineMoba/src/GamestateIO/ItemFactory.h"

#include "../Gameplay/Characters/AbilitySlotType.h"
#include "../Gameplay/Characters/CharacterData.h"
#include "../Gameplay/Characters/CharacterClassName.h"
#include "../Gameplay/Characters/CoreCharacter.h"

#include "CoreActorFactory.h"

class CoreCharacterFactory : CharacterFactory
{
protected:
	CoreActorFactory * m_coreActorFactory;

	CoreCharacter * m_coreCharacter;

public:
	CoreCharacterFactory();
	~CoreCharacterFactory();

	bool Init(CoreActorFactory * coreActorFactory, AbilityFactory * abilityFactory, ItemFactory * itemFactory);

	bool ConstructCharacter(
		CoreCharacter ** coreCharacterOut,
		CharacterClassName characterClass,
		Pathfinder * pathfinder,
		vector<ItemName> * itemSet,
		vector<Actor*>* teamActors,
		vector<Actor*>* opponentActors,
		vector<Actor*>* neutralActors,
		TeamName team,
		string * uniqueName,
		vector<AbilityName> * customAbilities);

	bool ConstructCharacterAbilities(
		vector<Ability*> * abilities,
		CharacterClassName name,
		vector<AbilityName> * customAbilityList,
		Actor * actor,
		vector<Actor*>* teamActors,
		vector<Actor*>* opponentActors,
		vector<Actor*>* neutralActors);

};

#endif