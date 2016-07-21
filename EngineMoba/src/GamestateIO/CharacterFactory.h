#if !defined(CHARACTERFACTORY_H)
#define CHARACTERFACTORY_H

#include "../Actors/Character.h"

#include "GameObjectFactory.h"
#include "ActorFactory.h"
#include "AbilityFactory.h"
#include "ItemFactory.h"



#include "../../../CoreGame/src/Gameplay/Characters/CharacterData.h"// (forward dependency) move once derived see below note

class CharacterFactory
{
protected:
	Character * m_character;
	ActorFactory * m_actorFactory;
	AbilityFactory * m_abilityFactory;
	ItemFactory * m_itemFactory;


	CharacterData m_characterData; //todo derive and init in derived, initted here through parameter from DerivedTypeCharacterFactor::Init(p)

public:
	CharacterFactory();
	~CharacterFactory();

	bool Init(ActorFactory * actorFactory, AbilityFactory * abilityFactory, ItemFactory * itemFactory);

	bool ConstructCharacter(
		Character ** characterOut,
		int characterClass,//CharacterClassName
		Pathfinder * pathfinder,
		vector<int> * itemSet,//ItemName
		vector<Actor*>* teamActors,
		vector<Actor*>* opponentActors,
		vector<Actor*>* neutralActors,
		TeamName team,
		string * uniqueName,
		vector<int> * customAbilities ); //AbilityName

	bool ConstructCharacterAbilities(
		vector<Ability*> * abilities,
		int name, //CharacterClassName 
		vector<int> * customAbilityList,//AbilityName
		Actor * actor,
		vector<Actor*>* opponents,
		vector<Actor*>* playerTeam,
		vector<Actor*>* npctargets );

	bool CharacterFactory::CharacterItems(
		Character * character,
		int invSize,
		vector<int> * itemSet);

};

#endif