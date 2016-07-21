#include "CharacterFactory.h"

CharacterFactory::CharacterFactory()
{
}

CharacterFactory::~CharacterFactory()
{
}

bool CharacterFactory::Init(ActorFactory * actorFactory, AbilityFactory * abilityFactory, ItemFactory * itemFactory)
{
	m_actorFactory = actorFactory;
	m_abilityFactory = abilityFactory;
	m_itemFactory = itemFactory;

	return true;
}

bool CharacterFactory::ConstructCharacter(
	Character ** characterOut,
	int characterClass,//CharacterClassName
	Pathfinder * pathfinder,
	vector<int> * itemSet,//ItemName
	vector<Actor*>* teamActors,
	vector<Actor*>* opponentActors,
	vector<Actor*>* neutralActors,
	TeamName team,
	string * uniqueName,
	vector<int> * customAbilities) //AbilityName
{
	ActorStats * actorStats = nullptr;
	Actor * actor = nullptr;
	
	if (! m_actorFactory->ConstructActor(&actor, characterClass, uniqueName, team)) return false;

	m_character = new Character(actor, pathfinder);

	CharacterItems(m_character, 10, itemSet);

	ConstructCharacterAbilities(
		m_character->GetAbilities(),
		characterClass,
		customAbilities,
		actor,
		teamActors,
		opponentActors,
		neutralActors
	);



	*characterOut = m_character;

	return true;
}

//Todo this whole function is Core game style of ability set up
//we can maintain the CharacterFactory Init (called from derived version) and used as is
//Then the included call to ConstructCharacterAbilities would be implmented in derived class with the below behavior

bool CharacterFactory::ConstructCharacterAbilities(
	vector<Ability*> * abilities,
	int name, //CharacterClassName 
	vector<int> * customAbilityList,//AbilityName
	Actor * actor,
	vector<Actor*>* opponents,
	vector<Actor*>* playerTeam,
	vector<Actor*>* npctargets )
{
	//breaks current code, abilities will need to be valid because core ui expects 8? elements in vec
	//todo we should handle empty abilities in all core games?
	return false;
}

bool CharacterFactory::CharacterItems(
	Character * character,
	int invSize,
	vector<int> * itemSet)//ItemName
{
	vector<Item*> * inventory = character->GetInventory();

	inventory->resize(10);

	for (unsigned int index = 0; index < 10 - itemSet->size(); index++)
	{
		inventory->at(index) = nullptr;
	}

	for (unsigned int i = 0; i < itemSet->size(); i++)
	{
		inventory->at(i) = m_itemFactory->GetItem(nullptr, (ItemName)itemSet->at(i));
	}

	return true;
}
