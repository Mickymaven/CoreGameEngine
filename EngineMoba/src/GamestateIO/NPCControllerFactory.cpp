#include "NPCControllerFactory.h"

NPCControllerFactory::NPCControllerFactory()
{
}

NPCControllerFactory::~NPCControllerFactory()
{
}

bool NPCControllerFactory::Init(CharacterFactory * characterFactory)
{
	m_characterFactory = characterFactory;
	return true;
}

bool NPCControllerFactory::ConstructNPC(
	NPCController ** npcOut,
	LMVector3 * position,
	int id,
	Pathfinder * pathfinder,
	vector<Actor*>* teamActors,
	vector<Actor*>* opponentActors,
	vector<Actor*>* neutralActors,
	CharacterClassName characterClass,
	vector<ItemName> * itemSet,
	bool targetable,
	TeamName team,
	string * uniqueName,
	vector<AbilityName> * customAbilities)
{
	Actor * actor;
	m_NPC = NULL;

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
		m_NPC = new NPCController(m_constructedCharacter);
		actor = m_NPC->GetCharacter()->GetActor();
	}
	else return false;

	*npcOut = m_NPC;

	return true;
}
