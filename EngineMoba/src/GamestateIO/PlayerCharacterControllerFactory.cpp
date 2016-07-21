#include "PlayerCharacterControllerFactory.h"

PlayerCharacterControllerFactory::PlayerCharacterControllerFactory()
{
}

PlayerCharacterControllerFactory::~PlayerCharacterControllerFactory()
{
}

bool PlayerCharacterControllerFactory::Init(CharacterFactory * characterFactory)
{
	m_characterFactory = characterFactory;
	return true;
}

bool PlayerCharacterControllerFactory::ConstructPlayerCharacter(
	unsigned long * playerID,
	PlayerCharacterController ** playerCharacterControllerOut,
	CharacterClassName characterClass,
	Pathfinder * pathfinder,
	vector<ItemName> * itemSet,
	vector<Actor*>* teamActors,
	vector<Actor*>* opponentActors,
	vector<Actor*>* neutralActors,
	TeamName team,
	string * uniqueName,
	vector<AbilityName> * customAbilities)
{	
	ActorStats * actorStats = NULL;
	
	if (m_characterFactory->ConstructCharacter(
		&m_constructedCharacter,
		characterClass,
		pathfinder,
		(vector<int> *) itemSet,
		teamActors,
		opponentActors,
		neutralActors,
		team,
		uniqueName,
		(vector<int> *) customAbilities))
	{
		m_playerCharacter = new PlayerCharacterController(m_constructedCharacter);

		*playerCharacterControllerOut = m_playerCharacter;
		return true;
	}
	
	return false;
}
