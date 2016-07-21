#include "CorePlayerCharacterControllerFactory.h"

CorePlayerCharacterControllerFactory::CorePlayerCharacterControllerFactory()
{
}

CorePlayerCharacterControllerFactory::~CorePlayerCharacterControllerFactory()
{
}

bool CorePlayerCharacterControllerFactory::Init(CoreCharacterFactory * coreCharacterFactory)
{
	m_coreCharacterFactory = coreCharacterFactory;

	return true;
}

bool CorePlayerCharacterControllerFactory::ConstructPlayerCharacterController(

	unsigned long * playerID,
	CorePlayerCharacterController ** playerCharacterControllerOut,
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
	ActorStats * actorStats = NULL;

	if (m_coreCharacterFactory->ConstructCharacter(
		&m_coreCharacter,
		characterClass,
		pathfinder,
		itemSet,
		teamActors,
		opponentActors,
		neutralActors,
		team,
		uniqueName,
		customAbilities))
	{
		m_corePlayerCharacterController = new CorePlayerCharacterController(m_coreCharacter);

		*playerCharacterControllerOut = m_corePlayerCharacterController;
		return true;
	}

	return false;
}
