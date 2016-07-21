#include "CoreCharacterFactory.h"

CoreCharacterFactory::CoreCharacterFactory()
{
}

CoreCharacterFactory::~CoreCharacterFactory()
{
}

bool CoreCharacterFactory::Init(CoreActorFactory * coreActorFactory, AbilityFactory * abilityFactory, ItemFactory * itemFactory)
{
	m_coreActorFactory = coreActorFactory;

	return CharacterFactory::Init(coreActorFactory, abilityFactory, itemFactory);
}

bool CoreCharacterFactory::ConstructCharacter(
	CoreCharacter ** coreCharacterOut,
	CharacterClassName characterClass,
	Pathfinder * pathfinder,
	vector<ItemName> * itemSet,
	vector<Actor*>* teamActors,
	vector<Actor*>* opponentActors,
	vector<Actor*>* neutralActors,
	TeamName team,
	string * uniqueName,
	vector<AbilityName> * customAbilities )
{
	//duplicate implementation order similar to CharacterFactory::ConstructCharacter(..)

	Actor * actor = nullptr;

	if (!m_coreActorFactory->ConstructCoreActor(&actor, characterClass, uniqueName, team)) return false;

	m_coreCharacter = new CoreCharacter(actor, pathfinder, teamActors, opponentActors, neutralActors);

	CharacterItems(m_coreCharacter, 10, (vector<int> *)itemSet);

	ConstructCharacterAbilities(//todo nullptr can mean skip abilities for now
		m_coreCharacter->GetAbilities(),
		characterClass,
		customAbilities,
		actor,
		teamActors,
		opponentActors,
		neutralActors
	);

	actor->SetUniqueName(*uniqueName);

	*coreCharacterOut = m_coreCharacter;

	return true;
}

bool CoreCharacterFactory::ConstructCharacterAbilities(
	vector<Ability*> * abilities,
	CharacterClassName name,
	vector<AbilityName> * customAbilityList,
	Actor * actor,
	vector<Actor*>* teamActors,
	vector<Actor*>* opponentActors,
	vector<Actor*>* neutralActors )
{
	Ability * ability = nullptr;

	m_coreCharacter->GetAbilities()->resize(9);

	for (unsigned int i = abilitySlot1; i <= abilitySlot4; i++)
	{
		if (!m_abilityFactory->ConstructAbility(
			&ability,//ability out pointer
			m_characterData.m_defaultAbilities.at(name).at(i - 1),//Ability name (enum)
			actor,
			teamActors,
			opponentActors,
			neutralActors
		)) return false;

		else m_coreCharacter->AddAbility(ability, (AbilitySlotType)i);//i was an (AbilitySlotType)
	}

	for (unsigned int j = abilitySlot5; j <= abilitySlot6; j++)
	{
		if (!m_abilityFactory->ConstructAbility(
			&ability,//ability out pointer
			customAbilityList->at(j - 5),//Ability name (enum)
			actor,
			teamActors,
			opponentActors,
			neutralActors
		)) return false;

		else m_coreCharacter->AddAbility(ability, (AbilitySlotType)j);// j was an (AbilitySlotType)
	}

	return true;
}
